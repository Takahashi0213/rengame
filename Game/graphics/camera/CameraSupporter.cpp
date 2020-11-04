#include "stdafx.h"
#include "CameraSupporter.h"

CameraSupporter* CameraSupporter::m_instance = nullptr;

CameraSupporter::CameraSupporter()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

CameraSupporter::~CameraSupporter()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void CameraSupporter::Update() {
	
	//カメラ移動フラグを確認
	if (m_cameraMoveFlag == true) {
		CameraMoveUpdate();
	}
	//カメラ回転移動フラグを確認
	if (m_cameraMoveFlag_Rot == true) {
		CameraMoveUpdate_Rot();
	}
	//カメラシェイクフラグを確認
	if (m_cameraMoveFlag_Bure == true) {
		CameraMoveUpdate_Bure();
	}
	//カメラズームフラグを確認
	if (m_cameraMoveFlag_Zoom == true) {
		CameraMoveUpdate_Zoom();
	}
	//注視点移動フラグを確認
	if (m_cameraTargetMoveFlag == true) {
		CameraTargetMoveUpdate();
	}
}

void CameraSupporter::Render() {
	//描画はしない
}

/// <summary>
/// カメラの場所を移動する準備
/// </summary>
/// <param name="move">移動する分のベクトル</param>
/// <param name="moveTime">移動時間</param>
/// <param name="moveDelay">移動ディレイ</param>
void CameraSupporter::CameraMove(const CVector3& move, const float& moveTime, const float& moveDelay) {

	//メンバ変数リセット
	m_cameraMoveFlag = true;
	m_cameraMoveTimer = 0.0f;

	//色々セット
	m_cameraMoveSpeed = move;
	m_cameraMoveTime = moveTime;
	m_cameraMoveDelay = moveDelay;

}

/// <summary>
/// 視点を中心にカメラを回転させる準備
/// </summary>
/// <param name="moveTime">移動時間</param>
/// <param name="moveDelay">移動ディレイ</param>
void CameraSupporter::CameraMove_Rot(const float& move, const float& moveTime, const float& moveDelay) {

	//メンバ変数リセット
	m_cameraMoveFlag_Rot = true;
	m_cameraMoveTimer_Rot = 0.0f;

	//色々セット
	m_cameraMoveSpeed_Rot = move;
	m_cameraMoveTime_Rot = moveTime;
	m_cameraMoveDelay_Rot = moveDelay;

}

/// <summary>
/// カメラをシェイクさせる準備
/// </summary>
/// <param name="bure">ブレる大きさ（最大値）</param>
/// <param name="speed">ブレる速さ</param>
/// <param name="moveTime">動作時間 ※-1.0fを設定すると停止するまで続けます</param>
/// <param name="moveDelay">動作ディレイ</param>
void CameraSupporter::CameraMove_Bure(const CVector2& bure, const float& speed, const float& moveTime, const float& moveDelay) {

	//メンバ変数リセット
	m_cameraMoveFlag_Bure = true;
	m_cameraMoveTimer_Bure = 0.0f;

	//色々セット
	m_cameraBure.x = bure.x;
	m_cameraBure.y = bure.y;
	m_cameraMoveSpeed_Bure = speed;
	m_cameraMoveTime_Bure = moveTime;
	m_cameraMoveDelay_Bure = moveDelay;

	m_cameraDefPos_Bure = g_camera3D.GetPosition();

}

/// <summary>
/// カメラをズームさせる準備
/// </summary>
/// <param name="angle">目標画角</param>
/// <param name="moveTime">ズーム時間</param>
/// <param name="moveDelay">ズームウェイト</param>
/// <param name="boundFlag">trueにすると目標を少し通り過ぎてバウンドします</param>
void CameraSupporter::CameraMove_Zoom(const float& angle, const float& moveTime, const float& moveDelay, const bool& boundFlag) {

	//メンバ変数リセット
	m_cameraMoveFlag_Zoom = true;
	m_cameraMoveTimer_Zoom = 0.0f;
	m_cameraMoveSpeed_ZoomBound = 0.0f;

	//色々セット
	m_cameraAngle_Zoom = CMath::DegToRad(angle);
	m_cameraMoveTime_Zoom = moveTime;
	m_cameraMoveDelay_Zoom = moveDelay;
	m_cameraZoomBound = boundFlag;

}

