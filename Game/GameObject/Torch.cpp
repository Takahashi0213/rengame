#include "stdafx.h"
#include "Torch.h"

namespace {
	const CVector3 PointLightColor = { 8.0f,2.0f,2.0f };	//ポイントライトの色
	const float PointLightRange = 900.0f;					//ポイントライトの有効範囲
	const float YURAGI_RANGE = 50.0f;						//揺らぎ幅。
}
Torch::Torch()
{
	m_model.Init(L"Assets/modelData/Torch.cmo");

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_yuragiSeed = static_cast<float>(rand() % 10);
}


Torch::~Torch()
{
	if (m_fireFlag == true) {
		//エフェクトとポイントライトの削除
		EffekseerSupporter::GetInstance()->EffectDelete(m_Effect);
		LightMaker::GetInstance()->P_LightDelete(m_pointLightNo);
	}
}

void Torch::Update() {

	m_yuragiSeed += 0.2f;

	float range = PointLightRange + sinf(m_yuragiSeed) * YURAGI_RANGE;
	LightMaker::GetInstance()->P_Light_SetRange(m_pointLightNo, range);

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

	//トーチ切り替え
	if (m_actionFlag == true && m_fireFlag == false) {
		//燃やす＆ポイントライト
		CVector3 effectPos = m_position;
		effectPos.y += Y_Hosei;
		effectPos += m_hosei;

		m_Effect = EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::TorchFire ,
			false, effectPos.x, effectPos.y, effectPos.z);
		m_pointLightNo = LightMaker::GetInstance()->GetPointLight_MakeNo();
		LightMaker::GetInstance()->P_LightMake(m_pointLightNo, effectPos, PointLightColor, PointLightRange);
		m_fireFlag = true;
	}
	if (m_actionFlag == false && m_fireFlag == true) {
		//エフェクトとポイントライトの削除
		EffekseerSupporter::GetInstance()->EffectDelete(m_Effect);
		m_Effect = -1;
		LightMaker::GetInstance()->P_LightDelete(m_pointLightNo);
		m_pointLightNo = -1;
		m_fireFlag = false;
	}

}
void Torch::Render() {
	m_model.Draw(g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}