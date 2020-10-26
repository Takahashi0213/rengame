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

	//�X�e�[�g�A�N�V����
	void MoveAction();
	void Attack_Wait();
	void AttackAction();

	CharacterController m_charaCon; //�L�����R��

	CVector3 m_moveSpeed = CVector3().Zero();

	State m_state = Move;	//�X�e�[�g

	float m_moveTimer = 0.0f;
	bool m_moveFlag = false;

	//�萔
	const float MoveWaitLimit = 2.0f;		//��~���郉�C��
	const float MoveWaitEndLimit = 3.0f;	//��~����߂āA�ړ����ĊJ���郉�C��
	const float RandomSpeed = 2.0f;			//�����_���ړ��̑��x

	const float FollowLength = 300.0f;		//�v���C���[�𔭌�����͈�
	const float EnemyAngle = 110.0f;		//����p

	const float BackSpeed = -2.0f;			//�U���o�b�N���x
	const float AttackWaitLimit = 0.5f;		//�U�������̎���

	const float AttackSpeed = 20.0f;		//�U���ړ����x
	const float AttackLimit = 0.5f;			//�U���̎���
	const float AttackEndLimit = 2.0f;		//�U���I���̎���

	const float Scale = 4.0f;				//�傫��

	const float DamageLength = 100.0f;		//�_���[�W�͈̔�

	const int ATK = 50;
	const int EXP = 20;

};

