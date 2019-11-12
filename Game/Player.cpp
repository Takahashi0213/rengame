#include "stdafx.h"
#include "Player.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

int a = Hash::MakeHash("Player");

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_model_Sl.Init(L"Assets/modelData/unityChan.cmo");
	//m_model.SetEmissionColor({ 100.0f,1.0f,1.0f });
	m_model_Sl.SetRenderMode(RenderMode::Silhouette);

	//ワールド行列の更新。
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	SpriteRender* r = NewGO<SpriteRender>("Obj");
	r->Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f, { -100.0f, -100.0f,0.0f });
	//r->SetPosition({ -100.0f, -100.0f,0.0f });
	r->m_spriteSupporter.SpriteMove({ 500.0f,500.0f }, 60, 60);
	r->m_spriteSupporter.SpriteMove({ -500.0f,50.0f }, 60, 120);
	r->m_spriteSupporter.SpriteMove({ 1000.0f,0.0f }, 60, 180);
	m_nextPos = m_position;

	r->m_spriteSupporter.SpriteRotation(20.0f, 60, 60, true);
	r->m_spriteSupporter.SpriteScale({ 0.5f,0.5f,0.5f }, 60, 60);
	r->m_spriteSupporter.SpriteColor({ 1.0f,0.5f,0.5f,0.5f }, 180, 60);

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(25, 30, m_position);

}


Player::~Player()
{

}

void Player::Update()
{
	//if (g_pad[0].IsTrigger(enButtonA)) {
	//	CGameObjectManager::GetInstance()->DeleteGO(this);
	//}
	//if (g_pad[0].IsTrigger(enButtonB)) {
	//	int s = CGameObjectManager::GetInstance()->ObjCount<Player>(a);
	//	Player* p = CGameObjectManager::GetInstance()->FindGO<Player>(a,false);
	//}

	//CVector2 a = MouseSupporter::GetInstance()->GetMousePos();

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

	//ワールド行列の更新。
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	if (m_gameObj->GetGameMode() == Game::ActionMode){ //アクションモードでなければ更新しない！

		//重力
		m_moveSpeed.y -= m_gravity;
		//キャラコン移動
		m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	}

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

	//左クリックの状態を判定
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	bool OnG_Flag = m_charaCon.IsOnGround();

	if (key == MouseSupporter::Release_Push && OnG_Flag == true && m_gameObj->GetGameMode() == Game::ActionMode) {
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

	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3().AxisY(), angle);

}

void Player::Jump() {
	
	m_moveSpeed.y = m_jumpPower;

}