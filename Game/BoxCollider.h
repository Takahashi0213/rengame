/*!
* @brief	�{�b�N�X�R���C�_�[�B
*/

#pragma once

#include "Physics/ICollider.h"

class BoxCollider : public ICollider
{
public:
	BoxCollider();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~BoxCollider();
	/*!
	* @brief	�{�b�N�X�R���C�_�[���쐬�B
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

