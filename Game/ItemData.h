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

	/// <summary>
	/// �A�C�e��
	/// </summary>
	Item_Data GameItem[MAX_ITEM_NOM]{
		//�񕜖�
		{
			L"�񕜖�",
			L"�n�[�g���P�񕜂���",
			L"",
			L""
		},
	};

};