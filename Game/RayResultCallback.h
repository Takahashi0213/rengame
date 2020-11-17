#pragma once
#include "stdafx.h"
#include "physics/CollisionAttr.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

//�}�E�X�ړ��ł̒n�ʂƂ̃R���W���������̃R�[���o�b�N�֐��I�u�W�F�N�g
class MouseMoveHitCallback : public btCollisionWorld::ClosestRayResultCallback
{
public:
	MouseMoveHitCallback(const btVector3&	rayFromWorld, const btVector3&	rayToWorld) :
		btCollisionWorld::ClosestRayResultCallback(rayFromWorld, rayToWorld) {}

	btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
	{
		if (rayResult.m_collisionObject->getUserIndex() != enCollisionAttr_MouseHit) {
			return 0.0f;
		}
		//�Փ˂����ʂ̖@���Ə�����Ƃ̓��ς��v�Z����B
		float angle = fabs(acos(rayResult.m_hitNormalLocal.y()));
		if (angle > CMath::DegToRad(10.0f)) {
			return 0.0f;
		}

		//
		return btCollisionWorld::ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
	}
};
