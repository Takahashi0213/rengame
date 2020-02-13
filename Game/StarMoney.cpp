#include "stdafx.h"
#include "StarMoney.h"


StarMoney::StarMoney()
{
	//èâä˙ê›íË
	m_model.Init(L"Assets/modelData/jewel.cmo");
	m_model_Kirameki.Init(L"Assets/modelData/jewel.cmo");
	m_model_Kirameki.SetRenderMode(RenderMode::Kirameki);

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