#include "stdafx.h"
#include "Game.h"

#include "GameObject/Player.h"
#include "GameSystem/Box/BoxMaker.h"

#include "GameCamera.h"

#include "GameSystem/StageSet/StageSet.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//生成
	m_gameData = new GameData;
	m_gameEffect = new GameEffect;

	if (SceneManager::GetInstance()->GetSystemInstance()->m_loadDataFlag == false) {
		//OPを生成
		m_op = new OP;
	}
	else {
		//OPスキップ
		GameSetUp();
	}

#ifdef _DEBUG
	//ワイヤーフレームを表示します
	g_physics->SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
#endif

}


Game::~Game()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void Game::Update() {

	switch (m_gameState)
	{
	case Game::GameState_OP:
		//OPクラスアップデート
		m_op->OP_Update();
		//OPが終わったら切り替える
		if (m_op->GetEndFlag() == true) {
			//切り替え
			delete m_op;
			m_op = nullptr;
			GameSetUp();
		}

		break;
	case Game::GamaState_Game:
		//ゲーム中専用
		m_gameEvent->GameEventUpdate();		//ゲームイベントアップデート
		m_damageSystem->DamageUpdate();		//ダメージシステムアップデート
		break;
	case Game::GamaState_GameOver:
		m_gameOver->GameOverUpdate();		//ゲームオーバーアップデート
		break;
	}

	//ゲームオーバーチェック
	if (m_gameState != Game::GamaState_GameOver &&
		SceneManager::GetInstance()->GetGameMode() == SceneManager::GameOver) {
		m_gameState = Game::GamaState_GameOver;
		m_gameOver = new GameOver;		//ゲームオーバー画面を生成する
	}

	//どのステートでもエフェクト更新はする
	m_gameEffect->GameEffectUpdate();

}

void Game::Render() {

}

void Game::GameSetUp() {

	//モード変更
	SceneManager::GetInstance()->SetGameMode(SceneManager::GameMode::ActionMode);
	//Dofを有効にする
	SceneManager::GetInstance()->GetGameGraphicInstance()->m_dofFlag = true;

	//ボックスメイカーの作成
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	//プレイヤーの作成
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	//ボックスメイカーに渡す
	m_box->SetPlayer(pl);
	//UIの作成
	m_ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	m_statusUI = CGameObjectManager::GetInstance()->NewGO<GameStatus_UISystem>("GameStatus_UISystem", 8);
	//カメラ
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");
	//ゲームイベント
	m_gameEvent = new GameEvent;
	//ダメージシステム
	m_damageSystem = new DamageSystem;
	//アイテムセーブ
	m_itemSave = new ItemSave;
	if (SceneManager::GetInstance()->GetSystemInstance()->m_loadDataFlag == false) {
		//ステージ
		StageSet::GetInstance()->InitStage(L"Tutorial");
		//チュートリアルBGMの再生
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(L"Assets/sound/BGM/Tutorial.wav");
	}
	else {
		//ステージ
		StageSet::GetInstance()->InitStage(GameData::GetInstance()->GetNowStageNo());
		//プレイヤーの座標を設定
		pl->SetPosition(GameData::GetInstance()->GetSavePosition());
		pl->SetRotation(GameData::GetInstance()->GetSaveRotation());
		//BGMの再生
		wchar_t* bgmName = StageSet::GetInstance()->GetStageBGM_Name(GameData::GetInstance()->GetPlace());
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(bgmName);
		//トランジション
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox,
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true);
		//ロードする
		FILE* fp = fopen("save.bin", "rb");
		if (fp != NULL) {
			fread(m_gameEvent->GetEventSave(), sizeof(EventSave), 1, fp);
			fclose(fp);
		}
	}
	//処理変更
	m_gameState = GamaState_Game;
}