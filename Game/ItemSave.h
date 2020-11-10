#pragma once
#include "stdafx.h"
#include "ItemData.h"

/// <summary>
/// �A�C�e���̏������Ȃǂ�ۑ�
/// </summary>
class ItemSave {
public:
	
	//�A�C�e���Z�[�u�\����
	struct Item_SaveData
	{
		int m_itemHave = 0;		//������
		bool m_getFlag = false;	//�擾�������Ƃ���H
	};

	//�擾�p
	const int& GetItemHave(const int& itemNo) {
		return Item_Save[itemNo].m_itemHave;
	}
	const bool& GetItemGetFlag(const int& itemNo) {
		return Item_Save[itemNo].m_getFlag;
	}
	//�ݒ�p
	void SetItemHave(const int& itemNo, const int itemHave) {
		Item_Save[itemNo].m_itemHave = itemHave;
	}
	void SetItemGetFlag(const int& itemNo) {
		Item_Save[itemNo].m_itemHave = true;
	}

private:

	//�A�C�e���Z�[�u
	Item_SaveData Item_Save[MAX_ITEM_NOM];

};