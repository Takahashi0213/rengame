#include "stdafx.h"
#include "StarMoney.h"


StarMoney::StarMoney()
{
	//‰ŠúÝ’è
	m_scale = CVector3{ 10.0f,10.0f,10.0f };
	m_model.Init(L"Assets/modelData/jewel.cmo");
	m_model_Kirameki.Init(L"Assets/modelData/jewel.cmo");
	m_model_Kirameki.SetRenderMode(RenderMode::Kirameki);
	//‚«‚ç‚ß‚«Ý’è
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/jewel_mask.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_kiramekiSRV);
	m_model_Kirameki.SetKirameki(m_kiramekiSRV);


}


StarMoney::~StarMoney()
{
}

void StarMoney::Update() {

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model_Kirameki.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void StarMoney::Render() {

	m_model.Draw(g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_model_Kirameki.Draw(g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}