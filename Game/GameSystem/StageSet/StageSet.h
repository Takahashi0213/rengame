#pragma once

#include "level/LevelSet.h"
#include "GameObject/BackGround.h"
#include "StageData.h"

/// <summary>
/// �X�e�[�W�ƃ��x���𓯎��ɍ쐬����
/// �}�b�v�؂�ւ��̓x�ɌĂяo��
/// ���V���O���g��
/// </summary>
class StageSet
{
	static StageSet* m_instance;
public:
	StageSet();
	~StageSet();

	/// <summary>
	/// ���O������ƌ��݂̃X�e�[�W��j�����ĐV�����X�e�[�W�����������
	/// �Ή����閼�O��StageData��Stage_Name�Q��
	/// 
	/// �X�e�[�W�ԍ��ł������
	/// </summary>
	/// <param name="stage_name"></param>
	void InitStage(const wchar_t* stage_name);
	void InitStage(const int& stage_nom);

	/// <summary>
	/// �X�e�[�W���폜����
	/// ���O������ĂԂ��Ƃ͂قƂ�ǂȂ��Ǝv���܂�
	/// </summary>
	void DeleteStage();

	/// <summary>
	/// �w�i��Ԃ�
	/// </summary>
	BackGround* GetStage() {
		return m_bg;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static StageSet* StageSet::GetInstance() {
		return m_instance;
	}

	void CreateStage(const wchar_t* stage_filePath, const wchar_t* level_filePath);

	//�X�e�[�W�ԍ�
	int GetStageNo() {
		return m_stageNo;
	}
	//�I�u�W�F�N�g�f�[�^�̐擪���擾
	LevelSet::Obj_Data* GetObjData() {
		return m_levelSet.GetObjData();
	}
	//�X�e�[�W�̏ꏊ�f�[�^
	const GameData::Place_Data GetStagePlace(const wchar_t* stage_name);
	//�X�e�[�W�̕\����
	const wchar_t* GetStage_HyouziName(const int& levelNo) {
		return m_stageData.GetHyouziName(levelNo);
	}
	//�X�e�[�W��BGM��
	wchar_t* GetStageBGM_Name(const GameData::Place_Data place) {
		return m_stageData.GetStageBGM(place);
	}
	//�X�e�[�W�̃A�C�R����
	wchar_t* GetStageIC_Name(const GameData::Place_Data place) {
		return m_stageData.GetStageIC(place);
	}

private:

	//�����o
	LevelSet m_levelSet;		//���x���Z�b�g�N���X
	StageData m_stageData;		//�X�e�[�W�f�[�^
	BackGround* m_bg = nullptr;	//�X�e�[�W
	int m_stageNo = -1;			//�X�e�[�W�ԍ�
};

