#include "stdafx.h"
#include "Player.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

int a = Hash::MakeHash("Player");

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_model_Sl.Init(L"Assets/modelData/unityChan.cmo");
	//m_model.SetEmissionColor({ 100.0f,1.0f,1.0f });
	m_model_Sl.SetRenderMode(RenderMode::Silhouette);

	//���[���h�s��̍X�V�B
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_nextPos = m_position;		//�ړ����������

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(25, 30, m_position);

	//���C�g���[�J�[�̎擾
	int a = Hash::MakeHash("LightMaker");
	m_lightMaker = CGameObjectManager::GetInstance()->FindGO<LightMaker>(a);

	//�V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

	//�j�Z�v���C���[�̍쐬
	SkinModelRender* smr = NewGO<SkinModelRender>("Player2", 0);
	smr->Model_Init(L"Assets/modelData/unityChan.cmo");
	smr->SetPosition({ 100.0f,50.0f,100.0f });

	//�X�v���C�g�}�X�N�̃e�X�g

	//MainSprite->ChangeMaskSprite();
	//MainSprite->Init(L"Assets/sprite/keis.dds", 588.0f, 1240.0f, 0);
	//MainSprite->SetPosition({ 250.0f,-250.0f ,1.0f });
	//MainSprite->InitSub(L"Assets/sprite/fukidasi.dds", 600.0f, 400.0f, 0);
	//MainSprite->SetPosition({ 250.0f,-50.0f ,0.0f }, true);

	//SpriteRender* test = NewGO<SpriteRender>("TESTSPRITE", 0);
	//test->Init(L"Assets/sprite/levelUp_8F.dds", 450.0f, 2000.0f, 0);
	//test->SetHighPattern(8, 0);
	//test->m_spriteSupporter.SpritePattern(1, false, 6);

}

Player::~Player()
{

}

void Player::Update()
{
	hoge = 10;
	if (hoge == 0) {
		GameEffect::GetInstance()->EasyEffect(L"�v��\R����\D�΂��\n�₯�ǁ`",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
		hoge++;
	}
	if (hoge == 2) {
		GameEffect::GetInstance()->EasyEffect(L"�����������V�C", GameEffect_Stand::Stand_Happy);
		hoge++;
	}
	if (hoge == 4) {
		GameEffect::GetInstance()->EasyEffect(L"���ѐH���Ă�\n����܂���",
			GameEffect_Stand::Stand_Sad,
			GameEffect_Stand::Shake_Stand);
		hoge++;
	}	
	if (hoge == 6) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::Jump_Stand);
		GameEffect::GetInstance()->GetInstance_Message()->MessageEffect(L"�΂��₪����");
		hoge++;
	}
	if (hoge == 8) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		hoge++;
	}
	if (GameEffect::GetInstance()->GetInstance_Message()->GetMessageOkuriFlag() == true) {
		hoge++;
	}

	//if (g_pad[0].IsTrigger(enButtonA)) {
	//	CGameObjectManager::GetInstance()->DeleteGO(this);
	//}
	//if (g_pad[0].IsTrigger(enButtonB)) {
	//	int s = CGameObjectManager::GetInstance()->ObjCount<Player>(a);
	//	Player* p = CGameObjectManager::GetInstance()->FindGO<Player>(a,false);
	//}

	//���m�N���ɂȁ[��
	if (m_gameObj != nullptr) {
		if (m_gameObj->GetGameMode() == Game::CreateMode && m_monochromeFlag == false) {
			m_model.SetRenderMode(RenderMode::Monochrome);
			m_monochromeFlag = true;
		}
		else if (m_gameObj->GetGameMode() != Game::CreateMode && m_monochromeFlag == true) {
			m_model.SetRenderMode(RenderMode::Default);
			m_monochromeFlag = false;
		}
	}

	Move();

	bool OnG_Flag = m_charaCon.IsOnGround();

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (m_jumpNow == false && OnG_Flag == true) {
			Jump();
		}
		m_jumpNow = true;
	}
	else {
		m_jumpNow = false;
	}

	//���[���h�s��̍X�V�B
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	if (m_gameObj->GetGameMode() == Game::ActionMode){ //�A�N�V�������[�h�łȂ���΍X�V���Ȃ��I

		//�d��
		m_moveSpeed.y -= m_gravity;
		//�L�����R���ړ�
		m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	}

	//�V���h�E�L���X�^�[��o�^�B
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
	ShadowMap::GetInstance()->Update(m_lightMaker->GetLightCameraPosition(), m_lightMaker->GetLightCameraTarget());

	//���C�g�J�������X�V
	CVector3 LC_Pos = LightMaker::GetInstance()->GetLightCameraPosition();
	LC_Pos = m_position;
	LC_Pos.y += 1000.0f;
	LightMaker::GetInstance()->SetLightCameraPosition(LC_Pos);
	//�^�[�Q�b�g���I
	LC_Pos = LightMaker::GetInstance()->GetLightCameraTarget();
	LC_Pos = m_position;
	LightMaker::GetInstance()->SetLightCameraTarget(LC_Pos);
}

void Player::Render()
{
	m_model_Sl.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Move() {

	//���N���b�N�̏�Ԃ𔻒�
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	bool OnG_Flag = m_charaCon.IsOnGround();

	if (key == MouseSupporter::Release_Push && m_gameObj->GetGameMode() == Game::ActionMode) {
		if (MouseSupporter::GetInstance()->GetMouseTimer(MouseSupporter::Left_Key) < 12) {

			m_nextPos = MouseSupporter::GetInstance()->GetMousePos_3D();

			//btCollisionWorld::ClosestRayResultCallback ResultCallback();
			btDiscreteDynamicsWorld* dw = g_physics.GetDynamicWorld();
			btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_nextPos);
			dw->rayTest((btVector3)g_camera3D.GetPosition(), m_nextPos, CRR_Callback);
			if (CRR_Callback.hasHit()) {
				m_nextPos = CRR_Callback.m_hitPointWorld;
			}
			else {
				m_nextPos = m_position;
			}

		}
	}

	m_nextPos.y = m_position.y;

	m_moveSpeed.x = m_nextPos.x - m_position.x;
	m_moveSpeed.z = m_nextPos.z - m_position.z;
	m_moveSpeed.x /= 20.0f;
	m_moveSpeed.z /= 20.0f;

	if (m_moveSpeed.x > m_moveMax) {
		m_moveSpeed.x = m_moveMax;
	}
	if (m_moveSpeed.x < -m_moveMax) {
		m_moveSpeed.x = -m_moveMax;
	}
	if (m_moveSpeed.z > m_moveMax) {
		m_moveSpeed.z = m_moveMax;
	}
	if (m_moveSpeed.z < -m_moveMax) {
		m_moveSpeed.z = -m_moveMax;
	}

	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3().AxisY(), angle);

}

void Player::Jump() {
	
	m_moveSpeed.y = m_jumpPower;

}