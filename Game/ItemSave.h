#pragma once
#include "stdafx.h"
#include "ItemData.h"

/// <summary>
/// アイテムの所持数などを保存
/// </summary>
class ItemSave {
public:
	
	//アイテムセーブ構造体
	struct Item_SaveData
	{
		int m_itemHave = 0;		//所持数
		bool m_getFlag = false;	//取得したことある？
	};

	//取得用
	const int& GetItemHave(const int& itemNo) {
		return Item_Save[itemNo].m_itemHave;
	}
	const bool& GetItemGetFlag(const int& itemNo) {
		return Item_Save[itemNo].m_getFlag;
	}
	//アイテムデータの取得
	ItemData* GetItemData() {
		return &m_itemData;
	}

	//設定用
	void SetItemHave(const int& itemNo) {
		Item_Save[itemNo].m_itemHave++;
	}
	void SetItemGetFlag(const int& itemNo) {
		Item_Save[itemNo].m_itemHave = true;
	}
	void SetItemSave(const int& itemNo) {
		SetItemHave(itemNo);
		SetItemGetFlag(itemNo);
	}

private:

	//アイテムセーブ
	Item_SaveData Item_Save[MAX_ITEM_NOM];
	//アイテムデータ
	ItemData m_itemData;

};