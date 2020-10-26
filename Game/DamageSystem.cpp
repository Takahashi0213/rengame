#include "stdafx.h"
#include "DamageSystem.h"


DamageSystem::DamageSystem()
{
}


DamageSystem::~DamageSystem()
{
}

void DamageSystem::Damage(const int& damage) {
	
	//無敵時間中でないならダメージを与える
	if (m_damageFlag == false) {
		GameData::GetInstance()->HP_Plus(damage);
		m_damageFlag = true;
	}

}

void DamageSystem::DamageUpdate() {

	//無敵時間の処理
	if (m_damageFlag == true) {
		m_damageTimer += CGameTime::GetFrameDeltaTime();

		if (m_damageTimer >= DamageLimit) {
			m_damageTimer = 0.0f;
			m_damageFlag = false;
		}
	}

	//ゲームオーバーチェック
	if (GameData::GetInstance()->GetHP() == 0 && 
		SceneManager::GetInstance()->GetGameMode() != SceneManager::GameOver) {
		//ゲームオーバーにする
		SceneManager::GetInstance()->SetGameMode(SceneManager::GameOver);
	}

}