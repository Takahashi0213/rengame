#pragma once
#include "character/CharacterController.h"
#include "GameObject/EnemySystem.h"

//テスト用の敵
class TestEnemy : public EnemySystem
{
public:
	enum State {
		Move,
		Follow,
		AttackWait,
		Attack,
		Death,
	};

	TestEnemy();
	~TestEnemy();
	void Update()override;
	void Render()override;

private:

	//ステートアクション
	void MoveAction();
	void FollowAction();

	CharacterController m_charaCon; //キャラコン

	CVector3 m_moveSpeed = CVector3().Zero();

	State m_state = Move;	//ステート

	//定数
	const float FollowLength = 300.0f;
	const float FollowSpeed = 5.0f; //追尾の速度

	const float Gravity = 2.0f;			//重力

	const int ATK = 10;
	const int EXP = 10;

};

