#pragma once
#include "physics/ICollider.h"

/// <summary>
/// �����I�u�W�F�N�g�̃x�[�X�N���X
/// </summary>
class PhysicsObjectBase
{
public:
	/// <summary>
	/// �S�[�X�g�I�u�W�F�N�g�����
	/// </summary>
	virtual void Release() = 0;
private:
	/// <summary>
	/// ���ʏ���
	/// </summary>
	virtual void CreateCommon(const CVector3& pos, const CQuaternion& rot, const float& mass) = 0;

public:
	/// <summary>
	/// �{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="size">�X�P�[��</param>
	void CreateBox(const CVector3& pos, const CQuaternion& rot, 
		const CVector3& size, const float& mass = 0.0f);
	/// <summary>
	/// �J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="radius">���a</param>
	/// <param name="height">����</param>
	void CreateCapsule(const CVector3& pos, const CQuaternion& rot,
		const float& radius, const float& height, const float mass = 0.0f);
	/// <summary>
	/// ���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="radius">���a</param>
	void CreateSphere(const CVector3& pos, const CQuaternion& rot,
		const float& radius, const float& mass = 0.0f);
protected:
	std::unique_ptr<ICollider> m_collider;	//�R���C�_�[�����
};

