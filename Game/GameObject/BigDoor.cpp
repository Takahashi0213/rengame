#include "stdafx.h"
#include "BigDoor.h"
#include "GameScene/SceneManager.h"

BigDoor::BigDoor()
{
	m_model = NewGO<SkinModelRender>("BigDoor_Render", 1);
	m_physicsStaticObject.CreateBox(m_position, m_rotation, StaticSize);

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

	//プレイヤー検索
	m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

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

	//プレイヤーが近くて該当アイテムを持っていたら開く
	float length = (m_position - m_pl->GetPosition()).Length();
	bool itemFlag = SceneManager::GetInstance()->GetItemSave()->GetItemGetFlag(m_itemNo);
	if (length < OpenRange && itemFlag == true && m_actionFlag == false) {
		m_actionFlag = true;
	}
	//ドアを開ける
	if (m_actionFlag == true && m_doorOpenFlag == false) {
		DoorOpen();
		m_doorOpenFlag = true;
	}

	//コライダー設定
	m_position = m_model->GetPosition();
	m_rotation = m_model->GetRotation();
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
}

void BigDoor::Render() {

}

void BigDoor::ModelChange(const DoorModel model) {

	//モデルの設定
	m_model->Model_Init(
		ModelNames[model],
		m_position,
		m_rotation,
		m_scale
	);

	m_thisModel = model;
	m_physicsStaticObject.CreateBox(m_position, m_rotation, StaticSize);

}

void BigDoor::DoorOpen() {

	//ドアが開きます
	switch (m_thisModel)
	{
	case BigDoor::Model_BigDoor:
		m_model->m_skinModelSupporter.SkinModelMove({ 70.0f, 0.0f, 130.0f }, 20, 0, true);
		m_model->m_skinModelSupporter.SkinModelRotation(4.5f, CVector3::AxisY(), 20, 0);
		break;
	case BigDoor::Model_BigDoor2:
		m_model->m_skinModelSupporter.SkinModelMove({ -70.0f, 0.0f, 130.0f }, 20, 0, true);
		m_model->m_skinModelSupporter.SkinModelRotation(-4.5f, CVector3::AxisY(), 20, 0);
		break;
	}

}