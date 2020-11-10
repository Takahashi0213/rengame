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

	/// <summary>
	/// アイテム
	/// </summary>
	Item_Data GameItem[MAX_ITEM_NOM]{
		//回復薬
		{
			L"回復薬",
			L"ハートを１つ回復する",
			L"",
			L""
		},
	};

};