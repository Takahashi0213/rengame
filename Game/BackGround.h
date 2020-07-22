#pragma once
#include "physics/PhysicsStaticObject.h"
#include "system/CGameObjectManager.h"
#include "Game.h"

class BackGround : public IGameObject, public ObjectClass
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

	void Init(const wchar_t* filePath);

private:
	bool m_initFlag = false;

	SkinModel m_model;	//スキンモデル。
	Game* m_game;
	bool m_monochromeFlag = false;
	LightMaker* m_lightMaker;

	PhysicsStaticObject m_physicsStaticObject;				//静的物理オブジェクト。

	CVector3 m_position = { 0.0f,0.0f,0.0f };
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 10.0f,10.0f,10.0f }; //拡大率


};

