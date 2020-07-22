#pragma once

class ObjectClass
{
public:
	ObjectClass();
	~ObjectClass();

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

	SkinModelRender * m_modelRender = nullptr;	//スキンモデル。

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率

};

