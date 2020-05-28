#include "stdafx.h"
#include "LevelSet.h"

//�܂Ƃ߂�
#include "IncludeHeader.h"

LevelSet* LevelSet::m_instance = nullptr;

LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}

LevelSet::~LevelSet()
{	
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
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