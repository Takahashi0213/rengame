#pragma once
#include "GameObject/ObjectClass.h"
#include "GameObject/Player.h"

class ItemSystem : public ObjectClass
{
public:
	ItemSystem();
	~ItemSystem();
	
	/// <summary>
	/// アイテムの取得チェック
	/// 近づいたらtrueを返す
	/// </summary>
	bool ItemGetCheck() {
		float length = (m_position - m_player->GetPosition()).Length();
		if (length < ItemGetRange) {
			return true;
		}
		else {
			return false;
		}
	}

	Player* m_player;				//プレイヤー

	float ItemGetRange = 150.0f;	//取得範囲
	int m_itemNo = -1;				//アイテム番号
	
};

