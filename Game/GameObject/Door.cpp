#include "stdafx.h"
#include "Door.h"


Door::Door()
{
	m_model = NewGO<SkinModelRender>("Door_Render", 0);
	m_model->Model_Init(
		L"Assets/modelData/Door.cmo",
		m_position, 
		m_rotation,
		m_scale
	);
	m_physicsStaticObject.CreateBox(m_position, m_rotation, StaticSize);
	m_actionFlag = false;

	//�^�O�ݒ�
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;
}


Door::~Door()
{
	//�폜
	DeleteGO(m_model);
}

void Door::Update() {

	//�X�V

	//���m�N���ɂȂ�
	if (Game::GetInstance() != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
			m_model->GetModel()->SetRenderMode(RenderMode::Monochrome);
			m_monochromeFlag = true;
		}
		else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
			m_model->GetModel()->SetRenderMode(RenderMode::Default);
			m_monochromeFlag = false;
		}
	}

	//���W�␳
	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3().AxisY(), 90.0f);	//�Ȃ�90�x��]���Ă����狭���ɖ߂�
	CQuaternion rot = m_rotation * RotationY;
	CVector3 pos = m_model->GetPosition();
	pos.y += StaticY_Hosei;

	m_physicsStaticObject.SetPositionAndRotation(pos, rot);

	//�t���O�X�V
	UpdateActionFlag();

	//�㉺�X�V
	DoorUpDowmUpdate();
}

void Door::Render() {
}

void Door::DoorUpDowmUpdate() {

	if (m_actionFlag == true && m_upDownFlag == false) {
		//��ɓ�����
		m_model->m_skinModelSupporter.SkinModelMove({ 0.0f,UpDown_Y,0.0f }, UpDownTime, 0, true);
		//
		m_upDownFlag = true;
	}
	if (m_actionFlag == false && m_upDownFlag == true) {
		//���ɓ�����
		m_model->m_skinModelSupporter.SkinModelMove({ 0.0f,-UpDown_Y,0.0f }, UpDownTime, 0, true);
		//
		m_upDownFlag = false;
	}
}