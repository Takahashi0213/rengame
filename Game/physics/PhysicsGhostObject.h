#pragma once
#include "PhysicsObjectBase.h"

/// <summary>
/// �S�[�X�g�I�u�W�F�N�g
/// </summary>
class PhysicsGhostObject : public PhysicsObjectBase
{
public:
	~PhysicsGhostObject()
	{
		Release();
	}
	void Release() override final;
	/// <summary>
	/// �����œn���ꂽ�I�u�W�F�N�g���������g������
	/// </summary>
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	void SetPosition(const CVector3& pos)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		pos.CopyTo(btPos);
		btTrans.setOrigin(btPos);
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	void SetRotation(const CQuaternion& rot)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btQuaternion btRot;
		rot.CopyTo(btRot);
		btTrans.setRotation(btRot);
	}

	int GetUserIndex() {
		return m_ghostObject.getUserIndex();
	}

private:
	/// <summary>
	/// �S�[�X�g�쐬���̋��ʏ���
	/// </summary>
	void CreateCommon(const CVector3& pos, const CQuaternion& rot, const float& mass = 0.0f) override;
private:
	bool						m_isRegistPhysicsWorld = false;	//!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	btGhostObject				m_ghostObject;	//!<�S�[�X�g
};