/// <summary>
/// カメラの注視点を移動する準備
/// </summary>
/// <param name="move">移動する分のベクトル</param>
/// <param name="moveTime">移動時間</param>
/// <param name="moveDelay">移動ディレイ</param>
/// <param name="posMoveFlag">trueなら同時にカメラの座標も移動する</param>
void CameraSupporter::CameraTargetMove(const CVector3& move, const float& moveTime, const float& moveDelay, const bool& posMoveFlag) {

	//メンバ変数リセット
	m_cameraTargetMoveFlag = true;
	m_cameraTargetMoveTimer = 0.0f;

	//色々セット
	m_cameraTargetMoveSpeed = move;
	m_cameraTargetMoveTime = moveTime;
	m_cameraTargetMoveDelay = moveDelay;
	m_cameraTargetMove_PosMove = posMoveFlag;

}

/// <summary>
/// カメラ移動を実行
/// </summary>
void CameraSupporter::CameraMoveUpdate() {

	if (m_cameraMoveTimer >= m_cameraMoveDelay) {

		//1フレームの移動距離を計算
		CVector3 move = m_cameraMoveSpeed / m_cameraMoveTime;
		CVector3 cameraPos = g_camera3D.GetPosition();
		cameraPos += move;
		g_camera3D.SetPosition(cameraPos);

		if (m_cameraMoveTimer >= m_cameraMoveTime + m_cameraMoveDelay) {
			//処理終了
			m_cameraMoveFlag = false;
		}
	}

	m_cameraMoveTimer += 1.0f;

}

/// <summary>
/// カメラ回転を実行
/// </summary>
void CameraSupporter::CameraMoveUpdate_Rot() {

	if (m_cameraMoveTimer_Rot == 0.0f) {
		m_targetToPos = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	}

	if (m_cameraMoveTimer_Rot >= m_cameraMoveDelay_Rot) {

		//注視点から視点に向かうベクトルを回す

		//Y軸周りの回転
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3().AxisY(), m_cameraMoveSpeed_Rot);
		qRot.Multiply(m_targetToPos);
		// X軸周りの回転
		CVector3 axisX;
		//外積を使って回転軸を求める。
		axisX.Cross(CVector3().AxisY(), m_targetToPos);
		//外積の結果は大きさ１ではないので、正規化する。　
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 0.0f);
		//注視点から視点に伸びるベクトルを回す。
		qRot.Multiply(m_targetToPos);

		//視点を動かす
		CVector3 cameraPos = g_camera3D.GetTarget() + m_targetToPos;
		g_camera3D.SetPosition(cameraPos);

		if (m_cameraMoveTimer_Rot >= m_cameraMoveTime_Rot + m_cameraMoveDelay_Rot) {
			//処理終了
			m_cameraMoveFlag_Rot = false;
		}
	}

	m_cameraMoveTimer_Rot += 1.0f;


}

/// <summary>
/// カメラブレを実行
/// </summary>
void CameraSupporter::CameraMoveUpdate_Bure() {

	if (m_cameraMoveTimer_Bure >= m_cameraMoveDelay_Bure) {

		//ブレるタイミングで実行
		int bure = (int)m_cameraMoveTimer_Bure % (int)m_cameraMoveSpeed_Bure;
		if (bure == 0) {

			g_camera3D.SetPosition(m_cameraDefPos_Bure);
			CVector3 cameraPos = g_camera3D.GetPosition();

			//大きさを設定
			float bure_x = 0.0f;
			float bure_y = 0.0f;
			if (m_cameraBure.x > 0.0f) {
				bure_x = (float)(rand() % (int)m_cameraBure.x);
			}
			else {
				bure_x = 0.0f;
			}
			if (m_cameraBure.y > 0.0f) {
				bure_y = (float)(rand() % (int)m_cameraBure.y);
			}
			else {
				bure_y = 0.0f;
			}

			//2分の1で反転
			if (rand() % 2 == 0) {
				bure_x *= -1.0f;
			}
			if (rand() % 2 == 0) {
				bure_y *= -1.0f;
			}

			cameraPos.x += bure_x;
			cameraPos.y += bure_y;

			g_camera3D.SetPosition(cameraPos);

		}

		if (m_cameraMoveTime_Bure != -1.0f) {
			if (m_cameraMoveTimer_Bure >= m_cameraMoveTime_Bure + m_cameraMoveDelay_Bure) {
				//処理終了
				CameraBure_Stop();
			}
		}
	}

	m_cameraMoveTimer_Bure += 1.0f;

}

