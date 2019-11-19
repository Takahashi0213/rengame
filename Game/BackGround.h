#pragma once
#include "physics/PhysicsStaticObject.h"
#include "system/CGameObjectManager.h"
#include "Game.h"

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Update()override;
	void Render()override;

	/// <summary>
	/// ゲームのポインタをほぞんぬ
	/// </summary>
	/// <param name="game">アドレス</param>
	void SetGame(Game* game) {
		m_game = game;
	}

private:
	SkinModel m_model;	//スキンモデル。
	Game* m_game;
	bool m_monochromeFlag = false;
	LightMaker* m_lightMaker;

	PhysicsStaticObject m_physicsStaticObject;				//静的物理オブジェクト。

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率


};

