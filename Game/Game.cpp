#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "BoxMaker.h"

#include "GameCamera.h"

Game::Game()
{
	//ƒvƒŒƒCƒ„[
	CGameObjectManager::GetInstance()->NewGO<Player>("Player");
	CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround");
	CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker");

}


Game::~Game()
{
}
