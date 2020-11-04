#include "stdafx.h"
#include "Switch.h"

#include "BoxMaker.h"

Switch::Switch()
{
	//�e�X�g�p
	m_scale = CVector3{ 5.0f,5.0f,5.0f };

	//�͂��܂��
	m_model.Init(L"Assets/modelData/Switch_Base.cmo");
	//m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation, m_scale);
	//�V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

	//�^�O�ݒ�
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

}

Switch::~Switch()
{
}

void Switch::Update() {

	//���m�N����
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_model.SetRenderMode(RenderMode::Monochrome);
		m_switchObj.SwitchRenderModeChange(RenderMode::Monochrome);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_model.SetRenderMode(RenderMode::Default);
		m_switchObj.SwitchRenderModeChange(RenderMode::Default);
		m_monochromeFlag = false;
	}
	//�N���G�C�g���[�h���͈�؂̍X�V�����Ȃ�
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode) {
		return;
	}

	//�X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

	//�X�C�b�`��Ԃ̍X�V
	m_actionFlag = GetSwitchState();

	//�g�嗦�̍Đݒ�
	m_switchObj.SetScale(m_scale);
	//�Ԃ������̍X�V
	m_switchObj.SwitchUpdate();

}

void Switch::Render() {

	//�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

	m_switchObj.SwitchDraw();
}

/// <summary>
/// SwitchObj
/// </summary>

SwitchObj::SwitchObj()
{
}

SwitchObj::~SwitchObj()
{
}

void SwitchObj::SwitchObj_Init(const CVector3& Pos) {

	//��������
	m_model.Init(L"Assets/modelData/Switch.cmo");
	//SkinModel Coli_Model;
	//Coli_Model.Init(L"Assets/modelData/Switch_Coli.cmo", EnFbxUpAxis::enFbxUpAxisZ);

	//���W�v�Z
	m_position = Pos + Local;
	//�ݒ�
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�S�[�X�g�̍��W���쐬
	CVector3 ghostPos = m_position;
	ghostPos.y += GhostY_Up;

	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_ghostObject.CreateBox(
		ghostPos,		//�������͍��W�B
		m_rotation,		//�������͉�]�N�H�[�^�j�I���B
		GhostScale		//��O�����̓{�b�N�X�̃T�C�Y�B
	);

	//�v���C���[����
	m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation, m_scale);
	//m_physicsStaticObject.CreateBox(m_position, m_rotation, m_scale);

	//�V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

}

void SwitchObj::SwitchUpdate() {

	//�X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

	//�A�N�V�������[�h�������s
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::ActionMode ) {
		GhostCheck();
	}
}

void SwitchObj::SwitchDraw() {

	//�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void SwitchObj::GhostCheck() {
	
	//�v���C���[�Ɣ��`�F�b�N
	bool OnFlag = false;

	//�v���C���[
	CharacterController* charaCon = m_pl->GetCharaCon();
	g_physics->ContactTest(*charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObject�ƂԂ�����
			OnFlag = true;
		}
		});

	//��
	std::list<GameBox*>boxList = BoxMaker::GetInstance()->GetBoxList();
	for (auto go : boxList) {

		if (go->GetColli_InitFlag() == true) {

			RigidBody* rigidBody = go->GetRigidBody();
			g_physics->ContactTest(*rigidBody, [&](const btCollisionObject& contactObject) {
				if (m_ghostObject.IsSelf(contactObject) == true) {
					//m_ghostObject�ƂԂ�����
					OnFlag = true;
				}
				});
		}
	}

	//�I���t���O�`�F�b�N�I
	if (OnFlag == false && m_switchState == On) {	//���݃I�������ǁA����������ĂȂ���

		m_switchState = Off;

		//�X�C�b�`�̐Ԃ������𓮂���
		m_position.y = m_position.y + SwitchMove;

		//�C�x���g���łȂ��Ȃ�SE�Đ�
		if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == false) {
			//SE
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/switch.wav");	
		}
	}
	else if (OnFlag == true && m_switchState == Off){	//���݃I�t�����ǁA�Ȃ񂩏���Ă��I�I

		m_switchState = On;

		//�X�C�b�`�̐Ԃ������𓮂���
		m_position.y = m_position.y - SwitchMove;
		//�C�x���g���łȂ��Ȃ�SE�Đ�
		if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == false) {
			//SE
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/switch.wav");
		}
	}

}