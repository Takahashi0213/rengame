#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"

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
	SkinModel m_model;	//�X�L�����f���B
	CharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B

	void Move();
	void Jump();

	//�v���C���[
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦
	CVector3 m_moveSpeed = CVector3().Zero();
	CVector3 m_nextPos = CVector3().Zero();

	//�W�����v
	bool m_jumpNow = false;
	const float m_jumpPower = 16.0f;	//�W�����v�ߩܧ
	const float m_gravity = 0.8f;		//�d���ߩܧ

};
