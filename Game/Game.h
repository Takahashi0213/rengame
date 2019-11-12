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
	/// ゲームモードをセット
	/// </summary>
	/// <param name="mode">モード</param>
	void SetGameMode(GameMode mode) {
		m_gameMode = mode;
	}
	/// <summary>
	/// ゲームモードを取得
	/// </summary>
	/// <returns>モード</returns>
	GameMode GetGameMode() {
		return m_gameMode;
	}

private:
	GameMode m_gameMode = ActionMode;
};

