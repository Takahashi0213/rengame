#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
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
	//基本的にレベルロード時に呼ぶ
	//一番最後に設定したオブジェクトのタグを参照して動作を決定する
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_LinkObjectTag = linkObj->m_object;	//このオブジェクトの種類（タグ）を引っ張ってくる
		m_setNom++;
	}
	
	SkinModelRender* GetSkinModelRender() {
		return m_model;
	}

private:

	//アクションフラグの変更
	//毎フレーム呼ばれて、今扉がどうするべきか判断する
	//ただし反応の仕様がエネミーの場合、一度開いたらもう実行しない
	void UpdateActionFlag() {

		//動作仕様がエネミー＆扉が上がっているならオワオワリ
		if (m_LinkObjectTag == ObjectClass::ObjectClass_Tag::EnemyObj &&
			m_actionFlag == true) {
			return;
		}

		bool CheckFlag = true;		//通過確認

		for (int i = 0; i < 10; i++) {
			if (m_LinkPt[i] != nullptr && m_LinkPt[i]->m_actionFlag == false) {
				CheckFlag = false;
			}
		}
		m_actionFlag = CheckFlag;	//trueのままならｵｹ
	}

	SkinModelRender* m_model;	//土台もで～～る

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

	void DoorUpDowmUpdate();	//ドアの上下移動あっぷでーーーーーーと

	ObjectClass* m_LinkPt[10] = { nullptr };	//ドア上下トリガー
	int m_setNom = 0;							//イマドコ
	bool m_upDownFlag = false;					//上下フラグ（1回だけ実行するためのbool）

	//反応の仕様を決めるくん
	//ギミック系→オフになったら閉じる
	//エネミー系→一度開いたら二度と閉じない（敵のインスタンスが消去されるため）
	ObjectClass_Tag m_LinkObjectTag = ObjectClass::ObjectClass_Tag::NullObj;

	//定数
	const CVector3 StaticSize = { 250.0f,300.0f,20.0f };	//扉の当たり判定サイズ
	const float StaticY_Hosei = 100.0f;		//当たり判定が埋まるので上に補正する

	const float UpDown_Y = 500.0f;			//扉の上下移動量
	const int UpDownTime = 20;				//扉の上下移動時間

};

