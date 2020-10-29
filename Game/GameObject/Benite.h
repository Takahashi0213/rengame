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

	enum EnAnimationClip {
		enAnimationClip_walk,	//待機
		enAnimationClip_attack, //攻撃
		enAnimationClip_Num,	 //アニメーションクリップ
	};

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
	AnimationClip m_animClips[enAnimationClip_Num];

	CVector3 m_moveSpeed = CVector3().Zero();

	State m_state = Move;	//ステート

	float m_moveTimer = 0.0f;
	bool m_moveFlag = false;
	bool m_attackAnimeFlag = false;			//アニメーション1回だけでいいので…

	//定数
	const float MoveWaitLimit = 2.0f;		//停止するライン
	const float MoveWaitEndLimit = 3.0f;	//停止をやめて、移動を再開するライン
	const float RandomSpeed = 2.0f;			//ランダム移動の速度

	const float FollowLength = 300.0f;		//プレイヤーを発見する範囲
	const float EnemyAngle = 110.0f;		//視野角

	const float BackSpeed = -2.0f;			//攻撃バック速度
	const float AttackWaitLimit = 0.5f;		//攻撃準備の時間

	const float AttackSpeed = 20.0f;		//攻撃移動速度
	const float AttackAnimeLimit = 0.4f;	//攻撃アニメの時間
	const float AttackLimit = 0.5f;			//攻撃の時間
	const float AttackEndLimit = 2.0f;		//攻撃終了の時間

	const float Scale = 1.0f;				//大きさ

	const float DamageLength = 150.0f;		//ダメージの範囲

	const int ATK = 50;
	const int EXP = 20;

};

