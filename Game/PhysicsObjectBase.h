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
	virtual void CreateCommon(CVector3 pos, CQuaternion rot) = 0;

public:
	/// <summary>
	/// ボックス形状のゴーストオブジェクトを作成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="size">スケール</param>
	void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);
	/// <summary>
	/// カプセル形状のゴーストオブジェクトを作成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="radius">半径</param>
	/// <param name="height">高さ</param>
	void CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height);
	/// <summary>
	/// 球体形状のゴーストオブジェクトを作成
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="radius">半径</param>
	void CreateSphere(CVector3 pos, CQuaternion rot, float radius);
protected:
	std::unique_ptr<ICollider> m_collider;	//コライダーちゃん
};

