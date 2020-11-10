#include "stdafx.h"
#include "GameData.h"

GameData* GameData::m_instance = nullptr;

GameData::GameData()
{
	if (m_instance == nullptr) {
		//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
		m_instance = this;
	}
}

GameData::~GameData()
{
	if (m_instance == this) {
		//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
		m_instance = nullptr;
	}
}

void GameData::LevelUpCheck() {

	//��x�ɕ����񃌃x���A�b�v����\�������邽�߃��[�v������
	while (true)
	{
		//���݌o���l���l�N�X�g�o���l���I�[�o�[���Ă��邩�H
		if (m_nowExp < m_nextExp) {
			break;		//�I�[�o�[���Ă��Ȃ��Ȃ�I��
		}

		//�������烌�x���A�b�v����
		m_nowExp = m_nowExp - m_nextExp;							//���݂̌o���l�����炷
		m_level++;													//���x���A�b�v
		m_nextExp = static_cast<int>(m_nextExp * NextEXP_Hosei);	//����o���l�㏸
		LevelUpStatus();											//���x���A�b�v���̃X�e�[�^�X�㏸
	}

}

void GameData::LevelUpStatus() {

	//���x���A�b�v�������̃X�e�[�^�X�㏸�ʂ��ʂɌ��߂�
	switch (m_level)
	{
	case 2:			//���x��2�ɂȂ������̃X�e�[�^�X�㏸��
		LevelUp_Mana(10);
		break;
	case 3:
		LevelUp_HP();
		break;
	case 4:
		LevelUp_Mana(10);
		break;
	case 5:
		LevelUp_Mana(5);
		break;
	case 6:
		LevelUp_Mana(5);
		break;
	case 7:
		LevelUp_HP();
		break;
	case 8:
		LevelUp_Mana(5);
		break;
	case 9:
		LevelUp_Mana(5);
		break;
	case 10:		//���������x��10�ɂȂ������̏㏸�ʁI
		LevelUp_Mana(10);
		break;

	}

}