#pragma once
#include "system/CGameObjectManager.h"
#include "GameObject/Player.h"
#include "GameSystem/Box/GameBox.h"

/// <summary>
/// ゲームカメラと操作色々
/// ・シングルトン
/// </summary>
class GameCamera final : public IGameObject
{
	static GameCamera* m_instance;
public:
	GameCamera();
	~GameCamera();
	void Update()override;
	void Render()override;

	/// <summary>
	/// 今見ている箱のアドレスです
	/// </summary>
	void SetGameBox(GameBox* gamebox) {
		m_gamebox = gamebox;
	}

	/// <summary>
	/// クリエイトモードからアクションモードに切り替わった時、カメラの移動を制御するフラグをtrueにしましょ
	/// </summary>
	void PlayerCameraMove() {
		m_camera_BoxToPlayer_MoveFlag = true;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static GameCamera* GameCamera::GetInstance() {
		return m_instance;
	}

	/// <summary>
	/// 外部からの強制カメラ実行
	/// </summary>
	/// <remarks>
	/// 例えば…
	///		カメラは停止しているけど更新だけ無理矢理させたい時に！
	/// </remarks>
	void ActionModeCameraMove() {
		ActionMode();
	}

private:
	void ActionMode();
	void CreateMode();
	void CommonMove();

	CVector3 m_cameraTarget;
	CVector3 m_cameraPos;

	Player* m_player;
	Game* m_game;
	GameBox* m_gamebox = nullptr;

	CVector3 m_cameraHosei = { 0.0f,300.0f,-300.0f };

	//プレイヤーに戻るカメラの処理
	bool m_camera_BoxToPlayer_MoveFlag = false;

	//定数
	const float CameraMoveHosei = 10.0f;		//モードチェンジ時、カメラの移動速度補正

};

