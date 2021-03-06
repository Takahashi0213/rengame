#pragma once
#include "Menu_BoxAllDelete.h"

//項目内容
#include "Menu_Create.h"
#include "Menu_BoxAllDelete.h"
#include "Menu_Save.h"

/// <summary>
/// メニューのアレコレを総括する
/// ・シングルトン
/// </summary>
class GameMenu final
{
	static GameMenu* m_instance;
public:
	enum MenuCommand {	//メニューの項目
		Create,			//マナ、アイテム、スターマネーを使用して色々創造
		Box_Release,	//全箱解放（箱を全て消去してマナを回復）
		Library,		//図鑑やあらすじ
		Save,			//セーブ
		CommandNum,		//コマンド数
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

	//ｴﾌｪｸﾄ
	void Update_Effect(const int& mode);
	void GameMenu_NoActiveEffect();								//コマンド選択中はメニューを半透明にする
	//コマンド
	void Update_Command();										//マウスカーソルの位置でコマンドの移動方法を変える
	void Update_CommandDelta(const int delta, bool& flag);		//マウスホイールの動作からコマンド位置を上下させる
	void Update_CommandDraw(bool drawStile);					//選択中のコマンドとそれ以外のコマンドで描画を変える処理
	void Update_MenuEnter(const int& leftKey);					//メニューのコマンド決定処理
	void Update_CommandNow();									//コマンド実行中、自動でアップデートする処理
	//メニューコマンドを削除
	void DeleteMenuCommand();									//コマンドを削除する

	//メンバ変数
	const int SpriteNo = 7;										//スプライトの基準となる優先度
	const float MenuMove = 370.0f;								//メニューを開閉する時の移動量
	const float MenuMove_Over = 30.0f;							//メニューを開閉する時の移動量（オーバーラン用）
	const int MenuMoveTime = 4;									//メニューを開閉する時間
	int m_menuMoveTimer = 0;									//移動用タイマー
	MenuCommand m_nowMenuCommand = MenuCommand::Create;			//現在のコマンド
	bool m_selectFlag = false;									//選択中
	bool m_commandNow = false;									//コマンド内容実行中
	bool m_selectSE_Flag = false;								//メニューボタンの効果音フラグ

	//メニュー関連の画像が多すぎ
	std::vector<SpriteRender*> m_spriteRenderList;
	std::vector<FontRender*> m_fontRenderList;

	//各コマンドのポインタ保存用 実行中だけ保存される
	Menu_Create* m_menu_Create = nullptr;
	Menu_BoxAllDelete* m_menu_BoxAllDelete = nullptr;
	Menu_Save* m_menu_Save = nullptr;

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
	const float MenuMahojinRotSpeed = -0.2f;	//魔法陣が自動で回転する速度 負の数で逆回転

	//メニューロゴ
	const CVector2 MenuLogoSize = { 450.0f,200.0f };			//メニューロゴの大きさ
	const CVector2 MenuLogoAccSize = { 70.0f,70.0f };			//メニューロゴ、星の部分の大きさ
	const CVector2 MenuLogoNami = { 450.0f,338.0f };			//メニューロゴの中身、波の大きさ
	const float MenuLogoScale = 0.8f;							//メニューロゴのサイズ調整
	const CVector3 DefMenuLogoPosition = { 830.0f,280.0f,1.0f };		//メニューロゴのデフォ座標
	const CVector3 DefMenuLogo_AccPosition = { 980.0f,300.0f,1.0f };
	const int MenuLogoMoveSpeed = 300;							//波の移動速度
	const int MenuLogo_AccRotSpeed = 30;						//星の回転速度
	int MenuLogoTimer = 0;
	int MenuLogoRotTimer = 0;
	const float MenuAccRot = 2.0f;								//1フレームごとの回転量

