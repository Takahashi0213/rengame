#pragma once
#include "character/CharacterController.h"
#include "EnemySystem.h"

//�e�X�g�p�̓G
class TestEnemy : public IGameObject, public EnemySystem,public ObjectClass
{
public:
	enum State {
		Move,
		Follow,
		Death,
	};

	TestEnemy();
	~TestEnemy();
	void Update()override;
	void Render()override;

private:

	CharacterController m_charaCon; //�L�����R��

	CVector3 m_moveSpeed = CVector3().Zero();

	State m_state = Move;	//�X�e�[�g
};

