#pragma once

/// <summary>
/// 立ち絵関連
/// </summary>
class GameEffect_Stand {

public:
	//立ち絵呼び出し用
	enum Stand_Name {
		Stand_Null,		//空白
		Stand_Normal,	//通常
		Stand_Happy,	//にっこり
		Stand_Sad,		//悲しい
		Stand_Ang,		//おこ
		Stand_Wow,		//びっくりした
	};
	//立ち絵操作コマンド
	enum Stand_Command {
		New_Stand,		//表示
		Delete_Stand,	//削除
		Jump_Stand,		//ジャンプする
		Shake_Stand,	//震える
	};

	/// <summary>
	/// 準備
	/// </summary>
	void StandInit();

	/// <summary>
	/// 立ち絵操作
	/// </summary>
	/// <param name="stand">表示する立ち絵</param>
	/// <param name="command">コマンド
	/// 
	/// New_Stand->第一引数に設定した立ち絵を表示
	///			   ※既に立ち絵表示済みの場合、右からスライドインする演出をスキップする
	/// Delete_Stand->問答無用で立ち絵を消去
	/// Jump_Stand->立ち絵をジャンプさせる（ステータスは定数）
	/// Shake_Stand->立ち絵が震える（ステータスは定数）
	/// 
	/// </param>
	/// <remarks>
	/// 
	/// 立ち絵が空白の場合、自動でNullが入ります
	/// Nullの場合立ち絵は更新されず現在の物が使われます
	/// 
	/// コマンドが空白の場合、自動でNew_Standが入ります
	/// 
	/// </remarks>
	void StandControl(Stand_Name stand = Stand_Null, Stand_Command command = Stand_Command::New_Stand);

private:

	struct Stand_Data {		//立ち絵データ構造体
		wchar_t* SpriteName;	//スプライトファイル名
		float High;				//高さ
		float Wide;				//幅
	};

	const Stand_Data Game_Stand_Data[6]{	//立ち絵配列
		{ L"test",100.0f,100.0f },		//予備データ
		{ L"Assets/sprite/keis.dds",588.0f,1240.0f },
		{ L"Assets/sprite/keis_happy.dds",588.0f,1240.0f },
		{ L"Assets/sprite/keis_sad.dds",588.0f,1240.0f },
		{ L"Assets/sprite/keis_ang.dds",588.0f,1240.0f },
		{ L"Assets/sprite/keis_wow.dds",588.0f,1240.0f },
	};

	//立ち絵表示用
	SpriteRender* m_standSprite;				//立ち絵のスプライトです！
	const int StandSpritePriority = 5;			//立ち絵の優先度

	Stand_Name m_nowStand = Stand_Name::Stand_Null;		//現在の立ち絵

	const CVector3 StandDefPos_Move = { 700.0f,-250.0f,0.0f };	//移動前
	const CVector2 StandDefPos = { 280.0f,-250.0f };			//移動後
	const CVector2 StandDefPos2 = { 250.0f,-250.0f };			//移動後2
	const float StandDefScale = 0.9f;

	bool m_standFlag = false;				//立ち絵表示中？

	//ジャンプ演出用定数
	const float JumpMove_A = 80.0f;		//最初のジャンプY距離
	const int JumpWait_A = 4;			//最初のジャンプ時間
	const float JumpMove_B = 20.0f;		//2回目のジャンプY距離
	const int JumpWait_B = 2;			//2回目のジャンプ時間

	//震え演出用定数
	const float ShakeMove_X = 50.0f;	//シェイクのX移動量
	const int ShakeCount = 6;			//シェイク回数
	

};

/// <summary>
/// メッセージ関連
/// </summary>
class GameEffect_Message {

public:

	/// <summary>
	/// 準備
	/// </summary>
	void MessageInit();

	/// <summary>
	/// ワンコマンドで会話します
	/// </summary>
	/// <param name="Message">会話内容</param>
	void MessageEffect(wchar_t* Message);

	/// <summary>
	/// メッセージ送り中は呼んでね～
	/// </summary>
	void MessageUpdate();

	/// <summary>
	/// メッセージ送りされた瞬間だけtrueを返す
	/// </summary>
	/// <returns>くりつく</returns>
	bool GetMessageOkuriFlag() {
		return m_messageClickFlag;
	}

private:

	//ログ関数
	void LogChange(bool Flag);
	void LogUpdate();

	//会話枠表示用
	SpriteRender* m_windowSprite;			//会話ウィンドウのスプライト
	const int WindowSpritePriority = 6;		//会話ウィンドウの優先度

	SpriteRender* m_windowOkuriSprite;				//会話送りアイコンのスプライト
	const int WindowOkuriSpritePriority = 6;		//会話送りアイコンの優先度

	SpriteRender* m_messageSkipSprite;				//スキップ中のスプライト
	const int MessageSkipSpritePriority = 6;		//スキップ中の優先度

	FontRender* m_messageFont;				//メッセージ
	const int MessageFontPriority = 7;		//メッセージの優先度

	FontRender* m_messageSkipOshiraseFont;				//スキップのお知らせ
	const int MessageSkipOshiraseFontPriority = 7;		//スキップお知らせの優先度

	SpriteRender* m_logBlack;				//ログウィンドウの背景スプライト
	SpriteRender* m_logWindow;				//ログウィンドウのスプライト
	const int LogWindowSpritePriority = 7;		//ログウィンドウとブラックアウトの優先度

	FontRender* m_logFont;				//ログ
	const int LogFontPriority = 7;		//ログの優先度

