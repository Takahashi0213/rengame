#pragma once
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	//�X�V
	void SoundManagerUpdate();

	//BGM����

	//BGM�̍Đ�
	void InitBGM(wchar_t* filePath, const float& Volume = 1.0f);
	//BGM�̒�~
	void BGM_Stop() {
		m_bgm->Stop();
	}
	//�{�����[���̐ݒ�
	void BGM_SetVolume(const float& Volume) {
		m_bgm->SetVolume(Volume);
	}

	//�{�����[���̃t�F�[�h�ύX
	void BGM_VolumeFade(const float& Volume, const int& changeTime) {
		m_volumeAdd = (Volume - m_bgm->GetVolume()) / static_cast<float>(changeTime);
		m_volumeTimer = 0;
		m_volumeLimit = changeTime;
	}

private:

	CSoundSource * m_bgm = nullptr;

	//�ۑ��p
	float m_volumeAdd = 0.0f;		//1�t���[���ɉ��Z�����
	int m_volumeTimer = 0;			//�{�����[���^�C�}�[
	int m_volumeLimit = 0;			//���Z�I���̃��~�b�g

};

