#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
	m_bgm = NewGO<CSoundSource>(0);
}


SoundManager::~SoundManager()
{
}

void SoundManager::InitBGM(wchar_t* filePath, const float& Volume) {

	m_bgm->Init(filePath);
	m_bgm->Play(true);			//ƒ‹[ƒvÄ¶
	BGM_SetVolume(Volume);

}

void SoundManager::SoundManagerUpdate() {

	if (m_volumeLimit != 0) {
		m_bgm->SetVolume((m_bgm->GetVolume() + m_volumeAdd));

		m_volumeTimer++;
		if (m_volumeTimer >= m_volumeLimit) {	//I—¹
			m_volumeAdd = 0.0f;
			m_volumeLimit = 0;
		}
	}

}