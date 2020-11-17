#include "stdafx.h"
#include "BackGround.h"
#include "physics/CollisionAttr.h"

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

	auto rb = m_physicsStaticObject.GetRigidBody();
	rb->GetBody()->setUserIndex(enCollisionAttr_MouseHit);
	//�V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

	//�w�i�̓f�B�U�����O����B
	m_model.SetDithering(true);
	//�n�ʂ̓f�B�U�����O���Ȃ��B
	m_model.SetGround_NoDithering(true);

	//Init������I
	m_initFlag = true;

}

void BackGround::Update() {

	if (m_initFlag == false) {
		return;
	}
	
	if (Game::GetInstance() != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
			m_model.SetRenderMode(RenderMode::Monochrome);
			m_sprite->SetRenderMode(Sprite_RenderMode::Sprite_Monochrome);
			m_monochromeFlag = true;
			m_model.SetGround_NoDithering(false);
		}
		else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
			m_model.SetRenderMode(RenderMode::Default);
			m_sprite->SetRenderMode(Sprite_RenderMode::Normal);
			m_monochromeFlag = false;
			m_model.SetGround_NoDithering(true);
		}
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�V���h�E�L���X�^�[��o�^�B
	if (m_shadowCasterFlag == true) {
		ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
		ShadowMap::GetInstance()->Update(m_lightMaker->GetLightCameraPosition(), m_lightMaker->GetLightCameraTarget());
	}

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