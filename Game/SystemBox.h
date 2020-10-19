#pragma once
#include "system/CGameObjectManager.h"
#include "PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// �S�[�X�g�{�b�N�X
/// �}�b�v�ړ����������A�͈͂ɓ�������N������C�x���g�Ɏg����
/// </summary>
class GhostBox : public IGameObject, public ObjectClass
{
public:
	GhostBox();
	~GhostBox();
	void Update()override;
	void Render()override;

	//�ݒ�p�i���x���������ɓ����ɌĂԂ̂���{�j
	void SetStageName(const wchar_t* stageName) {
		m_LoadStageName = stageName;
	}
	void SetPlayerMoveTarget(const CVector3 pos) {
		m_playerMoveTarget = pos;
	}

	/// <summary>
	/// �Ăяo���ƃS�[�X�g�𐶐�����
	/// </summary>
	void CreateGhost();

private:
	PhysicsGhostObject m_ghostObject;				//�S�[�X�g�I�u�W�F�N�g

	Player* m_player = nullptr;						//�v���C���[�͂����I

	//���x���Z�b�g���ɐݒ肷�����
	//�}�b�v�ړ���
	const wchar_t* m_LoadStageName = nullptr;		//�X�e�[�W�̖��O
	CVector3 m_playerMoveTarget;					//�v���C���[�̈ړ���
	//�Q�[���I�[�o�[��


};

/// <summary>
/// �ÓI�Ȕ�
/// �����ȕǂ�����
/// </summary>
class StaticBox : public IGameObject, public ObjectClass
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
