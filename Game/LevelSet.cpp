#include "stdafx.h"
#include "LevelSet.h"

//まとめて
#include "IncludeHeader.h"

LevelSet* LevelSet::m_instance = nullptr;

LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

LevelSet::~LevelSet()
{	
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

void LevelSet::Init(wchar_t LEVEL_Name[255]) {

	m_level.Init(LEVEL_Name, [&](LevelObjectData& objData) {

		if (objData.EqualObjectName(L"")) {

			return true;
		}

		return false;
	});

}