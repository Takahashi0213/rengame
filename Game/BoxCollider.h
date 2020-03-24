/*!
* @brief	ボックスコライダー。
*/

#pragma once

#include "Physics/ICollider.h"

class BoxCollider : public ICollider
{
public:
	BoxCollider();
	/*!
	* @brief	デストラクタ。
	*/
	~BoxCollider();
	/*!
	* @brief	ボックスコライダーを作成。
	*/
	void Create(const CVector3& size);
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
	btBoxShape * shape = nullptr;
	float radius = 0.0f;
	float height = 0.0f;
};

