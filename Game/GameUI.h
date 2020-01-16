#pragma once
#include "system/CGameObjectManager.h"

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();
	void Update()override;
	void Render()override;

};

