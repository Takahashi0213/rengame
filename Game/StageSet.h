#pragma once

#include "LevelSet.h"
#include "BackGround.h"
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
	/// </summary>
	/// <param name="stage_name"></param>
	void InitStage(const wchar_t* stage_name);

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

private:

	//メンバ
	LevelSet m_levelSet;		//レベルセットクラス
	StageData m_stageData;		//ステージデータ
	BackGround* m_bg = nullptr;	//ステージ
	int m_stageNo = -1;			//ステージ番号
};

