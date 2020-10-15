#pragma once

#include "LevelSet.h"
#include "BackGround.h"

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

	void CriateStage(const wchar_t* stage_filePath, const wchar_t* level_filePath);

	//�Q�[���̃A�h���X��@���t���Ă��
	void SetGame(Game* game) {
		m_bg->SetGame(game);
	}

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

private:
	LevelSet m_levelSet;		//���x���Z�b�g�N���X

	BackGround* m_bg = nullptr;	//�X�e�[�W

};

