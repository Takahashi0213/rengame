#pragma once

/// <summary>
/// メニューのアレコレを総括する…なんやろなあ
/// ・シングルトン
/// </summary>
class GameMenu
{
	static GameMenu* m_instance;
public:
	enum MenuCommand {	//メニューの項目
		Create,			//マナ、アイテム、スターマネーを使用して色々創造
		Box_Release,	//全箱解放（箱を全て消去してマナを回復）
		Library,		//図鑑やあらすじ
		Save,			//セーブ
	};

	GameMenu();
	~GameMenu();

	//GameUIが呼んでくれる
	void GameMenuUpdate();

	/// <summary>
	/// マウスカーソルがメニューボタンに被ってたらtrue
	/// </summary>
	bool GetSelectFlag() {
		return m_selectFlag;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static GameMenu* GameMenu::GetInstance() {
		return m_instance;
	}

private:

	//ｴﾌｪｸﾄｩ
	void Update_Effect(int mode);
	//こまんど
	void Update_Command();
	void Update_CommandDelta(const int delta, bool& flag);
	void Update_CommandDraw(bool drawStile);

	//メンバ変数
	const int SpriteNo = 7;		//スプライトの基準となる優先度
	const float MenuMove = 370.0f;	//メニューを開閉する時の移動量
	const float MenuMove_Over = 30.0f;	//メニューを開閉する時の移動量（オーバーラン用）
	const int MenuMoveTime = 4;	//メニューを開閉する時間
	int m_menuMoveTimer = 0;
	MenuCommand m_nowMenuCommand = MenuCommand::Create;	//現在のコマンドォ！
	bool m_selectFlag = false;		//選択中

	//メニュー関連の画像が多すぎめんどい
	std::vector<SpriteRender*> m_spriteRenderList;
	std::vector<FontRender*> m_fontRenderList;

	//メニュー枠関連
	const CVector2 DefMenuWindowSize = { 600.0f,742.0f };
	const CVector2 DefMenuWindow_2Size = { 350.0f,150.0f };		//Window2は説明欄

	const CVector3 DefMenuWindowPosition = { 530.0f,0.0f,1.0f };
	const CVector3 DefMenuWindow_2Position = { 450.0f,-250.0f,1.0f };
	const CVector3 DefMenuButtonPosition = { 220.0f,300.0f,1.0f };

	const float MenuButtonSize = 150.0f;
	const float MenuButtonSize_Hosei = 150.0f;

	//魔法陣
	const float MenuMahojinSize = 1000.0f;
	const CVector3 MenuMahojinDefPosition = { 1000.0f,-60.0f,1.0f };
	const float MezuMahojinScale = 0.6f;
	const float MenuMahojinAlpha = 0.2f;
	const float MenuMahojinRotSpeed = -0.2f;

	//メニューロゴ
	const CVector2 MenuLogoSize = { 450.0f,200.0f };
	const CVector2 MenuLogoAccSize = { 70.0f,70.0f };	//星の部分
	const CVector2 MenuLogoNami = { 450.0f,338.0f };
	const float MenuLogoScale = 0.8f;
	const CVector3 DefMenuLogoPosition = { 830.0f,280.0f,1.0f };
	const CVector3 DefMenuLogo_AccPosition = { 980.0f,300.0f,1.0f };
	const int MenuLogoMoveSpeed = 300;	//波の移動
	const int MenuLogo_AccRotSpeed = 30;	//星の回転
	int MenuLogoTimer = 0;
	int MenuLogoRotTimer = 0;
	const float MenuAccRot = 2.0f;		//1フレームごとの回転量

	//コマンド
	const CVector2 MenuCommandWindowDefSize = { 430.0f,75.0f };	//画像自体の大きさ
	const CVector2 MenuCommandWindowSize = { 350.0f,75.0f };	//最終の大きさ
	const float MenuCommand_SideScale = 350.0f;	//両端の大きさ
	const CVector3 DefMenuCommandPosition = { 450.0f,160.0f,1.0f };
	const float MenuCommand_YHosei = 90.0f;	//コマンドごとのY補正
	const CVector3 TextColor = { 0.1f,0.1f,0.5f };		//テキストの色
	const float TextFontSize = 0.6f;						//テキストの大きさ
	const CVector2 DefMenuCommand_TextPosition = { 375.0f,182.0f };
	const float SaveX_Hosei = 30.0f;
	//アクセサリー

	//説明文
	const CVector3 SetumeiTextColor = { 0.9f,0.9f,0.9f };		//説明文の色
	const float TextFontSize_Setumei = 0.5f;					//テキストの大きさ
	const CVector2 DefSetumei_TextPosition = { -140.0f,60.0f };	//説明文ウィンドウを基準にした座標
	//内容
	const wchar_t* SetumeiBun[4]{
		L"クリエイトの\n説明文だよ",
		L"全箱解放の\n説明文です",
		L"ライブラリの\n説明文だゾ",
		L"セーブの\n説明文だｯ！！",
	};

	//選択カーソル
	const CVector3 DefCursorPosition = { 280.0f,160.0f,1.0f };	//一番上のポジション！！
	int m_cursorMoveTimer = 0;			//カーソルの左右移動タイマー
	const int CursorMoveLimit = 20;		//カーソルが左右1往復するまでの時間
	const float Cursor_YMove = 10.0f;	//カーソルのY移動量

	//メニュー中のブラー関連
	const float BlurSpeed = 1.0f;	//1フレームごとの重み増減数
	const float MaxBlur = 5.0f;		//ブラーの最大重み

	//メニュー操作関連

	//※セレクトモードの仕様メモ
	//
	//falseならカーソルは重なっていないのでホイールで操作、マウスカーソルの位置は見ない
	//trueならカーソルがどれかのボタンに重なっているので、位置を見る
	//trueの時にホイールを操作されたらモードをfalseに変更し、
	//再度マウスカーソルを合わせるまでモードはずっとfalse
	bool m_selectMode = false;
	bool m_selectOverFlag = false;	//↑がtrueの時にホイールを操作されたよフラグ
	bool m_selectOverFlag_ = false;	//予備

	//↓ここから↓スプライト↓

	//全体
	SpriteRender* MenuWindow;
	SpriteRender* MenuWindow2;		//説明欄
	SpriteRender* MenuButton;
	//あくせさりぃ
	SpriteRender* MenuLogo_Under;
	SpriteRender* MenuLogo;
	SpriteRender* MenuLogo_Up;
	SpriteRender* Menu_Mahojin;		//魔法陣
	//コマンドです
	SpriteRender* MenuCommand_Sprite1;		//くりえいと
	FontRender* MenuCommand_Font1;
	SpriteRender* MenuCommand_Sprite2;		//全箱解放
	FontRender* MenuCommand_Font2;
	SpriteRender* MenuCommand_Sprite3;		//ライブラリー
	FontRender* MenuCommand_Font3;
	SpriteRender* MenuCommand_Sprite4;		//セーブ
	FontRender* MenuCommand_Font4;
	//コマンドアクセサリー

	//説明文
	FontRender* MenuSetumeiFont;
	//カーソル
	SpriteRender* MenuCommand_Cursor;		//選択カーソル

};

