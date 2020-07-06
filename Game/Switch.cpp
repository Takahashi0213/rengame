#include "stdafx.h"
#include "Switch.h"

#include "Game.h"
#include "BoxMaker.h"


Switch::Switch()
{
	//�͂��܂��
	m_model.Init(L"Assets/modelData/Switch_Base.cmo");
	//m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation, m_scale);
	//�V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

}

Switch::~Switch()
{
}

void Switch::Update() {

	//�X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

	m_switchObj.SwitchUpdate();

}

void Switch::Render() {
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

void SwitchObj::SwitchObj_Init(CVector3 Pos) {

	//��������
	m_model.Init(L"Assets/modelData/Switch.cmo");
	SkinModel Coli_Model;
	Coli_Model.Init(L"Assets/modelData/Switch_Coli.cmo");

	//���W�v�Z
	m_position = Pos + Local;
	//�ݒ�
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_ghostObject.CreateBox(
		m_position,		//�������͍��W�B
		m_rotation,		//�������͉�]�N�H�[�^�j�I���B
		GhostScale		//��O�����̓{�b�N�X�̃T�C�Y�B
	);

	//�v���C���[����
	m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	m_physicsStaticObject.CreateMeshObject(Coli_Model, m_position, m_rotation, m_scale);
	//m_physicsStaticObject.CreateBox(m_position, m_rotation, m_scale);

	//�V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

}

void SwitchObj::SwitchUpdate() {

	//�X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

	//�A�N�V�������[�h�������s
	if (Game::GetInstance()->GetGameMode() == Game::ActionMode ) {
		GhostCheck();
	}
}

void SwitchObj::SwitchDraw() {
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

	}
	else if (OnFlag == true && m_switchState == Off){	//���݃I�t�����ǁA�Ȃ񂩏���Ă��I�I

		m_switchState = On;

		//�X�C�b�`�̐Ԃ������𓮂���
		m_position.y = m_position.y - SwitchMove;

	}

}