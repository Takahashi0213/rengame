#include "stdafx.h"
#include "Benite.h"

Benite::Benite()
{
	//���f������
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"Assets/animData/BeniteWalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_attack].Load(L"Assets/animData/BeniAttackFull.tka");
	m_animClips[enAnimationClip_attack].SetLoopFlag(false);

	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Benite", 1);
	m_modelRender->Model_Init_Anim(L"Assets/modelData/Benite.cmo",
		m_animClips, enAnimationClip_Num);
	m_modelRender->SetPosition(m_position);
	m_modelRender->SetRotation(m_rotation);
	m_modelRender->SetScale(Scale);
	m_modelRender->PlayAnimation(enAnimationClip_walk);	//��{����

	m_modelRender->SetScale(Scale);

	//�V���h�E���V�[�o�[�ɂ���B
	m_modelRender->SetShadowReciever(true);

	//�V���h�E�L���X�^�[�ɂ��o�^
	m_modelRender->SetShadowCasterFlag(true);

	//�L�����R���I�I
	m_charaCon.Init(
		60.0f,  //�L�����N�^�[�̔��a�B
		80.0f,  //�L�����N�^�[�̍����B
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
	if (m_modelRender != nullptr) {
		CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
	}
	m_charaCon.RemoveRigidBoby();
}

void Benite::Update() {

	//���m�N����
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_modelRender->GetModel()->SetRenderMode(RenderMode::Monochrome);
		m_modelRender->SetIsUpdateAnimation(false);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_modelRender->GetModel()->SetRenderMode(RenderMode::Default);
		m_modelRender->SetIsUpdateAnimation(true);
		m_monochromeFlag = false;
	}

	//�N���G�C�g���[�h����Q�[���I�[�o�[���͈�؂̍X�V�����Ȃ�
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode || 
		SceneManager::GetInstance()->GetGameMode() == SceneManager::GameOver) {
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
		bool damageFlag = Game::GetInstance()->GetDamageSystem()->Damage(-ATK);
		if (damageFlag == true) {
			m_player->PlayerMiss(m_position);		//�v���C���[�̃m�b�N�o�b�N
		}
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
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Enemy_Death.wav");	//SE
		EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::EnemyDeath,
			false, m_position.x, m_position.y, m_position.z);
		CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
		m_modelRender = nullptr;
		CGameObjectManager::GetInstance()->DeleteGO(this);
		break;
	}

	//�L�����R���ړ�
	m_charaCon.SetPosition(m_position);
	//�L�����R�����s
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	//ModelRender�X�V
	if (m_modelRender != nullptr) {
		m_modelRender->SetPosition(m_position);
		m_modelRender->SetRotation(m_rotation);
	}

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

		CVector3 front = { 0.0f, 0.0f,-1.0f };
		//�v���C���[�̌����ɉ�]
		m_moveSpeed.y = 0.0f;
		diff = m_moveSpeed;
		diff.Normalize();
		CQuaternion qRot;
		qRot.SetRotation(front, diff);
		m_rotation = qRot;

		//�G�t�F�N�g
		m_effect = EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::EnemyDiscovery,
			false, m_position.x, m_position.y + EnemyEffect_YHosei, m_position.z);
	}

	//�^�C�}�[���Z
	m_moveTimer += CGameTime::GetFrameDeltaTime();

	//�G�t�F�N�g�̍��W�X�V
	CGameObjectManager::GetInstance()->GetEffekseerManager()->SetLocation(m_effect, m_position.x, m_position.y + EnemyEffect_YHosei, m_position.z);

	if (m_moveTimer >= AttackWaitLimit) {
		//�U���ֈڍs
		m_moveSpeed = CVector3::Zero();
		m_moveTimer = 0.0f;
		m_state = Attack;
	}

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

	//�U���A�j���[�V����
	if (m_moveTimer >= AttackAnimeLimit && m_attackAnimeFlag == false) {
		m_modelRender->PlayAnimation(enAnimationClip_attack);	//�U��
		m_attackAnimeFlag = true;
	}
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
		m_attackAnimeFlag = false;
		m_modelRender->PlayAnimation(enAnimationClip_walk);	//��{����
	}

	//�U���A�j���[�V�����I��
	if (m_attackAnimeFlag == true && m_modelRender->IsPlayingAnimation() == false) {
		m_modelRender->PlayAnimation(enAnimationClip_walk);	//��{����
	}

}