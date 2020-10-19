#include "stdafx.h"
#include "StarMoney.h"


StarMoney::StarMoney()
{
	//初期設定
	m_scale = DefScale;
	m_model.Init(L"Assets/modelData/jewel.cmo");
	m_model_Kirameki.Init(L"Assets/modelData/jewel.cmo");
	m_model_Kirameki.SetRenderMode(RenderMode::Kirameki);
	//きらめき設定
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/jewel_mask.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_kiramekiSRV);
	m_model_Kirameki.SetKirameki(m_kiramekiSRV);

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::ItemObj;

}


StarMoney::~StarMoney()
{
}

void StarMoney::Update() {

	StarMoneyMove();

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model_Kirameki.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//シャドウキャスター
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);	
	ShadowMap::GetInstance()->Update(LightMaker::GetInstance()->GetLightCameraPosition(), 
		LightMaker::GetInstance()->GetLightCameraTarget());

}

void StarMoney::Render() {

	m_model.Draw(g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_model_Kirameki.Draw(g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void StarMoney::StarMoneyMove() {

	//タイマー加算
	m_upDowmTimer += CGameTime::GetFrameDeltaTime();

	//移動処理
	if (m_upDowmFlag == false) {
		m_position.y += UpDownMove;
	}
	else {
		m_position.y -= UpDownMove;
	}

	//リミット
	if (m_upDowmTimer >= UpDownLimit) {
		m_upDowmTimer = 0.0f;
		if (m_upDowmFlag == false) {
			m_upDowmFlag = true;
		}
		else {
			m_upDowmFlag = false;
		}
	}

}