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

	//�����N�I�u�W�F�N�g�̐ݒ�
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_setNom++;
	}

private:
	//�A�N�V�����t���O�̕ύX
	void UpdateActionFlag() {
		bool CheckFlag = true;		//�ʉߊm�F

		for (int i = 0; i < 10; i++) {
			if (m_LinkPt[i] != nullptr && m_LinkPt[i]->m_actionFlag == false) {
				CheckFlag = false;
			}
		}

		m_actionFlag = CheckFlag;
	}
	SkinModel m_model;	//�X�C�b�`�̓y����Ł`�`��

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g

	void DoorUpDowmUpdate();	//�h�A�̏㉺�ړ������ՂŁ[�[�[�[�[�[��

	ObjectClass* m_LinkPt[10] = { nullptr };
	int m_setNom = 0;

};

