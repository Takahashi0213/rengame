#pragma once
#include "level/Level.h"
#include "LevelData.h"

/// <summary>
/// レベルを設定するクラス
/// Initでスターーート！！！です
/// </summary>
class LevelSet
{
	static LevelSet* m_instance;
public:
	LevelSet();
	~LevelSet();
	void Init(const wchar_t* LEVEL_Name);
	void LevelDelete();

	//インスタンスの取得
	static LevelSet* LevelSet::GetInstance() {
		return m_instance;
	}

private:
	
	LevelData Level_Data;				//レベルデータ本体
	Level m_level;						//レベルデータ。
	int m_levelNo = -1;					//レベルの配列番号（-1で初期化しましょ！）

	//オブジェクトの生成
	void NewObj(LevelObjectData& data, LevelData::Obj_Tag tag);
	//オブジェクトのリンク作業オブ作業
	void LinkObj(int levelNo, int i);

	//現在設置されているオブジェクトのデータ
	struct Obj_Data
	{
		LevelData::Obj_Tag ObjTag = LevelData::Obj_Tag::Tag_NULL;		//タグ
		const wchar_t* ObjName = L"";									//オブジェクトの名前
		const wchar_t* LinkObjName = L"";								//リンクされているオブジェクトの名前
	};
	//オブジェクトデータの配列
	Obj_Data m_Obj_Data[MAX_LEVEL_OBJ];
};

