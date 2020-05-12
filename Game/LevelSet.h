#pragma once
#include "level/Level.h"

class LevelSet
{
	static LevelSet* m_instance;
public:
	LevelSet();
	~LevelSet();
	void Init(wchar_t LEVEL_Name[255]);

	//インスタンスの取得
	static LevelSet* LevelSet::GetInstance() {
		return m_instance;
	}

private:
	Level m_level;	//レベルデータ。

};

