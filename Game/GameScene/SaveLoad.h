#pragma once

/// <summary>
/// ロード画面
/// ・シングルトン
/// </summary>
class SaveLoad : public IGameObject
{
	static SaveLoad* m_instance;
public:
	SaveLoad();
	~SaveLoad();
	void Update()override;
	void Render()override;

	//ロード結果
	enum SaveLoadEnd {
		NULL_LoadEnd,	//空白
		LoadSuccess,	//ロードした
		NoLoad,			//ロードしなかった
	};

	/// <summary>
	/// ロード結果を返す
	/// </summary>
	const SaveLoadEnd& Get_SaveLoadEnd()const {
		return m_saveLoadEnd;
	}
	/// <summary>
	/// 終了フラグを返す
	/// </summary>
	bool GetEndFlag() {
		return m_endFlag;
	}

private:

	void CommandWait();
	void LoadData();

	SaveLoadEnd m_saveLoadEnd = NULL_LoadEnd;					//ロード終了

	//現在の選択状況
	enum NowCommand {
		NullSelect_Command,		//どこも選んでいない
		Yes_Command,			//はいを選択中
		No_Command,				//いいえを選択中
	};
	NowCommand m_nowCommand = NullSelect_Command;		//現在の選択コマンド

	//確認メッセージ
	const wchar_t* LoadCheckText = L"このデータをロードしますか？";
	const wchar_t* LoadCheckText_No = L"セーブデータが見つかりません";
	const wchar_t* LoadNowText = L"ロード成功";
	const wchar_t* YesText = L"ロード";
	const wchar_t* NoText = L"もどる";

	//スプライトレンダー
	SpriteRender* m_BG = nullptr;								//背景
	SpriteRender* m_BG_Acc = nullptr;							//背景アクセサリー

	SpriteRender* m_keis = nullptr;								//ケイスちゃん
	const CVector3 Keis_DefPos = { 240.0f,-90.0f,0.0f };		//座標
	const CVector2 Keis_Size = { 400.0f,400.0f };				//サイズ

	SpriteRender* m_loadBanner = nullptr;						//ロードバナー
	const CVector3 LoadBanner_DefPos = { -500.0f,250.0f,0.0f };	//座標
	const CVector2 LoadBanner_Size = { 600.0f,100.0f };			//サイズ

	SpriteRender* m_BGWindow = nullptr;							//背景ウィンドウ
	const CVector3 BGWindow_DefPos = { -300.0f,-80.0f,0.0f };	//座標
	const CVector2 BGWindow_Size = { 540.0f,300.0f };			//サイズ

	SpriteRender* ButtonWindow_Left = nullptr;					//左ウィンドウ
	SpriteRender* ButtonWindow_Right = nullptr;					//右ウィンドウ
	const CVector3 MenuButtonDefSize = { 200.0f,60.0f,0.0f };	//大きさ
	const CVector2 MenuButtonPosHosei = { 150.0f,-170.0f };		//座標補正（ウィンドウ基準）

	SpriteRender* m_saveWindow = nullptr;						//旧セーブのウィンドウ
	const CVector3 SaveDefPos = { -300.0f,0.0f,0.0f };			//座標
	const CVector2 SaveWindowSize = { 500.0f,100.0f };			//サイズ

	SpriteRender* m_mapIC = nullptr;							//マップアイコン
	const CVector3 MapIC_PosHosei = { -180.0f, 0.0f,0.0f };		//座標補正（セーブウィンドウ基準）
	const CVector2 MapIC_Size = { 80.0f,80.0f };				//サイズ
	
	//フォントレンダー
	FontRender* m_loadChackText = nullptr;						//ロードしますか？orセーブデータがありませんorロードしました
	const CVector2 LoadChackTextPos = { -480.0f,-75.0f };		//テキストの座標
	const float Check_FontSize = 0.5f;							//セーブしますか？の大きさ
	const CVector4 Check_FontColor = { 1.0f,0.5f,0.0f,1.0f };	//チェックフォントの色
	const float LoadX_Hosei = 100.0f;							//ロードしましたのX補正

	FontRender* Yes_Font = nullptr;								//はいのテキスト
	const float YesFont_XHosei = -5.0f;							//はいのテキストX補正
	FontRender* No_Font = nullptr;								//いいえのテキスト
	const float NoFont_XHosei = -5.0f;							//いいえのテキストX補正
	const CVector2 YesNo_Font_Hosei = { -40.0f,23.0f };			//↑テキストの座標補正
	const float YesNo_FontSize = 0.6f;							//大きさ

	FontRender* m_load_PlayerLevel = nullptr;					//データのプレイヤーレベル
	const CVector2 PlayerLevel_Hosei = { -130.0f,35.0f };		//↑テキストの座標補正

	FontRender* m_load_PlayerHP = nullptr;						//データのプレイヤーHP
	const CVector2 PlayerHP_Hosei = { 10.0f,35.0f };			//↑テキストの座標補正

	FontRender* m_load_PlayerPlace = nullptr;					//データのプレイヤー位置
	const CVector2 PlayerPlace_Hosei = { -130.0f,-5.0f };		//↑テキストの座標補正

	const float SaveDataFontSize = 0.4f;						//セーブデータ情報の大きさ

	//ロード処理関連
	FILE * fp = nullptr;										//ロードファイル
	bool m_fifeFlag = false;									//ファイル存在する？
	GameData* m_gameData_Load = nullptr;						//旧データ用臨時

	//画面フェードアウト
	int m_fadeoutTimer = 0;										//フェードアウトタイマー
	const int FadeOutLimit = 60;								//フェードアウト制限時間
	int m_fadeinTimer = 0;										//フェードインタイマー
	const int FadeInLimit = 60;									//フェードイン制限時間
	const int FadeInEndLimit = 120;								//フェードイン制限時間+終了時間

	bool m_loadFlag = false;									//ロードフラグ
	bool m_noLoadFlag = false;									//ロードしないフラグ
	bool m_endFlag = false;										//これをtrueにしたら終了
	bool m_loadDataFlag = false;								//ゲームデータを1回だけロードする

	//ケイスアニメーション
	int m_keisTimer = 0;										//ケイス用タイマー
	const int KeisAnimeLimit = 60;								//ケイス用アニメーションリミット
	bool m_keisAnimePattern = false;							//ケイス用アニメーションパターン

	//効果音
	bool m_seFlag = false;										//効果音フラグ

	//定数
	const int SpriteNo = 8;										//スプライトの基準となる優先度
	const float NoActiveAlpha = 0.5f;							//非選択の時の半透明アルファ値
	const CVector4 CanNotSelect = { 0.2f,0.2f,0.2f,0.5f };		//選択できません
	const int DeleteTime = 6;									//削除時間

};

