#include "stdafx.h"
#include "GameData.h"

GameData* GameData::m_instance = nullptr;

GameData::GameData()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


GameData::~GameData()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}
