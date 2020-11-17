#pragma once
#include "stdafx.h"

/// <summary>
/// アイテムの情報
/// </summary>
class ItemData {
#define MAX_PATH          260
public:

	//アイテム構造体
	struct Item_Data {
		wchar_t Item_Name[MAX_PATH];				//アイテム名前
		wchar_t Item_Explanation[MAX_PATH];			//アイテム説明
		wchar_t Item_FilaPath_Sprite[MAX_PATH];		//アイテム画像2D
		wchar_t Item_FilaPath_Model[MAX_PATH];		//アイテム3Dモデル
	};

	//名前からアイテム番号を検索
	const int ItemNoSearch(const wchar_t* name) {
		for (int i = 0; i < MAX_ITEM_NOM; i++) {
			if (wcscmp(name, GameItem[i].Item_Name) == 0) {
				return i;
			}
		}
		return -1;
	}

	/// <summary>
	/// アイテム
	/// </summary>
	const Item_Data GameItem[MAX_ITEM_NOM]{
		//回復薬
		{
			L"回復薬",
			L"ハートを１つ回復する",
			L"",
			L""
		},
		//鍵1
		{
			L"草原の鍵",
			L"どこかの扉を開けられる",
			L"Assets/sprite/Key1.dds",
			L"Assets/modelData/Key1.cmo",
		},
	};

};