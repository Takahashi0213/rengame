#pragma once


/// <summary>
/// �X�e�[�W�f�[�^
/// </summary>
class StageData {

public:

	//�X�e�[�W�f�[�^�\����
	struct Stage_Srtuct {
		wchar_t Stage_Name[255];		//�X�e�[�W���O
		wchar_t Stage_HyouziName[255];	//�e�}�b�v�̕\���� �ɁX�����l�[�����ǂ�
		wchar_t LoadStageModel[255];	//�X�e�[�W���f���̃t�@�C���p�X
		wchar_t LoadStageLevel[255];	//�X�e�[�W���x���̃t�@�C���p�X
		GameData::Place_Data ThisPlace;	//�����͂ǂ�
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
		},
		//����1
		{
			L"Sougen1",
			L"�j���[���[���h",
			L"Assets/modelData/Sougen_1_1.cmo",
			L"Assets/level/stage_1_1.tkl",
			GameData::Place_Data::Meadow,
		},
		//����2
		{
			L"Sougen2",
			L"�����炬�𒴂���",
			L"Assets/modelData/Sougen_1_2.cmo",
			L"Assets/level/stage_1_2.tkl",
			GameData::Place_Data::Meadow,
		},
		//����3
		{
			L"Sougen3",
			L"���ʂ���V��",
			L"Assets/modelData/Sougen_1_3.cmo",
			L"Assets/level/stage_1_3.tkl",
			GameData::Place_Data::Meadow,
		},


	};

};
