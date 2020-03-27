#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "BoxMaker.h"
#include "TestEnemy.h"

#include "GameCamera.h"
#include "GameUI.h"

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

	BackGround* bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");
	GameUI* ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	TestEnemy* test = CGameObjectManager::GetInstance()->NewGO<TestEnemy>("TestEnemy", 1);
	m_ui = ui;

	TransitionGenerator* tg = CGameObjectManager::GetInstance()->NewGO<TransitionGenerator>("TransitionGenerator", 10);
	tg->SetObjectTag(objectTag::t_Sprite);		//とにかく最後に実行されるようにする

	//ボックスメイカーに渡すよ
	m_box->SetPlayer(pl);
	//背景に渡す
	bg->SetGame(this);

	//ボックス形状のゴーストを作成する。
	m_ghostObject.CreateBox(
		{ -500.0f, 100.0f, 0.0f },	//第一引数は座標。
		CQuaternion::Identity(),		//第二引数は回転クォータニオン。
		{ 200.0f, 200.0f, 200.0f }	//第三引数はボックスのサイズ。
	);
	//キャラコン取得
	m_charaCon = pl->GetCharaCon();
}


Game::~Game()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void Game::Update() {

	m_gameEffect.GameEffectUpdate();

	int a = 0;
	//キャラクターとゴーストのあたり判定を行う。
	g_physics.ContactTest(*m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった
			int hoge = 0;
		}
		});

}

void Game::Render() {

}