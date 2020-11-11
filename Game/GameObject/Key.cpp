#include "stdafx.h"
#include "Key.h"


Key::Key()
{
}

Key::~Key()
{
}

void Key::DataSet() {

	m_scale.Set(DefScale, DefScale, DefScale);

	m_skinModelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Key", 1);
	m_skinModelRender->Model_Init(Game::GetInstance()->GetItemSave()->GetItemData()->GameItem[m_itemNo].Item_FilaPath_Model);
	m_skinModelRender->SetUp(m_position, m_rotation, m_scale);

	m_setFlag = true;
}

void Key::Update() {

}

void Key::Render() {

}