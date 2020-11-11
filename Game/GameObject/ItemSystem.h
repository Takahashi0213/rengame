#pragma once
#include "GameObject/ObjectClass.h"
#include "GameObject/Player.h"

class ItemSystem : public ObjectClass
{
public:
	ItemSystem();
	~ItemSystem();
	
	/// <summary>
	/// �A�C�e���̎擾�`�F�b�N
	/// �߂Â�����true��Ԃ�
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

	Player* m_player;				//�v���C���[

	float ItemGetRange = 150.0f;	//�擾�͈�
	int m_itemNo = -1;				//�A�C�e���ԍ�
	
};

