#include "stdafx.h"
#include "StarMoney.h"
#include "GameSystem/GameUI/GameStatusUI.h"

StarMoney::StarMoney()
{
	//�����ݒ�
	m_scale = DefScale;
	m_model.Init(L"Assets/modelData/jewel.cmo");
	m_model_Kirameki.Init(L"Assets/modelData/jewel.cmo");
	m_model_Kirameki.SetRenderMode(RenderMode::Kirameki);
	//����߂��ݒ�
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/jewel_mask.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_kiramekiSRV);
	m_model_Kirameki.SetKirameki(m_kiramekiSRV);

	//�v���C���[�̌���
	m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	//�^�O�ݒ�
	m_object = ObjectClass::ObjectClass_Tag::ItemObj;

}


StarMoney::~StarMoney()
{
}

void StarMoney::Update() {

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

	StarMoneyMove();

	//�擾�`�F�b�N
	float length = (m_position - m_pl->GetPosition()).Length();
	if (length < GetRange) {
		//�擾����
		GameStatus_UISystem::GetInstance()->AddStarMoney(GetStarMoney);
		//SE
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/StarMoney.wav");
		DeleteGO(this);
	}

	//�X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model_Kirameki.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�V���h�E�L���X�^�[
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

	//�^�C�}�[���Z
	m_upDowmTimer += CGameTime::GetFrameDeltaTime();

	//�ړ�����
	if (m_upDowmFlag == false) {
		m_position.y += UpDownMove;
	}
	else {
		m_position.y -= UpDownMove;
	}

	//���~�b�g
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