#include "stdafx.h"
#include "ItemSystem.h"


ItemSystem::ItemSystem()
{
	//�v���C���[�̌���
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));
}


ItemSystem::~ItemSystem()
{
}
