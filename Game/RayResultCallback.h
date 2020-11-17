#pragma once
#include "stdafx.h"
#include "physics/CollisionAttr.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

//マウス移動での地面とのコリジョン処理のコールバック関数オブジェクト
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
		//衝突した面の法線と上方向との内積を計算する。
		float angle = fabs(acos(rayResult.m_hitNormalLocal.y()));
		if (angle > CMath::DegToRad(10.0f)) {
			return 0.0f;
		}

		//
		return btCollisionWorld::ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
	}
};
