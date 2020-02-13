#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "Game.h"
#include "MouseOver.h"
#include "GameBox.h"

#include "StarMoney.h"

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

	//常時呼ばれる
	void BoxUp();

	SkinModel m_model;	//スキンモデル。
	SkinModel m_model_Sl;	//スキンモデル（シルエット）
	CharacterController m_charaCon;		//キャラクターコントローラー。
	Game* m_gameObj;
	LightMaker* m_lightMaker;
	MouseOver ms;

	//巨人
	SkinModel m_titan;	//スキンモデル。
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;
	ID3D11ShaderResourceView* m_specMapSRV = nullptr;
	ID3D11ShaderResourceView* m_aoMapSRV = nullptr;
	//宝石
	StarMoney* m_starMoney;

	//モノクロフラグ
	bool m_monochromeFlag = false;

	//行動
	void Move();
	void Jump();
	void BoxCatch();

	//プレイヤー
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率
	CVector3 m_moveSpeed = CVector3().Zero();
	CVector3 m_nextPos = CVector3().Zero();

	//移動
	const float m_moveMax = 30.0f;
	int hoge = 0;

	//ジャンプ
	bool m_jumpNow = false;
	const float m_jumpPower = 16.0f;	//ジャンプﾊﾟｩﾜｧ
	const float m_gravity = 0.8f;		//重力ﾊﾟｩﾜｧ

	//箱持ち上げ
	GameBox* m_upBox = nullptr;		//持ち上げている箱
	bool m_boxUpFlag = false;		//箱持ち上げ中？
	bool m_boxButtonFlag = false;	//箱のボタン

};

