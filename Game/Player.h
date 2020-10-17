#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "Game.h"
#include "MouseOver.h"
#include "GameBox.h"

#include "StarMoney.h"

class Player final: public IGameObject
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
	CVector3 GetPosition() {
		return m_position;
	}

	/// <summary>
	/// �v���C���[�̉�]��Ԃ�
	/// </summary>
	/// <returns>��]</returns>
	CQuaternion Getm_Rotation() {
		return m_rotation;
	}

	/// <summary>
	/// �L�����R�����擾
	/// </summary>
	CharacterController* GetCharaCon() {
		return &m_charaCon;
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
	void BoxSearch();
	void BoxMove();

	//�v���C���[
	CVector3 m_position = /*CVector3().Zero()*/{ 0.0f,100.0f,-500.0f };
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦
	CVector3 m_moveSpeed = CVector3().Zero();
	CVector3 m_nextPos = CVector3().Zero();

	//�ړ�
	const float m_moveMax = 30.0f;

	//�W�����v
	bool m_jumpNow = false;
	const float m_jumpPower = 16.0f;	//�W�����v�ߩܧ
	const float m_gravity = 0.8f;		//�d���ߩܧ

	//�������グ
	GameBox* m_upBox = nullptr;				//�����グ�Ă��锠
	GameBox* m_upKouho_Box = nullptr;		//�����グ���̔�
	bool m_boxUpFlag = false;				//�������グ���H
	bool m_boxMoveFlag = false;				//���グ���낵���쒆�H�i���쒆�͓����܂���j
	bool m_upOrDown = false;				//�����グ�Ă���Ȃ�false�A�����Ă���Ȃ�true
	bool m_boxButtonFlag = false;			//���̃{�^��
	const float m_boxPutHosei = 4.0f;		//����u���������邩�̊�␳�i�傫������ƒu���₷���Ȃ�j
	const float m_boxUpRange = 200.0f;		//���������グ����͈�
	const float m_boxUp_Y_Max = 50.0f;		//���������グ���鍂���͈̔�
	const float m_boxUp_Angle = 90.0f;		//���������グ�鎋��p�͈�
	//�グ�����ړ��icatmull�j�i���������ǃx�W�F�Ȑ��ɕύX�j
	CVector3 m_point_1 = CVector3::Zero();	//�I�_���
	CVector3 m_point_2 = CVector3::Zero();	//�n�_
	CVector3 m_point_3 = CVector3::Zero();	//�I�_
	CVector3 m_point_4 = CVector3::Zero();	//�n�_���
	float m_catmull_U = 0.0f;
	const float m_boxMove_Y_Hosei = 150.0f;		//�����グ��ۂ̍ō����B�_Y�␳
	const float m_boxMove_Y_Hosei_Put = 50.0f;	//�������낷�ۂ̍ō����B�_Y�␳
	const float m_boxPos_Y_Hosei = 150.0f;		//���������グ�Ă���Ƃ��̃v���C���[Y�␳
	const float m_boxPut_Hosei = 150.0f;		//����u���Ƃ��̈ړ���
};

