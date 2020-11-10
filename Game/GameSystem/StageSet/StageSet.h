#pragma once

#include "level/LevelSet.h"
#include "GameObject/BackGround.h"
#include "StageData.h"

/// <summary>
/// ステージとレベルを同時に作成する
/// マップ切り替えの度に呼び出す
/// ※シングルトン
/// </summary>
class StageSet
{
	static StageSet* m_instance;
public:
	StageSet();
	~StageSet();

	/// <summary>
	/// 名前を入れると現在のステージを破棄して新しいステージが生成される
	/// 対応する名前はStageDataのStage_Name参照
	/// 
	/// ステージ番号版もあるよ
	/// </summary>
	/// <param name="stage_name"></param>
	void InitStage(const wchar_t* stage_name);
	void InitStage(const int& stage_nom);

	/// <summary>
	/// ステージを削除する
	/// ※外部から呼ぶことはほとんどないと思います
	/// </summary>
	void DeleteStage();

	/// <summary>
	/// 背景を返す
	/// </summary>
	BackGround* GetStage() {
		return m_bg;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static StageSet* StageSet::GetInstance() {
		return m_instance;
	}

	void CreateStage(const wchar_t* stage_filePath, const wchar_t* level_filePath);

	//ステージ番号
	int GetStageNo() {
		return m_stageNo;
	}
	//オブジェクトデータの先頭を取得
	LevelSet::Obj_Data* GetObjData() {
		return m_levelSet.GetObjData();
	}
	//ステージの場所データ
	const GameData::Place_Data GetStagePlace(const wchar_t* stage_name);
	//ステージの表示名
	const wchar_t* GetStage_HyouziName(const int& levelNo) {
		return m_stageData.GetHyouziName(levelNo);
	}
	//ステージのBGM名
	wchar_t* GetStageBGM_Name(const GameData::Place_Data place) {
		return m_stageData.GetStageBGM(place);
	}
	//ステージのアイコン名
	wchar_t* GetStageIC_Name(const GameData::Place_Data place) {
		return m_stageData.GetStageIC(place);
	}

private:

	//メンバ
	LevelSet m_levelSet;		//レベルセットクラス
	StageData m_stageData;		//ステージデータ
	BackGround* m_bg = nullptr;	//ステージ
	int m_stageNo = -1;			//ステージ番号
};

