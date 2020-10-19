#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "Game.h"
#include "MouseOver.h"
#include "GameBox.h"

class Player final: public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	void Render()override;

	/// <summary>
	/// プレイヤーが落下したら呼びましょう！
	/// </summary>
	void PlayerMiss();

	/// <summary>
	/// プレイヤーのポジションを返す
	/// </summary>
	/// <returns>プレイヤーの場所</returns>
	CVector3 GetPosition() {
		return m_position;
	}
	//プレイヤーの座標を設定
	void SetPosition(const CVector3 pos) {
		m_position = pos;
	}

	/// <summary>
	/// プレイヤーの回転を返す
	/// </summary>
	/// <returns>回転</returns>
	CQuaternion GetRotation() {
		return m_rotation;
	}

	/// <summary>
	/// キャラコンを取得
	/// </summary>
	CharacterController* GetCharaCon() {
		return &m_charaCon;
	}

private:

	//常時呼ばれる
	void BoxUp();

	SkinModel m_model;					//スキンモデル。
	SkinModel m_model_Sl;				//スキンモデル（シルエット）
	CharacterController m_charaCon;		//キャラクターコントローラー。
	Game* m_gameObj;
	LightMaker* m_lightMaker;
	//MouseOver ms;

	//モノクロフラグ
	bool m_monochromeFlag = false;

	//行動
	void Move();
	void Jump();
	//行動 箱関連
	void BoxCatch();
	void BoxSearch();
	void BoxMove();
	void BoxDelete();

	//プレイヤー
	CVector3 m_position = { 0.0f,100.0f,-500.0f };
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率
	CVector3 m_moveSpeed = CVector3().Zero();
	CVector3 m_nextPos = CVector3().Zero();

	//移動
	const float m_moveMax = 30.0f;

	//ジャンプ
	bool m_jumpNow = false;
	const float m_jumpPower = 16.0f;		//ジャンプﾊﾟｩﾜｧ
	const float m_gravity = 0.8f;			//重力ﾊﾟｩﾜｧ

	//箱持ち上げ
	GameBox* m_upBox = nullptr;				//持ち上げている箱
	GameBox* m_upKouho_Box = nullptr;		//持ち上げ候補の箱
	bool m_boxUpFlag = false;				//箱持ち上げ中？
	bool m_boxMoveFlag = false;				//箱上げ下ろし動作中？（動作中は動けません）
	bool m_upOrDown = false;				//箱を上げているならfalse、下しているならtrue
	bool m_boxButtonFlag = false;			//箱のボタン
	bool m_boxDeleteButtonFlag = false;		//箱のボタン
	const float m_boxPutHosei = 4.0f;		//箱を置くか投げるかの基準補正（大きくすると置きやすくなる）
	const float m_boxUpRange = 200.0f;		//箱を持ち上げられる範囲
	const float m_boxUp_Y_Max = 50.0f;		//箱を持ち上げられる高さの範囲
	const float m_boxUp_Angle = 90.0f;		//箱を持ち上げる視野角範囲
	//上げ下げ移動（catmull）（だったけどベジェ曲線に変更）
	CVector3 m_point_1 = CVector3::Zero();	//終点寄り
	CVector3 m_point_2 = CVector3::Zero();	//始点
	CVector3 m_point_3 = CVector3::Zero();	//終点
	CVector3 m_point_4 = CVector3::Zero();	//始点寄り
	float m_catmull_U = 0.0f;
	const float m_boxMove_Y_Hosei = 150.0f;		//箱を上げる際の最高到達点Y補正
	const float m_boxMove_Y_Hosei_Put = 50.0f;	//箱を下ろす際の最高到達点Y補正
	const float m_boxPos_Y_Hosei = 150.0f;		//箱を持ち上げているときのプレイヤーY補正
	const float m_boxPut_Hosei = 150.0f;		//箱を置くときの移動量
};

