#pragma once
#include <map>
#include"IncludeHeader.h"

class LevelData
{
public:

	//���̖��O�Ȃ炱�̃I�u�W�F�N�g�����܂���I�ȃf�[�^
	//std::map < std::string, std::string > Level_Map =
	//{ 
	//	{"Switch" , "Switch" }
	//};

	//�I�u�W�F�N�g�̎��
	enum Obj_Tag {
		Tag_Switch,			//�X�C�b�` �Ή������h�A�Ȃǂ̃M�~�b�N��LinkObj�ɐݒ肷��
		Tag_Door,			//�h�A �X�C�b�`����M�����󂯎�����ꍇ�ړ�����
		Tag_Test_Enemy		//�e�X�g�G�l�~�[ ���łł���������
	};

	//���x�����Ƃɂ������I�u�W�F�N�g�̐������K�v
	struct Obj_Data
	{
		wchar_t Obj_Name[255];		//���x�����̃I�u�W�F�N�g��
		Obj_Tag Tag;				//��ނ�I��
		wchar_t LinkObj_Name[255];	//�֘A����I�u�W�F�N�g�̖��O
	};
	//���x���f�[�^�\����
	struct Level_Data
	{
		wchar_t Level_Name[255];			//���x���̃t�@�C����
		Obj_Data Obj_Array[MAX_LEVEL_OBJ];	//���̃��x���̃I�u�W�F�N�g����
	};

	//��������f�[�^�擾�p�֐��`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

	/// <summary>
	/// ���x���̃t�@�C�����擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <returns>�t�@�C����</returns>
	const wchar_t* GetLevelName(int num) {
		return m_levelData[num].Level_Name;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̖��O�擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <param name="obj_num">�I�u�W�F�N�g�ԍ�</param>
	/// <returns>�I�u�W�F�N�g�̖��O</returns>
	const wchar_t* GetObjectName(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Obj_Name;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̃^�O�擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�L�[</returns>	
	Obj_Tag GetObjectTag(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Tag;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̃����N�I�u�W�F�N�g�̖��O���擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <returns>obj_num����ݒ肳��Ă��郊���N��I�u�W�F�N�g�̖��O</returns>	
	const wchar_t* GetObject_LinkObj(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].LinkObj_Name;
	}

	/// <summary>
	/// LevelData�̃T�C�Y���擾
	/// </summary>
	int GetLevelDataSize() {
		return sizeof(m_levelData) / sizeof(Level_Data);
	}

	/// <summary>
	/// �w�肵���ԍ����x���̃I�u�W�F�N�g�ꗗ�����v����I�u�W�F�N�gNo������
	/// �q�b�g���Ȃ������ꍇ��-1��Ԃ�
	/// </summary>
	/// <param name="LevelNo">���x��No</param>
	/// <param name="objName">�������閼�O</param>
	/// <returns>�q�b�g�����ꏊ</returns>
	int ObjName_Search(int LevelNo, const wchar_t* objName);

private:

	//���x���f�[�^�{�́i�蓮���́j
	const Level_Data m_levelData[2]{
		//�`���[�g���A��
		{
			L"Assets/level/stage_00.tkl",	//���x���t�@�C����
			{
				{ L"Switch1",Tag_Switch,L"Door1" },
				{ L"Switch2",Tag_Switch,L"Door3" },
				{ L"Switch3",Tag_Switch,L"Door3" },
				{ L"Door1",Tag_Door,L"" },
				{ L"Door2",Tag_Door,L"" },
				{ L"Door3",Tag_Door,L"" },
				{ L"Test_Enemy",Tag_Test_Enemy,L"Door2" },
			}
		}
	};

};

