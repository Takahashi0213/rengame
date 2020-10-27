#include "stdafx.h"
#include "BigDoor.h"


BigDoor::BigDoor()
{
	m_model = NewGO<SkinModelRender>("BigDoor_Render", 0);
	m_physicsStaticObject.CreateBox(m_position, m_rotation, StaticSize);

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

}


BigDoor::~BigDoor()
{
	//削除
	DeleteGO(m_model);
}

void BigDoor::Update() {

	//モノクロ化
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_model->SetRenderMode(RenderMode::Monochrome);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_model->SetRenderMode(RenderMode::Default);
		m_monochromeFlag = false;
	}
	//クリエイトモード中は一切の更新をしない
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode) {
		return;
	}

	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

}

void BigDoor::Render() {

}

void BigDoor::ModelChange(const DoorModel model) {

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

	m_thisModel = model;
	m_physicsStaticObject.CreateBox(m_position, m_rotation, StaticSize);

}