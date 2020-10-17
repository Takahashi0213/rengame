#include "stdafx.h"
#include "SystemBox.h"

#include "StageSet.h"

GhostBox::GhostBox()
{
	//�v���C���[�̌���
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}


GhostBox::~GhostBox()
{
}

void GhostBox::Update() {

	//�v���C���[�Ƃ̏Փ˔���
	CharacterController* charaCon = m_player->GetCharaCon();
	g_physics->ContactTest(*charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObject�ƂԂ�����
			StageSet::GetInstance()->InitStage(m_LoadStageName);
		}
		});

}

void GhostBox::Render() {

}

void GhostBox::CreateGhost() {

	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_ghostObject.CreateBox(
		m_position,		//�������͍��W�B
		m_rotation,		//�������͉�]�N�H�[�^�j�I���B
		m_scale			//��O�����̓{�b�N�X�̃T�C�Y�B
	);

}

/// <summary>
/// ��������X�^�e�B�b�N�{�b�N�X
/// </summary>

StaticBox::StaticBox()
{
	//�����쐬
	m_physicsStaticObject.CreateBox(m_position, m_rotation, m_scale);
}


StaticBox::~StaticBox()
{
}

void StaticBox::Update() {

	//�����X�V
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
}

void StaticBox::Render() {

}
