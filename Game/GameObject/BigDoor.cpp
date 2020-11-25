#include "stdafx.h"
#include "BigDoor.h"
#include "GameScene/SceneManager.h"

BigDoor::BigDoor()
{
	m_model = NewGO<SkinModelRender>("BigDoor_Render", 1);
	m_physicsStaticObject.CreateBox(m_position, m_rotation, StaticSize);

	//�^�O�ݒ�
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

	//�v���C���[����
	m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

}


BigDoor::~BigDoor()
{
	//�폜
	DeleteGO(m_model);
}

void BigDoor::Update() {

	//���m�N����
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_model->SetRenderMode(RenderMode::Monochrome);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_model->SetRenderMode(RenderMode::Default);
		m_monochromeFlag = false;
	}
	//�N���G�C�g���[�h���͈�؂̍X�V�����Ȃ�
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode) {
		return;
	}

	//�v���C���[���߂��ĊY���A�C�e���������Ă�����J��
	float length = (m_position - m_pl->GetPosition()).Length();
	bool itemFlag = SceneManager::GetInstance()->GetItemSave()->GetItemGetFlag(m_itemNo);
	if (length < OpenRange && itemFlag == true && m_actionFlag == false) {
		m_actionFlag = true;
	}
	//�h�A���J����
	if (m_actionFlag == true && m_doorOpenFlag == false) {
		DoorOpen();
		m_doorOpenFlag = true;
	}

	//�R���C�_�[�ݒ�
	m_position = m_model->GetPosition();
	m_rotation = m_model->GetRotation();
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
}

void BigDoor::Render() {

}

void BigDoor::ModelChange(const DoorModel model) {

	//���f���̐ݒ�
	m_model->Model_Init(
		ModelNames[model],
		m_position,
		m_rotation,
		m_scale
	);

	m_thisModel = model;
	m_physicsStaticObject.CreateBox(m_position, m_rotation, StaticSize);

}

void BigDoor::DoorOpen() {

	//�h�A���J���܂�
	switch (m_thisModel)
	{
	case BigDoor::Model_BigDoor:
		m_model->m_skinModelSupporter.SkinModelMove({ 70.0f, 0.0f, 130.0f }, 20, 0, true);
		m_model->m_skinModelSupporter.SkinModelRotation(4.5f, CVector3::AxisY(), 20, 0);
		break;
	case BigDoor::Model_BigDoor2:
		m_model->m_skinModelSupporter.SkinModelMove({ -70.0f, 0.0f, 130.0f }, 20, 0, true);
		m_model->m_skinModelSupporter.SkinModelRotation(-4.5f, CVector3::AxisY(), 20, 0);
		break;
	}

}