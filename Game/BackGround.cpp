#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	//���C�g���[�J�[�̎擾
	int a = Hash::MakeHash("LightMaker");
	m_lightMaker = CGameObjectManager::GetInstance()->FindGO<LightMaker>(a);

	m_sprite = NewGO<SpriteRender>("Sky", 0);
	m_sprite->Init(L"Assets/sprite/Sky.dds", 1280.0f, 855.0f, 0);
	m_sprite->SetObjectTag(objectTag::t_BackSprite);
	m_sprite->SetPosition(CVector3::Zero());
}

BackGround::~BackGround()
{
	DeleteGO(m_sprite);
}

void BackGround::Init(const wchar_t* filePath) {

	m_model.Init(filePath);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//PhysicsStaticObject�̏�����
	m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation, m_scale);

	//�V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

	//Init������I
	m_initFlag = true;
}

void BackGround::Update() {

	if (m_initFlag == false) {
		return;
	}
	
	if (m_game != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
			m_model.SetRenderMode(RenderMode::Monochrome);
			m_monochromeFlag = true;
		}
		else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
			m_model.SetRenderMode(RenderMode::Default);
			m_monochromeFlag = false;
		}
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�V���h�E�L���X�^�[��o�^�B
	//ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
	//ShadowMap::GetInstance()->Update(m_lightMaker->GetLightCameraPosition(), m_lightMaker->GetLightCameraTarget());

}

void BackGround::Render() {

	if (m_initFlag == false) {
		return;
	}

	//�`��
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}