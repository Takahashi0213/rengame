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
	//m_physicsStaticObject.CreateMeshObject(m_model->GetModel_(), m_position, m_rotation);

}


Door::~Door()
{
}

void Door::Update() {
	//更新

	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3().AxisY(), 90.0f);
	CQuaternion rot = m_rotation * RotationY;
	CVector3 pos = m_model->GetPosition();
	pos.y += StaticY_Hosei;

	m_physicsStaticObject.SetPositionAndRotation(pos, rot);

	//フラグ更新
	UpdateActionFlag();

	//上下更新
	DoorUpDowmUpdate();
}

void Door::Render() {
	//m_model.Render();

}

void Door::DoorUpDowmUpdate() {

	if (m_actionFlag == true && m_upDownFlag == false) {
		//上に動かす
		m_model->m_skinModelSupporter.SkinModelMove({ 0.0f,500.0f,0.0f }, 20, 0, true);
		//
		m_upDownFlag = true;
	}
	if (m_actionFlag == false && m_upDownFlag == true) {
		//下に動かす
		m_model->m_skinModelSupporter.SkinModelMove({ 0.0f,-500.0f,0.0f }, 20, 0, true);
		//
		m_upDownFlag = false;
	}
}