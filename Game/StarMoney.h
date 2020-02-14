#pragma once
#include "system/CGameObjectManager.h"

class StarMoney : public IGameObject
{
public:
	StarMoney();
	~StarMoney();
	void Update()override;
	void Render()override;

	//�ݒ�
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}

private:

	SkinModel m_model;	//�X�L�����f���B
	SkinModel m_model_Kirameki;	//�L�����L����
	ID3D11ShaderResourceView* m_kiramekiSRV = nullptr;

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 10.0f,10.0f,10.f }; //�g�嗦



};

