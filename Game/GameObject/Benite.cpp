#include "stdafx.h"
#include "Benite.h"

Benite::Benite()
{

	//���f������
	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Benite", 1);
	m_modelRender->Model_Init(L"Assets/modelData/Mannequin.cmo",
		m_position, m_rotation, m_scale);

	m_modelRender->SetScale(Scale);

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

Benite::~Benite()
{
	//�Еt����
	CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
	m_charaCon.RemoveRigidBoby();
}

void Benite::Update() {

	//���m�N����
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_modelRender->GetModel()->SetRenderMode(RenderMode::Monochrome);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_modelRender->GetModel()->SetRenderMode(RenderMode::Default);
		m_monochromeFlag = false;
	}

	//�N���G�C�g���[�h���͈�؂̍X�V�����Ȃ�
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode) {
		return;
	}

	//���Ƃ̏Փ˔���
	bool DeathFlag = BoxAttackSearch(m_position);
	if (DeathFlag == true) {
		//���񂶂����
		m_state = State::Death;
	}

	//�v���C���[�Ƃ̃_���[�W����
	CVector3 toPlayerDir = m_player->GetPosition() - m_position;
	float toPlayerLen = toPlayerDir.Length();
	if (toPlayerLen < DamageLength) {
		Game::GetInstance()->GetDamageSystem()->Damage(-ATK);
	}

	//�X�e�[�g�ŕ���
	switch (m_state)
	{
	case Benite::Move:
		//�ړ�
		MoveAction();
		break;
	case Benite::AttackWait:
		//�\������
		Attack_Wait();
		break;
	case Benite::Attack:
		//�U��
		AttackAction();
		break;
	case Benite::Death:
		//���S
		m_actionFlag = true;
		GameStatus_UISystem::GetInstance()->AddEXP(EXP);		//�o���l���l��
		CGameObjectManager::GetInstance()->DeleteGO(this);
		break;
	}

	//�L�����R���ړ�
	m_charaCon.SetPosition(m_position);
	//�L�����R�����s
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	//ModelRender�X�V
	m_modelRender->SetPosition(m_position);
	m_modelRender->SetRotation(m_rotation);

}
void Benite::Render() {

}

void Benite::MoveAction() {

	if (m_moveTimer == 0.0f) {
		//�����_���ړ�
		int random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY(), static_cast<float>(random));
		CVector3 front = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(front);
		m_moveSpeed = front * RandomSpeed;
	}

	if (m_moveTimer >= MoveWaitLimit && m_moveFlag == false) {
		//��~����
		m_moveSpeed = CVector3::Zero();
		m_moveFlag = true;
	}
	
	//�^�C�}�[���Z
	m_moveTimer += CGameTime::GetFrameDeltaTime();

	if (m_moveTimer >= MoveWaitEndLimit) {
		//��~���I������i�ړ����ĊJ����j
		m_moveTimer = 0.0f;
		m_moveFlag = false;
	}

	//�v���C���[�̒T��
	CVector3 enemyForward = CVector3::AxisZ();
	m_rotation.Multiply(enemyForward);
	CVector3 toPlayerDir = m_player->GetPosition() - m_position;
	//���K�����s���O�ɁA�v���C���[�܂ł̋��������߂Ă����B
	float toPlayerLen = toPlayerDir.Length();
	//���K���I
	toPlayerDir.Normalize();
	//enemyForward��toPlayerDir�Ƃ̓��ς��v�Z����B
	float d = enemyForward.Dot(toPlayerDir);
	//���ς̌��ʂ�acos�֐��ɓn���āAenemyForward��toPlayerDir�̂Ȃ��p�����߂�B
	float angle = acos(d);
	//�p�x�̓}�C�i�X�����݂��邩��A��Βl�ɂ���B
	if (fabsf(angle) < CMath::DegToRad(EnemyAngle) && toPlayerLen < FollowLength) {
		//�U�������ֈڍs
		m_moveSpeed = CVector3::Zero();
		m_moveTimer = 0.0f;
		m_moveFlag = false;
		m_state = AttackWait;
	}
}

void Benite::Attack_Wait() {

	if (m_moveTimer == 0.0f) {
		CVector3 P_Position = m_player->GetPosition();
		CVector3 diff = P_Position - m_position;
		m_moveSpeed = diff;
		m_moveSpeed.Normalize();
		m_moveSpeed *= BackSpeed;
	}

	//�^�C�}�[���Z
	m_moveTimer += CGameTime::GetFrameDeltaTime();

	if (m_moveTimer >= AttackWaitLimit) {
		//�U���ֈڍs
		m_moveSpeed = CVector3::Zero();
		m_moveTimer = 0.0f;
		m_state = Attack;
	}

	CVector3 front = { 0.0f, 0.0f,1.0f };
	//�v���C���[�̌����ɉ�]
	m_moveSpeed.y = 0.0f;
	CVector3 diff = m_moveSpeed;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(front, diff);
	m_rotation = qRot;
}

void Benite::AttackAction() {

	if (m_moveTimer == 0.0f) {
		CVector3 P_Position = m_player->GetPosition();
		CVector3 diff = P_Position - m_position;
		m_moveSpeed = diff;
		m_moveSpeed.Normalize();
		m_moveSpeed *= AttackSpeed;

		CVector3 front = { 0.0f, 0.0f,1.0f };
		//�v���C���[�̌����ɉ�]
		m_moveSpeed.y = 0.0f;
		diff = m_moveSpeed;
		diff.Normalize();
		CQuaternion qRot;
		qRot.SetRotation(front, diff);
		m_rotation = qRot;
	}

	//�^�C�}�[���Z
	m_moveTimer += CGameTime::GetFrameDeltaTime();

	//�ړ���̃X�^��
	if (m_moveTimer >= AttackLimit && m_moveFlag == false) {
		m_moveSpeed = CVector3::Zero();
		m_moveFlag = true;
	}

	if (m_moveTimer >= AttackEndLimit) {
		//�ړ��ֈڍs
		m_moveSpeed = CVector3::Zero();
		m_moveTimer = 0.0f;
		m_moveFlag = false;
		m_state = Move;
	}


}