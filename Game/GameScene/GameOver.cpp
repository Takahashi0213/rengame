#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver()
{
	//�v���C���[�̌���
	Player* m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
	
}

GameOver::~GameOver()
{
}

void GameOver::GameOverUpdate() {

}