#pragma once
#include "physics/ICollider.h"

/// <summary>
/// 物理オブジェクトのベースクラス
/// </summary>
class PhysicsObjectBase
{
public:
	/// <summary>
	/// ゴーストオブジェクトを解放
	/// </summary>
	virtual void Release() = 0;
private:
	/// <summary>
	/// 共通処理
	/// </summary>
	virtual void CreateCommon(const CVector3& pos, const CQuaternion& rot, const float& mass) = 0;

public:
	/// <summary>
	/// ボックス形状のゴーストオブジェクトを作成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="size">スケール</param>
	void CreateBox(const CVector3& pos, const CQuaternion& rot, 
		const CVector3& size, const float& mass = 0.0f);
	/// <summary>
	/// カプセル形状のゴーストオブジェクトを作成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="radius">半径</param>
	/// <param name="height">高さ</param>
	void CreateCapsule(const CVector3& pos, const CQuaternion& rot,
		const float& radius, const float& height, const float mass = 0.0f);
	/// <summary>
	/// 球体形状のゴーストオブジェクトを作成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="radius">半径</param>
	void CreateSphere(const CVector3& pos, const CQuaternion& rot,
		const float& radius, const float& mass = 0.0f);
protected:
	std::unique_ptr<ICollider> m_collider;	//コライダーちゃん
};

