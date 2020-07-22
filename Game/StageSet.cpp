#include "stdafx.h"
#include "StageSet.h"

StageSet* StageSet::m_instance = nullptr;

StageSet::StageSet()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


StageSet::~StageSet()
{
}

void StageSet::CriateStage(const wchar_t* stage_filePath, const wchar_t* level_filePath) {

	if (m_bg != nullptr) {
		CGameObjectManager::GetInstance()->DeleteGO(m_bg);
	}

	//ステージの生成
	m_bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	m_bg->Init(stage_filePath);

	//レベルの生成
	m_levelSet.Init(level_filePath);

}