	//コマンド
	const CVector2 MenuCommandWindowDefSize = { 430.0f,75.0f };	//画像自体の大きさ
	const CVector2 MenuCommandWindowSize = { 350.0f,75.0f };	//最終の大きさ
	const float MenuCommand_SideScale = 350.0f;					//両端の大きさ
	const CVector3 DefMenuCommandPosition = { 450.0f,160.0f,1.0f };
	const float MenuCommand_YHosei = 90.0f;						//コマンドごとのY補正
	const CVector3 TextColor = { 0.1f,0.1f,0.5f };				//テキストの色
	const float TextFontSize = 0.6f;							//テキストの大きさ
	const CVector2 DefMenuCommand_TextPosition = { 375.0f,182.0f };
	const float SaveX_Hosei = 30.0f;
	const float MenuCommandSelectJumpY = 10.0f;					//選択時のジャンプ幅
	const int MenuCommandSelectJumpTime = 2;					//選択時のジャンプ時間

	//項目内容
	const wchar_t* Koumoku[CommandNum]{
		L"クリエイト",
		L"全箱解放",
		L"ライブラリ",
		L"セーブ",
	};
	//アクセサリー


	//説明文
	const CVector3 SetumeiTextColor = { 0.9f,0.9f,0.9f };		//説明文の色
	const float TextFontSize_Setumei = 0.5f;					//テキストの大きさ
	const CVector2 DefSetumei_TextPosition = { -140.0f,60.0f };	//説明文ウィンドウを基準にした座標
	//内容
	const wchar_t* SetumeiBun[CommandNum]{
		L"マナやアイテムを\n消費して便利な\n装備を作ります。",
		L"生成されている箱を\n全て削除して、\nマナを全回復させます。",
		L"今までの冒険の\n記録を閲覧できます。",
		L"現在のプレイ状況を\n保存します。こまめに\n保存しましょう。",
	};

	//選択カーソル
	const CVector3 DefCursorPosition = { 280.0f,160.0f,1.0f };	//一番上のポジション
	int m_cursorMoveTimer = 0;									//カーソルの左右移動タイマー
	const int CursorMoveLimit = 20;								//カーソルが左右1往復するまでの時間
	const float Cursor_YMove = 10.0f;							//カーソルのY移動量

	//メニュー中のブラー関連
	const float BlurSpeed = 1.0f;								//1フレームごとの重み増減数
	const float MaxBlur = 5.0f;									//ブラーの最大重み

	//コマンド選択中関連
	const float NoActiveAlpha = 0.5f;							//非アクティブの間のコマンドアルファ
	bool m_commandEndFlag = false;								//コマンド終了フラグ
	int m_commandEndTimer = 0;									//コマンド終了タイマー
	const int CommandEndLimit = 10;								//コマンド終了リミット

	//サウンド関連
	const float MenuBGM_Volume = 0.5f;							//メニュー中はBGMの音量を下げる
	const int MenuBGM_FadeTime = 6;								//BGMの音量変化フェード速度

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
	SpriteRender* MenuWindow = nullptr;
	SpriteRender* MenuWindow2 = nullptr;		//説明欄
	SpriteRender* MenuButton = nullptr;
	//アクセサリー
	SpriteRender* MenuLogo_Under = nullptr;
	SpriteRender* MenuLogo = nullptr;
	SpriteRender* MenuLogo_Up = nullptr;
	SpriteRender* Menu_Mahojin = nullptr;		//魔法陣
	//コマンド
	SpriteRender* MenuCommand_Sprite1 = nullptr;		//くりえいと
	FontRender* MenuCommand_Font1 = nullptr;
	SpriteRender* MenuCommand_Sprite2 = nullptr;		//全箱解放
	FontRender* MenuCommand_Font2 = nullptr;
	SpriteRender* MenuCommand_Sprite3 = nullptr;		//ライブラリー
	FontRender* MenuCommand_Font3 = nullptr;
	SpriteRender* MenuCommand_Sprite4 = nullptr;		//セーブ
	FontRender* MenuCommand_Font4 = nullptr;
	//コマンドアクセサリー

	//説明文
	FontRender* MenuSetumeiFont = nullptr;
	//カーソル
	SpriteRender* MenuCommand_Cursor = nullptr;		//選択カーソル

};

