#pragma once
#include "level/Level.h"
#include "LevelData.h"

class LevelSet
{
	static LevelSet* m_instance;
public:
	LevelSet();
	~LevelSet();
	void Init(wchar_t LEVEL_Name[255]);

	//�C���X�^���X�̎擾
	static LevelSet* LevelSet::GetInstance() {
		return m_instance;
	}

private:
	Level m_level;	//���x���f�[�^�B

	//���ݐݒu����Ă���I�u�W�F�N�g�̃f�[�^

};

