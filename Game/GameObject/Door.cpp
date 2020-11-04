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

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;
}


Door::~Door()
{
	//削除
	DeleteGO(m_model);
}

void Door::Update() {

	//更新

	//モノクロになる
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

	//座標補正
	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3().AxisY(), 90.0f);	//なんか90度回転してたから強引に戻す
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
}

void Door::DoorUpDowmUpdate() {

	if (m_actionFlag == true && m_upDownFlag == false) {
		//上に動かす
		m_model->m_skinModelSupporter.SkinModelMove({ 0.0f,UpDown_Y,0.0f }, UpDownTime, 0, true);
		//
		m_upDownFlag = true;
	}
	if (m_actionFlag == false && m_upDownFlag == true) {
		//下に動かす
		m_model->m_skinModelSupporter.SkinModelMove({ 0.0f,-UpDown_Y,0.0f }, UpDownTime, 0, true);
		//
		m_upDownFlag = false;
	}
}