/// <summary>
/// ズームを実行
/// </summary>
void CameraSupporter::CameraMoveUpdate_Zoom() {

	//初回準備
	if (m_cameraMoveTimer_Zoom == 0.0f) {
		//1フレームの移動距離を計算
		m_cameraMoveSpeed_Zoom = ( m_cameraAngle_Zoom - g_camera3D.GetViewAngle()) / m_cameraMoveTime_Zoom;
		if (m_cameraZoomBound == true) { //バウンドする場合余分にする
			m_cameraMoveSpeed_Zoom *= m_zoomHosei;
		}

	}

	if (m_cameraMoveTimer_Zoom >= m_cameraMoveDelay_Zoom) {

		//ズームインアウトしますわよ
		float angle = g_camera3D.GetViewAngle();

		if (m_cameraZoomBound == true && m_cameraMoveTimer_Zoom >= m_cameraMoveTime_Zoom + m_cameraMoveDelay_Zoom) {
			//バウンドアリでバウンド時間中なら実行
			if (m_cameraMoveSpeed_ZoomBound == 0.0f) {
				//移動距離計算
				m_cameraMoveSpeed_ZoomBound = (m_cameraAngle_Zoom - g_camera3D.GetViewAngle()) / m_cameraZoomOverLimit;
				//m_cameraMoveSpeed_ZoomBound = CMath::DegToRad(m_cameraMoveSpeed_ZoomBound);
			}
			angle += m_cameraMoveSpeed_ZoomBound;
		}
		else {
			angle += m_cameraMoveSpeed_Zoom;
		}

		g_camera3D.SetViewAngle(angle);

		if (m_cameraZoomBound == false) {
			if (m_cameraMoveTimer_Zoom >= m_cameraMoveTime_Zoom + m_cameraMoveDelay_Zoom) {
				//処理終了
				m_cameraMoveFlag_Zoom = false;
				g_camera3D.SetViewAngle(m_cameraAngle_Zoom);
			}
		}
		else {
			if (m_cameraMoveTimer_Zoom >= m_cameraMoveTime_Zoom + m_cameraMoveDelay_Zoom + m_cameraZoomOverLimit) {
				//処理終了
				m_cameraMoveFlag_Zoom = false;
				g_camera3D.SetViewAngle(m_cameraAngle_Zoom);
			}
		}
	}

	m_cameraMoveTimer_Zoom += 1.0f;

}

/// <summary>
/// 注視点移動を実行
/// </summary>
void CameraSupporter::CameraTargetMoveUpdate() {

	if (m_cameraTargetMoveTimer >= m_cameraTargetMoveDelay) {

		//1フレームの移動距離を計算
		CVector3 move = m_cameraTargetMoveSpeed / m_cameraTargetMoveTime;
		CVector3 cameraPos = g_camera3D.GetTarget();
		cameraPos += move;
		g_camera3D.SetTarget(cameraPos);
		//フラグがtrueならカメラの座標も移動させる
		if (m_cameraTargetMove_PosMove == true) {
			cameraPos = g_camera3D.GetPosition();
			cameraPos += move;
			g_camera3D.SetPosition(cameraPos);
		}

		if (m_cameraTargetMoveTimer >= m_cameraTargetMoveTime + m_cameraTargetMoveDelay) {
			//処理終了
			m_cameraTargetMoveFlag = false;
		}
	}

	m_cameraTargetMoveTimer += 1.0f;

}