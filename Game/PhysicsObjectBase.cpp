#include "stdafx.h"
#include "PhysicsObjectBase.h"

#include "physics/CapsuleCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

using namespace std;

void PhysicsObjectBase::CreateBox(const CVector3& pos, const CQuaternion& rot,
	const CVector3& size, const float& mass)
{
	Release();
	auto boxCollider = make_unique<BoxCollider>();
	boxCollider->Create(size);
	m_collider = move(boxCollider);
	CreateCommon(pos, rot,mass);
}
void PhysicsObjectBase::CreateCapsule(const CVector3& pos, const CQuaternion& rot,
	const float& radius, const float& height, const float mass)
{
	Release();
	auto capusuleCollider = make_unique<CapsuleCollider>();
	capusuleCollider->Create(radius, height);
	m_collider = move(capusuleCollider);
	CreateCommon(pos, rot, mass);
}

void PhysicsObjectBase::CreateSphere(const CVector3& pos, const CQuaternion& rot, 
	const float& radius, const float& mass)
{
	Release();
	auto sphereCollider = make_unique<SphereCollider>();
	sphereCollider->Create(radius);
	m_collider = move(sphereCollider);
	CreateCommon(pos, rot, mass);
}

