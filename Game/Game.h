#pragma once
#include "SystemData.h"
#include "GameGraphic.h"
#include "GameUI.h"
#include "GameStatusUI.h"
#include "system/CGameObjectManager.h"
#include "OP.h"

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

	enum GameState {	//OPからゲーム開始まで
		GameState_OP,		//オープニング
		GamaState_Game,		//ゲーム開始！
	};

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

	//OPが終わってゲームが始まるときのやーつ
	void GameSetUp();

	GameState m_gameState = GameState_OP;		//最初はOPから入ります

	//ここからゲーム用

	GameData m_gameData;		//保存するデータ色々
	GameEffect m_gameEffect;	//ここでアップデートする
	GameUI* m_ui = nullptr;
	GameStatus_UISystem* m_statusUI;
	OP* m_op = nullptr;			//OPが終わったら削除される

};

