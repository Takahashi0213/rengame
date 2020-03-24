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
	virtual void CreateCommon(CVector3 pos, CQuaternion rot) = 0;

public:
	/// <summary>
	/// �{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="size">�X�P�[��</param>
	void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);
	/// <summary>
	/// �J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="radius">���a</param>
	/// <param name="height">����</param>
	void CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height);
	/// <summary>
	/// ���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="radius">���a</param>
	void CreateSphere(CVector3 pos, CQuaternion rot, float radius);
protected:
	std::unique_ptr<ICollider> m_collider;	//�R���C�_�[�����
};

