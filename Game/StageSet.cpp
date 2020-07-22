#include "stdafx.h"
#include "StageSet.h"

StageSet* StageSet::m_instance = nullptr;

StageSet::StageSet()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


StageSet::~StageSet()
{
}

void StageSet::CriateStage(const wchar_t* stage_filePath, const wchar_t* level_filePath) {

	if (m_bg != nullptr) {
		CGameObjectManager::GetInstance()->DeleteGO(m_bg);
	}

	//�X�e�[�W�̐���
	m_bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	m_bg->Init(stage_filePath);

	//���x���̐���
	m_levelSet.Init(level_filePath);

}