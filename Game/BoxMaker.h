#pragma once
#include "system/CGameObjectManager.h"
#include "Game.h"
#include "GameBox.h"
#include "Player.h"
#include "GameCamera.h"

/// <summary>
/// 箱を生成したり操作したり
/// ・シングルトン
/// </summary>
class BoxMaker : public IGameObject
{
	static BoxMaker* m_instance;
public:
	enum BoxMakerMode {
		NomalMode,
		FocusMode,
	};

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

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static BoxMaker* BoxMaker::GetInstance() {
		return m_instance;
	}

private:
	void BoxUpdate();

	Game* m_game = nullptr;
	CVector3 m_boxPos = CVector3().Zero();
	Player* m_player = nullptr;

	BoxMakerMode m_boxMakerMode = NomalMode;		//ボックスメイカーモ～～ド

	CVector3 m_boxN = CVector3::Zero();				//法線だ

	//箱リスト
	std::list<GameBox*> m_boxList;
	GameBox* m_nowBox = nullptr;			//現在見ているボックスさん
	GameBox* m_nowBox_Stock = nullptr;		//以前見ていたボックスを一時保存！
	std::list<GameBox*> m_nowBoxList;

	//面チェック用
	bool m_surfaceFlag = false;				//m_boxPointの設定フラグ！！！

	//箱拡大用
	CVector3 m_box_N = CVector3::Zero();	//現在見ているボックスの方向
	CVector2 m_mouseMove = { 0.0f,0.0f };	//マウスの移動量を保存（マイナスになったらヤバい）
	CVector3 m_boxScale = CVector3().One(); //拡大率！
	CVector3 m_boxScaleDef = CVector3().One();
	//座標
	CVector3 m_boxPoint[4];
	CVector3 m_boxPoint_Stock[4];			//比較用の格納場所

	//定数
	const float PosHoseiY = 200.0f;					//レイがヒットしなかった時の補正

};

