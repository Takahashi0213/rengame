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

	void SetStageName(const wchar_t* stageName) {
		m_LoadStageName = stageName;
	}

	/// <summary>
	/// �Ăяo���ƃS�[�X�g�𐶐�����
	/// </summary>
	void CreateGhost();

private:
	PhysicsGhostObject m_ghostObject;	//�S�[�X�g�I�u�W�F�N�g

	Player* m_player = nullptr;

	const wchar_t* m_LoadStageName;		//�X�e�[�W�̖��O

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

private:
	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g

};
