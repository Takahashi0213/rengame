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

	//サウンドエンジンを初期化。
	m_soundEngine.Init();

	//生成

	//ライトメーカーの生成
	CGameObjectManager::GetInstance()->NewGO<LightMaker>("LightMaker");

	//カメラサポーターの生成
	CGameObjectManager::GetInstance()->NewGO<CameraSupporter>("CameraSupporter");

	//BackGround* bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");
	GameUI* ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	//TestEnemy* test = CGameObjectManager::GetInstance()->NewGO<TestEnemy>("TestEnemy", 1);
	m_ui = ui;

	TransitionGenerator* tg = CGameObjectManager::GetInstance()->NewGO<TransitionGenerator>("TransitionGenerator", 10);
	tg->SetObjectTag(objectTag::t_Sprite);		//とにかく最後に実行されるようにする

	//ボックスメイカーに渡すよ
	m_box->SetPlayer(pl);
	//背景に渡す
	//bg->SetGame(this);

	//ワイヤーフレームを表示しますすうすすすうう
	g_physics->SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

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