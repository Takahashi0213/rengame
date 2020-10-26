#pragma once

/// <summary>
/// 「全箱解放」
/// 箱を全て削除するコマンド
/// BAD(BoxAllDelete)
/// </summary>
class Menu_BoxAllDelete
{
public:
	Menu_BoxAllDelete();
	~Menu_BoxAllDelete();

	//アップデート（GameMenuに呼んでもらう）
	void DeleteCheckUpdate();
	//コマンドのフェードアウト
	void CommandEnd();

	bool GetDeleteFlag() {
		return m_deleteFlag;
	}

private:


	//現在の選択状況
	enum NowCommand {
		NullSelect_Command,		//どこも選んでいない
		Yes_Command,			//はいを選択中
		No_Command,				//いいえを選択中
	};
	NowCommand m_nowCommand = NullSelect_Command;		//現在の選択コマンド

	//箱を消すときの確認メッセージ
	const wchar_t* HeaderText = L"全箱解放";
	const wchar_t* CheckText = L"全ての箱を削除して\nマナを全回復しますか？";
	const wchar_t* YesText = L"ＯＫ！";
	const wchar_t* NoText = L"やめる";

	//スプライトレンダー
	SpriteRender* MenuWindow;									//ウィンドウ
	const CVector3 MenuDefPos = { -200.0f,-50.0f,0.0f };		//座標
	const CVector2 DefMenuWindowSize = { 600.0f,400.0f };		//サイズ

	SpriteRender* ButtonWindow_Left;							//左ウィンドウ
	SpriteRender* ButtonWindow_Right;							//右ウィンドウ
	const CVector3 MenuButtonDefSize = { 200.0f,60.0f,0.0f };	//大きさ
	const CVector2 MenuButtonPosHosei = { 150.0f,-200.0f };		//座標補正（ウィンドウ基準）

	//フォント
	FontRender* Header_Font;									//ウィンドウのヘッダー
	const float Header_FontSize = 0.6f;							//ヘッダーテキストの大きさ
	const CVector2 Header_Font_Hosei = { -80.0f,190.0f };		//ヘッダーテキストの座標補正

	FontRender* Check_Font;										//消しますか？のテキスト
	const CVector2 Check_Font_Hosei = { -180.0f,20.0f };		//消しますか？の座標補正

	FontRender* Yes_Font;										//はいのテキスト
	const float YesFont_XHosei = 5.0f;							//はいのテキストX補正
	FontRender* No_Font;										//いいえのテキスト
	const float NoFont_XHosei = -5.0f;							//いいえのテキストX補正
	const CVector2 YesNo_Font_Hosei = { -40.0f,23.0f };			//↑テキストの座標補正

	//削除フラグ
	bool m_deleteFlag = false;									//trueをGameMenuに返すと削除してもらえる

	//定数
	const int SpriteNo = 8;										//スプライトの基準となる優先度
	const float NoActiveAlpha = 0.5f;							//非選択の時の半透明アルファ値
	const int DeleteTime = 6;									//削除時間

};

