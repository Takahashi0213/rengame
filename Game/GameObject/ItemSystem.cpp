#include "stdafx.h"
#include "ItemSystem.h"


ItemSystem::ItemSystem()
{
	//プレイヤーの検索
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));
}


ItemSystem::~ItemSystem()
{
}
