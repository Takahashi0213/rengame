#pragma once

class ObjectClass
{
public:
	ObjectClass();
	~ObjectClass();

	//���W
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}
	CVector3 GetPosition() {
		return m_position;
	}

	//��]
	void SetRotation(CQuaternion rot) {
		m_rotation = rot;
	}
	CQuaternion GetRotation() {
		return m_rotation;
	}

	//�g�嗦
	void SetScale(CVector3 scl) {
		m_scale = scl;
	}
	CVector3 GetScale() {
		return m_scale;
	}

	//�ꉞ�p�u���b�N�̂܂܂Łc

	SkinModelRender * m_modelRender = nullptr;	//�X�L�����f���B

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦

};

