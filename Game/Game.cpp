#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BoxMaker.h"
#include "TestEnemy.h"

#include "GameCamera.h"
#include "GameUI.h"

#include "Switch.h"
#include "StageSet.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//現在をゲーム（アクションモード）にする
	SceneManager::GetInstance()->SetGameMode(SceneManager::ActionMode);
	//Dofを有効にする
	SceneManager::GetInstance()->GetGameGraphicInstance()->m_dofFlag = true;

	//生成
	
	//ライトメーカー
	if(LightMaker::GetInstance() == nullptr) {
		CGameObjectManager::GetInstance()->NewGO<LightMaker>("LightMaker");
	}
	//アンビエントライトを初期化する
	LightMaker::GetInstance()->ResetAmbientColor();

	//カメラサポーターの生成
	CGameObjectManager::GetInstance()->NewGO<CameraSupporter>("CameraSupporter");

	//BackGround* bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	GameUI* ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	m_ui = ui;

	//カメラ
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");

	//ボックスメイカーに渡すよ
	m_box->SetPlayer(pl);

	//トランジション
	TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox, 
		SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true);

	//ワイヤーフレームを表示しますすうすすすうう
	g_physics->SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	//ステージ
	StageSet m_stageSet;
	m_stageSet.CriateStage(L"Assets/modelData/0_0.cmo",L"Assets/level/stage_00.tkl");
	m_stageSet.SetGame(this);

}


Game::~Game()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void Game::Update() {

	m_gameEffect.GameEffectUpdate();

}

void Game::Render() {

}