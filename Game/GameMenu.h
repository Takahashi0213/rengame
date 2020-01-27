#pragma once

/// <summary>
/// メニューのアレコレを総括する…なんやろなあ
/// </summary>
class GameMenu
{
public:
	enum MenuCommand {	//メニューの項目
		Item,			//持ってるアイテムを確認
		Create,			//マナ、アイテム、スターマネーを使用して色々創造
		Box_Release,	//全箱解放（箱を全て消去してマナを回復）
		Library,		//図鑑やあらすじ
		Save,			//セーブ
		GameEnd,		//終了！
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

private:

	void Update_Effect(int mode);


	//メンバ変数
	const int SpriteNo = 7;		//スプライトの基準となる優先度
	const float MenuMove = 370.0f;	//メニューを開閉する時の移動量
	const float MenuMove_Over = 30.0f;	//メニューを開閉する時の移動量（オーバーラン用）
	const int MenuMoveTime = 4;	//メニューを開閉する時間
	MenuCommand m_nowMenuCommand = MenuCommand::Item;	//現在のコマンドォ！
	bool m_selectFlag = false;		//選択中

	//メニュー関連の画像が多すぎめんどい
	std::vector<SpriteRender*> m_spriteRenderList;

	//メニュー枠関連
	const CVector2 DefMenuWindowSize = { 600.0f,742.0f };
	const CVector2 DefMenuWindow_2Size = { 350.0f,150.0f };

	const CVector3 DefMenuWindowPosition = { 530.0f,0.0f,1.0f };
	const CVector3 DefMenuWindow_2Position = { 450.0f,-250.0f,1.0f };
	const CVector3 DefMenuButtonPosition = { 220.0f,300.0f,1.0f };

	const float MenuButtonSize = 150.0f;
	const float MenuButtonSize_Hosei = 150.0f;

	//メニュー中のブラー関連
	const float BlurSpeed = 1.0f;	//1フレームごとの重み増減数
	const float MaxBlur = 5.0f;		//ブラーの最大重み

	//↓ここから↓スプライト↓

	//全体
	SpriteRender* MenuWindow;
	SpriteRender* MenuWindow2;		//説明欄
	SpriteRender* MenuButton;
	//コマンドです


};

