#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"

Game::Game()
{
	//�v���C���[
	CGameObjectManager::GetInstance()->NewGO<Player>("Player");
	CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround");

}


Game::~Game()
{
}
