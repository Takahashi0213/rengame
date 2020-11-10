#include "stdafx.h"
#include "StageSet.h"
#include "GameSystem/Box/BoxMaker.h"

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

void StageSet::InitStage(const wchar_t* stage_name) {
	
	//�ŏ��ɃX�e�[�W�ƃ��x�����폜
	DeleteStage();

	int Size = m_stageData.GetStageListSize();
	
	//�ǂ̃��x�����`�F�b�N���邽�߂̃��[�v
	for (int i = 0; i < Size; i++) {
		//��v����ꍇ�����Ɍ��肷��
		if (wcscmp(m_stageData.GetStageName(i), stage_name) == 0) {
			m_stageNo = i;	//���O�����c���Ȃ��I
			break;
		}
	}

	//�G���[�`�F�b�N
	if (m_stageNo == -1) {
		//�ǂ�ɂ������������Ă��Ȃ����߃G���[
		std::abort();
	}

	//�������琶������

	//�X�e�[�W�ԍ����Z�b�g
	GameData::GetInstance()->SetNowStageNo(m_stageNo);
	//�X�e�[�W�ꏊ���Z�b�g
	GameData::GetInstance()->SetPlace(m_stageData.GetStagePlace(m_stageNo));
	//������ݒ�
	LightMaker::GetInstance()->SetAmbientColor(m_stageData.GetStageAmbientColor(m_stageNo));
	//���̑S�폜
	BoxMaker::GetInstance()->BoxAllDelete();

	//�����^�C��
	CreateStage(m_stageData.GetStageModel(m_stageNo),
		m_stageData.GetStageLevel(m_stageNo));
}

void StageSet::InitStage(const int& stage_nom) {

	//�ŏ��ɃX�e�[�W�ƃ��x�����폜
	DeleteStage();

	//�G���[�`�F�b�N
	if (stage_nom == -1) {
		//�ǂ�ɂ������������Ă��Ȃ����߃G���[
		std::abort();
	}

	//�������琶������

	//�X�e�[�W�ԍ����Z�b�g
	GameData::GetInstance()->SetNowStageNo(stage_nom);
	//�X�e�[�W�ꏊ���Z�b�g
	GameData::GetInstance()->SetPlace(m_stageData.GetStagePlace(stage_nom));
	//������ݒ�
	LightMaker::GetInstance()->SetAmbientColor(m_stageData.GetStageAmbientColor(stage_nom));
	//���̑S�폜
	BoxMaker::GetInstance()->BoxAllDelete();

	//�����^�C��
	CreateStage(m_stageData.GetStageModel(stage_nom),
		m_stageData.GetStageLevel(stage_nom));
}

void StageSet::CreateStage(const wchar_t* stage_filePath, const wchar_t* level_filePath) {

	//�X�e�[�W�̐���
	m_bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	m_bg->Init(stage_filePath);

	//���x���̐���
	m_levelSet.Init(level_filePath);

}

void StageSet::DeleteStage() {

	//�����o�X�e�[�W�ԍ������Z�b�g
	m_stageNo = -1;
	//�X�e�[�W�ԍ������Z�b�g
	GameData::GetInstance()->SetNowStageNo(-1);
	//���x���ԍ������Z�b�g
	GameData::GetInstance()->SetNowMapLevel(-1);

	//�w�i�̍폜
	if (m_bg != nullptr) {
		CGameObjectManager::GetInstance()->DeleteGO(m_bg);
		m_bg = nullptr;
	}

	//���x���̍폜
	m_levelSet.LevelDelete();

}

const GameData::Place_Data StageSet::GetStagePlace(const wchar_t* stage_name) {

	int Size = m_stageData.GetStageListSize();
	int stageNo = -1;

	//�ǂ̃��x�����`�F�b�N���邽�߂̃��[�v
	for (int i = 0; i < Size; i++) {
		//��v����ꍇ�����Ɍ��肷��
		if (wcscmp(m_stageData.GetStageName(i), stage_name) == 0) {
			stageNo = i;	//���O�����c���Ȃ��I
			break;
		}
	}

	//�G���[�`�F�b�N
	if (stageNo == -1) {
		//�ǂ�ɂ������������Ă��Ȃ����߃G���[
		std::abort();
	}

	return m_stageData.GetStagePlace(stageNo);
}