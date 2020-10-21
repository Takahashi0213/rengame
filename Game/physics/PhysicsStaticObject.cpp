/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
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
	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(skinModel, nullptr);
	//���̂��쐬�A
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //���̂Ɍ`��(�R���C�_�[)��ݒ肷��B
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create(rbInfo);
	//���̂𕨗����[���h�ɒǉ�����B
	g_physics->AddRigidBody(m_rigidBody);

	m_rigidFlag = true;
}

void PhysicsStaticObject::CreateMeshObject(SkinModel& skinModel, CVector3 pos, CQuaternion rot, CVector3 scl) {

	
	//���b�V���R���C�_�[���쐬�B
	CMatrix mScale;
	mScale.MakeScaling(scl);
	//m_meshCollider.CreateFromSkinModel(skinModel, nullptr, mScale, false);
	m_meshCollider.CreateFromSkinModel(skinModel, &mScale);
	//���̂��쐬�A
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //���̂Ɍ`��(�R���C�_�[)��ݒ肷��B
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create(rbInfo);
	//���̂𕨗����[���h�ɒǉ�����B
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