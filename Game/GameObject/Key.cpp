#include "stdafx.h"
#include "Key.h"


Key::Key()
{
}

Key::~Key()
{
	DeleteGO(m_skinModelRender);
}

void Key::DataSet() {

	m_scale.Set(DefScale, DefScale, DefScale);

	m_skinModelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Key", 1);
	m_skinModelRender->Model_Init(Game::GetInstance()->GetItemSave()->GetItemData()->GameItem[m_itemNo].Item_FilaPath_Model);
	m_position.y -= 450.0f;
	m_skinModelRender->SetUp(m_position, m_rotation, m_scale);
	//������]
	m_skinModelRender->m_skinModelSupporter.SkinModelRotation(AutoRotation, CVector3::AxisY(), 1, 0, true);

	m_setFlag = true;
}

void Key::Update() {

	//�A�N�V�����t���O��true�Ȃ献��`�悷��
	if (m_actionFlag == true && m_drawFlag == false) {
		m_drawFlag = true;
	}
	m_skinModelRender->SetActiveFlag(m_drawFlag);

	//�X�|�[��
	if (m_actionFlag_2 == true && m_spawnFlag == false) {
		KeySpawn();
		m_spawnFlag = true;
	}
	//�t���O�X�V
	UpdateActionFlag();

}

void Key::Render() {

}

void Key::KeySpawn() {

	m_skinModelRender->m_skinModelSupporter.SkinModelMove({ 0.0f,560.0f,0.0f }, 20, 0, true);
	m_skinModelRender->m_skinModelSupporter.SkinModelMove({ 0.0f,-100.0f,0.0f }, 10, 20, true);

}