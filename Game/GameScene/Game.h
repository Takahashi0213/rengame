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
	GameEvent* GetGameEvent() {
		return m_gameEvent;
	}
	DamageSystem* GetDamageSystem() {
		return m_damageSystem;
	}

private:

	//OPが終わってゲームが始まるときのやーつ
	void GameSetUp();

	GameState m_gameState = GameState_OP;		//最初はOPから入ります

	//ここからゲーム用

	GameData* m_gameData = nullptr;				//保存するデータ色々
	GameEffect* m_gameEffect = nullptr;			//ここでアップデートする
	GameUI* m_ui = nullptr;						//UI
	GameStatus_UISystem* m_statusUI = nullptr;	//UI
	GameEvent* m_gameEvent = nullptr;			//ゲームイベント
	DamageSystem* m_damageSystem = nullptr;		//ダメージの付与やゲームオーバーの管理
	OP* m_op = nullptr;							//OPが終わったら削除される
	GameOver* m_gameOver = nullptr;				//ゲームオーバーになったら生成される
	TutorialSupporter* m_tutorialSupporter = nullptr;	//チュートリアルの下部文字
	UI_Supporter* m_ui_Supporter = nullptr;		//操作方法を表示する

};

