#pragma once
#include "stdafx.h"

/// <summary>
/// �A�C�e���̏��
/// </summary>
class ItemData {
#define MAX_PATH          260
public:

	//�A�C�e���\����
	struct Item_Data {
		wchar_t Item_Name[MAX_PATH];				//�A�C�e�����O
		wchar_t Item_Explanation[MAX_PATH];			//�A�C�e������
		wchar_t Item_FilaPath_Sprite[MAX_PATH];		//�A�C�e���摜2D
		wchar_t Item_FilaPath_Model[MAX_PATH];		//�A�C�e��3D���f��
	};

	//���O����A�C�e���ԍ�������
	const int ItemNoSearch(const wchar_t* name) {
		for (int i = 0; i < MAX_ITEM_NOM; i++) {
			if (wcscmp(name, GameItem[i].Item_Name) == 0) {
				return i;
			}
		}
		return -1;
	}

	/// <summary>
	/// �A�C�e��
	/// </summary>
	const Item_Data GameItem[MAX_ITEM_NOM]{
		//�񕜖�
		{
			L"�񕜖�",
			L"�n�[�g���P�񕜂���",
			L"",
			L""
		},
		//��1
		{
			L"�����̌�",
			L"�ǂ����̔����J������",
			L"Assets/sprite/Key1.dds",
			L"Assets/modelData/Key1.cmo",
		},
	};

};