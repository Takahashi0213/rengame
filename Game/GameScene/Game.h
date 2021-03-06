#pragma once
#include "SystemData.h"
#include "GameGraphic.h"
#include "GameSystem/GameUI/GameUI.h"
#include "GameSystem/GameUI/GameStatusUI.h"
#include "system/CGameObjectManager.h"
#include "Event/GameEvent.h"
#include "OP.h"
#include "GameScene/GameOver.h"
#include "GameSystem/GameUI/DamageSystem.h"
#include "GameSystem/PlayerSupporter/TutorialSupporter.h"
#include "GameSystem/PlayerSupporter/UI_Supporter.h"
#include "ItemSave.h"
#include "GameSystem/GameUI/ItemGet.h"

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
		GamaState_GameOver,	//ゲームオーバー
	};

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static Game* GetInstance() {
		return m_instance;
	}
	GameUI* GetUI() {
		return m_ui;
	}
	DamageSystem* GetDamageSystem() {
		return m_damageSystem;
	}
	ItemGet* GetItemGet() {
		return m_itemGet;
	}
	UI_Supporter* GetUI_Supporter(){
		return m_ui_Supporter;
	}

private:

	//OPが終わってゲームが始まるときのやーつ
	void GameSetUp();

	GameState m_gameState = GameState_OP;				//最初はOPから入ります

	//ここからゲーム用

	GameData* m_gameData = nullptr;						//保存するデータ色々
	GameEffect* m_gameEffect = nullptr;					//ここでアップデートする
	GameUI* m_ui = nullptr;								//UI
	GameStatus_UISystem* m_statusUI = nullptr;			//UI
	DamageSystem* m_damageSystem = nullptr;				//ダメージの付与やゲームオーバーの管理
	OP* m_op = nullptr;									//OPが終わったら削除される
	GameOver* m_gameOver = nullptr;						//ゲームオーバーになったら生成される
	TutorialSupporter* m_tutorialSupporter = nullptr;	//チュートリアルの下部文字
	UI_Supporter* m_ui_Supporter = nullptr;				//操作方法を表示する
	ItemGet* m_itemGet = nullptr;						//アイテム取得演出

};

