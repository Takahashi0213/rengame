#pragma once

/// <summary>
/// セーブ画面
/// </summary>
class Menu_Save
{
public:
	Menu_Save();
	~Menu_Save();

	//アップデート（GameMenuに呼んでもらう）
	void SaveUpdate();
	//コマンドのフェードアウト
	void CommandEnd();

	bool GetDeleteFlag() {
		return m_deleteFlag;
	}

private:

	//セーブ演出
	void SaveEffect();

	//現在の選択状況
	enum NowCommand {
		NullSelect_Command,		//どこも選んでいない
		Yes_Command,			//はいを選択中
		No_Command,				//いいえを選択中
	};
	NowCommand m_nowCommand = NullSelect_Command;		//現在の選択コマンド

	//確認メッセージ
	const wchar_t* HeaderText = L"セーブ";
	const wchar_t* SaveCheckText = L"現在の状況をセーブしますか？";
	const wchar_t* SaveNowText = L"セーブしました！";
	const wchar_t* YesText = L"セーブ";
	const wchar_t* NoText = L"やめる";
	const wchar_t* NewText = L"新";
	const wchar_t* OldText = L"旧";

	//スプライトレンダー
	SpriteRender* MenuWindow = nullptr;							//ウィンドウ
	const CVector3 MenuDefPos = { -200.0f,-100.0f,0.0f };		//座標
	const CVector2 DefMenuWindowSize = { 700.0f,500.0f };		//サイズ

	SpriteRender* ButtonWindow_Left = nullptr;					//左ウィンドウ
	SpriteRender* ButtonWindow_Right = nullptr;					//右ウィンドウ
	const CVector3 MenuButtonDefSize = { 200.0f,60.0f,0.0f };	//大きさ
	const CVector2 MenuButtonPosHosei = { 150.0f,-200.0f };		//座標補正（ウィンドウ基準）

	SpriteRender* NewSaveWindow = nullptr;						//新しいセーブのウィンドウ
	const CVector3 NewSaveDefPos = { -200.0f,0.0f,0.0f };		//座標
	SpriteRender* OldSaveWindow = nullptr;						//旧セーブのウィンドウ
	const CVector3 OldSaveDefPos = { -200.0f,-150.0f,0.0f };	//座標
	const CVector2 SaveWindowSize = { 500.0f,100.0f };			//サイズ

	SpriteRender* NewMapIC = nullptr;							//マップアイコン新
	SpriteRender* OldMapIC = nullptr;							//マップアイコン旧
	const CVector3 MapIC_PosHosei = { -180.0f, 0.0f,0.0f };		//座標補正（セーブウィンドウ基準）
	const CVector2 MapIC_Size = { 80.0f,80.0f };				//サイズ

	SpriteRender* SaveCursor = nullptr;							//上下するセーブカーソル
	const CVector3 SaveCursorPos = { -200.0f,-73.0f,0.0f };		//座標
	const CVector2 DefSaveCursorSize = { 60.0f,40.0f };			//サイズ
	const float SaveCursorMove = 5.0f;							//移動量
	const int SaveCursorMoveTime = 6;							//移動時間

	//フォント
	FontRender* Header_Font = nullptr;							//ウィンドウのヘッダー
	const float Header_FontSize = 0.6f;							//ヘッダーテキストの大きさ
	const CVector2 Header_Font_Hosei = { -60.0f,235.0f };		//ヘッダーテキストの座標補正

	FontRender* Check_Font = nullptr;							//セーブしますか？のテキスト
	const float Check_FontSize = 0.5f;							//セーブしますか？の大きさ
	const CVector2 Check_Font_Hosei = { -190.0f,-120.0f };		//セーブしますか？の座標補正
	const CVector2 Check_Font_Hosei2 = { -115.0f,-120.0f };		//セーブしますか？の座標補正2

	FontRender* Yes_Font = nullptr;								//はいのテキスト
	const float YesFont_XHosei = -5.0f;							//はいのテキストX補正
	FontRender* No_Font = nullptr;								//いいえのテキスト
	const float NoFont_XHosei = -5.0f;							//いいえのテキストX補正
	const CVector2 YesNo_Font_Hosei = { -40.0f,23.0f };			//↑テキストの座標補正

	FontRender* NewSave_Text = nullptr;							//「新」のテキスト
	FontRender* OldSave_Text = nullptr;							//「旧」のテキスト
	const float NewOld_FontSize = 0.6f;							//新旧テキストの大きさ
	const CVector2 NewOld_Font_Hosei = { -310.0f,25.0f };		//↑テキストの座標補正

	FontRender* NewSave_PlayerLevel = nullptr;					//新データのプレイヤーレベル
	FontRender* OldSave_PlayerLevel = nullptr;					//旧データのプレイヤーレベル
	const CVector2 NewOld_PlayerLevel_Hosei = { -130.0f,35.0f };//↑テキストの座標補正

	FontRender* NewSave_PlayerHP = nullptr;						//新データのプレイヤーHP
	FontRender* OldSave_PlayerHP = nullptr;						//旧データのプレイヤーHP
	const CVector2 NewOld_PlayerHP_Hosei = { 10.0f,35.0f };		//↑テキストの座標補正

	FontRender* NewSave_PlayerPlace = nullptr;					//新データのプレイヤー位置
	FontRender* OldSave_PlayerPlace = nullptr;					//旧データのプレイヤー位置
	const CVector2 NewOld_PlayerPlace_Hosei = { -130.0f,-5.0f };//↑テキストの座標補正

	const float NewOld_SaveDataFontSize = 0.4f;					//セーブデータ情報の大きさ

	//まとめて動かしたい！
	std::vector<SpriteRender*> m_newSave_SpriteRenderList;
	std::vector<FontRender*> m_newSave_FontRenderList;
	std::vector<SpriteRender*> m_oldSave_SpriteRenderList;
	std::vector<FontRender*> m_oldSave_FontRenderList;

	//セーブ演出関連
	bool m_saveFlag = false;									//セーブフラグ（セーブ中）
	int m_saveTimer = 0;										//セーブタイマー
	const int SaveTimeLimit = 40;								//セーブ終了時間
	const CVector3 EffectPos = { -200.0f,0.0f,0.0f };			//エフェクト座標

	const float SaveMove_1 = 10.0f;								//反動
	const float SaveMove_2 = -170.0f;							//下がる
	const float SaveMove_3 = 60.0f;								//上がる
	const int MoveTime_1 = 3;									//移動時間
	const int MoveTime_2 = 6;									//移動時間
	const int MoveTime_3 = 10;									//移動時間

	//セーブ処理関連
	FILE* fp = nullptr;											//セーブファイル
	bool m_fifeFlag = false;									//ファイル存在する？
	GameData* m_gameData_Load = nullptr;						//旧データ用臨時

	//削除フラグ
	bool m_deleteFlag = false;									//trueをGameMenuに返すと削除してもらえる

	//定数
	const int SpriteNo = 8;										//スプライトの基準となる優先度
	const float NoActiveAlpha = 0.5f;							//非選択の時の半透明アルファ値
	const int DeleteTime = 6;									//削除時間


};

