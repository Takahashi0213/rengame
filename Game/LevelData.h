#pragma once
#include <map>
#include"IncludeHeader.h"

class LevelData
{
	//���̖��O�Ȃ炱�̃I�u�W�F�N�g�����܂���I�ȃf�[�^
	std::map < std::string, std::string > Level_Map =
	{ 
		{"Switch" , "Switch" }
	};

	//���x�����Ƃɂ������I�u�W�F�N�g�̐������K�v
	struct Obj_Data
	{
		std::string Obj_Name;		//���x�����̃I�u�W�F�N�g��
		std::string Key;			//�}�b�v�����ނ�I��
		std::string LinkObj_Name;	//�֘A����I�u�W�F�N�g�̖��O
	};
	//���x���f�[�^�\����
	struct Level_Data
	{
		std::string Level_Name;		//���x���̃t�@�C����
		Obj_Data Obj_Array[100];	//���̃��x���̃I�u�W�F�N�g����
	};

	/// <summary>
	/// ��������f�[�^�擾�p�֐��`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
	/// </summary>

	/// <summary>
	/// ���x���̃t�@�C�����擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <returns>�t�@�C����</returns>
	std::string GetLevelName(int num) {
		return m_levelData[num].Level_Name;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̖��O�擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <param name="obj_num">�I�u�W�F�N�g�ԍ�</param>
	/// <returns>�I�u�W�F�N�g�̖��O</returns>
	std::string GetObjectName(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Obj_Name;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̃L�[�擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�L�[</returns>	
	std::string GetObjectKey(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Key;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̃����N�I�u�W�F�N�g�̖��O���擾
	/// </summary>
	/// <returns>obj_num����ݒ肳��Ă��郊���N��I�u�W�F�N�g�̖��O</returns>	
	std::string GetObject_LinkObj(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].LinkObj_Name;
	}

private:

	//���x���f�[�^�{�́i�蓮���́j
	Level_Data m_levelData[2]{

	};

};