	//座標指定
	const CVector3 WindowDefPos = { -200.0f,50.0f,0.0f };
	const CVector3 WindowOkuriDefPos = { -50.0f,-50.0f,0.0f };
	const CVector2 TextDefPos = { -350.0f,125.0f };
	const CVector2 TextSkipDefPos = { -600.0f,-300.0f };

	//メッセージ送りアイコン
	const float MessageOkuriMove = 50.0f;	//メッセージ送りアイコンの移動量
	const int MessageOkuriMoveTime = 30;	//メッセージ送りアイコンの移動が1ループするフレーム数

	//色指定
	const CVector3 TextColor = { 1.0f,0.1f,0.3f };		//テキストの色

	//メッセージフラグ
	bool m_nowMessage = false;			//メッセージ表示ちう
	bool m_messageOkuriWait = false;	//クリック待ち！
	bool m_messageClickFlag = false;	//メッセージ送りされた瞬間だけtrueになる これを取得したらメッセージ送りがスムーズ

	//メッセージ送り
	const int MessageDelateWait = 4;	//メッセージが消えるまでの待ち時間
	int m_messageTimer = 0;

	//スキップ
	bool m_skipFlag = false;			//スキップ中？
	int m_skipTimer = 0;				//スキップタイマー
	const int SkipLimit = 30;			//スキップの制限時間

	//スキップお知らせテキスト
	const wchar_t* SkipText = L"ＳＰＡＣＥ長押し：スキップ";

	//ログ関連
	bool m_logFlag = false;			//ログ中？？？
	struct LogData {
		wchar_t* Name;		//話し手の名前
		wchar_t* Message;	//会話内容
	};
	wchar_t m_logText[4096] = L"";								//ログ保存用
	int m_logHigh = 0;											//ログの高さ
	int m_logCursorPos = 0;										//ログの参照位置
	const CVector2 LogWindowSize = { 800.0f,600.0f };			//ログウィンドウの大きさ
	const float LogFontSize = 0.6f;								//ログテキストの大きさ
	const CVector2 LogFontPosition = { -350.0f,-300.0f };		//ログテキストの基準座標
	const int LogTime = 6;										//ログの表示＆消去にかかる時間
	const float LogOffsetY = 38;								//1行ごとのY補正
	const int DeltaHoseiY = 10;									//ログでホイール入力された時の移動量補正

};

class GameEffect_AnimationSprite {

public:
	//アニメ呼び出し用
	enum Anime_Name {
		Anime_LevelUp,		//レベルアップ
	};

	/// <summary>
	/// パターンアニメーション呼び出し
	/// </summary>
	/// <param name="m_animeName">呼び出すアニメの種類</param>
	/// <param name="pos">座標</param>
	/// <param name="m_scale">大きさ</param>
	void NewAnimationSprite(Anime_Name m_animeName, CVector3 pos, CVector3 m_scale = CVector3().One(), int priority = 0);

	void SpriteAnimationUpdate();

private:

	//スプライトレンダーのリスト アルファが0になったレンダーを消去すれば大量にアニメを出しても大丈夫！多分！
	struct SpriteRenderList
	{
		SpriteRender* SpriteRender_pt;
		bool DeleteFlag = false;
	};
	std::list<SpriteRenderList> m_spriteRenderList;	//ここに保存される

	int AnimationNom = 0;	//作成したアニメーション数

	struct SpriteAnime_Data {		//スプライトパターンデータ構造体
		wchar_t* SpriteName;	//スプライトファイル名
		float High;				//高さ
		float Wide;				//幅
		int Pattern;			//縦パターン数
		bool Loop;				//ループする？
	};

	//アニメデータ
	const SpriteAnime_Data Game_SpriteAnime_Data[2]{
		{ L"Assets/sprite/levelUp_8F.dds", 450.0f, 2000.0f, 8,false },
		{ L"Assets/sprite/levelUp_8F.dds", 450.0f, 2000.0f, 8,false },

	};

};

/// <summary>
/// ゲームの演出サポート
/// ※シングルトン
/// </summary>
class GameEffect
{
	static GameEffect* m_instance;
public:

	GameEffect();
	~GameEffect();

	/// <summary>
	/// インスタンスを取得シリーズ
	/// </summary>
	/// <returns>インスタンスです</returns>
	static GameEffect* GameEffect::GetInstance() {
		return m_instance;
	}
	GameEffect_Stand* GetInstance_Stand() {
		return &m_stand;
	}
	GameEffect_Message* GetInstance_Message() {
		return &m_message;
	}
	GameEffect_AnimationSprite* GetInstance_SpriteAnime() {
		return &m_spriteAnime;
	}

	/// <summary>
	/// 更新処理
	/// </summary>
	void GameEffectUpdate() {
		m_message.MessageUpdate();
		m_spriteAnime.SpriteAnimationUpdate();
	}

	/// <summary>
	/// 2つの会話処理をセットにしたもの
	/// </summary>
	/// <param name="Message">メッセージ</param>
	/// <param name="stand">立ち絵</param>
	/// <param name="command">演出</param>
	void EasyEffect(wchar_t* Message,
		GameEffect_Stand::Stand_Name stand = GameEffect_Stand::Stand_Name::Stand_Null,
		GameEffect_Stand::Stand_Command command = GameEffect_Stand::Stand_Command::New_Stand){

		m_message.MessageEffect(Message);
		m_stand.StandControl(stand, command);

	}

private:
	GameEffect_Stand m_stand;
	GameEffect_Message m_message;
	GameEffect_AnimationSprite m_spriteAnime;
};
