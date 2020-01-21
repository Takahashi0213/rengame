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

private:

	//メンバ変数
	const int SpriteNo = 7;		//スプライトの基準となる優先度
	const float MenuMove = 370.0f;	//メニューを開閉する時の移動量
	MenuCommand m_nowMenuCommand = MenuCommand::Item;	//現在のコマンドォ！

	//メニュー枠関連
	const CVector2 DefMenuWindowSize = { 500.0f,742.0f };
	const CVector2 DefMenuWindow_2Size = { 350.0f,200.0f };

	const CVector3 DefMenuWindowPosition = { 480.0f + MenuMove,0.0f,1.0f };
	const CVector3 DefMenuWindow_2Position = { 450.0f + MenuMove,-220.0f,1.0f };
	const CVector3 DefMenuButtonPosition = { 220.0f + MenuMove,300.0f,1.0f };

	const float MenuButtonSize = 150.0f;
	const float MenuButtonSize_Hosei = 150.0f;

	//↓ここから↓スプライト↓

	//全体
	SpriteRender* MenuWindow;
	SpriteRender* MenuWindow2;		//説明欄
	SpriteRender* MenuButton;
	//コマンドです


};

