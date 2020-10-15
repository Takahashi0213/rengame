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

	Game();
	~Game();
	void Update()override;
	void Render()override;

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static Game* Game::GetInstance() {
		return m_instance;
	}
	GameUI* Game::GetUI() {
		return m_ui;
	}

private:

	//ここからゲーム用

	GameData m_gameData;
	GameEffect m_gameEffect;

	GameUI* m_ui = nullptr;

	CharacterController* m_charaCon;
	PhysicsGhostObject m_ghostObject;						//ゴーストオブジェクトとを４つ。
};

