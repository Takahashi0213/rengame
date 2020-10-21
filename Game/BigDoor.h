#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

class BigDoor : public ObjectClass
{
public:
	BigDoor();
	~BigDoor();
	void Update()override;
	void Render()override;

	//モデルの種類
	enum BoxModel {
		Model_BigDoor,
		Model_BigDoor2,
		Model_BigDoorNum,
	};

	/// <summary>
	/// モデルの種類を設定
	/// 内容は同じだけど見た目が違うドアがたくさんあるので
	/// </summary>
	/// <param name="model">モデルの種類</param>
	void ModelChange(const BoxModel model);

private:
	SkinModelRender * m_model = nullptr;			//土台もで～～る

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

	//定数
	const CVector3 StaticSize = { 250.0f,300.0f,20.0f };	//扉の当たり判定サイズ
	const float StaticY_Hosei = 100.0f;						//当たり判定が埋まるので上に補正するs

};

