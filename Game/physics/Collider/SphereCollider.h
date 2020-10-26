/*!
* @brief	スフィアコライダー。
*/

#pragma once

#include "physics/Collider/ICollider.h"

class SphereCollider : public ICollider
{
public:
	/*!
	* @brief	デストラクタ。
	*/
	SphereCollider();
	~SphereCollider();
	/*!
	* @brief	スフィアコライダーを作成。
	*/
	void Create(const float radius);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
	float GetRadius() const
	{
		return radius;
	}
	float GetHeight() const
	{
		return height;
	}
private:
	btSphereShape * shape = nullptr;
	float radius = 0.0f;
	float height = 0.0f;
};

