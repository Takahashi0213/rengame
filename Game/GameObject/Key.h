#pragma once
#include "system/CGameObjectManager.h"
#include "GameObject/Player.h"
#include "GameObject/ItemSystem.h"

class Key : public ItemSystem
{
public:
	Key();
	~Key();
	void DataSet();
	void Update()override;
	void Render()override;

	//�ݒ�p�i���x���������ɓ����ɌĂԂ̂���{�j
	void SetItemNo(const int& itemNo) {
		m_itemNo = itemNo;
	}

	//�����N�I�u�W�F�N�g�̐ݒ�
	//��{�I�Ƀ��x�����[�h���ɌĂ�
	//��ԍŌ�ɐݒ肵���I�u�W�F�N�g�̃^�O���Q�Ƃ��ē�������肷��
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_setNom++;
	}

private:

	//�A�N�V�����t���O�̕ύX
	//���t���[���Ă΂�āA�ǂ�����ׂ������f����
	void UpdateActionFlag() {

		//�A�N�V�����ς݂Ȃ�I���
		if (m_actionFlag == true) {
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

	void KeySpawn();				//���o�����o

	SkinModelRender * m_skinModelRender = nullptr;

	bool m_setFlag = false;
	bool m_drawFlag = false;
	bool m_spawnFlag = false;

	const float DefScale = 5.0f;					//�g�嗦
	const float AutoRotation = 5.0f;				//������]��

	//�����N�I�u�W�F�N�g
	ObjectClass* m_LinkPt[MAX_LINK_OBJECT] = { nullptr };		//�o���g���K�[
	int m_setNom = 0;											//���܂ǂ��ɂ���H

};

