#include "stdafx.h"
#include "TestEnemy.h"

TestEnemy::TestEnemy()
{
	//�f�o�b�O�p����
	m_scale.Set(10.0f, 10.0f, 10.0f);

	//���f������
	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("TestEnemy", 1);
	m_modelRender->Model_Init(L"Assets/modelData/Test_Enemy.cmo",
		m_position, m_rotation, m_scale);

	//�V���h�E���V�[�o�[�ɂ���B
	m_modelRender->SetShadowReciever(true);

	//�V���h�E�L���X�^�[�ɂ��o�^
	m_modelRender->SetShadowCasterFlag(true);

	//�L�����R���I�I
	m_charaCon.Init(
		60.0f,  //�L�����N�^�[�̔��a�B
		60.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	//�v���C���[�̌���
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	//�^�O�ݒ�
	m_object = ObjectClass::ObjectClass_Tag::EnemyObj;

}

TestEnemy::~TestEnemy()
{
	//�Еt����
	CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
	m_charaCon.RemoveRigidBoby();
}

void TestEnemy::Update() {

	//���Ƃ̏Փ˔���
	bool DeathFlag = BoxAttackSearch(m_position);
	if (DeathFlag == true) {
		//���񂶂����
		m_state = State::Death;
	}

	//�X�e�[�g�ŕ���
	switch (m_state)
	{
	case TestEnemy::Move:
		//�ړ�
		MoveAction();
		break;
	case TestEnemy::Follow:
		//�ǔ�
		FollowAction();
		break;
	case TestEnemy::AttackWait:
		//�\������



		break;
	case TestEnemy::Attack:
		//�U��



		break;
	case TestEnemy::Death:
		//���S
		m_actionFlag = true;
		GameStatus_UISystem::GetInstance()->AddEXP(EXP);		//�o���l���l��
		CGameObjectManager::GetInstance()->DeleteGO(this);
		break;
	}

	//�L�����R���ړ�
	m_charaCon.SetPosition(m_position);
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	//ModelRender�X�V
	m_modelRender->SetPosition(m_position);

}

void TestEnemy::Render() {

}

void TestEnemy::MoveAction() {

	CVector3 P_Position = m_player->GetPosition();
	CVector3 diff = P_Position - m_position;

	if (diff.Length() < FollowLength) {
		//�������߂��̂Œǔ�����B
		m_state = Follow;
	}


}

void TestEnemy::FollowAction() {

	CVector3 P_Position = m_player->GetPosition();
	CVector3 diff = P_Position - m_position;

	if (diff.Length() > FollowLength) {
		//�ǔ��I��
		m_state = Move;
	}

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

	//�@���������������̃x�N�g�����v�Z����B
	CVector3 enemyVec = diff;
	enemyVec.Normalize();
	enemyVec *= FollowSpeed;
	CVector3 targetVector = P_Position - m_position;
	//�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;
	m_moveSpeed = enemyVec;
}