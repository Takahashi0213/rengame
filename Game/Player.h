#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	void Render()override;

	/// <summary>
	/// プレイヤーのポジションを返す
	/// </summary>
	/// <returns>プレイヤーの場所</returns>
	CVector3 Getm_Position() {
		return m_position;
	}
	/// <summary>
	/// プレイヤーの回転を返す
	/// </summary>
	/// <returns>回転</returns>
	CQuaternion Getm_Rotation() {
		return m_rotation;
	}

private:
	SkinModel m_model;	//スキンモデル。
	SkinModel m_model2;	//スキンモデル。

	PhysicsStaticObject m_physicsStaticObject;				//静的物理オブジェクト。

	void Move();

	//プレイヤー
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率

	CVector3 m_nextPos = CVector3().Zero();

};

