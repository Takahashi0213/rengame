#pragma once

#include "LevelSet.h"
#include "BackGround.h"
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
	/// </summary>
	/// <param name="stage_name"></param>
	void InitStage(const wchar_t* stage_name);

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

private:

	//�����o
	LevelSet m_levelSet;		//���x���Z�b�g�N���X
	StageData m_stageData;		//�X�e�[�W�f�[�^
	BackGround* m_bg = nullptr;	//�X�e�[�W
	int m_stageNo = -1;			//�X�e�[�W�ԍ�
};

