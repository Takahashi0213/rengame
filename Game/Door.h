#pragma once
#include "system/CGameObjectManager.h"
#include "SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// 信号を受け取って上下移動する扉
/// </summary>
class Door : public IGameObject, public ObjectClass
{
public:
	Door();
	~Door();
	void Update()override;
	void Render()override;

	//フラグ操作
	void SetFlag(bool flag) {
		m_upDownFlag = flag;
	}
	bool GetFlag() {
		return m_upDownFlag;
	}

	//リンクオブジェクトの設定
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt = linkObj;
	}

private:
	SkinModel m_model;	//スイッチの土台もで～～る

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

	bool m_upDownFlag = false;		//上下状態 faise=降下 true=上昇
	ObjectClass* m_LinkPt;

};

