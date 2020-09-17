#pragma once

class ObjectClass
{
public:
	//オブジェクトの種類
	enum ObjectClass_Tag {
		NullObj,		//ダミー
		ItemObj,		//アイテム
		GimmickObj,		//ギミック系
		EnemyObj,		//敵（そのまんま）
	};

	ObjectClass();
	~ObjectClass();

	//インスタンス取得
	ObjectClass* GetInstance() {
		return this;
	}

	//座標
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}
	CVector3 GetPosition() {
		return m_position;
	}

	//回転
	void SetRotation(CQuaternion rot) {
		m_rotation = rot;
	}
	CQuaternion GetRotation() {
		return m_rotation;
	}

	//拡大率
	void SetScale(CVector3 scl) {
		m_scale = scl;
	}
	CVector3 GetScale() {
		return m_scale;
	}

	//一応パブリックのままで…

	ObjectClass_Tag m_object = NullObj;	//こいつが何者かを示すやつです

	SkinModelRender * m_modelRender = nullptr;	//スキンモデル。

	//よくつかう群
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率

	//反応フラグ
	//なんかアクションさせたいとき用
	bool m_actionFlag = false;

};