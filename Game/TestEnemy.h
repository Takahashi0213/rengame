#pragma once
#include "character/CharacterController.h"
#include "EnemySystem.h"

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
	const float FollowSpeed = 10.0f; //追尾の速度

	const int ATK = 10;
	const int EXP = 10;

};

