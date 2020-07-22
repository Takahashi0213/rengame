#include "stdafx.h"
#include "TestEnemy.h"

TestEnemy::TestEnemy()
{
	//����
	m_position.Set(0.0f, 100.0f, 200.0f);
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
		//���񂶂����B�B�B�B
		m_state = State::Death;
	}

	//�X�e�[�g�ŕ���
	switch (m_state)
	{
	case TestEnemy::Move:
		//�ړ�
		m_moveSpeed.z = 1.0f;
		break;
	case TestEnemy::Follow:
		//�ǔ�
		break;
	case TestEnemy::Death:
		//���S
		CGameObjectManager::GetInstance()->DeleteGO(this);
		break;
	}

	//�ړ�
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	//ModelRender�X�V
	m_modelRender->SetPosition(m_position);

}

void TestEnemy::Render() {

}