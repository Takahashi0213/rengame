#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// �X�C�b�`�̐Ԃ����
/// ���L�̃X�C�b�`�y��ɃA�b�v�f�[�g�E�����_�[���Ă�ł�����Ă���
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

	void SetScale(CVector3 scale) {
		m_scale = scale;
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

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 5.0f,5.0f,5.0f }; //�g�嗦

	SwitchState m_switchState = Off;	//�I���I�t���

	//�萔
	const CVector3 Local = { 0.0f,5.0f,0.0f };	//�x�[�X����ɂ����Ԃ������̃��[�J�����W
	const CVector3 GhostScale = { 160.0f,0.5f,160.0f };	//����p�S�[�X�g�͈̔�
	const float GhostY_Up = 15.0f;		//����p�S�[�X�g����Ɏ����グ�Ă����ړ���
	const float SwitchMove = 14.0f;		//�����ꂽ�Ƃ��߂������̈ړ���
	const int SwitchMoveTime = 12;		//�����ꂽ�Ƃ��߂������̈ړ�����

};

/// <summary>
/// �X�C�b�`�̃x�[�[�X
/// ��ɂȂ�̂͂������ł�
/// </summary>
class Switch : public IGameObject, public ObjectClass
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
		if (m_switchObj.GetSwitchState() == false) {
			return true;
		}
		if (m_switchObj.GetSwitchState() == true) {
			return false;
		}
		return false;
	}

private:

	SkinModel m_model;	//�X�C�b�`�̓y����Ł`�`��
	SwitchObj m_switchObj;	//�Ԃ���������

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g

};

