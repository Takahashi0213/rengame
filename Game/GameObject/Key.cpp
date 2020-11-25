#include "stdafx.h"
#include "Key.h"


Key::Key()
{
	//�擾�͈͂�ݒ�
	ItemGetRange = GetRange;
}

Key::~Key()
{
	DeleteGO(m_modelRender);
}

void Key::DataSet() {

	//����ς݂Ȃ�J�b�g
	if (SceneManager::GetInstance()->GetItemSave()->GetItemGetFlag(m_itemNo) == true) {
		return;
	}

	//�l�X�ȕ␳
	m_scale.Set(DefScale, DefScale, DefScale);
	m_drawFlag = true;
	if (SceneManager::GetInstance()->GetItemSave()->GetItemData()->ItemNoSearch(L"�����̌�") == m_itemNo &&
		SceneManager::GetInstance()->GetGameEvent()->GetEventSave()->m_eventFlag[3] == false) {
		m_position.y -= DownHosei;
		m_moveFlag = true;
		m_drawFlag = false;
	}
	//����
	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Key", 1);
	m_modelRender->Model_Init(SceneManager::GetInstance()->GetItemSave()->GetItemData()->GameItem[m_itemNo].Item_FilaPath_Model);
	m_modelRender->SetUp(m_position, m_rotation, m_scale);
	//������]
	m_modelRender->m_skinModelSupporter.SkinModelRotation(AutoRotation, CVector3::AxisY(), 1, 0, true);

	m_setFlag = true;
}

void Key::Update() {

	//����ς݂Ȃ�J�b�g
	if (SceneManager::GetInstance()->GetItemSave()->GetItemGetFlag(m_itemNo) == true) {
		return;
	}

	//���m�N���ɂȂ�
	if (Game::GetInstance() != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
			m_modelRender->GetModel()->SetRenderMode(RenderMode::Monochrome);
			//������]��~
			m_modelRender->m_skinModelSupporter.SkinModelRotation(0.0f, CVector3::Zero(), 0, 0);
			m_monochromeFlag = true;
		}
		else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
			m_modelRender->GetModel()->SetRenderMode(RenderMode::Default);
			//������]
			m_modelRender->m_skinModelSupporter.SkinModelRotation(AutoRotation, CVector3::AxisY(), 1, 0, true);
			m_monochromeFlag = false;
		}
	}

	//�A�N�V�����t���O��true�Ȃ献��`�悷��
	if (m_actionFlag == true && m_drawFlag == false) {
		m_drawFlag = true;
	}
	m_modelRender->SetActiveFlag(m_drawFlag);

	//�X�|�[��
	if (m_actionFlag_2 == true && m_spawnFlag == false) {
		KeySpawn();
		m_spawnFlag = true;
	}

	//�擾�`�F�b�N
	if (ItemGetCheck() == true) {
		//�A�C�e���Q�b�g�i���o�A���j
		Game::GetInstance()->GetItemGet()->ItemGetEffect(m_itemNo);
		//�폜
		DeleteGO(this);
	}

	//���W�X�V
	m_position = m_modelRender->GetPosition();
	//�t���O�X�V
	UpdateActionFlag();

}

void Key::Render() {

}

void Key::KeySpawn() {

	//������ɏグ��
	if (m_moveFlag == true) {
		m_modelRender->m_skinModelSupporter.SkinModelMove({ 0.0f,UpMove,0.0f }, UpTime, 0, true);
		m_modelRender->m_skinModelSupporter.SkinModelMove({ 0.0f,-UpMove_Bound,0.0f }, UpTime / 2, UpTime, true);
	}

}