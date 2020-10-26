#include "stdafx.h"
#include "DamageSystem.h"


DamageSystem::DamageSystem()
{
}


DamageSystem::~DamageSystem()
{
}

void DamageSystem::Damage(const int& damage) {
	
	//���G���Ԓ��łȂ��Ȃ�_���[�W��^����
	if (m_damageFlag == false) {
		GameData::GetInstance()->HP_Plus(damage);
		m_damageFlag = true;
	}

}

void DamageSystem::DamageUpdate() {

	//���G���Ԃ̏���
	if (m_damageFlag == true) {
		m_damageTimer += CGameTime::GetFrameDeltaTime();

		if (m_damageTimer >= DamageLimit) {
			m_damageTimer = 0.0f;
			m_damageFlag = false;
		}
	}

	//�Q�[���I�[�o�[�`�F�b�N
	if (GameData::GetInstance()->GetHP() == 0 && 
		SceneManager::GetInstance()->GetGameMode() != SceneManager::GameOver) {
		//�Q�[���I�[�o�[�ɂ���
		SceneManager::GetInstance()->SetGameMode(SceneManager::GameOver);
	}

}