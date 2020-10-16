#pragma once
#include "system/CGameObjectManager.h"

/// <summary>
/// ロゴに内包されるスプライトが多すぎるのでまとめることにしました
/// </summary>
class TitleRogo {
public:

	//ロゴ（パーツ分け）
	std::map<std::string, SpriteRender*> TitleRogo_Circle;
	std::map<std::string, SpriteRender*> TitleRogo_Mozi;

	SpriteRender* m_titleRogo_Mozi_Hakobun;	//右上ミニ文字「HAKOBUN」

	//ロゴ関連の定数 描画編
	const CVector2 RogoSpriteSize = { 1000.0f,400.0f };		//ロゴ画像の大きさ
	const CVector3 RogoDefPos = { 0.0f,0.0f,0.0f };			//ロゴの基準
	const int RogoCirclePriority = 9;						//サイクルの優先度
	const int RogoMoziPriority = 10;						//文字の優先度（ミニ文字含む）
	//演出編 サイクル
	const int RogoCircleDelay = 2;							//サイクルごとのディレイ
	const float RogoCircleMaxScale = 1.2f;					//サイクルの最大サイズ
	const int RogoCircleScaleTime = 12;						//サイクルの拡大時間
	//演出編 文字
	const int RogoMoziDelay = 6;							//文字ごとのディレイ
	const int RogoMoziTime = 12;							//文字の演出時間
	const float RogoMoziStartHosei = 200.0f;				//文字の初期Y位置補正（落下時）
	const float RogoMoziMove = -250.0f;						//文字の移動量（落下時）
	//演出編 ミニ文字
	const int RogoMiniMoziFadeTime = 12;					//文字の表示時間
	const int RogoMiniMoziFadeDelay = 30;					//文字のディレイ

};

/// <summary>
/// たいとる！
/// ・シングルトン
/// </summary>
class Title final : public IGameObject
{
	static Title* m_instance;
public:
	Title();
	~Title();
	void Update()override;
	void Render()override;

	//コマンドの選択状態
	enum TitleCommand {
		No_Select,		//未選択
		Game_Start,		//はじめから
		Game_Continue,	//つづきから
		Game_End,		//終了
	};

	//コマンドの選択状態を返す
	//選んだコマンドの内部処理はSceneManagerが行う
	const TitleCommand& GetCommand()const {
		return m_nowCommand;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static Title* Title::GetInstance() {
		return m_instance;
	}

private:
	//関数
	void SetUp();
	void CommandSelect();
	//エフェクトアップデート
	void EffectUpdate_RogoEffect();
	void EffectUpdate_TitleEffect();
	void EffectUpdate_CommandWait();
	void EffectUpdate_CommandEffect();
	//ループ背景
	void BG_Update();

	//コマンドじゃん
	TitleCommand m_nowCommand = No_Select;		//最初は未選択
	TitleCommand m_memberCommand = No_Select;	//内部用

	//ライトメーカー
	LightMaker* lm = nullptr;

	//表示状態
	enum TitleEffect {	//エフェクトの状況
		Rogo_Effect,	//ロゴ出し中
		Title_Effect,	//ロゴ出し終わってタイトルに移行中
		Command_Wait,	//プレイヤーの選択待ち
		Command_Effect,	//コマンド選択演出中
	};
	TitleEffect m_titleEffect = Rogo_Effect;	//エフェクト状態

	//モデル
	SkinModelRender* m_ball;									//まわるボール（地球？）
	const CVector3 Ball_DefPos = { 150.0f,-150.0f,-200.0f };	//初期座標
	const CVector3 Ball_RotAxis = CVector3::AxisY();			//初期回転軸
	const float Ball_RotAngle = 35.0f;							//初期回転量
	const float Ball_AutoRotAngle = 1.0f;						//自動回転速度
	const CVector3 Ball_AutoRotAxis = CVector3::AxisX();		//自動回転軸

	SkinModelRender* m_player;				//プレイヤー
	const CVector3 Player_DefPos = { -70.0f,146.0f,-100.0f };	//初期座標（ボールを基準にする）
	const float Player_Scale = 0.5f;							//拡大率
	const float Plyer_RotAngleX = 20.0f;						//X回転量

	SkinModelRender* m_dummyBox;			//ダミーボックス


	//スプライト
	SpriteRender* m_black;					//土台
	const int Black_Priority = 8;			//優先度

	SpriteRender* m_bg1;					//ループ背景1（モデルより先に描く）
	const int BG1_Priority = 0;				//優先度

	SpriteRender* m_bg2;					//ループ背景2（モデルより先に描く）
	const int BG2_Priority = 0;				//優先度
	int m_bgMoveTimer = 0;					//背景用タイマー
	const int BG_MoveTime = 600;			//背景移動時間
	bool m_BG_MoveMode = false;				//移動状態

	//タイトルロゴ
	TitleRogo Rogo;												//ロゴ
	//タイトルコマンド
	SpriteRender* m_command_Start;								//開始コマンド
	SpriteRender* m_command_Continue;							//つづきから！
	SpriteRender* m_command_End;								//ゲーム終了
	const CVector3 Command_DefPos = { -400.0f,0.0f,0.0f };		//初期座標
	const float Command_Y_Hosei = 120.0f;						//コマンド同士の間隔
	const CVector2 CommandSpriteSize = { 350.0f,120.0f };		//コマンド画像の大きさ
	const int Command_Priority = 5;								//優先度
	const float Command_Y_Up = 800.0f;							//コマンドの初期位置Y補正（落とす用）

	//ロゴエフェクト
	float m_rogoEffectTimer = 0.0f;								//ロゴエフェクト用タイマー
	const float RogoEffectRimit = 1.5f;							//このエフェクトが終わって次に切り替わるまでの時間
	//ロゴ→タイトル
	float m_titleEffectTimer = 0.0f;							//タイトルエフェクト用タイマー
	const int TitleMoveTime = 60;								//タイトルエフェクト中の文字の移動時間
	const int TitleFadeTime = 80;								//タイトルエフェクト中のフェード時間
	const CVector2 TitleRogoPos = { -380.0f,230.0f };			//ロゴの最終移動先
	const float TitleRogoScale = 0.5f;							//ロゴの最終拡大率
	const float TitleCommandEffectRimit = 1.0f;					//コマンドが落下するタイミング
	bool m_commandMoveFlag = false;								//コマンド落下フラグ
	const float TitleCommandDrop_YHosei = 15.0f;				//コマンドがオーバーに落下する移動量
	const int TitleCommandDrop_Time = 20;						//コマンドごとの移動時間
	const int TitleCommandDrop_Delay = 10;						//コマンドごとのディレイ
	const float TitleEffectRimit = 2.0f;						//このエフェクトが終わって次に切り替わるまでの時間
	//コマンド選択エフェクト
	const CVector4 CommandMulColor = { 1.0f,0.4f,0.4f,1.0f };	//コマンド選択時の色
	const float CommandSelectMove = 10.0f;						//コマンド選択時の移動量
	const int CommandSelectMoveTime = 3;						//コマンド選択時の移動時間
	//コマンド開始エフェクト
	float m_commandStartEffectTimer = 0.0f;						//コマンドエフェクト用タイマー
	const int CommandAlphaTime = 12;							//選択外のコマンドが消去される時間
	const float CommandStartEffectRimit = 1.0f;					//コマンドが決定されてゲームマネージャーへ返却されるまでの時間

	//定数


};

