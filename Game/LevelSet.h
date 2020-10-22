#pragma once
#include "level/Level.h"
#include "LevelData.h"

/// <summary>
/// ���x����ݒ肷��N���X
/// Init�ŃX�^�[�g�ł�
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
	/// <summary>
	/// �I�u�W�F�N�g�����̋��ʏ����B
	/// </summary>
	template<class T>
	T* NewObjCommon(LevelObjectData& data);
private:
	
	LevelData Level_Data;				//���x���f�[�^�{��
	Level m_level;						//���x���f�[�^�B
	int m_levelNo = -1;					//���x���̔z��ԍ��i-1�ŏ��������܂��傤�I�j

	//�I�u�W�F�N�g�̐���
	void NewObj(LevelObjectData& data, const LevelData::Obj_Tag tag);
	//�I�u�W�F�N�g�̃����N��ƃI�u���
	void LinkObj(const int levelNo, const int i);

	//���ݐݒu����Ă���I�u�W�F�N�g�̃f�[�^
	struct Obj_Data
	{
		LevelData::Obj_Tag ObjTag = LevelData::Obj_Tag::Tag_NULL;		//�^�O
		const wchar_t* ObjName = L"";									//�I�u�W�F�N�g�̖��O
		int nameKey = 0;												//���O�L�[�B
		const wchar_t* LinkObjName = L"";								//�����N����Ă���I�u�W�F�N�g�̖��O
		int linkObjectNameKey;											//�����N����Ă���I�u�W�F�N�g�̖��O�L�[�B
	};
	//�I�u�W�F�N�g�f�[�^�̔z��
	Obj_Data m_Obj_Data[MAX_LEVEL_OBJ];
};

