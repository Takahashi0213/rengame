#pragma once
#include "character/CharacterController.h"
#include "GameObject/EnemySystem.h"

class Benite : public EnemySystem
{
public:
	Benite();
	~Benite();
	void Update()override;
	void Render()override;

	enum State {
		Move,
		AttackWait,
		Attack,
		Death,
	};

private:

	//ステートアクション
	void MoveAction();
	void Attack_Wait();
	void AttackAction();

	CharacterController m_charaCon; //キャラコン

	CVector3 m_moveSpeed = CVector3().Zero();

	State m_state = Move;	//ステート

	float m_moveTimer = 0.0f;
	bool m_moveFlag = false;

	//定数
	const float MoveWaitLimit = 2.0f;		//停止するライン
	const float MoveWaitEndLimit = 3.0f;	//停止をやめて、移動を再開するライン
	const float RandomSpeed = 2.0f;			//ランダム移動の速度

	const float FollowLength = 300.0f;		//プレイヤーを発見する範囲
	const float EnemyAngle = 110.0f;		//視野角

	const float BackSpeed = -2.0f;			//攻撃バック速度
	const float AttackWaitLimit = 0.5f;		//攻撃準備の時間

	const float AttackSpeed = 20.0f;		//攻撃移動速度
	const float AttackLimit = 0.5f;			//攻撃の時間
	const float AttackEndLimit = 2.0f;		//攻撃終了の時間

	const float Scale = 4.0f;				//大きさ

	const float DamageLength = 100.0f;		//ダメージの範囲

	const int ATK = 50;
	const int EXP = 20;

};

