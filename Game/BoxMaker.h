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
	/// <summary>
	/// モード
	/// NomalMode→通常 面のクリック待ち
	/// FocusMode→拡大中 左ドラッグで拡大、離すとノーマルモードに戻る
	/// </summary>
	enum BoxMakerMode {
		NomalMode,
		FocusMode,
	};
	/// <summary>
	/// 箱の向き
	/// </summary>
	enum BoxDirection {
		X_Direction,
		Y_Direction,
		Z_Direction,
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
	void ModeChange();

	Game* m_game = nullptr;
	CVector3 m_boxPos = CVector3().Zero();
	Player* m_player = nullptr;

	BoxMakerMode m_boxMakerMode = NomalMode;		//ボックスメイカーモ～～ド

	CVector3 m_boxN = CVector3::Zero();				//法線だ

	//箱リスト
	std::list<GameBox*> m_boxList;
	GameBox* m_nowBox = nullptr;					//現在見ているボックスさん
	GameBox* m_nowBox_Stock = nullptr;				//以前見ていたボックスを一時保存！
	std::list<GameBox*> m_nowBoxList;				//今変更中のボックスりすりす
	GameBox* m_originBox = nullptr;					//最初の箱

	//面チェック用
	bool m_surfaceFlag = false;						//m_boxPointの設定フラグ！！！

	//箱拡大用
	CVector3 m_box_N = CVector3::Zero();			//見ているボックスの方向
	CVector3 m_box_N_Now = CVector3::Zero();		//現在見ているボックスの方向
	CVector2 m_mouseMove = { 0.0f,0.0f };			//マウスの移動量を保存（マイナスになったらヤバい）
	CVector3 m_boxScale = CVector3().One();			//拡大率！
	CVector3 m_boxScaleDef = { 0.1f,0.1f,0.1f };	//デフォルト下限のや～～つ
	CVector3 m_surfaceScaleNew = CVector3::Zero();	//今拡大しようとしている面の大きさ
	CVector3 m_boxScaleHosei = CVector3().One();	//箱のデフォルトサイズと選択した面の大きさを比較して補正を計算する！！！
	CVector3 m_planeScale = CVector3::Zero();		//面の大きさを代入する場所（一時保存）
	CVector3 m_planeScaleNow = CVector3::Zero();	//面の大きさを代入する場所（最新版）
	BoxDirection m_boxDirection;					//現在の箱の向き
	CVector3 m_boxScale_Ratio = CVector3::Zero();	//箱の拡大率比率

	//座標
	//CVector3 m_boxPoint[4];						//箱の4つの座標！
	//CVector3 m_boxPoint_Stock[4];					//比較用の格納場所

	//クリエイト制御
	int m_box_Nom = 1;								//箱の数
	bool m_undoFlag = false;						//アンドゥボタンが押されているかフラグ

	//定数
	const float PosHoseiY = 200.0f;									//レイがヒットしなかった時の補正
	const float m_mouseMoveHosei = 0.5f;							//マウスの移動に応じた拡大率変更の補正値
	const CVector3 m_surfaceScaleDef = { 100.0f,100.0f,100.0f };	//面のデフォルトサイズ
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };

};

