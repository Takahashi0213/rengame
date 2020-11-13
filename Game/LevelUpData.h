#pragma once

/// <summary>
/// レベルアップ時のイベント
/// </summary>
enum LevelUpEvent {
	None = 0,			//イベント無し
	Up_Mana = 1,		//マナの向上
	Up_Hp = 1 << 1,		//HP向上
	Up_Mp = 1 << 2,
};
/// <summary>
/// レベルアップデータ
/// </summary>
struct LevelUpData {
	unsigned int levelUpEvent;
	int manaUp;	//マナの上昇量。

};
/// <summary>
/// レベルアップデータテーブル。
/// </summary>
static LevelUpData LEVEL_UP_DATA_TABLE[] = {
	{ None				,	0 },		//レベル0。イベントは何もない
	{ None				,	0 },		//レベル1。イベントは何もない
	{ Up_Mana			,	10 },		//レベル2。
	{ Up_Hp				,	0 },		//レベル3。
	{ Up_Mana			,	10 },		//レベル4。
	{ Up_Mana			,	5 },		//レベル5。
	{ Up_Mana			,	5 },		//レベル6。
	{ Up_Mana | Up_Hp	,	5 },		//レベル7。
	{ Up_Mana			,	5 },		//レベル8。
	{ Up_Mana			,	5 },		//レベル9。
	{ Up_Mana			,	10 },		//レベル10。
};
