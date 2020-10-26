#include "stdafx.h"
#include "Mannequin.h"

Mannequin::Mannequin()
{
	//���f������
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	//m_animClips[enAnimationClip_wait].Load(L"animData/MannequinStay.tka");
	//m_animClips[enAnimationClip_wait].SetLoopFlag(true);

	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Mannequin", 1);
	m_modelRender->Model_Init(L"Assets/modelData/Mannequin.cmo"/*,
		m_animClips, enAnimationClip_Num*/);
	m_modelRender->SetPosition(m_position);
	m_modelRender->SetRotation(m_rotation);
	m_modelRender->SetScale(Scale);
	//m_modelRender->PlayAnimation(enAnimationClip_wait);

	//�V���h�E���V�[�o�[�ɂ���B
	m_modelRender->SetShadowReciever(true);

	//�V���h�E�L���X�^�[�ɂ��o�^
	m_modelRender->SetShadowCasterFlag(true);

	//�L�����R���I�I
	m_charaCon.Init(
		60.0f,  //�L�����N�^�[�̔��a�B
		100.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	//�v���C���[�̌���
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	//�^�O�ݒ�
	m_object = ObjectClass::ObjectClass_Tag::EnemyObj;
}


Mannequin::~Mannequin()
{
	//�Еt����
	CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
	m_charaCon.RemoveRigidBoby();
}

void Mannequin::Update() {

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
		m_actionFlag = true;
		GameStatus_UISystem::GetInstance()->AddEXP(EXP);		//�o���l���l��
		CGameObjectManager::GetInstance()->DeleteGO(this);
	}

	//�L�����R�����s
	m_position = m_charaCon.Execute(1.0f, CVector3::Zero());
	//ModelRender�X�V
	m_modelRender->SetPosition(m_position);
}
void Mannequin::Render() {

}
