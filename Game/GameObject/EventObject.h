#pragma once
#include "system/CGameObjectManager.h"

/// <summary>
/// �C�x���g�I�u�W�F�N�g
/// �����𖞂�������N������C�x���g
/// </summary>
class EventObject : public ObjectClass
{
public:
	EventObject();
	~EventObject();
	void Update()override;
	void Render()override;

	//�����N�I�u�W�F�N�g�̐ݒ�
	//��{�I�Ƀ��x�����[�h���ɌĂ�
	//��ԍŌ�ɐݒ肵���I�u�W�F�N�g�̃^�O���Q�Ƃ��ē�������肷��
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_setNom++;
	}

	//�ݒ�p�i���x���������ɓ����ɌĂԂ̂���{�j
	void SetEventName(const wchar_t* eventName) {
		m_eventName = eventName;
	}

private:
	//�A�N�V�����t���O�̕ύX
	//���ƈ���Ėⓚ���p�Ŏ��s�����A���s�ケ�̃I�u�W�F�N�g�͍폜�����
	void UpdateActionFlag() {

		bool CheckFlag = true;		//�ʉߊm�F

		for (int i = 0; i < 10; i++) {
			if (m_LinkPt[i] != nullptr && m_LinkPt[i]->m_actionFlag == false) {
				CheckFlag = false;
			}
		}
		m_actionFlag = CheckFlag;	//true�̂܂܂Ȃ絹
	}

	const wchar_t* m_eventName = nullptr;			//�C�x���g�̖��O

	ObjectClass* m_LinkPt[MAX_LINK_OBJECT] = { nullptr };		//�C�x���g�g���K�[
	int m_setNom = 0;											//�C�x���g�g���K�[�Q�ƈʒu

};

