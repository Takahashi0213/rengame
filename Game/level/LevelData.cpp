#include "stdafx.h"
#include "LevelData.h"

int LevelData::ObjName_Search(const int& LevelNo, const wchar_t* objName) {

	//�w�肵�����x���ɐݒ肳�ꂽ�I�u�W�F�N�g�̌���
	for (int i = 0; i < MAX_LEVEL_OBJ; i++) {
		const wchar_t* name = GetObjectName(LevelNo, i);
		if (wcscmp(name, objName) == 0) {
			return i;	//���O�ł��B
		}
	}

	return -1;	//-1�ł��Ԃ��Ƃ���

}