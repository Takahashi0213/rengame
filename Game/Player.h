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
	SkinModel m_model2;	//�X�L�����f���B

	PhysicsStaticObject m_physicsStaticObject;				//�ÓI�����I�u�W�F�N�g�B

	void Move();

	//�v���C���[
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦

	CVector3 m_nextPos = CVector3().Zero();

};

