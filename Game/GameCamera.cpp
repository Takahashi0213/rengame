#include "stdafx.h"
#include "GameCamera.h"

GameCamera* GameCamera::m_instance = nullptr;

GameCamera::GameCamera()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//遠平面を設定する
	g_camera3D.SetFar(30000.0f);
	//画角を変更
	g_camera3D.SetViewAngle(CMath::DegToRad(60.0f));
	//取得タイム
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
	m_game = Game::GetInstance();

	//注視点を動かす
	CVector3 P_Position = m_player->Getm_Position();

	m_cameraTarget.x = P_Position.x;
	m_cameraTarget.y = P_Position.y + 100.0f;	//プレイヤーのちょっと上にする
	m_cameraTarget.z = P_Position.z;

	//視点をカメラに伝える
	m_cameraPos.x = P_Position.x + m_cameraHosei.x;
	m_cameraPos.y = P_Position.y + m_cameraHosei.y;
	m_cameraPos.z = P_Position.z + m_cameraHosei.z;

}


GameCamera::~GameCamera()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void GameCamera::Update() {

	SceneManager::GameMode NowGameMode = SceneManager::GetInstance()->GetGameMode();		//現在のゲームモードを呼び出す

	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == false) {	//イベント中はどれも実行しない

		if (NowGameMode == SceneManager::ActionMode || NowGameMode == SceneManager::CreateMode) {
			//共通のカメラ処理
			CommonMove();
		}

		if (NowGameMode == SceneManager::ActionMode) {
			ActionMode();
		}
		else if (NowGameMode == SceneManager::CreateMode) {
			CreateMode();
		}

	}

	//注視点をカメラに伝える
	g_camera3D.SetTarget(m_cameraTarget);
	g_camera3D.SetPosition(m_cameraPos);

	g_camera3D.Update();
}

void GameCamera::Render() {

}

void GameCamera::ActionMode() {

	CVector3 P_Position = m_player->Getm_Position();
	CQuaternion P_qRot = m_player->Getm_Rotation();
	CVector3 vBase = { 0.0f,0.0f,1.0f };
	CVector3 Camera_Position = g_camera3D.GetTarget();

	if (m_camera_BoxToPlayer_MoveFlag == true) {

		Camera_Position.y -= 100.0f;
		CVector3 Move = (P_Position - Camera_Position) / CameraMoveHosei;
		P_Position = Camera_Position + Move;
	}

	//注視点を動かす
	m_cameraTarget.x = P_Position.x;
	m_cameraTarget.y = P_Position.y + 100.0f;	//プレイヤーのちょっと上にする
	m_cameraTarget.z = P_Position.z;

	//視点をカメラに伝える
	m_cameraPos.x = P_Position.x + m_cameraHosei.x;
	m_cameraPos.y = P_Position.y + m_cameraHosei.y;
	m_cameraPos.z = P_Position.z + m_cameraHosei.z;

	/*
	P_qRot.Multiply(vBase);
	//プレイヤーの真後ろについていくよ
	CVector3 vpos = vBase * -300.0f;
	m_cameraPos = vpos + m_cameraTarget;
	m_cameraPos.y = m_cameraPos.y + 200.0f;
	*/

}

void GameCamera::CreateMode() {

	//注視点を動かす
	CVector3 P_Position = m_player->Getm_Position();
	if (m_gamebox != nullptr) {
		CVector3 Box_Position = m_gamebox->GetPosition();
		CVector3 Camera_Position = g_camera3D.GetTarget();
		CVector3 Move = (Box_Position - Camera_Position) / CameraMoveHosei;
		P_Position = Camera_Position + Move;

		m_cameraTarget.x = P_Position.x;
		m_cameraTarget.y = P_Position.y;	//プレイヤーのちょっと上にする
		m_cameraTarget.z = P_Position.z;
	}

	//視点をカメラに伝える
	m_cameraPos.x = P_Position.x + m_cameraHosei.x;
	m_cameraPos.y = P_Position.y + m_cameraHosei.y;
	m_cameraPos.z = P_Position.z + m_cameraHosei.z;

}

void GameCamera::CommonMove() {

	//回転

	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Right_Key);
	if (key == MouseSupporter::Now_Pushing) {
		//カメラ操作
		CVector2 move_c = MouseSupporter::GetInstance()->GetBeforeMouse(1);
		CVector3 move_cc = CVector3().Zero();
		move_cc.x = move_c.x;
		move_cc.y = move_c.y;
		move_cc.y *= -1.0f;
		move_cc.Normalize();

		CVector3 toCameraPosOld = m_cameraHosei;
		float x = move_cc.x;
		float y = move_cc.y;
		x *= 3.0f;
		y *= 3.0f;
		//Y軸周りの回転
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3().AxisY(), 3.0f * x);
		qRot.Multiply(m_cameraHosei);
		//X軸周りの回転。
		CVector3 axisX;
		axisX.Cross(CVector3().AxisY(), m_cameraHosei);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 3.0f * y);
		qRot.Multiply(m_cameraHosei);

		//カメラの回転の上限をチェックする。
		CVector3 toPosDir = m_cameraHosei;
		toPosDir.Normalize();
		if (toPosDir.y < 0.1f) {
			//カメラが上向きすぎ。
			m_cameraHosei = toCameraPosOld;
		}
		else if (toPosDir.y > 0.98f) {
			//カメラが下向きすぎ。
			m_cameraHosei = toCameraPosOld;
		}

	}

	//拡大

	int now_delta = MouseSupporter::GetInstance()->GetWheelMove();
	float Angle = g_camera3D.GetViewAngle();

	if (now_delta > 0) {
		Angle -= 0.1f;
		if (Angle < 0.5f) {
			Angle = 0.5f;
		}
	}
	else if (now_delta < 0) {
		Angle += 0.1f;
		if (Angle > 1.7f) {
			Angle = 1.7f;
		}
	}
	g_camera3D.SetViewAngle(Angle);

}