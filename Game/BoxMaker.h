#pragma once
#include "system/CGameObjectManager.h"
#include "Game.h"
#include "GameBox.h"
#include "Player.h"
#include "GameCamera.h"

class BoxMaker : public IGameObject
{
public:
	BoxMaker();
	~BoxMaker();
	void Update()override;
	void Render()override;

	/// <summary>
	/// ゲームのポインタをほぞんぬ
	/// </summary>
	/// <param name="game">アドレス</param>
	void SetGame(Game* game) {
		m_game = game;
	}
	/// <summary>
	/// プレイヤーのポインタをほぞんぬ
	/// </summary>
	/// <param name="game">アドレス</param>
	void SetPlayer(Player* pl) {
		m_player = pl;
	}

private:
	void BoxUpdate();

	Game* m_game = nullptr;
	CVector3 m_boxPos = CVector3().Zero();
	Player* m_player = nullptr;

	//箱リスト
	std::list<GameBox*> m_boxList;
	GameBox* m_nowBox = nullptr;		//現在見ているボックスさん
	std::list<GameBox*> m_nowBoxList;

	//座標
	CVector3 m_boxPoint[4];

	//定数
	const float PosHoseiY = 200.0f;		//レイがヒットしなかった時の補正

};

