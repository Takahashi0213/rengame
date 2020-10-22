#pragma once
#include "level/Level.h"
#include "LevelData.h"

/// <summary>
/// レベルを設定するクラス
/// Initでスタートです
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
	/// <summary>
	/// オブジェクト生成の共通処理。
	/// </summary>
	template<class T>
	T* NewObjCommon(LevelObjectData& data);
private:
	
	LevelData Level_Data;				//レベルデータ本体
	Level m_level;						//レベルデータ。
	int m_levelNo = -1;					//レベルの配列番号（-1で初期化しましょう！）

	//オブジェクトの生成
	void NewObj(LevelObjectData& data, const LevelData::Obj_Tag tag);
	//オブジェクトのリンク作業オブ作業
	void LinkObj(const int levelNo, const int i);

	//現在設置されているオブジェクトのデータ
	struct Obj_Data
	{
		LevelData::Obj_Tag ObjTag = LevelData::Obj_Tag::Tag_NULL;		//タグ
		const wchar_t* ObjName = L"";									//オブジェクトの名前
		int nameKey = 0;												//名前キー。
		const wchar_t* LinkObjName = L"";								//リンクされているオブジェクトの名前
		int linkObjectNameKey;											//リンクされているオブジェクトの名前キー。
	};
	//オブジェクトデータの配列
	Obj_Data m_Obj_Data[MAX_LEVEL_OBJ];
};

