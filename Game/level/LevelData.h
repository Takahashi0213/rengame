#pragma once
#include <map>
#include"IncludeHeader.h"

class LevelData
{
public:

	//�I�u�W�F�N�g�̎��
	enum Obj_Tag {
		Tag_NULL,					//�_�~�[�f�[�^
		Tag_Switch,					//�X�C�b�` �Ή������h�A�Ȃǂ̃M�~�b�N��LinkObj�ɐݒ肷��
		Tag_Door,					//�h�A �X�C�b�`����M�����󂯎�����ꍇ�ړ�����
		Tag_BigDoor1,				//����h�A�i�������č����j
		Tag_BigDoor2,				//����h�A�i�������ĉE���j
		Tag_Test_Enemy,				//�e�X�g�G�l�~�[ ���łł�����
		Tag_Mannequin,				//�}�l�L�� �`���[�g���A���p�̓����Ȃ��I
		Tag_Benite,					//�x�j�e�[�i�G�j
		Tag_Jewel,					//�X�^�[�W���G��
		Tag_Board,					//�Ŕ�Obj_Memo�ɓ��e������
		Tag_GhostBox_MapMove,		//�}�b�v�ړ��p�S�[�X�g��obj_Memo�ɐڐG���Ă΂��}�b�v�̖��O������
		Tag_GhostBox_Event,			//�C�x���g�p�S�[�X�g��obj_Memo�ɐڐG���Ă΂��C�x���g�̖��O������
		Tag_GhostBox_Damage,		//�����p�S�[�X�g �G���ƃ_���[�W���󂯂Ē��O�̍��W�ɖ߂����
		Tag_StaticBox,				//��
		Tag_EventObject,			//�C�x���g�N�� �M�����󂯎�����ꍇ�ړ����遨obj_Memo�ɃC�x���g�̖��O������
		Tag_Key1,					//��1
		Tag_Torch,					//�g�[�`�i�|�C���g���C�g�j��BoolMemo�ŏ����̏����_����Ԃ�ݒ� false�Ȃ�I�t�Atrue�Ȃ�I��
	};

	//���x�����Ƃɂ������I�u�W�F�N�g�̐������K�v
	struct Obj_Data
	{
		wchar_t Obj_Name[MAX_PATH];			//���x�����̃I�u�W�F�N�g��
		Obj_Tag Tag;						//��ނ�I��
		wchar_t LinkObj_Name[MAX_PATH];		//�֘A����I�u�W�F�N�g�̖��O
		wchar_t Obj_Memo[MAX_PATH];			//�ŔƂ��̃e�L�X�g
		CVector3 Position_Memo;				//�ړ���Ȃǂ̐ݒ�p
		bool BoolMemo = false;				//bool�^�̃���
		float FloatMemo = 0.0f;				//float�^�̃���
		float FloatMemo2 = 0.0f;			//float�^�̃���
	};
	//���x���f�[�^�\����
	struct Level_Data
	{
		wchar_t Level_Name[MAX_PATH];		//���x���̃t�@�C����
		Obj_Data Obj_Array[MAX_LEVEL_OBJ];	//���̃��x���̃I�u�W�F�N�g����
	};

	//��������f�[�^�擾�p�֐�

	/// <summary>
	/// ���x���̃t�@�C�����擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <returns>�t�@�C����</returns>
	const wchar_t* GetLevelName(const int num) {
		return m_levelData[num].Level_Name;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̖��O�擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <param name="obj_num">�I�u�W�F�N�g�ԍ�</param>
	/// <returns>�I�u�W�F�N�g�̖��O</returns>
	const wchar_t* GetObjectName(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Obj_Name;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̃^�O�擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�L�[</returns>	
	Obj_Tag GetObjectTag(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Tag;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̃����N�I�u�W�F�N�g�̖��O���擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <returns>obj_num����ݒ肳��Ă��郊���N��I�u�W�F�N�g�̖��O</returns>	
	const wchar_t* GetObject_LinkObj(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].LinkObj_Name;
	}

	/// <summary>
	/// �I�u�W�F�N�g�������擾
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <param name="obj_num">�I�u�W�F�N�g�ԍ�</param>
	/// <returns></returns>
	const wchar_t* GetObject_ObjMemo(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Obj_Memo;
	}

	/// <summary>
	/// Vector3�������擾
	/// �}�b�v�ړ����̃v���C���[�ړ�����W�Ȃ�
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <param name="obj_num">�I�u�W�F�N�g�ԍ�</param>
	/// <returns>Vector3����</returns>
	const CVector3 GetObject_Vector3Memo(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Position_Memo;
	}

	/// <summary>
	/// bool�������擾
	/// �ėp�I�Ɏg��
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <param name="obj_num">�I�u�W�F�N�g�ԍ�</param>
	/// <returns>bool����</returns>
	const bool GetObject_BoolMemo(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].BoolMemo;
	}

	/// <summary>
	/// float�������擾
	/// �ėp�I�Ɏg��
	/// </summary>
	/// <param name="num">���x���ԍ�</param>
	/// <param name="obj_num">�I�u�W�F�N�g�ԍ�</param>
	/// <returns>float����</returns>
	const float GetObject_FloatMemo(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].FloatMemo;
	}
	const float GetObject_FloatMemo2(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].FloatMemo2;
	}

