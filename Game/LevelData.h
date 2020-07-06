#pragma once
#include <map>
#include"IncludeHeader.h"

class LevelData
{
	//この名前ならこのオブジェクトを作りますよ的なデータ
	std::map < std::string, std::string > Level_Map =
	{ 
		{"Switch" , "Switch" }
	};

	//レベルごとにこいつがオブジェクトの数だけ必要
	struct Obj_Data
	{
		std::string Obj_Name;		//レベル内のオブジェクト名
		std::string Key;			//マップから種類を選択
		std::string LinkObj_Name;	//関連するオブジェクトの名前
	};
	//レベルデータ構造体
	struct Level_Data
	{
		std::string Level_Name;		//レベルのファイル名
		Obj_Data Obj_Array[100];	//このレベルのオブジェクトたち
	};

	//ここからデータ取得用関数～～～～～～～～～～～～～～～～

	/// <summary>
	/// レベルのファイル名取得
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <returns>ファイル名</returns>
	std::string GetLevelName(int num) {
		return m_levelData[num].Level_Name;
	}

	/// <summary>
	/// オブジェクトの名前取得
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <param name="obj_num">オブジェクト番号</param>
	/// <returns>オブジェクトの名前</returns>
	std::string GetObjectName(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Obj_Name;
	}

	/// <summary>
	/// オブジェクトのキー取得
	/// </summary>
	/// <returns>オブジェクトキー</returns>	
	std::string GetObjectKey(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Key;
	}

	/// <summary>
	/// オブジェクトのリンクオブジェクトの名前を取得
	/// </summary>
	/// <returns>obj_numから設定されているリンク先オブジェクトの名前</returns>	
	std::string GetObject_LinkObj(int num, int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].LinkObj_Name;
	}

private:

	//レベルデータ本体（手動入力）
	Level_Data m_levelData[2]{
		//1-1
		{
			"stage_00",	//レベルファイル名
			{
			}
		}
	};

};

