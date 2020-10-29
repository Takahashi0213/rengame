#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::InitBGM(wchar_t* filePath, const float& Volume) {

	if (m_bgm != nullptr) {
		m_bgm->Stop();
		DeleteGO(m_bgm);
	}
	m_bgm = NewGO<CSoundSource>(0);
	m_bgm->Init(filePath);
	m_bgm->Play(true);			//ループ再生
	float hosei = 1.0f;
	if (GameData::GetInstance() != nullptr) {
		hosei = (GameData::GetInstance()->Get_BGMVolume() / 100.0f);
	}
	BGM_SetVolume(Volume * hosei);

}

void SoundManager::SoundManagerUpdate() {

	//ボリュームフェード
	if (m_volumeLimit != 0) {
		float hosei = 1.0f;
		if (GameData::GetInstance() != nullptr) {
			hosei = (GameData::GetInstance()->Get_BGMVolume() / 100.0f);
		}
		m_bgm->SetVolume((m_bgm->GetVolume() + m_volumeAdd) * hosei);

		m_volumeTimer++;
		if (m_volumeTimer >= m_volumeLimit) {	//終了
			m_volumeAdd = 0.0f;
			m_volumeLimit = 0;
		}
	}

}

CSoundSource* SoundManager::InitSE(wchar_t* filePath, const float& Volume) {

	CSoundSource* ss = NewGO<CSoundSource>(0);
	ss->Init(filePath);

	float hosei = 1.0f;
	if (GameData::GetInstance() != nullptr) {
		hosei = (GameData::GetInstance()->Get_SEVolume() / 100.0f);
	}

	ss->SetVolume(Volume * hosei);
	ss->Play(false);		//ワンショット再生

	return ss;
}