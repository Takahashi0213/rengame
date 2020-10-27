#pragma once
#include "system/CGameObjectManager.h"
#include "physics/PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// �S�[�X�g�{�b�N�X
/// �}�b�v�ړ����������A�͈͂ɓ�������N������C�x���g�Ɏg����
/// </summary>
class GhostBox : public ObjectClass
{
public:
	enum GhostBox_System {
		MapMove,	//�}�b�v�ړ�
		MapEvent,	//�}�b�v�C�x���g
		DamageZone,	//�����_���[�W
	};
	//����̎�ނ�ݒ�
	void SetGhostBox_System(const GhostBox_System boxSystem) {
		m_boxSystem = boxSystem;
	}

	GhostBox();
	~GhostBox();
	void Update()override;
	void Render()override;

	//�ݒ�p�i���x���������ɓ����ɌĂԂ̂���{�j
	void SetStageName(const wchar_t* stageName) {
		m_LoadName = stageName;
	}
	void SetPlayerMoveTarget(const CVector3& pos) {
		m_playerMoveTarget = pos;
	}
	void SetYazirushiRot(const float& rotAngle) {
		m_yazirushiRotAngle = rotAngle;
	}
	void SetYazirushiYHosei(const float& hosei) {
		m_yazirushiYHosei = hosei;
	}
	void SetRotFlag(const bool& rotFlag) {
		YazirushiRotFlag = rotFlag;
	}

	/// <summary>
	/// �Ăяo���ƃS�[�X�g�𐶐�����
	/// </summary>
	void CreateGhost();

private:
	void GhostAction();		//�v���C���[�ڐG���̔���

	PhysicsGhostObject m_ghostObject;				//�S�[�X�g�I�u�W�F�N�g
	SkinModelRender* m_Yazirushi = nullptr;			//�}�b�v�ړ��S�[�X�g�̏ꍇ�g�p����

	Player* m_player = nullptr;						//�v���C���[�͂����I
	GhostBox_System m_boxSystem;					//���̔��̎��

	//���x���Z�b�g���ɐݒ肷�����
	const wchar_t* m_LoadName = nullptr;			//�X�e�[�W/�C�x���g�̖��O
	CVector3 m_playerMoveTarget;					//�v���C���[�̈ړ���
	float m_yazirushiRotAngle = 0.0f;				//���̉�]
	float m_yazirushiYHosei = 0.0f;					//����Y�␳
	bool m_mapMoveFlag = false;						//�}�b�v�ړ��t���O
	int m_mapMoveTimer = 0;							//�}�b�v�ړ��^�C�}�[
	const float YazirushiMoveHosei = 30.0f;			//���̈ړ��ʕ␳
	const int YazirushiMoveTime = 10;				//���̈ړ�����
	bool YazirushiRotFlag = false;					//���̉�]�t���O�iY_UP�j
	const int FallDamage = 50;						//�����_���[�W

};

/// <summary>
/// �ÓI�Ȕ�
/// �����ȕǂ�����
/// </summary>
class StaticBox : public ObjectClass
{
public:
	StaticBox();
	~StaticBox();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �Ăяo���ƐÓI�����I�u�W�F�N�g�𐶐�����
	/// </summary>
	void CreateStaticBox();

private:
	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g

};