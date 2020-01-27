#pragma once
#include "SystemData.h"
#include "GameGraphic.h"

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

private:
	GameMode m_gameMode = ActionMode;
	GameData m_gameData;
	GameEffect m_gameEffect;

	SystemData m_systemData;
	GameGraphic m_gameGraphic;

};

