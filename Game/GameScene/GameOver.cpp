#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver()
{
	//ƒvƒŒƒCƒ„[‚ÌŒŸõ
	Player* m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
	
}

GameOver::~GameOver()
{
}

void GameOver::GameOverUpdate() {

}