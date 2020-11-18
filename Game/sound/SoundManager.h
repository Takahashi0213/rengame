#pragma once

/// <summary>
/// BGMや効果音の管理
/// </summary>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	//更新
	void SoundManagerUpdate();

	//BGM処理

	//BGMの再生
	void InitBGM(wchar_t* filePath, const float& Volume = 1.0f);
	//BGMの停止
	void BGM_Stop() {
		m_bgm->Stop();
	}
	//一時停止
	void BGM_Pause() {
		m_bgm->Pause();
	}
	//停止から再開
	void BGM_Play() {
		m_bgm->Play(true);			//ループ再生
	}

	//ボリュームの設定
	void BGM_SetVolume(const float& Volume) {
		m_bgm->SetVolume(Volume);
	}

	//ボリュームのフェード変更
	void BGM_VolumeFade(const float& Volume, const int& changeTime) {
		m_volumeAdd = (Volume - m_bgm->GetVolume()) / static_cast<float>(changeTime);
		m_volumeTimer = 0;
		m_volumeLimit = changeTime;
	}

	//SE処理

	//SEの再生（自動でワンショットになる）
	CSoundSource* InitSE(wchar_t* filePath, const float& Volume = 1.0f);

private:

	CSoundSource * m_bgm = nullptr;

	//保存用
	float m_volumeAdd = 0.0f;		//1フレームに加算する量
	int m_volumeTimer = 0;			//ボリュームタイマー
	int m_volumeLimit = 0;			//加算終了のリミット

};

