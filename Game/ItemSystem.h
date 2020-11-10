#pragma once
#include "GameObject/ObjectClass.h"
#include "GameObject/Player.h"

class ItemSystem : public ObjectClass
{
public:
	ItemSystem();
	~ItemSystem();

	Player* m_player;				//ƒvƒŒƒCƒ„[

};

