#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BoxMaker.h"

#include "GameCamera.h"

#include "StageSet.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//生成
	
	//OPを生成
	m_op = new OP;

	//トランジション
	TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox, 
		SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true);

#ifdef _DEBUG
	//ワイヤーフレームを表示しますすうすすすうう
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

		break;
	}

	//どのステートでもエフェクト更新はする
	m_gameEffect.GameEffectUpdate();

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
	//ボックスメイカーに渡すよ
	m_box->SetPlayer(pl);
	//UIの作成
	m_ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	//カメラ
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");
	//ステージ
	StageSet m_stageSet;
	m_stageSet.InitStage(L"Sougen1");
	//StageSet::GetInstance()->InitStage(L"Tutorial");
	//処理変更
	m_gameState = GamaState_Game;
}