#pragma once

/// <summary>
/// ゲーム！
/// ・シングルトン
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

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static Game* Game::GetInstance() {
		return m_instance;
	}

private:
	GameMode m_gameMode = ActionMode;
	GameData m_gameData;
	GameEffect m_gameEffect;
};

