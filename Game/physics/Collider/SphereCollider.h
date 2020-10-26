/*!
* @brief	�X�t�B�A�R���C�_�[�B
*/

#pragma once

#include "physics/Collider/ICollider.h"

class SphereCollider : public ICollider
{
public:
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	SphereCollider();
	~SphereCollider();
	/*!
	* @brief	�X�t�B�A�R���C�_�[���쐬�B
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

