#pragma once
#include "system/CGameObjectManager.h"
#include "SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// �M�����󂯎���ď㉺�ړ������
/// </summary>
class Door : public IGameObject, public ObjectClass
{
public:
	Door();
	~Door();
	void Update()override;
	void Render()override;

	//�t���O����
	void SetFlag(bool flag) {
		m_upDownFlag = flag;
	}
	bool GetFlag() {
		return m_upDownFlag;
	}

	//�����N�I�u�W�F�N�g�̐ݒ�
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt = linkObj;
	}

private:
	SkinModel m_model;	//�X�C�b�`�̓y����Ł`�`��

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g

	bool m_upDownFlag = false;		//�㉺��� faise=�~�� true=�㏸
	ObjectClass* m_LinkPt;

};

