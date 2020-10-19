#pragma once
#include "level/Level.h"
#include "LevelData.h"

/// <summary>
/// ���x����ݒ肷��N���X
/// Init�ŃX�^�[�[�[�g�I�I�I�ł�
/// </summary>
class LevelSet
{
	static LevelSet* m_instance;
public:
	LevelSet();
	~LevelSet();
	void Init(const wchar_t* LEVEL_Name);
	void LevelDelete();

	//�C���X�^���X�̎擾
	static LevelSet* LevelSet::GetInstance() {
		return m_instance;
	}

private:
	
	LevelData Level_Data;				//���x���f�[�^�{��
	Level m_level;						//���x���f�[�^�B
	int m_levelNo = -1;					//���x���̔z��ԍ��i-1�ŏ��������܂���I�j

	//�I�u�W�F�N�g�̐���
	void NewObj(LevelObjectData& data, LevelData::Obj_Tag tag);
	//�I�u�W�F�N�g�̃����N��ƃI�u���
	void LinkObj(int levelNo, int i);

	//���ݐݒu����Ă���I�u�W�F�N�g�̃f�[�^
	struct Obj_Data
	{
		LevelData::Obj_Tag ObjTag = LevelData::Obj_Tag::Tag_NULL;		//�^�O
		const wchar_t* ObjName = L"";									//�I�u�W�F�N�g�̖��O
		const wchar_t* LinkObjName = L"";								//�����N����Ă���I�u�W�F�N�g�̖��O
	};
	//�I�u�W�F�N�g�f�[�^�̔z��
	Obj_Data m_Obj_Data[MAX_LEVEL_OBJ];
};

