#include "stdafx.h"
#include "StarMoney.h"
#include "GameSystem/GameUI/GameStatusUI.h"

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

	//プレイヤーの検索
	m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::ItemObj;

}


StarMoney::~StarMoney()
{
}

void StarMoney::Update() {

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

	StarMoneyMove();

	//取得チェック
	float length = (m_position - m_pl->GetPosition()).Length();
	if (length < GetRange) {
		//取得する
		GameStatus_UISystem::GetInstance()->AddStarMoney(GetStarMoney);
		//SE
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/StarMoney.wav");
		DeleteGO(this);
	}

	//更新
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