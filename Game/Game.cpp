#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "BoxMaker.h"

#include "GameCamera.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//生成
	m_physicsWorld.Init();

	//ライトメーカーの生成
	CGameObjectManager::GetInstance()->NewGO<LightMaker>("LightMaker");

	//カメラサポーターの生成
	CGameObjectManager::GetInstance()->NewGO<CameraSupporter>("CameraSupporter");

	BackGround* bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");

	//ボックスメイカーに渡すよ
	m_box->SetGame(this);
	m_box->SetPlayer(pl);
	//プレイヤーに渡す
	pl->SetGame(this);
	//背景に渡す
	bg->SetGame(this);
}


Game::~Game()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void Game::Update() {

	//m_physicsWorld.Update();

}

void Game::Render() {

}