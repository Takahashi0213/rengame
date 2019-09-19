#include "stdafx.h"
#include "Player.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

int a = Hash::MakeHash("Player");

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_model.SetEmissionColor({ 100.0f,1.0f,1.0f });
	m_model2.Init(L"Assets/modelData/map.cmo");

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model2.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

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

	CVector2 a = MouseSupporter::GetInstance()->GetMousePos();
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);

	if (key == MouseSupporter::Release_Push) {
		if (MouseSupporter::GetInstance()->GetMouseTimer(MouseSupporter::Left_Key) < 12) {
			m_nextPos = MouseSupporter::GetInstance()->GetMousePos_3D();
			//m_nextPos.y = m_position.y;

			btCollisionWorld::ClosestRayResultCallback ResultCallback();
			btDiscreteDynamicsWorld* dw = g_physics.GetDynamicWorld();
			btCollisionWorld::ClosestRayResultCallback CRR_Callback(m_position, m_nextPos);
			dw->rayTest((btVector3)m_position, m_nextPos, CRR_Callback);
			//m_nextPos = CRR_Callback.m_hitPointWorld;

		}
	}

	CVector3 vec = m_nextPos - m_position;
	vec /= 20.0f;
	m_position += vec;

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model2.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());

}

void Player::Render()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	m_model2.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Move() {


}