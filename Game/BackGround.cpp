#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	m_model.Init(L"Assets/modelData/map.cmo");
	m_model.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

	//PhysicsStaticObjectの初期化
	m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation);

	//ライトメーカーの取得
	int a = Hash::MakeHash("LightMaker");
	m_lightMaker = CGameObjectManager::GetInstance()->FindGO<LightMaker>(a);

	//シャドウレシーバーにする。
	m_model.SetShadowReciever(true);

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

	//シャドウキャスターを登録。
	//ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
	//ShadowMap::GetInstance()->Update(m_lightMaker->GetLightCameraPosition(), m_lightMaker->GetLightCameraTarget());

}

void BackGround::Render() {
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}