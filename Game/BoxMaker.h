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
class BoxMaker final : public IGameObject
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
	/// プレイヤーのポインタを保存
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

	//箱の色々を取得する
	std::list<GameBox*> GetBoxList() {
		return m_boxList;
	}

	/// <summary>
	/// 箱の消去
	/// </summary>
	/// <param name="deleteBox"></param>
	void BoxDelete(GameBox* deleteBox);
	std::list<GameBox*>::iterator BoxDelete_it(std::list<GameBox*>::iterator deleteBox_it);
	//箱の全消去
	void BoxAllDelete();

private:
	void BoxUpdate();
	void ModeChange();
	//作成地点とプレイヤーの距離が一定以下じゃないと作れない
	bool BoxCreateCheck();

	Game* m_game = nullptr;
	Player* m_player = nullptr;

	CVector3 m_boxPos = CVector3().Zero();			//箱座標

	BoxMakerMode m_boxMakerMode = NomalMode;		//ボックスメイカーモード

	CVector3 m_boxN = CVector3::Zero();				//法線だ

	//箱リスト
	std::list<GameBox*> m_boxList;					//箱リスト
	std::list<int>m_manaList;						//この箱がどのくらいマナ圧迫してるかな？のリスト
	GameBox* m_nowBox = nullptr;					//現在見ているボックス
	GameBox* m_nowBox_Stock = nullptr;				//以前見ていたボックスを一時保存！
	std::list<GameBox*> m_nowBoxList;				//今変更中のボックスリスト
	GameBox* m_originBox = nullptr;					//最初の箱

	//面チェック用
	bool m_surfaceFlag = false;						//m_boxPointの設定フラグ

	//箱拡大用
	CVector3 m_box_N = CVector3::Zero();			//見ているボックスの方向
	CVector3 m_box_N_Now = CVector3::Zero();		//現在見ているボックスの方向
	CVector2 m_mouseMove = { 0.0f,0.0f };			//マウスの移動量を保存（マイナスになったらヤバい）
	CVector3 m_boxScale = CVector3().One();			//拡大率！
	CVector3 m_boxScaleDef = { 0.1f,0.1f,0.1f };	//デフォルト下限のやつ
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
	int m_box_Nom = 1;								//存在する箱の数
	bool m_undoFlag = false;						//アンドゥボタンが押されているかフラグ

	//マナ制御
	int m_downMana = 0;								//箱生成のマナ減少量
	int m_startMana = 0;							//移行時のマナ
	int m_downMana_Stock = 0;						//拡大縮小用一時保存
	int m_manaHosei = 0;							//拡大縮小用補正

	//定数
	const float PosHoseiY = 200.0f;									//レイがヒットしなかった時の補正
	const float m_mouseMoveHosei = 0.5f;							//マウスの移動に応じた拡大率変更の補正値
	const CVector3 m_surfaceScaleDef = { 100.0f,100.0f,100.0f };	//面のデフォルトサイズ
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };			//箱の初期スケール
	const float Player_Box_MaxRange = 500.0f;						//箱作成の限界距離

	//クリエイトモードに移行するために必要な最低マナ数、初代箱を生成するときに消費するマナ数でもある
	const int CreateModeChangeBorder = 10;
	const float DefManaHosei = 5.0f;								//箱作成の消費マナ補正 結果に除算→値が大きいほど安くなる

};

