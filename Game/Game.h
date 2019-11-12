#pragma once

class Game : public IGameObject
{
public:
	enum GameMode {
		Title,
		ActionMode,
		CreateMode,
		Menu,
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

private:
	GameMode m_gameMode = ActionMode;
};

