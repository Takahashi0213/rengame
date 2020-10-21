#include "stdafx.h"
#include "BigDoor.h"


BigDoor::BigDoor()
{
	m_model = NewGO<SkinModelRender>("BigDoor_Render", 0);
	m_physicsStaticObject.CreateBox(m_position, m_rotation, StaticSize);

	//ƒ^ƒOÝ’è
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

}


BigDoor::~BigDoor()
{
	//íœ
	DeleteGO(m_model);
}

void BigDoor::Update() {

	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

}

void BigDoor::Render() {

}

void BigDoor::ModelChange(const BoxModel model) {

	const wchar_t* modelNames[Model_BigDoorNum] = {
		L"Assets/modelData/BigDoor.cmo",
		L"Assets/modelData/BigDoor_.cmo"
	};
	m_model->Model_Init(
		modelNames[model],
		m_position,
		m_rotation,
		m_scale
	);
}