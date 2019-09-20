#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
	//遠平面を設定する
	g_camera3D.SetFar(30000.0f);
	//画角を変更
	g_camera3D.SetViewAngle(CMath::DegToRad(60.0f));

	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}


GameCamera::~GameCamera()
{
}

void GameCamera::Update() {

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
			x *= 2.0f;
			y *= 2.0f;
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

	CVector3 P_Position = m_player->Getm_Position();
	CQuaternion P_qRot = m_player->Getm_Rotation();
	CVector3 vBase = { 0.0f,0.0f,1.0f };
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

	//注視点をカメラに伝える
	g_camera3D.SetTarget(m_cameraTarget);
	g_camera3D.SetPosition(m_cameraPos);

	g_camera3D.Update();
}

void GameCamera::Render() {

}