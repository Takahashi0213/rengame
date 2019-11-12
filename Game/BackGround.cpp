#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	m_model.Init(L"Assets/modelData/map.cmo");
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	//PhysicsStaticObject‚Ì‰Šú‰»
	m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation);

}


BackGround::~BackGround()
{
}

void BackGround::Update() {

	if (m_game != nullptr) {
		if (m_game->GetGameMode() == Game::CreateMode && m_monochromeFlag == false) {
			m_model.SetRenderMode(RenderMode::Monochrome);
			m_monochromeFlag = true;
		}
		else if (m_game->GetGameMode() != Game::CreateMode && m_monochromeFlag == true) {
			m_model.SetRenderMode(RenderMode::Default);
			m_monochromeFlag = false;
		}
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void BackGround::Render() {
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}