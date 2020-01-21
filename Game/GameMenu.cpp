#include "stdafx.h"
#include "GameMenu.h"
#include "Game.h"

GameMenu::GameMenu()
{
	MenuWindow = NewGO<SpriteRender>("MenuWindow", SpriteNo);
	MenuWindow->ChangeSliceSprite({ 150.0f,150.0f });
	MenuWindow->Init(L"Assets/sprite/window3.dds", 
		DefMenuWindowSize.x,
		DefMenuWindowSize.y,
		SpriteNo);
	MenuWindow->SetPosition(DefMenuWindowPosition);

	MenuButton = NewGO<SpriteRender>("MenuButton", SpriteNo);
	MenuButton->Init(L"Assets/sprite/MenuButton.dds", MenuButtonSize, MenuButtonSize, SpriteNo);
	MenuButton->SetPosition(DefMenuButtonPosition);

	MenuWindow2 = NewGO<SpriteRender>("MenuWindow2", SpriteNo);
	MenuWindow2->ChangeSliceSprite({ 150.0f,150.0f });
	MenuWindow2->Init(L"Assets/sprite/window1.dds",
		DefMenuWindow_2Size.x,
		DefMenuWindow_2Size.y,
		SpriteNo);
	MenuWindow2->SetPosition(DefMenuWindow_2Position);

}

GameMenu::~GameMenu()
{
}

void GameMenu::GameMenuUpdate() {

	//取得
	Game::GameMode GameMode = Game::GetInstance()->GetGameMode();
	CVector2 MousePos = MouseSupporter::GetInstance()->GetMousePos_Sprite();
	int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);

	float PosX = DefMenuButtonPosition.x + (MenuButtonSize / 2.0f);
	float PosX2 = DefMenuButtonPosition.x - (MenuButtonSize / 2.0f);
	float PosY = DefMenuButtonPosition.y + (MenuButtonSize / 2.0f);
	float PosY2 = DefMenuButtonPosition.y - (MenuButtonSize / 2.0f);

	//まずはメニューフラグの更新
	switch (GameMode)
	{
	case Game::ActionMode:
		//ボタンと座標一致 かつ アクションモードならボタンのスプライトを大きくする
		if (MousePos.x <= PosX && MousePos.x >= PosX2 && MousePos.y <= PosY && MousePos.y >= PosY2 &&
			GameMode == Game::GameMode::ActionMode) {

			//調整
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });

		}
		else {		//そうでなければ戻す

			MenuButton->SetScale(1.0f);
			MenuButton->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}

		//ボタンと座標一致 かつ アクションモード かつ 左クリックされたら
		//メニューを開き、モードをメニューモードに変更する

		break;
	case Game::MenuMode:
		//ボタンと座標一致 かつ メニューモードならボタンのスプライトを大きくする

		//そうでなければ戻す

		//ボタンと座標一致 かつ メニューモード かつ 左クリックされたら
		//メニューを閉じ、モードをアクションモードに変更する

		break;
	}


}