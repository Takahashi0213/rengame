#pragma once
#include "system/CGameObjectManager.h"
#include "Player.h"

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
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}

private:

	void StarMoneyMove();

	SkinModel m_model;			//�X�L�����f���B
	SkinModel m_model_Kirameki;	//�L�����L����
	Player* m_pl = nullptr;
	ID3D11ShaderResourceView* m_kiramekiSRV = nullptr;

	//�V�F�C�N
	bool m_upDowmFlag = false;			//�㉺�t���O
	float m_upDowmTimer = 0.0f;			//�㉺�^�C�}�[
	const float UpDownLimit = 0.5f;		//�㉺���~�b�g
	const float UpDownMove = 0.5f;		//�㉺�ړ���

	//�萔
	const CVector3 DefScale = { 10.0f,10.0f,10.0f };	//�����T�C�Y
	const float GetRange = 150.0f;						//�擾�ł���͈�
	const int GetStarMoney = 1;							//�擾��

};

