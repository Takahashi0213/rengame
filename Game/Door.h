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

	//リンクオブジェクトの設定
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_setNom++;
	}

	SkinModelRender* GetSkinModelRender() {
		return m_model;
	}

private:
	//アクションフラグの変更
	void UpdateActionFlag() {
		bool CheckFlag = true;		//通過確認

		for (int i = 0; i < 10; i++) {
			if (m_LinkPt[i] != nullptr && m_LinkPt[i]->m_actionFlag == false) {
				CheckFlag = false;
			}
		}

		m_actionFlag = CheckFlag;
	}
	SkinModelRender* m_model;	//スイッチの土台もで～～る

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

	void DoorUpDowmUpdate();	//ドアの上下移動あっぷでーーーーーーと

	ObjectClass* m_LinkPt[10] = { nullptr };
	int m_setNom = 0;

	bool m_upDownFlag = false;		//上下フラグ（1回だけ実行するためのbool）

	//定数
	const CVector3 StaticSize = { 250.0f,300.0f,20.0f };	//扉の当たり判定サイズ
	const float StaticY_Hosei = 100.0f;		//当たり判定が埋まるので上に補正する

};

