#pragma once
#include "system/CGameObjectManager.h"

class BoxMaker : public IGameObject
{
public:
	BoxMaker();
	~BoxMaker();
	void Update()override;
	void Render()override;

private:


};

