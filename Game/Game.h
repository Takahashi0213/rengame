#pragma once
#include "SystemData.h"
#include "GameGraphic.h"
#include "GameUI.h"
#include "PhysicsGhostObject.h"
#include "system/CGameObjectManager.h"

/// <summary>
/// �Q�[���I
/// �E�V���O���g��
/// </summary>
class Game : public IGameObject
{
	static Game* m_instance;
public:
	enum GameMode {
		Title,
		ActionMode,
		CreateMode,
		MenuMode,
	};

	Game();
	~Game();
	void Update()override;
	void Render()override;

	void GameUpdate();

	/// <summary>
	/// �Q�[�����[�h���Z�b�g
	/// </summary>
	/// <param name="mode">���[�h</param>
	void SetGameMode(GameMode mode) {
		m_gameMode = mode;
	}
	/// <summary>
	/// �Q�[�����[�h���擾
	/// </summary>
	/// <returns>���[�h</returns>
	GameMode GetGameMode() {
		return m_gameMode;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static Game* Game::GetInstance() {
		return m_instance;
	}
	SystemData* Game::GetSystemInstance() {
		return &m_systemData;
	}
	GameGraphic* Game::GetGameGraphicInstance() {
		return &m_gameGraphic;
	}
	GameUI* Game::GetUI() {
		return m_ui;
	}

private:

	//��������Q�[���p

	GameMode m_gameMode = ActionMode;
	GameData m_gameData;
	GameEffect m_gameEffect;

	SystemData m_systemData;
	GameGraphic m_gameGraphic;

	GameUI* m_ui = nullptr;

	CSoundEngine m_soundEngine;				//�T�E���h�G���W���B

	CharacterController* m_charaCon;
	PhysicsGhostObject m_ghostObject;						//�S�[�X�g�I�u�W�F�N�g�Ƃ��S�B
};

