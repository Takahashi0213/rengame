#include "stdafx.h"
#include "LevelData.h"

int LevelData::ObjName_Search(const int& LevelNo, const wchar_t* objName) {

	//指定したレベルに設定されたオブジェクトの検索
	for (int i = 0; i < MAX_LEVEL_OBJ; i++) {
		const wchar_t* name = GetObjectName(LevelNo, i);
		if (wcscmp(name, objName) == 0) {
			return i;	//お前です。
		}
	}

	return -1;	//-1でも返しとくか

}