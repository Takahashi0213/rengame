#include "stdafx.h"
#include "ItemSystem.h"


ItemSystem::ItemSystem()
{
	//ƒvƒŒƒCƒ„[‚ÌŒŸõ
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));
}


ItemSystem::~ItemSystem()
{
}