	/// <summary>
	/// LevelData�̃T�C�Y���擾
	/// </summary>
	int GetLevelDataSize() {
		return sizeof(m_levelData) / sizeof(Level_Data);
	}

	//�����p

	/// <summary>
	/// �w�肵���ԍ����x���̃I�u�W�F�N�g�ꗗ�����v����I�u�W�F�N�gNo������
	/// �q�b�g���Ȃ������ꍇ��-1��Ԃ�
	/// </summary>
	/// <param name="LevelNo">���x��No</param>
	/// <param name="objName">�������閼�O</param>
	/// <returns>�q�b�g�����ꏊ</returns>
	int ObjName_Search(const int& LevelNo, const wchar_t* objName);

private:

	//���x���f�[�^�{�́i�蓮���́j
	const Level_Data m_levelData[6]{
		//�`���[�g���A��
		{
			L"Assets/level/stage_00.tkl",	//���x���t�@�C����
			{
				{ L"Switch1",Tag_Switch,L"Door1" },
				{ L"Switch2",Tag_Switch,L"Door3" },
				{ L"Switch3",Tag_Switch,L"Door3" },
				{ L"Door1",Tag_Door,L"EventObject1" },
				{ L"Door2",Tag_Door,L"" },
				{ L"Door3",Tag_Door,L"" },
				{ L"Torch1",Tag_Torch,L"",L"",{ -50.0f,0.0f,0.0f },true },
				{ L"Torch2",Tag_Torch,L"",L"",{ -50.0f,0.0f,0.0f },true },
				{ L"Torch3",Tag_Torch,L"",L"",{ -50.0f,0.0f,0.0f },true },
				{ L"Torch4",Tag_Torch,L"",L"",{ -50.0f,0.0f,0.0f },true },
				{ L"Torch5",Tag_Torch,L"",L"",{ 50.0f,0.0f,0.0f },true },
				{ L"Torch6",Tag_Torch,L"",L"",{ 50.0f,0.0f,0.0f },true },
				{ L"Torch7",Tag_Torch,L"",L"",{ 50.0f,0.0f,0.0f },true },
				{ L"Torch8",Tag_Torch,L"",L"",{ 50.0f,0.0f,0.0f },true },
				{ L"Mannequin1",Tag_Mannequin,L"Door2" },
				{ L"GhostBox",Tag_GhostBox_MapMove,L"",L"Sougen1",{ 700.0f,110.0f,-950.0f }, false ,180.0f,-50.0f },	//�ړ���}�b�v�����ړ�����W
				{ L"EventBox1",Tag_GhostBox_Event,L"",L"Tutorial_1" },
				{ L"EventBox2",Tag_GhostBox_Event,L"",L"Tutorial_2" },
				{ L"EventObject1",Tag_EventObject,L"",L"Tutorial_3" },
			}
		},
		//����1
		{
			L"Assets/level/stage_1_1.tkl",	//���x���t�@�C����
			{
				{ L"Benite1",Tag_Benite,L"" },
				{ L"Benite2",Tag_Benite,L"" },
				{ L"jewel1",Tag_Jewel,L"" },
				{ L"jewel2",Tag_Jewel,L"" },
				{ L"jewel3",Tag_Jewel,L"" },
				{ L"jewel4",Tag_Jewel,L"" },
				{ L"jewel5",Tag_Jewel,L"" },
				{ L"Board1",Tag_Board,L"",L"�e�X�g�Ŕ�\n���b�Z�[�W" },
				{ L"StaticBox1",Tag_StaticBox,L"" },
				{ L"StaticBox2",Tag_StaticBox,L"" },
				{ L"StaticBox3",Tag_StaticBox,L"" },
				{ L"StaticBox4",Tag_StaticBox,L"" },
				{ L"StaticBox5",Tag_StaticBox,L"" },
				{ L"StaticBox6",Tag_StaticBox,L"" },
				{ L"GhostBox1",Tag_GhostBox_MapMove,L"",L"Sougen2",{ 0.0f,100.0f,-950.0f }, false ,180.0f,-750.0f },	//�ړ���}�b�v�����ړ�����W
				{ L"GhostBox2",Tag_GhostBox_MapMove,L"",L"Sougen3",{ 922.0f,100.0f,-428.0f }, false ,180.0f,-750.0f },	//�ړ���}�b�v�����ړ�����W
				{ L"GhostBox3",Tag_GhostBox_MapMove,L"",L"Tutorial",{ 0.0f,50.0f,2145.0f }, false ,180.0f,-50.0f },		//�ړ���}�b�v�����ړ�����W
			}
		},
		//����2
		{
			L"Assets/level/stage_1_2.tkl",	//���x���t�@�C����
			{
				{ L"jewel1",Tag_Jewel,L"" },
				{ L"jewel2",Tag_Jewel,L"" },
				{ L"BigDoor",Tag_BigDoor1,L"" },
				{ L"BigDoor_",Tag_BigDoor2,L"" },
				{ L"Benite1",Tag_Benite,L"" },
				{ L"StaticBox1",Tag_StaticBox,L"" },
				{ L"StaticBox2",Tag_StaticBox,L"" },
				{ L"StaticBox3",Tag_StaticBox,L"" },
				{ L"StaticBox4",Tag_StaticBox,L"" },
				{ L"StaticBox5",Tag_StaticBox,L"" },
				{ L"StaticBox6",Tag_StaticBox,L"" },
				{ L"StaticBox7",Tag_StaticBox,L"" },
				{ L"DamageZone",Tag_GhostBox_Damage,L"" },
				{ L"GhostBox1",Tag_GhostBox_MapMove,L"",L"Sougen1",{ -800.0f,100.0f,1000.0f }, true ,-90.0f,-100.0f },	//�ړ���}�b�v�����ړ�����W
			}
		},
		//����3
		{
			L"Assets/level/stage_1_3.tkl",	//���x���t�@�C����
			{
				{ L"jewel1",Tag_Jewel,L"" },
				{ L"jewel2",Tag_Jewel,L"" },
				{ L"jewel3",Tag_Jewel,L"" },
				{ L"Switch1",Tag_Switch,L"Key1" },
				{ L"Switch2",Tag_Switch,L"Key1" },
				{ L"StaticBox1",Tag_StaticBox,L"" },
				{ L"StaticBox2",Tag_StaticBox,L"" },
				{ L"StaticBox3",Tag_StaticBox,L"" },
				{ L"StaticBox4",Tag_StaticBox,L"" },
				{ L"StaticBox5",Tag_StaticBox,L"" },
				{ L"DamageZone",Tag_GhostBox_Damage,L"" },
				{ L"Key1",Tag_Key1,L"EventObject1" },
				{ L"EventObject1",Tag_EventObject,L"",L"Sougen_Key" },
				{ L"GhostBox1",Tag_GhostBox_MapMove,L"",L"Sougen1",{ -700.0f,110.0f,-500.0f }, false ,180.0f,-280.0f },	//�ړ���}�b�v�����ړ�����W
			}
		},
		//�����{�X
		{
			L"Assets/level/stage_1_Boss.tkl",	//���x���t�@�C����
			{
				{ L"StaticBox1",Tag_StaticBox,L"" },
				{ L"StaticBox2",Tag_StaticBox,L"" },
				{ L"StaticBox3",Tag_StaticBox,L"" },
				{ L"StaticBox4",Tag_StaticBox,L"" },
				{ L"StaticBox5",Tag_StaticBox,L"" },
				{ L"EventObject1",Tag_EventObject,L"",L"Sougen_Boss" },
			}
		}

	};

};

