#include "stdafx.h"
#include "Key.h"


Key::Key()
{
	//取得範囲を設定
	ItemGetRange = GetRange;
}

Key::~Key()
{
	DeleteGO(m_modelRender);
}

void Key::DataSet() {

	//入手済みならカット
	if (SceneManager::GetInstance()->GetItemSave()->GetItemGetFlag(m_itemNo) == true) {
		return;
	}

	//様々な補正
	m_scale.Set(DefScale, DefScale, DefScale);
	m_drawFlag = true;
	if (SceneManager::GetInstance()->GetItemSave()->GetItemData()->ItemNoSearch(L"草原の鍵") == m_itemNo &&
		SceneManager::GetInstance()->GetGameEvent()->GetEventSave()->m_eventFlag[3] == false) {
		m_position.y -= DownHosei;
		m_moveFlag = true;
		m_drawFlag = false;
	}
	//生成
	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Key", 1);
	m_modelRender->Model_Init(SceneManager::GetInstance()->GetItemSave()->GetItemData()->GameItem[m_itemNo].Item_FilaPath_Model);
	m_modelRender->SetUp(m_position, m_rotation, m_scale);
	//自動回転
	m_modelRender->m_skinModelSupporter.SkinModelRotation(AutoRotation, CVector3::AxisY(), 1, 0, true);

	m_setFlag = true;
}

void Key::Update() {

	//入手済みならカット
	if (SceneManager::GetInstance()->GetItemSave()->GetItemGetFlag(m_itemNo) == true) {
		return;
	}

	//モノクロになる
	if (Game::GetInstance() != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
			m_modelRender->GetModel()->SetRenderMode(RenderMode::Monochrome);
			//自動回転停止
			m_modelRender->m_skinModelSupporter.SkinModelRotation(0.0f, CVector3::Zero(), 0, 0);
			m_monochromeFlag = true;
		}
		else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
			m_modelRender->GetModel()->SetRenderMode(RenderMode::Default);
			//自動回転
			m_modelRender->m_skinModelSupporter.SkinModelRotation(AutoRotation, CVector3::AxisY(), 1, 0, true);
			m_monochromeFlag = false;
		}
	}

	//アクションフラグがtrueなら鍵を描画する
	if (m_actionFlag == true && m_drawFlag == false) {
		m_drawFlag = true;
	}
	m_modelRender->SetActiveFlag(m_drawFlag);

	//スポーン
	if (m_actionFlag_2 == true && m_spawnFlag == false) {
		KeySpawn();
		m_spawnFlag = true;
	}

	//取得チェック
	if (ItemGetCheck() == true) {
		//アイテムゲット（演出アリ）
		Game::GetInstance()->GetItemGet()->ItemGetEffect(m_itemNo);
		//削除
		DeleteGO(this);
	}

	//座標更新
	m_position = m_modelRender->GetPosition();
	//フラグ更新
	UpdateActionFlag();

}

void Key::Render() {

}

void Key::KeySpawn() {

	//鍵を上に上げる
	if (m_moveFlag == true) {
		m_modelRender->m_skinModelSupporter.SkinModelMove({ 0.0f,UpMove,0.0f }, UpTime, 0, true);
		m_modelRender->m_skinModelSupporter.SkinModelMove({ 0.0f,-UpMove_Bound,0.0f }, UpTime / 2, UpTime, true);
	}

}