#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "BoxMaker.h"

#include "GameCamera.h"

Game::Game()
{
	//生成

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
	//ゲームカメラに渡す
	int a = Hash::MakeHash("GameCamera");
	GameCamera* GC = CGameObjectManager::GetInstance()->FindGO<GameCamera>(a);
	GC->SetGame(this);
	//プレイヤーに渡す
	pl->SetGame(this);
	//背景に渡す
	bg->SetGame(this);
}


Game::~Game()
{
}

void Game::Update() {

}

void Game::Render() {

}