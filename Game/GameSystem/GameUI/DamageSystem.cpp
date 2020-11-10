#include "stdafx.h"
#include "DamageSystem.h"


DamageSystem::DamageSystem()
{
}


DamageSystem::~DamageSystem()
{
}

bool DamageSystem::Damage(const int& damage) {
	
	//���G���Ԓ��łȂ��Ȃ�_���[�W��^����
	if (m_damageFlag == false) {
		GameData::GetInstance()->HP_Plus(damage);
		m_damageFlag = true;
		//�_���[�W�t�H���g
		m_damageFont = CGameObjectManager::GetInstance()->NewGO<FontRender>(L"DamageFont", 5);
		m_damageFont->SetPosition(CVector2::Zero());
		wchar_t text[MAX_PATH];
		swprintf(text, MAX_PATH - 1, L"-%d", damage);
		m_damageFont->SetText(text);
		m_damageFont->SetColor({ 1.0f,0.0f,0.0f,1.0f });
		m_damageFont->SetScale(DamageFontSize);
		m_damageFont->m_fontSupporter.FontMoveSet({ 0.0f,DamageFontMoveY }, DamageFontMoveTime, 0, true);
		m_damageFont->m_fontSupporter.FontColorSet({ 1.0f,0.0f,0.0f,0.0f }, DamageFontAlphaTime, DamageFontAlphaDelay);

		return true;
	}
	return false;
}

void DamageSystem::DamageUpdate() {

	//���G���Ԃ̏���
	if (m_damageFlag == true) {
		m_damageTimer += CGameTime::GetFrameDeltaTime();

		if (m_damageTimer >= DamageLimit) {
			m_damageTimer = 0.0f;
			CGameObjectManager::GetInstance()->DeleteGO(m_damageFont);
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