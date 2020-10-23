#pragma once


/// <summary>
/// ステージデータ
/// </summary>
class StageData {

public:

	//ステージデータ構造体
	struct Stage_Srtuct {
		wchar_t Stage_Name[MAX_PATH];		//ステージ名前
		wchar_t Stage_HyouziName[MAX_PATH];	//各マップの表示名 痛々しいネームが良い
		wchar_t LoadStageModel[MAX_PATH];	//ステージモデルのファイルパス
		wchar_t LoadStageLevel[MAX_PATH];	//ステージレベルのファイルパス
		GameData::Place_Data ThisPlace;		//ここはどこ
		CVector3 AmbientColor;				//このマップの環境光
	};
	//BGMデータ構造体
	struct Stage_BGM {
		wchar_t* BGM_Name;					//BGMの名前
	};
	
	//取得ゾーン

	/// <summary>
	/// ステージ名を取得
	/// </summary>
	/// <param name="stageNo">ステージ番号</param>
	const wchar_t* GetStageName(const int stageNo) {
		return StageList[stageNo].Stage_Name;
	}
	//表示名
	const wchar_t* GetHyouziName(const int stageNo) {
		return StageList[stageNo].Stage_HyouziName;
	}
	//ステージモデルのファイルパス
	const wchar_t* GetStageModel(const int stageNo) {
		return StageList[stageNo].LoadStageModel;
	}
	//レベルのファイルパス
	const wchar_t* GetStageLevel(const int stageNo) {
		return StageList[stageNo].LoadStageLevel;
	}
	//ステージの場所データ
	const GameData::Place_Data GetStagePlace(const int stageNo) {
		return StageList[stageNo].ThisPlace;
	}
	//ステージの環境光
	const CVector3 GetStageAmbientColor(const int stageNo) {
		return StageList[stageNo].AmbientColor;
	}

	//ステージのBGM名
	wchar_t* GetStageBGM(const GameData::Place_Data place) {
		return StageBGM[place].BGM_Name;
	}

	//計算ゾーン

	/// <summary>
	/// StageListの要素数を取得
	/// </summary>
	int GetStageListSize() {
		return sizeof(StageList) / sizeof(Stage_Srtuct);
	}

private:
	const Stage_Srtuct StageList[5]{
		//チュートリアルステージ
		{
			L"Tutorial",
			L"はじまりの洞窟",
			L"Assets/modelData/0_0.cmo",
			L"Assets/level/stage_00.tkl",
			GameData::Place_Data::Warehouse,
			{ 0.1f,0.1f,0.2f }
		},
		//草原1
		{
			L"Sougen1",
			L"ニューワールド",
			L"Assets/modelData/Sougen_1_1.cmo",
			L"Assets/level/stage_1_1.tkl",
			GameData::Place_Data::Meadow,
			{ 0.5f,0.5f,0.5f }
		},
		//草原2
		{
			L"Sougen2",
			L"せせらぎを超えて",
			L"Assets/modelData/Sougen_1_2.cmo",
			L"Assets/level/stage_1_2.tkl",
			GameData::Place_Data::Meadow,
			{ 0.5f,0.5f,0.5f }
		},
		//草原3
		{
			L"Sougen3",
			L"水面を穿つ天柱",
			L"Assets/modelData/Sougen_1_3.cmo",
			L"Assets/level/stage_1_3.tkl",
			GameData::Place_Data::Meadow,
			{ 0.5f,0.5f,0.5f }
		},


	};

	const Stage_BGM StageBGM[5]{
		L"Assets/sound/BGM/Title.wav",		//無
		L"Assets/sound/BGM/Tutorial.wav",	//チュートリアル
		L"Assets/sound/BGM/Stage1.wav",		//草原
	};

};
