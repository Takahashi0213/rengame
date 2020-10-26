#pragma once

#include "Title.h"
#include "Game.h"
#include "system/CGameObjectManager.h"
#include "StageSet.h"
#include "sound/SoundManager.h"

/// <summary>
/// �V�[���؂�ւ�������΂�N���X
/// �E�V���O���g��
/// </summary>
class SceneManager : public IGameObject
{
	static SceneManager* m_instance;
public:
	SceneManager();
	~SceneManager();
	void Update()override;
	void Render()override;

	enum NowScene {
		Title_Scene,
		Game_Sence
	};
	enum GameMode {	//�Q�[�����ł�
		Null_Mode,	//�_�~�[���[�h�i�����p�j
		TitleMode,
		ActionMode,
		CreateMode,
		MenuMode,
		GameOver,
	};

	/// <summary>
	/// ���݃V�[���̎擾
	/// �����^�C�g�����Q�[���������m�F�ł���
	/// </summary>
	NowScene GetNowScene() {
		return m_nowScene;
	}

	/// <summary>
	/// �Q�[�����[�h���Z�b�g
	/// </summary>
	/// <param name="mode">���[�h</param>
	void SetGameMode(const GameMode mode) {
		m_gameMode = mode;
	}
	/// <summary>
	/// �Q�[�����[�h���擾
	/// </summary>
	/// <returns>���[�h</returns>
	GameMode GetGameMode() {
		return m_gameMode;
	}

	//�^�C�g���I�����ɌĂ�
	void EndTitle() {
		m_title = nullptr;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static SceneManager* GetInstance() {
		return m_instance;
	}
	SystemData* GetSystemInstance() {
		return &m_systemData;
	}
	GameGraphic* GetGameGraphicInstance() {
		return &m_gameGraphic;
	}
	SoundManager* GetSoundManagerInstance() {
		return &m_soundManager;
	}

private:

	void TitleUpdate();
	void GameUpdate();

	void TitleCommand(const Title::TitleCommand command);

	//��
	NowScene m_nowScene = Title_Scene;		//��������SceneManager��p
	GameMode m_gameMode = Null_Mode;		//�������͊O������ύX�\

	//�S�̂Ŏg������
	SystemData m_systemData;
	GameGraphic m_gameGraphic;
	CSoundEngine m_soundEngine;				//�T�E���h�G���W���B
	StageSet m_stageSet;
	SoundManager m_soundManager;

	//�V�[��
	Title* m_title = nullptr;
	Game* m_game = nullptr;

};

