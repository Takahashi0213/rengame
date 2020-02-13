#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "Game.h"
#include "MouseOver.h"
#include "GameBox.h"

#include "StarMoney.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �v���C���[�̃|�W�V������Ԃ�
	/// </summary>
	/// <returns>�v���C���[�̏ꏊ</returns>
	CVector3 Getm_Position() {
		return m_position;
	}
	/// <summary>
	/// �v���C���[�̉�]��Ԃ�
	/// </summary>
	/// <returns>��]</returns>
	CQuaternion Getm_Rotation() {
		return m_rotation;
	}

private:

	//�펞�Ă΂��
	void BoxUp();

	SkinModel m_model;	//�X�L�����f���B
	SkinModel m_model_Sl;	//�X�L�����f���i�V���G�b�g�j
	CharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	Game* m_gameObj;
	LightMaker* m_lightMaker;
	MouseOver ms;

	//���l
	SkinModel m_titan;	//�X�L�����f���B
	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;
	ID3D11ShaderResourceView* m_specMapSRV = nullptr;
	ID3D11ShaderResourceView* m_aoMapSRV = nullptr;
	//���
	StarMoney* m_starMoney;

	//���m�N���t���O
	bool m_monochromeFlag = false;

	//�s��
	void Move();
	void Jump();
	void BoxCatch();

	//�v���C���[
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦
	CVector3 m_moveSpeed = CVector3().Zero();
	CVector3 m_nextPos = CVector3().Zero();

	//�ړ�
	const float m_moveMax = 30.0f;
	int hoge = 0;

	//�W�����v
	bool m_jumpNow = false;
	const float m_jumpPower = 16.0f;	//�W�����v�ߩܧ
	const float m_gravity = 0.8f;		//�d���ߩܧ

	//�������グ
	GameBox* m_upBox = nullptr;		//�����グ�Ă��锠
	bool m_boxUpFlag = false;		//�������グ���H
	bool m_boxButtonFlag = false;	//���̃{�^��

};

