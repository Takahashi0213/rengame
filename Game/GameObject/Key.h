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

	//���o�p�t���O
	bool m_setFlag = false;
	bool m_moveFlag = false;
	bool m_drawFlag = false;
	bool m_spawnFlag = false;
	//�萔
	const float DefScale = 5.0f;					//�g�嗦
	const float AutoRotation = 5.0f;				//������]��
	const float DownHosei = 450.0f;					//���擾���A�n�ʂɖ��܂��
	const float UpMove = 560.0f;					//�o�����A��Ɉړ������
	const float UpMove_Bound = 100.0f;				//�o�����A���Ƀo�E���h�����
	const int UpTime = 20;							//�o�����o����
	const float GetRange = 150.0f;					//�擾�ł���͈�

	//�����N�I�u�W�F�N�g
	ObjectClass* m_LinkPt[MAX_LINK_OBJECT] = { nullptr };		//�o���g���K�[
	int m_setNom = 0;											//���܂ǂ��ɂ���H

};

