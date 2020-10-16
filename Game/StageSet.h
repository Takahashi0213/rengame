#pragma once

#include "LevelSet.h"
#include "BackGround.h"

class StageData;
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

	void CriateStage(const wchar_t* stage_filePath, const wchar_t* level_filePath);

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

private:
	LevelSet m_levelSet;		//レベルセットクラス

	//StageData m_stageData;		//ステージごとの処理をする場所

	BackGround* m_bg = nullptr;	//ステージ

};

class StageData {



};