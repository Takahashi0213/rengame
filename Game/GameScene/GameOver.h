#pragma once

/// <summary>
/// ゲームオーバー
/// （プレイヤーのHPが0になると生成される）
/// </summary>
class GameOver
{
public:
	GameOver();
	~GameOver();

	//Gameに呼んでもらう
	void GameOverUpdate();

private:
};

