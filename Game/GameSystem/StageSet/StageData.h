#pragma once


/// <summary>
/// �X�e�[�W�f�[�^
/// </summary>
class StageData {

public:

	//�X�e�[�W�f�[�^�\����
	struct Stage_Srtuct {
		wchar_t Stage_Name[MAX_PATH];		//�X�e�[�W���O
		wchar_t Stage_HyouziName[MAX_PATH];	//�e�}�b�v�̕\���� �ɁX�����l�[�����ǂ�
		wchar_t LoadStageModel[MAX_PATH];	//�X�e�[�W���f���̃t�@�C���p�X
		wchar_t LoadStageLevel[MAX_PATH];	//�X�e�[�W���x���̃t�@�C���p�X
		GameData::Place_Data ThisPlace;		//�����͂ǂ�
		CVector3 AmbientColor;				//���̃}�b�v�̊���
	};
	//BGM�f�[�^�\����
	struct Stage_BGM {
		wchar_t* BGM_Name;					//BGM�̖��O
	};
	//�A�C�R���f�[�^�\����
	struct Stage_Icon {
		wchar_t* Icon_Name;					//�A�C�R���̖��O
	};

	//�擾�]�[��

	/// <summary>
	/// �X�e�[�W�����擾
	/// </summary>
	/// <param name="stageNo">�X�e�[�W�ԍ�</param>
	const wchar_t* GetStageName(const int& stageNo) {
		return StageList[stageNo].Stage_Name;
	}
	//�\����
	const wchar_t* GetHyouziName(const int& stageNo) {
		return StageList[stageNo].Stage_HyouziName;
	}
	//�X�e�[�W���f���̃t�@�C���p�X
	const wchar_t* GetStageModel(const int& stageNo) {
		return StageList[stageNo].LoadStageModel;
	}
	//���x���̃t�@�C���p�X
	const wchar_t* GetStageLevel(const int& stageNo) {
		return StageList[stageNo].LoadStageLevel;
	}
	//�X�e�[�W�̏ꏊ�f�[�^
	const GameData::Place_Data GetStagePlace(const int& stageNo) {
		return StageList[stageNo].ThisPlace;
	}
	//�X�e�[�W�̊���
	const CVector3 GetStageAmbientColor(const int& stageNo) {
		return StageList[stageNo].AmbientColor;
	}

	//�X�e�[�W��BGM��
	wchar_t* GetStageBGM(const GameData::Place_Data place) {
		return StageBGM[place].BGM_Name;
	}
	//�X�e�[�W�̃A�C�R����
	wchar_t* GetStageIC(const GameData::Place_Data place) {
		return StageIC[place].Icon_Name;
	}
	//�X�e�[�W�̃V���h�E�L���X�^�[�t���O
	bool GetStageShadowFlag(const GameData::Place_Data place) {
		return StageShadowFlag[place];
	}

	//�v�Z�]�[��

	/// <summary>
	/// StageList�̗v�f�����擾
	/// </summary>
	int GetStageListSize() {
		return sizeof(StageList) / sizeof(Stage_Srtuct);
	}

private:
	//�X�e�[�W���
	const Stage_Srtuct StageList[MAX_STAGE_NOM]{
		//�`���[�g���A���X�e�[�W
		{
			L"Tutorial",
			L"�͂��܂�̓��A",
			L"Assets/modelData/0_0.cmo",
			L"Assets/level/stage_00.tkl",
			GameData::Place_Data::Warehouse,
			{ 0.2f,0.2f,0.3f }
		},
		//����1
		{
			L"Sougen1",
			L"�j���[���[���h",
			L"Assets/modelData/Sougen_1_1.cmo",
			L"Assets/level/stage_1_1.tkl",
			GameData::Place_Data::Meadow,
			{ 0.7f,0.7f,0.7f }
		},
		//����2
		{
			L"Sougen2",
			L"�����炬�𒴂���",
			L"Assets/modelData/Sougen_1_2.cmo",
			L"Assets/level/stage_1_2.tkl",
			GameData::Place_Data::Meadow,
			{ 0.7f,0.7f,0.7f }
		},
		//����3
		{
			L"Sougen3",
			L"���ʂ���V��",
			L"Assets/modelData/Sougen_1_3.cmo",
			L"Assets/level/stage_1_3.tkl",
			GameData::Place_Data::Meadow,
			{ 0.7f,0.7f,0.7f }
		},
		//�����{�X
		{
			L"SougenBoss",
			L"�����̃{�X",
			L"Assets/modelData/Sougen_1_Boss.cmo",
			L"Assets/level/stage_1_Boss.tkl",
			GameData::Place_Data::Meadow,
			{ 0.7f,0.7f,0.7f }
		},


	};

	//�X�e�[�W���Ƃ̃��C��BGM
	const Stage_BGM StageBGM[MAX_STAGE_NOM]{
		L"Assets/sound/BGM/Title.wav",			//��
		L"Assets/sound/BGM/Tutorial.wav",		//�`���[�g���A��
		L"Assets/sound/BGM/Stage1.wav",			//����
	};
	//�X�e�[�W���Ƃ̃A�C�R���i�Z�[�u�����[�h�Ŏg�p�j
	const Stage_Icon StageIC[MAX_STAGE_NOM]{
		L"Assets/sprite/MapIC_Nodata.dds",		//��
		L"Assets/sprite/MapIC0.dds",			//�`���[�g���A��
		L"Assets/sprite/MapIC1.dds",			//����
	};
	//�X�e�[�W���Ƃ̃V���h�E�L���X�^�[�t���O
	const bool StageShadowFlag[MAX_STAGE_NOM]{
		false,
		false,
		true,
	};
};
