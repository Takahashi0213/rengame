#pragma once
#include "system/CGameObjectManager.h"

/// <summary>
/// �G���Ǝ�ɓ��邨��
/// </summary>
class StarMoney : public IGameObject, public ObjectClass
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

};

