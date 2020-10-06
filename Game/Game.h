#pragma once
#include "SystemData.h"
#include "GameGraphic.h"
#include "GameUI.h"
#include "PhysicsGhostObject.h"
#include "system/CGameObjectManager.h"

/// <summary>
/// ゲーム！
/// ・シングルトン
/// </summary>
class Game : public IGameObject
{
	static Game* m_instance;
public:
	enum GameMode {
		Title,
		ActionMode,
		CreateMode,
		MenuMode,
	};

	Game();
	~Game();
	void Update()override;
	void Render()override;

	void GameUpdate();

	/// <summary>
	/// ゲームモードをセット
	/// </summary>
	/// <param name="mode">モード</param>
	void SetGameMode(GameMode mode) {
		m_gameMode = mode;
	}
	/// <summary>
	/// ゲームモードを取得
	/// </summary>
	/// <returns>モード</returns>
	GameMode GetGameMode() {
		return m_gameMode;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static Game* Game::GetInstance() {
		return m_instance;
	}
	SystemData* Game::GetSystemInstance() {
		return &m_systemData;
	}
	GameGraphic* Game::GetGameGraphicInstance() {
		return &m_gameGraphic;
	}
	GameUI* Game::GetUI() {
		return m_ui;
	}

private:

	//ここからゲーム用

	GameMode m_gameMode = ActionMode;
	GameData m_gameData;
	GameEffect m_gameEffect;

	SystemData m_systemData;
	GameGraphic m_gameGraphic;

	GameUI* m_ui = nullptr;

	CSoundEngine m_soundEngine;				//サウンドエンジン。

	CharacterController* m_charaCon;
	PhysicsGhostObject m_ghostObject;						//ゴーストオブジェクトとを４つ。
};

