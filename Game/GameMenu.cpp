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
	MenuWindow->SetPosition({ DefMenuWindowPosition.x + MenuMove ,
		DefMenuWindowPosition.y,DefMenuWindowPosition.z });

	MenuButton = NewGO<SpriteRender>("MenuButton", SpriteNo);
	MenuButton->Init(L"Assets/sprite/MenuButton.dds", MenuButtonSize, MenuButtonSize, SpriteNo);
	MenuButton->SetPosition({ DefMenuButtonPosition.x + MenuMove ,
		DefMenuButtonPosition.y,DefMenuButtonPosition.z });

	MenuWindow2 = NewGO<SpriteRender>("MenuWindow2", SpriteNo);
	MenuWindow2->ChangeSliceSprite({ 150.0f,150.0f });
	MenuWindow2->Init(L"Assets/sprite/window1.dds",
		DefMenuWindow_2Size.x,
		DefMenuWindow_2Size.y,
		SpriteNo);
	MenuWindow2->SetPosition({ DefMenuWindow_2Position.x + MenuMove ,
		DefMenuWindow_2Position.y,DefMenuWindow_2Position.z });

	//登録しとく
	m_spriteRenderList.push_back(MenuWindow);
	m_spriteRenderList.push_back(MenuWindow2);
	m_spriteRenderList.push_back(MenuButton);

}

GameMenu::~GameMenu()
{
}

void GameMenu::GameMenuUpdate() {

	//取得
	Game::GameMode GameMode = Game::GetInstance()->GetGameMode();
	CVector2 MousePos = MouseSupporter::GetInstance()->GetMousePos_Sprite();
	int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);

	//他の更新
	Update_Effect(GameMode);

	//フラグリセット
	m_selectFlag = false;

	//座標計算
	float PosX = DefMenuButtonPosition.x + (MenuButtonSize / 2.0f);
	float PosX2 = DefMenuButtonPosition.x - (MenuButtonSize / 2.0f);
	float PosY = DefMenuButtonPosition.y + (MenuButtonSize / 2.0f);
	float PosY2 = DefMenuButtonPosition.y - (MenuButtonSize / 2.0f);

	//まずはメニューフラグの更新
	switch (GameMode)
	{
	case Game::ActionMode:

		//座標補正
		PosX += MenuMove;
		PosX2 += MenuMove;
		//ボタンと座標一致 かつ アクションモードならボタンのスプライトを大きくする
		if (MousePos.x <= PosX && MousePos.x >= PosX2 && MousePos.y <= PosY && MousePos.y >= PosY2 &&
			GameMode == Game::GameMode::ActionMode) {

			//調整
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });
			//フラグ変更
			m_selectFlag = true;

			//左クリックされたらメニューを開き、モードをメニューモードに変更する
			if (Left_Key == MouseSupporter::Release_Push) {

				Game::GetInstance()->SetGameMode(Game::GameMode::MenuMode);
				//移動
				MenuButton->Init(L"Assets/sprite/MenuButton_Back.dds", MenuButtonSize, MenuButtonSize, SpriteNo);

				for (int i = 0 ; i < m_spriteRenderList.size() ; i++) {

					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ +MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -(MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

			}

		}
		else {		//そうでなければ戻す

			MenuButton->SetScale(1.0f);
			MenuButton->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}

		break;
	case Game::MenuMode:
		//ボタンと座標一致 かつ メニューモードならボタンのスプライトを大きくする
		if (MousePos.x <= PosX && MousePos.x >= PosX2 && MousePos.y <= PosY && MousePos.y >= PosY2 &&
			GameMode == Game::GameMode::MenuMode) {

			//調整
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });
			//フラグ変更
			m_selectFlag = true;

			//左クリックされたらメニューを閉じ、モードをアクションモードに変更する
			if (Left_Key == MouseSupporter::Release_Push) {

				Game::GetInstance()->SetGameMode(Game::GameMode::ActionMode);
				//移動
				MenuButton->Init(L"Assets/sprite/MenuButton.dds", MenuButtonSize, MenuButtonSize, SpriteNo);

				for (int i = 0; i < m_spriteRenderList.size(); i++) {

					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ (MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

			}

		}
		else {		//そうでなければ戻す

			MenuButton->SetScale(1.0f);
			MenuButton->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}


		break;
	}


}

void GameMenu::Update_Effect(int mode) {

	//メニューモードなら！画面にブラーをかけるゥ！
	if (mode == Game::GameMode::MenuMode) {

		float blur = Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity;
		blur += BlurSpeed;
		if (blur > MaxBlur) {
			blur = MaxBlur;
		}
		Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity = blur;

	}
	//違うなら戻すｯ！！！！
	if (mode != Game::GameMode::MenuMode) {

		float blur = Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity;
		blur -= BlurSpeed;
		if (blur < 0.0f) {
			blur = 0.0f;
		}
		Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity = blur;
	}
}