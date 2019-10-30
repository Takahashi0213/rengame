#pragma once
#include "system/CGameObjectManager.h"
#include "Player.h"
#include "Game.h"
#include "GameBox.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update()override;
	void Render()override;

	/// <summary>
	/// ゲームのアドレスをセット
	/// </summary>
	/// <param name="game">アドレスよ</param>
	void SetGame(Game* game) {
		m_game = game;
	}
	/// <summary>
	/// 今見ている箱のアドレスです
	/// </summary>
	/// <param name="gamebox">アドレスです</param>
	void SetGameBox(GameBox* gamebox) {
		m_gamebox = gamebox;
	}

private:
	void ActionMode();
	void CreateMode();

	CVector3 m_cameraTarget;
	CVector3 m_cameraPos;

	Player* m_player;
	Game* m_game;
	GameBox* m_gamebox = nullptr;

	CVector3 m_cameraHosei = { 0.0f,300.0f,-300.0f };

};

