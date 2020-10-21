/*!
 * @brief	静的オブジェクト。
 */


#include "stdafx.h"
#include "physics/PhysicsStaticObject.h"
using namespace std;

PhysicsStaticObject::PhysicsStaticObject()
{
}
void PhysicsStaticObject::Release()
{
	g_physics->RemoveRigidBody(m_rigidBody);
}
void PhysicsStaticObject::CreateCommon(CVector3 pos, CQuaternion rot)
{
	RigidBodyInfo rbInfo;
	rbInfo.collider = m_collider.get();
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create(rbInfo);
	g_physics->AddRigidBody(m_rigidBody);
}

void PhysicsStaticObject::CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot)
{
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(skinModel, nullptr);
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加する。
	g_physics->AddRigidBody(m_rigidBody);

	m_rigidFlag = true;
}

void PhysicsStaticObject::CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot, CVector3 scl) {

	
	//メッシュコライダーを作成。
	CMatrix mScale;
	mScale.MakeScaling(scl);
	//m_meshCollider.CreateFromSkinModel(skinModel, nullptr, mScale, false);
	m_meshCollider.CreateFromSkinModel(skinModel, &mScale);
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create(rbInfo);
	//剛体を物理ワールドに追加する。
	g_physics->AddRigidBody(m_rigidBody);
	

	m_rigidFlag = true;

	//Release();
	//CMatrix mScale;
	//mScale.MakeScaling(scl);
	//auto meshCollider = make_unique<MeshCollider>();
	//meshCollider->CreateFromSkinModel(skinModel, &mScale);
	//m_collider = move(meshCollider);
	//CreateCommon(
	//	pos,
	//	rot
	//);


}