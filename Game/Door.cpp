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
	//更新
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//フラグ更新
	UpdateActionFlag();

	//上下更新
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