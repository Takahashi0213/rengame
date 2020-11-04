#pragma once
#include "system/CGameObjectManager.h"

//IGameObjectを継承しているので開始時にNewGOしてください。

/// <summary>
/// 実行するとカメラを楽に動かせる。
/// ・シングルトン
/// </summary>
class CameraSupporter : public IGameObject
{
	static CameraSupporter* m_instance;
public:
	CameraSupporter();
	~CameraSupporter();
	void Update()override;
	void Render()override;

	//カメラ操作関数
	void CameraMove(const CVector3& move, const float& moveTime, const float& moveDelay);
	void CameraMove_Rot(const float& move, const float& moveTime, const float& moveDelay);
	void CameraMove_Bure(const CVector2& bure, const float& speed, const float& moveTime, const float& moveDelay);
	void CameraMove_Zoom(const float& angle, const float& moveTime, const float& moveDelay, const bool& boundFlag = false);
	void CameraTargetMove(const CVector3& move, const float& moveTime, const float& moveDelay, const bool& posMoveFlag = false);

	/// <summary>
	/// カメラバックアップ
	/// CameraBackupで現在のカメラ座標、注視点、画角を保存
	/// CameraBackup_Restoreで最後に保存した上記の情報を復元する
	/// CameraBackup_RestoreSetは移動せず一瞬でセットする
	/// 
	/// イベントでカメラを動かした後サクッと元の状態に戻したい時などに
	/// moveTimeを設定するとスムーズに動く
	/// 
	/// </summary>
	void CameraBackup() {
		m_cameraPosBackup = g_camera3D.GetPosition();
		m_cameraTargetBackup = g_camera3D.GetTarget();
		//m_cameraViewAngleBackup = g_camera3D.GetViewAngle();
	}
	void CameraBackup_Restore(const float& moveTime = 1) {
		CameraMove(m_cameraPosBackup - g_camera3D.GetPosition(), moveTime, 0);
		CameraTargetMove(m_cameraTargetBackup - g_camera3D.GetTarget(), moveTime, 0);
		//CameraMove_Zoom(m_cameraViewAngleBackup, moveTime, 0);
	}
	void CameraBackup_RestoreSet() {
		g_camera3D.SetPosition(m_cameraPosBackup);
		g_camera3D.SetTarget(m_cameraTargetBackup);
	}

	/// <summary>
	/// カメラのブレを停止
	/// </summary>
	void CameraBure_Stop() {
		m_cameraMoveFlag_Bure = false;
		g_camera3D.SetPosition(m_cameraDefPos_Bure);
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static CameraSupporter* CameraSupporter::GetInstance() {
		return m_instance;
	}

private:
	void CameraSupporter::CameraMoveUpdate();
	void CameraSupporter::CameraMoveUpdate_Rot();
	void CameraSupporter::CameraMoveUpdate_Bure();
	void CameraSupporter::CameraMoveUpdate_Zoom();
	void CameraSupporter::CameraTargetMoveUpdate();

	//メンバ変数 普通に移動
	bool m_cameraMoveFlag = false;					//カメラは移動中？
	CVector3 m_cameraMoveSpeed = CVector3().Zero(); //カメラの移動速度
	float m_cameraMoveTime = 0.0f;					//カメラの移動時間
	float m_cameraMoveDelay = 0.0f;					//カメラの移動ウェイト
	float m_cameraMoveTimer = 0.0f;					//カメラの移動タイマー
	//メンバ変数 視点を中心に回る
	bool m_cameraMoveFlag_Rot = false;				//カメラは回転移動中？
	float m_cameraMoveSpeed_Rot = 0.0f;				//カメラの回転移動速度
	float m_cameraMoveTime_Rot = 0.0f;				//カメラの回転移動時間
	float m_cameraMoveDelay_Rot = 0.0f;				//カメラの回転移動ウェイト
	float m_cameraMoveTimer_Rot = 0.0f;				//カメラの回転移動タイマー
	CVector3 m_targetToPos = CVector3().Zero();		//ベクトル保存用
	//メンバ変数 カメラブレ
	bool m_cameraMoveFlag_Bure = false;				//カメラブレ中？
	CVector2 m_cameraBure = CVector2().Zero();		//ブレる最大値
	float m_cameraMoveSpeed_Bure = 0.0f;			//カメラのブレ速度
	float m_cameraMoveTime_Bure = 0.0f;				//カメラのブレる時間
	float m_cameraMoveDelay_Bure = 0.0f;			//カメラのブレるウェイト
	float m_cameraMoveTimer_Bure = 0.0f;			//カメラブレタイマー
	CVector3 m_cameraDefPos_Bure = CVector3().Zero(); //カメラの初期位置保存
	//メンバ変数 ズームイン・アウト
	bool m_cameraMoveFlag_Zoom = false;				//ズーム中？
	float m_cameraAngle_Zoom = 0.0f;				//カメラの目標画角
	float m_cameraMoveSpeed_Zoom = 0.0f;			//1フレームの移動距離
	float m_cameraMoveTime_Zoom = 0.0f;				//カメラのズーム時間
	float m_cameraMoveDelay_Zoom = 0.0f;			//カメラのズームウェイト
	float m_cameraMoveTimer_Zoom = 0.0f;			//カメラズームタイマー
	bool m_cameraZoomBound = false;					//カメラズーム時のバウンドフラグ
	float m_cameraMoveSpeed_ZoomBound = 0.0f;		//バウンド時の1フレームの移動距離
	const float m_cameraZoomOverLimit = 2.0f;		//カメラをバウンドさせて戻るまでの時間
	const float m_zoomHosei = 1.1f;					//ズームバウンド時の補正
	//メンバ変数 注視点移動
	bool m_cameraTargetMoveFlag = false;			//注視点は移動中？
	CVector3 m_cameraTargetMoveSpeed = CVector3().Zero(); //注視点の移動速度
	float m_cameraTargetMoveTime = 0.0f;			//注視点の移動時間
	float m_cameraTargetMoveDelay = 0.0f;			//注視点の移動ウェイト
	float m_cameraTargetMoveTimer = 0.0f;			//注視点の移動タイマー
	bool m_cameraTargetMove_PosMove = false;		//ターゲットが移動した時、カメラの座標も同じだけ移動させる？
	//メンバ変数 カメラバックアップ
	CVector3 m_cameraPosBackup = CVector3::Zero();	//バックアップ用 カメラ位置
	CVector3 m_cameraTargetBackup = CVector3::Zero();	//バックアップ用 カメラ注視点
	float m_cameraViewAngleBackup = 0.0f;			//バックアップ用 カメラ画角

};

