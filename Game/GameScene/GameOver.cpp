#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver()
{
	//プレイヤーの検索
	Player* m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
	m_player->GemaOverFlag();

}

GameOver::~GameOver()
{
}

void GameOver::GameOverUpdate() {

}