#pragma once
#include "system/CGameObjectManager.h"
#include "GameObject/Player.h"

class Key : public ObjectClass
{
public:
	Key();
	~Key();
	void Update()override;
	void Render()override;

	//�����N�I�u�W�F�N�g�̐ݒ�
	//��{�I�Ƀ��x�����[�h���ɌĂ�
	//��ԍŌ�ɐݒ肵���I�u�W�F�N�g�̃^�O���Q�Ƃ��ē�������肷��
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_setNom++;
	}

private:

	SkinModelRender * m_skinModelRender = nullptr;
	
	//�A�C�e���f�[�^
	const wchar_t* m_ModelName = nullptr;			//���f���̖��O
	const int m_itemNo = -1;

	//�����N�I�u�W�F�N�g
	ObjectClass* m_LinkPt[10] = { nullptr };		//�o���g���K�[
	int m_setNom = 0;								//���܂ǂ��ɂ���H


};

