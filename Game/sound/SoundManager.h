#pragma once
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

private:

	CSoundSource * m_bgm = nullptr;

	//保存用
	float m_volumeAdd = 0.0f;		//1フレームに加算する量
	int m_volumeTimer = 0;			//ボリュームタイマー
	int m_volumeLimit = 0;			//加算終了のリミット

};

