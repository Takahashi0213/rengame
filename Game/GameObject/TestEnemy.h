#pragma once
#include "character/CharacterController.h"
#include "GameObject/EnemySystem.h"

//�e�X�g�p�̓G
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

	//�X�e�[�g�A�N�V����
	void MoveAction();
	void FollowAction();

	CharacterController m_charaCon; //�L�����R��

	CVector3 m_moveSpeed = CVector3().Zero();

	State m_state = Move;	//�X�e�[�g

	//�萔
	const float FollowLength = 300.0f;
	const float FollowSpeed = 5.0f; //�ǔ��̑��x

	const float Gravity = 2.0f;			//�d��

	const int ATK = 10;
	const int EXP = 10;

};

