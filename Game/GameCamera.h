#pragma once
#include "system/CGameObjectManager.h"
#include "Player.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update()override;
	void Render()override;

private:
	CVector3 m_cameraTarget;
	CVector3 m_cameraPos;

	Player* m_player;

	CVector3 m_cameraHosei = { 0.0f,300.0f,-300.0f };

};

