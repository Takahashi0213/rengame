#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
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
	//��{�I�Ƀ��x�����[�h���ɌĂ�
	//��ԍŌ�ɐݒ肵���I�u�W�F�N�g�̃^�O���Q�Ƃ��ē�������肷��
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_LinkObjectTag = linkObj->m_object;	//���̃I�u�W�F�N�g�̎�ށi�^�O�j�����������Ă���
		m_setNom++;
	}
	
	SkinModelRender* GetSkinModelRender() {
		return m_model;
	}

private:

	//�A�N�V�����t���O�̕ύX
	//���t���[���Ă΂�āA�������ǂ�����ׂ������f����
	//�����������̎d�l���G�l�~�[�̏ꍇ�A��x�J������������s���Ȃ�
	void UpdateActionFlag() {

		//����d�l���G�l�~�[�������オ���Ă���Ȃ�I���I����
		if (m_LinkObjectTag == ObjectClass::ObjectClass_Tag::EnemyObj &&
			m_actionFlag == true) {
			return;
		}

		bool CheckFlag = true;		//�ʉߊm�F

		for (int i = 0; i < 10; i++) {
			if (m_LinkPt[i] != nullptr && m_LinkPt[i]->m_actionFlag == false) {
				CheckFlag = false;
			}
		}
		m_actionFlag = CheckFlag;	//true�̂܂܂Ȃ絹
	}

	SkinModelRender* m_model;	//�y����Ł`�`��

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g

	void DoorUpDowmUpdate();	//�h�A�̏㉺�ړ������ՂŁ[�[�[�[�[�[��

	ObjectClass* m_LinkPt[10] = { nullptr };	//�h�A�㉺�g���K�[
	int m_setNom = 0;							//�C�}�h�R
	bool m_upDownFlag = false;					//�㉺�t���O�i1�񂾂����s���邽�߂�bool�j

	//�����̎d�l�����߂邭��
	//�M�~�b�N�n���I�t�ɂȂ��������
	//�G�l�~�[�n����x�J�������x�ƕ��Ȃ��i�G�̃C���X�^���X����������邽�߁j
	ObjectClass_Tag m_LinkObjectTag = ObjectClass::ObjectClass_Tag::NullObj;

	//�萔
	const CVector3 StaticSize = { 250.0f,300.0f,20.0f };	//���̓����蔻��T�C�Y
	const float StaticY_Hosei = 100.0f;		//�����蔻�肪���܂�̂ŏ�ɕ␳����

	const float UpDown_Y = 500.0f;			//���̏㉺�ړ���
	const int UpDownTime = 20;				//���̏㉺�ړ�����

};

