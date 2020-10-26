#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	m_model.Init(L"Assets/modelData/Board.cmo");

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}


Board::~Board()
{
}

void Board::Update() {

	//モノクロ化
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_model.SetRenderMode(RenderMode::Monochrome);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_model.SetRenderMode(RenderMode::Default);
		m_monochromeFlag = false;
	}
	//クリエイトモード中は一切の更新をしない
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode) {
		return;
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//シャドウキャスター
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
	ShadowMap::GetInstance()->Update(LightMaker::GetInstance()->GetLightCameraPosition(),
		LightMaker::GetInstance()->GetLightCameraTarget());

}

void Board::Render() {

	m_model.Draw(g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}
