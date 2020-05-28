#pragma once
#include "system/CGameObjectManager.h"
#include "SkinModelRender.h"
#include "PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// �X�C�b�`�̐Ԃ����
/// </summary>
class SwitchObj
{
public:
	SwitchObj();
	~SwitchObj();
	void SwitchObj_Init(CVector3 Pos);

	void SwitchUpdate();
	void SwitchDraw();

	/// <summary>
	/// �X�C�b�`�̃I���I�t��Ԃ�Ԃ�
	/// </summary>
	bool GetSwitchState() {
		return m_switchState;
	}

private:

	void GhostCheck();

	//�X�C�b�`���
	enum SwitchState {
		On,
		Off,
	};

	SkinModel m_model;	//�X�C�b�`�̂��Ł`�`��
	Player* m_pl = nullptr;			//�v���C���[

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
	PhysicsGhostObject m_ghostObject;	//�S�[�X�g�I�u�W�F�N�g

	const CVector3 Local = { 0.0f,5.0f,0.0f };	//�x�[�X����ɂ����Ԃ������̃��[�J�����W
	const CVector3 GhostScale = { 160.0f,0.1f,160.0f };	//����p�S�[�X�g�͈̔�
	const float SwitchMove = 14.0f;		//�����ꂽ�Ƃ��߂������̈ړ���
	const int SwitchMoveTime = 12;		//�����ꂽ�Ƃ��߂������̈ړ�����

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 5.0f,5.0f,5.0f }; //�g�嗦

	SwitchState m_switchState = Off;

};

class Switch : public IGameObject
{
public:
	Switch();
	~Switch();
	void Update()override;
	void Render()override;

	//�ݒ�
	void SetPosition(CVector3 pos) {
		m_position = pos;
		m_switchObj.SwitchObj_Init(m_position);
	}

	/// <summary>
	/// ���W��Ԃ�
	/// </summary>
	CVector3 GetPosition() {
		return m_position;
	}

	/// <summary>
	/// �X�C�b�`�̃I���I�t��Ԃ�Ԃ�
	/// </summary>
	bool GetSwitchState() {
		return m_switchObj.GetSwitchState();
	}

private:

	SkinModel m_model;	//�X�C�b�`�̓y����Ł`�`��
	SwitchObj m_switchObj;	//�Ԃ���������

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 5.0f,5.0f,5.0f }; //�g�嗦

};

