#pragma once
#include "physics/PhysicsStaticObject.h"
#include "system/CGameObjectManager.h"

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update()override;
	void Render()override;

private:
	SkinModel m_model;	//スキンモデル。

	PhysicsStaticObject m_physicsStaticObject;				//静的物理オブジェクト。

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率


};

