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
	
	//�擾�]�[��

	/// <summary>
	/// �X�e�[�W�����擾
	/// </summary>
	/// <param name="stageNo">�X�e�[�W�ԍ�</param>
	const wchar_t* GetStageName(const int stageNo) {
		return StageList[stageNo].Stage_Name;
	}
	//�\����
	const wchar_t* GetHyouziName(const int stageNo) {
		return StageList[stageNo].Stage_HyouziName;
	}
	//�X�e�[�W���f���̃t�@�C���p�X
	const wchar_t* GetStageModel(const int stageNo) {
		return StageList[stageNo].LoadStageModel;
	}
	//���x���̃t�@�C���p�X
	const wchar_t* GetStageLevel(const int stageNo) {
		return StageList[stageNo].LoadStageLevel;
	}
	//�X�e�[�W�̏ꏊ�f�[�^
	const GameData::Place_Data GetStagePlace(const int stageNo) {
		return StageList[stageNo].ThisPlace;
	}
	//�X�e�[�W�̊���
	const CVector3 GetStageAmbientColor(const int stageNo) {
		return StageList[stageNo].AmbientColor;
	}

	//�X�e�[�W��BGM��
	wchar_t* GetStageBGM(const GameData::Place_Data place) {
		return StageBGM[place].BGM_Name;
	}

	//�v�Z�]�[��

	/// <summary>
	/// StageList�̗v�f�����擾
	/// </summary>
	int GetStageListSize() {
		return sizeof(StageList) / sizeof(Stage_Srtuct);
	}

private:
	const Stage_Srtuct StageList[5]{
		//�`���[�g���A���X�e�[�W
		{
			L"Tutorial",
			L"�͂��܂�̓��A",
			L"Assets/modelData/0_0.cmo",
			L"Assets/level/stage_00.tkl",
			GameData::Place_Data::Warehouse,
			{ 0.1f,0.1f,0.2f }
		},
		//����1
		{
			L"Sougen1",
			L"�j���[���[���h",
			L"Assets/modelData/Sougen_1_1.cmo",
			L"Assets/level/stage_1_1.tkl",
			GameData::Place_Data::Meadow,
			{ 0.5f,0.5f,0.5f }
		},
		//����2
		{
			L"Sougen2",
			L"�����炬�𒴂���",
			L"Assets/modelData/Sougen_1_2.cmo",
			L"Assets/level/stage_1_2.tkl",
			GameData::Place_Data::Meadow,
			{ 0.5f,0.5f,0.5f }
		},
		//����3
		{
			L"Sougen3",
			L"���ʂ���V��",
			L"Assets/modelData/Sougen_1_3.cmo",
			L"Assets/level/stage_1_3.tkl",
			GameData::Place_Data::Meadow,
			{ 0.5f,0.5f,0.5f }
		},


	};

	const Stage_BGM StageBGM[5]{
		L"Assets/sound/BGM/Title.wav",		//��
		L"Assets/sound/BGM/Tutorial.wav",	//�`���[�g���A��
		L"Assets/sound/BGM/Stage1.wav",		//����
	};

};