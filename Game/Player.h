#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "Game.h"
#include "MouseOver.h"

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

	void SetGame(Game* game) {
		m_gameObj = game;
	}

private:
	SkinModel m_model;	//スキンモデル。
	SkinModel m_model_Sl;	//スキンモデル（シルエット）
	CharacterController m_charaCon;		//キャラクターコントローラー。
	Game* m_gameObj;
	LightMaker* m_lightMaker;
	MouseOver ms;

	//モノクロフラグ
	bool m_monochromeFlag = false;

	void Move();
	void Jump();

	//プレイヤー
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率
	CVector3 m_moveSpeed = CVector3().Zero();
	CVector3 m_nextPos = CVector3().Zero();

	//移動
	const float m_moveMax = 30.0f;

	//ジャンプ
	bool m_jumpNow = false;
	const float m_jumpPower = 16.0f;	//ジャンプﾊﾟｩﾜｧ
	const float m_gravity = 0.8f;		//重力ﾊﾟｩﾜｧ

};

