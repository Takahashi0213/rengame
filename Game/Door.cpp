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
	//çXêV
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void Door::Render() {
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}