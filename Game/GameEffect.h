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
	/// Delete_Stand->問答無用で立ち絵を消去
	/// Jump_Stand->立ち絵をジャンプさせる（ステータスは定数）
	/// </param>
	void StandControl(Stand_Name stand, Stand_Command command);

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

	const CVector3 StandDefPos_Move = { 700.0f,-250.0f,0.0f };	//移動前
	const CVector2 StandDefPos = { 280.0f,-250.0f };			//移動後
	const CVector2 StandDefPos2 = { 250.0f,-250.0f };			//移動後2
	const float StandDefScale = 0.9f;

	bool m_standFlag = false;				//立ち絵表示中？

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

private:

	//会話枠表示用
	SpriteRender* m_windowSprite;			//会話ウィンドウのスプライト
	const int WindowSpritePriority = 6;		//会話ウィンドウの優先度

	FontRender* m_messageFont;				//メッセージ
	const int MessageFontPriority = 7;		//メッセージの優先度

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

private:
	GameEffect_Stand m_stand;
	GameEffect_Message m_message;

};
