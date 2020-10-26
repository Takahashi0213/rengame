#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	m_model.Init(L"Assets/modelData/Board.cmo");

	//�^�O�ݒ�
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}


Board::~Board()
{
}

void Board::Update() {

	//���m�N����
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_model.SetRenderMode(RenderMode::Monochrome);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_model.SetRenderMode(RenderMode::Default);
		m_monochromeFlag = false;
	}
	//�N���G�C�g���[�h���͈�؂̍X�V�����Ȃ�
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode) {
		return;
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�V���h�E�L���X�^�[
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
	ShadowMap::GetInstance()->Update(LightMaker::GetInstance()->GetLightCameraPosition(),
		LightMaker::GetInstance()->GetLightCameraTarget());

}

void Board::Render() {

	m_model.Draw(g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}
