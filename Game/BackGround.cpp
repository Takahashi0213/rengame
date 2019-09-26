#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	m_model.Init(L"Assets/modelData/map.cmo");
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	//PhysicsStaticObjectÇÃèâä˙âª
	m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation);

}


BackGround::~BackGround()
{
}

void BackGround::Update() {
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void BackGround::Render() {
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}