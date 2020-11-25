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
	enum DoorModel {
		Model_BigDoor,
		Model_BigDoor2,
		Model_BigDoorNum,
	};

	/// <summary>
	/// モデルの種類を設定
	/// 内容は同じだけど見た目が違うドアがたくさんあるので
	/// </summary>
	/// <param name="model">モデルの種類</param>
	void ModelChange(const DoorModel model);

	/// <summary>
	/// 鍵のアイテム番号を設定
	/// </summary>
	void SetItemNo(const int& no) {
		m_itemNo = no;
	}

private:
	void DoorOpen();

	SkinModelRender * m_model = nullptr;			//土台モデル

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト
	DoorModel m_thisModel;							//モデルの種類
	Player* m_pl = nullptr;							//プレイヤー

	int m_itemNo = -1;								//対応アイテム番号
	bool m_doorOpenFlag = false;					//ドア開きフラグ

	//DoorModelに対応したモデルの種類
	const wchar_t* ModelNames[Model_BigDoorNum] = {
		L"Assets/modelData/BigDoor.cmo",
		L"Assets/modelData/BigDoor_.cmo"
	};

	//定数
	const CVector3 StaticSize = { 250.0f,300.0f,20.0f };	//扉の当たり判定サイズ
	const float StaticY_Hosei = 100.0f;						//当たり判定が埋まるので上に補正する
	const float OpenRange = 700.0f;							//取得できる範囲

};

