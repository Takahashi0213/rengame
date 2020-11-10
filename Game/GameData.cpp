#include "stdafx.h"
#include "GameData.h"

GameData* GameData::m_instance = nullptr;

GameData::GameData()
{
	if (m_instance == nullptr) {
		//このインスタンスを唯一のインスタンスとして記録する
		m_instance = this;
	}
}

GameData::~GameData()
{
	if (m_instance == this) {
		//インスタンスが破棄されたので、nullptrを代入
		m_instance = nullptr;
	}
}

void GameData::LevelUpCheck() {

	//一度に複数回レベルアップする可能性もあるためループさせる
	while (true)
	{
		//現在経験値がネクスト経験値をオーバーしているか？
		if (m_nowExp < m_nextExp) {
			break;		//オーバーしていないなら終了
		}

		//ここからレベルアップ処理
		m_nowExp = m_nowExp - m_nextExp;							//現在の経験値を減らす
		m_level++;													//レベルアップ
		m_nextExp = static_cast<int>(m_nextExp * NextEXP_Hosei);	//次回経験値上昇
		LevelUpStatus();											//レベルアップ時のステータス上昇
	}

}

void GameData::LevelUpStatus() {

	//レベルアップした時のステータス上昇量を個別に決める
	switch (m_level)
	{
	case 2:			//レベル2になった時のステータス上昇量
		LevelUp_Mana(10);
		break;
	case 3:
		LevelUp_HP();
		break;
	case 4:
		LevelUp_Mana(10);
		break;
	case 5:
		LevelUp_Mana(5);
		break;
	case 6:
		LevelUp_Mana(5);
		break;
	case 7:
		LevelUp_HP();
		break;
	case 8:
		LevelUp_Mana(5);
		break;
	case 9:
		LevelUp_Mana(5);
		break;
	case 10:		//ここがレベル10になった時の上昇量！
		LevelUp_Mana(10);
		break;

	}

}