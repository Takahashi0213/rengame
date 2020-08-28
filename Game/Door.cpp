#include "stdafx.h"
#include "Door.h"


Door::Door()
{
	m_model.Init(L"Assets/modelData/Door.cmo");
	//m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation, m_scale);

}


Door::~Door()
{
}

void Door::Update() {
	//�X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�t���O�X�V
	UpdateActionFlag();

	//�㉺�X�V
	DoorUpDowmUpdate();
}

void Door::Render() {
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}

void Door::DoorUpDowmUpdate() {

	if (m_actionFlag == true) {
		int hoge = 0;
	}

}