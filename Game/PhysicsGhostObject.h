#pragma once
#include "PhysicsObjectBase.h"

/// <summary>
/// ゴーストオブジェクト
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
	/// 引数で渡されたオブジェクトが自分自身か判定
	/// </summary>
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	/// <summary>
	/// 座標を設定
	/// </summary>
	void SetPosition(const CVector3& pos)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		pos.CopyTo(btPos);
		btTrans.setOrigin(btPos);
	}
	/// <summary>
	/// 回転を設定
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
	/// ゴースト作成時の共通処理
	/// </summary>
	void CreateCommon(const CVector3& pos, const CQuaternion& rot, const float& mass = 0.0f) override;
private:
	bool						m_isRegistPhysicsWorld = false;	//!<物理ワールドに登録しているかどうかのフラグ。
	btGhostObject				m_ghostObject;	//!<ゴースト
};

