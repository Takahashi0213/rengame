#include "stdafx.h"
#include "GameMenu.h"
#include "Game.h"

GameMenu* GameMenu::m_instance = nullptr;

GameMenu::GameMenu()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//メニューのメイン部分
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

	//魔法陣
	Menu_Mahojin = NewGO<SpriteRender>("MenuMahojin", SpriteNo);
	Menu_Mahojin->Init(L"Assets/sprite/mahojin.dds", MenuMahojinSize, MenuMahojinSize, SpriteNo);
	Menu_Mahojin->SetPosition(MenuMahojinDefPosition);
	Menu_Mahojin->SetScale(MezuMahojinScale);
	Menu_Mahojin->SetAlpha(MenuMahojinAlpha);
	Menu_Mahojin->m_spriteSupporter.SpriteRotation(MenuMahojinRotSpeed, 1, 0, true);

	//説明欄
	MenuWindow2 = NewGO<SpriteRender>("MenuWindow2", SpriteNo);
	MenuWindow2->ChangeSliceSprite({ 150.0f,150.0f });
	MenuWindow2->Init(L"Assets/sprite/window1.dds",
		DefMenuWindow_2Size.x,
		DefMenuWindow_2Size.y,
		SpriteNo);
	MenuWindow2->SetPosition({ DefMenuWindow_2Position.x + MenuMove ,
		DefMenuWindow_2Position.y,DefMenuWindow_2Position.z });

	//ボタンと装飾

	//ろご
	MenuLogo_Under = NewGO<SpriteRender>("MenuLogo_Under", SpriteNo);
	MenuLogo_Under->Init(L"Assets/sprite/MenuLogo_Under.dds", MenuLogoSize.x, MenuLogoSize.y, SpriteNo);
	MenuLogo_Under->SetPosition(DefMenuLogoPosition);
	MenuLogo_Under->SetScale(MenuLogoScale);
	MenuLogo = NewGO<SpriteRender>("MenuLogo", SpriteNo);
	MenuLogo->ChangeMaskSprite();
	MenuLogo->Init(L"Assets/sprite/MenuLogo.dds", MenuLogoSize.x, MenuLogoSize.y, SpriteNo);
	MenuLogo->SetPosition(DefMenuLogoPosition);
	MenuLogo->SetScale(MenuLogoScale);
	//ロゴ中身
	MenuLogo->InitSub(L"Assets/sprite/MenuLogo_Nami.dds", MenuLogoNami.x, MenuLogoNami.y, 
		DefMenuLogoPosition, { 1.0f,1.0f,1.0f,1.0f }, SpriteNo);
	MenuLogo->InitSub(L"Assets/sprite/MenuLogo_Nami.dds", MenuLogoNami.x, MenuLogoNami.y,
		{ DefMenuLogoPosition.x + MenuLogoNami.x ,DefMenuLogoPosition.y ,DefMenuLogoPosition.z }, { 1.0f,1.0f,1.0f,1.0f }, SpriteNo);
	MenuLogo->InitSub(L"Assets/sprite/MenuLogoLight.dds", MenuLogoSize.x, MenuLogoSize.y,
		{ DefMenuLogoPosition.x - MenuMove ,DefMenuLogoPosition.y,DefMenuLogoPosition.z }, { 1.0f,1.0f,1.0f,1.0f }, SpriteNo);
	//ロゴ飾り
	MenuLogo_Up = NewGO<SpriteRender>("MenuLogo_Up", SpriteNo);
	MenuLogo_Up->Init(L"Assets/sprite/MenuLogo_Up.dds", MenuLogoAccSize.x, MenuLogoAccSize.y, SpriteNo);
	MenuLogo_Up->SetPosition(DefMenuLogo_AccPosition);
	MenuLogo_Up->SetScale(MenuLogoScale);
	//ロゴのレンダーモード変更
	MenuLogo->ChangeRenderMode_Mask(Sprite_RenderMode::Overlay, 0);
	MenuLogo->ChangeRenderMode_Mask(Sprite_RenderMode::Overlay, 1);
	MenuLogo->ChangeRenderMode_Mask(Sprite_RenderMode::Add, 2);

	//めにゅう
	float Y_Hosei = 0.0f;
	MenuCommand_Sprite1 = NewGO<SpriteRender>("MenuCommand_Sprite1", SpriteNo);
	MenuCommand_Sprite1->ChangeSliceSprite(MenuCommandWindowDefSize);
	MenuCommand_Sprite1->Set3Slice(MenuCommand_SideScale);
	MenuCommand_Sprite1->Init(L"Assets/sprite/window5.dds",
		MenuCommandWindowSize.x,
		MenuCommandWindowSize.y,
		SpriteNo);
	MenuCommand_Sprite1->SetPosition({ DefMenuCommandPosition.x + MenuMove ,
		DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
	MenuCommand_Font1 = NewGO<FontRender>("MenuCommand_Font1", SpriteNo);
	MenuCommand_Font1->SetText(Koumoku[0]);
	MenuCommand_Font1->SetColor(TextColor);
	MenuCommand_Font1->SetScale(TextFontSize);
	MenuCommand_Font1->SetPosition({ DefMenuCommand_TextPosition.x + MenuMove ,
		DefMenuCommand_TextPosition.y + Y_Hosei });
	//
	Y_Hosei -= MenuCommand_YHosei;
	MenuCommand_Sprite2 = NewGO<SpriteRender>("MenuCommand_Sprite2", SpriteNo);
	MenuCommand_Sprite2->ChangeSliceSprite(MenuCommandWindowDefSize);
	MenuCommand_Sprite2->Set3Slice(MenuCommand_SideScale);
	MenuCommand_Sprite2->Init(L"Assets/sprite/window5.dds",
		MenuCommandWindowSize.x,
		MenuCommandWindowSize.y,
		SpriteNo);
	MenuCommand_Sprite2->SetPosition({ DefMenuCommandPosition.x + MenuMove ,
		DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
	MenuCommand_Font2 = NewGO<FontRender>("MenuCommand_Font2", SpriteNo);
	MenuCommand_Font2->SetText(Koumoku[1]);
	MenuCommand_Font2->SetColor(TextColor);
	MenuCommand_Font2->SetScale(TextFontSize);
	MenuCommand_Font2->SetPosition({ DefMenuCommand_TextPosition.x + MenuMove , 
		DefMenuCommand_TextPosition.y + Y_Hosei });
	//
	Y_Hosei -= MenuCommand_YHosei;
	MenuCommand_Sprite3 = NewGO<SpriteRender>("MenuCommand_Sprite3", SpriteNo);
	MenuCommand_Sprite3->ChangeSliceSprite(MenuCommandWindowDefSize);
	MenuCommand_Sprite3->Set3Slice(MenuCommand_SideScale);
	MenuCommand_Sprite3->Init(L"Assets/sprite/window5.dds",
		MenuCommandWindowSize.x,
		MenuCommandWindowSize.y,
		SpriteNo);
	MenuCommand_Sprite3->SetPosition({ DefMenuCommandPosition.x + MenuMove ,
		DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
	MenuCommand_Font3 = NewGO<FontRender>("MenuCommand_Font3", SpriteNo);
	MenuCommand_Font3->SetText(Koumoku[2]);
	MenuCommand_Font3->SetColor(TextColor);
	MenuCommand_Font3->SetScale(TextFontSize);
	MenuCommand_Font3->SetPosition({ DefMenuCommand_TextPosition.x + MenuMove ,
		DefMenuCommand_TextPosition.y + Y_Hosei });
	//
	Y_Hosei -= MenuCommand_YHosei;
	MenuCommand_Sprite4 = NewGO<SpriteRender>("MenuCommand_Sprite4", SpriteNo);
	MenuCommand_Sprite4->ChangeSliceSprite(MenuCommandWindowDefSize);
	MenuCommand_Sprite4->Set3Slice(MenuCommand_SideScale);
	MenuCommand_Sprite4->Init(L"Assets/sprite/window5.dds",
		MenuCommandWindowSize.x,
		MenuCommandWindowSize.y,
		SpriteNo);
	MenuCommand_Sprite4->SetPosition({ DefMenuCommandPosition.x + MenuMove ,
		DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
	MenuCommand_Font4 = NewGO<FontRender>("MenuCommand_Font4", SpriteNo);
	MenuCommand_Font4->SetText(Koumoku[3]);
	MenuCommand_Font4->SetColor(TextColor);
	MenuCommand_Font4->SetScale(TextFontSize);
	MenuCommand_Font4->SetPosition({ DefMenuCommand_TextPosition.x + MenuMove + SaveX_Hosei,
		DefMenuCommand_TextPosition.y + Y_Hosei });

	//コマンドあくせさりぃ


	//説明文
	MenuSetumeiFont = NewGO<FontRender>("MenuSetumeiFont", SpriteNo);
	MenuSetumeiFont->SetText(L"");
	MenuSetumeiFont->SetColor(SetumeiTextColor);
	MenuSetumeiFont->SetScale(TextFontSize_Setumei);
	MenuSetumeiFont->SetPosition({ DefMenuWindow_2Position.x + DefSetumei_TextPosition.x + MenuMove ,
		DefMenuWindow_2Position.y + DefSetumei_TextPosition.y });

	//カーソル
	MenuCommand_Cursor = NewGO<SpriteRender>("MenuCommand_Cursor", SpriteNo);
	MenuCommand_Cursor->Init(L"Assets/sprite/MenuCursor.dds", 60.0f, 50.0f, SpriteNo);
	MenuCommand_Cursor->SetPosition({ DefCursorPosition.x + MenuMove,DefCursorPosition.y,DefCursorPosition.z });
	MenuCommand_Cursor->SetAlpha(0.0f);

	//登録しとく
	m_spriteRenderList.push_back(MenuWindow);
	m_spriteRenderList.push_back(MenuWindow2);
	m_spriteRenderList.push_back(MenuButton);
	m_spriteRenderList.push_back(Menu_Mahojin);
	m_spriteRenderList.push_back(MenuLogo_Under);
	m_spriteRenderList.push_back(MenuLogo);
	m_spriteRenderList.push_back(MenuLogo_Up);
	m_spriteRenderList.push_back(MenuCommand_Sprite1);
	m_spriteRenderList.push_back(MenuCommand_Sprite2);
	m_spriteRenderList.push_back(MenuCommand_Sprite3);
	m_spriteRenderList.push_back(MenuCommand_Sprite4);
	m_spriteRenderList.push_back(MenuCommand_Cursor);
	//
	m_fontRenderList.push_back(MenuCommand_Font1);
	m_fontRenderList.push_back(MenuCommand_Font2);
	m_fontRenderList.push_back(MenuCommand_Font3);
	m_fontRenderList.push_back(MenuCommand_Font4);
	m_fontRenderList.push_back(MenuSetumeiFont);

}

GameMenu::~GameMenu()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void GameMenu::GameMenuUpdate() {

	//取得
	Game::GameMode GameMode = Game::GetInstance()->GetGameMode();
	CVector2 MousePos = MouseSupporter::GetInstance()->GetMousePos_Sprite();
	int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	int Right_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Right_Key);

	//他の更新
	Update_Effect(GameMode);
	Update_Command();
	Update_CommandNow();

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
		if (MenuButton->MouseOverMouse() == true &&
			GameMode == Game::GameMode::ActionMode) {

			//調整
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });
			//フラグ変更
			m_selectFlag = true;

			//左クリックされたらメニューを開き、モードをメニューモードに変更する
			if (Left_Key == MouseSupporter::Release_Push) {

				Game::GetInstance()->SetGameMode(Game::GameMode::MenuMode);
				MenuLogoTimer = -1;
				MenuCommand_Cursor->SetAlpha(1.0f);
				m_nowMenuCommand = MenuCommand::Create;	//カーソル位置リセリセ
				m_menuMoveTimer = 0;
				EffekseerSupporter::GetInstance()->NoPostStop();
				m_commandNow = false;

				//コマンドの描画をリセット
				Update_CommandDraw(true);

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

				for (int i = 0; i < m_fontRenderList.size(); i++) {

					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ +MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ -(MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ MenuMove_Over,0.0f },
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
		if ((MenuButton->MouseOverMouse() == true &&
			GameMode == Game::GameMode::MenuMode) || 
			Right_Key == MouseSupporter::New_Push) {

			//調整
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });
			//フラグ変更
			m_selectFlag = true;

			//左クリックされたらメニューを閉じ、モードをアクションモードに変更する
			if (Left_Key == MouseSupporter::Release_Push ||
				Right_Key == MouseSupporter::New_Push) {

				Game::GetInstance()->SetGameMode(Game::GameMode::ActionMode);
				MenuCommand_Cursor->SetAlpha(0.0f);
				EffekseerSupporter::GetInstance()->NoPostMove();

				//移動
				MenuButton->Init(L"Assets/sprite/MenuButton.dds", MenuButtonSize, MenuButtonSize, SpriteNo);
				MenuLogo_Up->m_spriteSupporter.SpriteDelayReset();

				for (int i = 0; i < m_spriteRenderList.size(); i++) {

					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ (MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

				for (int i = 0; i < m_fontRenderList.size(); i++) {

					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ (MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ -MenuMove_Over,0.0f },
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

	//タイマー更新
	if (GameMode == Game::MenuMode) {
		m_menuMoveTimer++;
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

	//メニューの波です

	//メニューモードなら波をシームレス移動
	if (mode == Game::GameMode::MenuMode) {

		if (MenuLogoTimer == -1) {
			//初回移動！

			//マスクスプライトの移動をリセット
			MenuLogo->GetSubSpriteSupporter(0)->SpriteDelayReset();
			MenuLogo->GetSubSpriteSupporter(1)->SpriteDelayReset();
			
			MenuLogo_Up->SetRotation(CQuaternion::Identity());

			//初期位置へワープ
			MenuLogo->SetPosition({ DefMenuLogoPosition.x - MenuMove ,
				DefMenuLogoPosition.y,DefMenuLogoPosition.z}, 0);
			MenuLogo->SetPosition({ DefMenuLogoPosition.x + MenuLogoNami.x - MenuMove ,
				DefMenuLogoPosition.y ,DefMenuLogoPosition.z }, 1);

			MenuLogo->GetSubSpriteSupporter(0)->SpriteMove({ -MenuLogoNami.x,0.0f }, MenuLogoMoveSpeed, 0, true);
			MenuLogo->GetSubSpriteSupporter(1)->SpriteMove({ -MenuLogoNami.x,0.0f }, MenuLogoMoveSpeed, 0, true);

			MenuLogo_Up->m_spriteSupporter.SpriteRotation(MenuAccRot, MenuLogo_AccRotSpeed, 0, false);

			MenuLogoRotTimer = 0;
			MenuLogoTimer++;
		}

		MenuLogoTimer++;
		MenuLogoRotTimer++;

		if (MenuLogoMoveSpeed -1 == MenuLogoTimer) {		//ちょっと補正
			//移動更新してタイマーリセット

			//２つを比べて左にいる方を右に持っていく
			CVector3 Pos1 = MenuLogo->GetPosition(0);
			CVector3 Pos2 = MenuLogo->GetPosition(1);

			if (Pos1.x < Pos2.x) {
				//0番が左にいる
				MenuLogo->SetPosition({ DefMenuLogoPosition.x + MenuLogoNami.x - MenuMove ,
					DefMenuLogoPosition.y ,DefMenuLogoPosition.z }, 0);
				
			}
			else {
				//1番が左にいる
				MenuLogo->SetPosition({ DefMenuLogoPosition.x + MenuLogoNami.x - MenuMove ,
					DefMenuLogoPosition.y ,DefMenuLogoPosition.z }, 1);

			}

			//移動
			MenuLogo->GetSubSpriteSupporter(0)->SpriteMove({ -MenuLogoNami.x,0.0f }, MenuLogoMoveSpeed, 0, true);
			MenuLogo->GetSubSpriteSupporter(1)->SpriteMove({ -MenuLogoNami.x,0.0f }, MenuLogoMoveSpeed, 0, true);

			MenuLogoTimer = 0;
		}

		//回転用
		if (MenuLogoRotTimer == MenuLogo_AccRotSpeed) {
			MenuLogo_Up->m_spriteSupporter.SpriteRotation(-MenuAccRot, MenuLogoMoveSpeed, 0, false);
		}
		if (MenuLogoRotTimer == MenuLogo_AccRotSpeed * 2) {
			MenuLogo_Up->m_spriteSupporter.SpriteRotation(MenuAccRot, MenuLogoMoveSpeed, 0, false);
			MenuLogoRotTimer = 0;
		}

	}

}

/// <summary>
/// コマンドの更新
/// </summary>
void GameMenu::Update_Command() {

	//そもそもメニュー開いてます？
	if (Game::GetInstance()->GetGameMode() != Game::MenuMode) {
		return;
	}
	//移動完了してないなら実行させません
	if (m_menuMoveTimer < MenuMoveTime) {
		return;
	}

	//問答無用で左右移動する
	if (m_cursorMoveTimer == 0) {
		//移動を予約
		MenuCommand_Cursor->m_spriteSupporter.SpriteMove({ Cursor_YMove ,0.0f }, CursorMoveLimit / 2, 0, true);
		MenuCommand_Cursor->m_spriteSupporter.SpriteMove({ -Cursor_YMove ,0.0f }, CursorMoveLimit / 2, CursorMoveLimit / 2, true);
	}
	else if (m_cursorMoveTimer == CursorMoveLimit) {
		m_cursorMoveTimer = -1;	//ﾘｾｯﾄｩ
	}
	m_cursorMoveTimer++;

	//マウスの入力で選択中のコマンドをカエール
	int now_delta = MouseSupporter::GetInstance()->GetWheelMove();		//移動量
	bool ChangeFlag = false;

	//もしカーソルがどれかのコマンドに重なっていたらモード変更！
	if (((MenuCommand_Sprite1->MouseOverMouse() == true) ||
		(MenuCommand_Sprite2->MouseOverMouse() == true)  ||
		(MenuCommand_Sprite3->MouseOverMouse() == true)  ||
		(MenuCommand_Sprite4->MouseOverMouse() == true)) && m_selectOverFlag == false) {

		m_selectMode = true;		//カーソル位置を参照するモードに変更

	}

	if (m_selectMode == false) {
		//位置は関係なくホイールだけ取得する
		Update_CommandDelta(now_delta, ChangeFlag);
	}
	else if(m_selectMode == true && m_selectOverFlag == false){
		//位置を見つつ、ホイール操作があった場合はモード変更する
		if (MenuCommand_Sprite1->MouseOverMouse() == true && 
			m_nowMenuCommand != GameMenu::Create) {
			ChangeFlag = true;
			m_nowMenuCommand = GameMenu::Create;
		}
		if (MenuCommand_Sprite2->MouseOverMouse() == true &&
			m_nowMenuCommand != GameMenu::Box_Release) {
			ChangeFlag = true;
			m_nowMenuCommand = GameMenu::Box_Release;
		}
		if (MenuCommand_Sprite3->MouseOverMouse() == true &&
			m_nowMenuCommand != GameMenu::Library) {
			ChangeFlag = true;
			m_nowMenuCommand = GameMenu::Library;
		}
		if (MenuCommand_Sprite4->MouseOverMouse() == true &&
			m_nowMenuCommand != GameMenu::Save) {
			ChangeFlag = true;
			m_nowMenuCommand = GameMenu::Save;
		}

		//ホイール動いた！
		if (now_delta != 0) {
			Update_CommandDelta(now_delta, ChangeFlag);
			m_selectMode = false;
			m_selectOverFlag = true;
		}
	}
	
	//モード調整
	if ((MenuCommand_Sprite1->MouseOverMouse() == false) &&
		(MenuCommand_Sprite2->MouseOverMouse() == false) &&
		(MenuCommand_Sprite3->MouseOverMouse() == false) &&
		(MenuCommand_Sprite4->MouseOverMouse() == false) &&
		m_selectOverFlag == true) {

		m_selectOverFlag_ = true;
	}
	if (((MenuCommand_Sprite1->MouseOverMouse() == true) ||
		(MenuCommand_Sprite2->MouseOverMouse() == true) ||
		(MenuCommand_Sprite3->MouseOverMouse() == true) ||
		(MenuCommand_Sprite4->MouseOverMouse() == true)) && m_selectOverFlag_ == true) {

		m_selectOverFlag_ = false;
		m_selectOverFlag = false;

	}

	//更新されたら絵も更新する
	if (ChangeFlag == true) {
		Update_CommandDraw(false);
	}

}

/// <summary>
/// コマンドの上下移動
/// </summary>
void GameMenu::Update_CommandDelta(const int delta, bool& flag) {
	
	//コマンド実行中は動かさない
	if (m_commandNow == true) {
		return;
	}

	if (delta < 0) {	//ホイール上
		flag = true;
		switch (m_nowMenuCommand)
		{
		case GameMenu::Create:
			m_nowMenuCommand = GameMenu::Box_Release;
			break;
		case GameMenu::Box_Release:
			m_nowMenuCommand = GameMenu::Library;
			break;
		case GameMenu::Library:
			m_nowMenuCommand = GameMenu::Save;
			break;
		case GameMenu::Save:
			m_nowMenuCommand = GameMenu::Create;
			break;
		}
	}
	else if (delta > 0) {	//ホイール下
		flag = true;
		switch (m_nowMenuCommand)
		{
		case GameMenu::Create:
			m_nowMenuCommand = GameMenu::Save;
			break;
		case GameMenu::Box_Release:
			m_nowMenuCommand = GameMenu::Create;
			break;
		case GameMenu::Library:
			m_nowMenuCommand = GameMenu::Box_Release;
			break;
		case GameMenu::Save:
			m_nowMenuCommand = GameMenu::Library;
			break;
		}
	}

}

/// <summary>
/// コマンドと説明文の描画
/// </summary>
void GameMenu::Update_CommandDraw(bool drawStile) {

	//コマンド位置の移動
	m_cursorMoveTimer = 0;
	//リセットしないとヤバ
	MenuCommand_Cursor->m_spriteSupporter.SpriteDelayReset();
	{
		MenuCommand_Sprite1->m_spriteSupporter.SpriteDelayReset();
		MenuCommand_Font1->m_fontSupporter.FontDelayReset();
		MenuCommand_Sprite2->m_spriteSupporter.SpriteDelayReset();
		MenuCommand_Font2->m_fontSupporter.FontDelayReset();
		MenuCommand_Sprite3->m_spriteSupporter.SpriteDelayReset();
		MenuCommand_Font3->m_fontSupporter.FontDelayReset();
		MenuCommand_Sprite4->m_spriteSupporter.SpriteDelayReset();
		MenuCommand_Font4->m_fontSupporter.FontDelayReset();
	}

	if (drawStile == false) {
		MenuCommand_Cursor->SetPosition({ DefCursorPosition.x ,
			DefCursorPosition.y - (MenuCommand_YHosei * m_nowMenuCommand),DefCursorPosition.z });	//コマンドY位置は補正する

		float Y_Hosei = 0.0f;
		MenuCommand_Sprite1->SetPosition({ DefMenuCommandPosition.x,
			DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
		MenuCommand_Font1->SetPosition({ DefMenuCommand_TextPosition.x,
			DefMenuCommand_TextPosition.y + Y_Hosei });
		Y_Hosei -= MenuCommand_YHosei;
		MenuCommand_Sprite2->SetPosition({ DefMenuCommandPosition.x,
			DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
		MenuCommand_Font2->SetPosition({ DefMenuCommand_TextPosition.x,
			DefMenuCommand_TextPosition.y + Y_Hosei });
		Y_Hosei -= MenuCommand_YHosei;
		MenuCommand_Sprite3->SetPosition({ DefMenuCommandPosition.x,
			DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
		MenuCommand_Font3->SetPosition({ DefMenuCommand_TextPosition.x,
			DefMenuCommand_TextPosition.y + Y_Hosei });
		Y_Hosei -= MenuCommand_YHosei;
		MenuCommand_Sprite4->SetPosition({ DefMenuCommandPosition.x,
			DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
		MenuCommand_Font4->SetPosition({ DefMenuCommand_TextPosition.x + SaveX_Hosei,
			DefMenuCommand_TextPosition.y + Y_Hosei });
	}
	else {
		MenuCommand_Cursor->SetPosition({ DefCursorPosition.x + MenuMove,
			DefCursorPosition.y - (MenuCommand_YHosei * m_nowMenuCommand),DefCursorPosition.z });	//コマンドY位置は補正する
	}

	//個別の更新
	switch (m_nowMenuCommand)
	{
	case GameMenu::Create:
		MenuCommand_Sprite1->SetAlpha(1.0f);
		MenuCommand_Font1->SetAlpha(1.0f);
		MenuCommand_Sprite2->SetAlpha(0.5f);
		MenuCommand_Font2->SetAlpha(0.5f);
		MenuCommand_Sprite3->SetAlpha(0.5f);
		MenuCommand_Font3->SetAlpha(0.5f);
		MenuCommand_Sprite4->SetAlpha(0.5f);
		MenuCommand_Font4->SetAlpha(0.5f);
		//
		MenuCommand_Sprite1->m_spriteSupporter.SpriteMove({ 0.0f,10.0f }, 2, 0, true);
		MenuCommand_Sprite1->m_spriteSupporter.SpriteMove({ 0.0f,-10.0f }, 2, 2, true);
		MenuCommand_Font1->m_fontSupporter.FontMoveSet({ 0.0f,10.0f }, 2, 0, true);
		MenuCommand_Font1->m_fontSupporter.FontMoveSet({ 0.0f,-10.0f }, 2, 2, true);
		break;
	case GameMenu::Box_Release:
		MenuCommand_Sprite1->SetAlpha(0.5f);
		MenuCommand_Font1->SetAlpha(0.5f);
		MenuCommand_Sprite2->SetAlpha(1.0f);
		MenuCommand_Font2->SetAlpha(1.0f);
		MenuCommand_Sprite3->SetAlpha(0.5f);
		MenuCommand_Font3->SetAlpha(0.5f);
		MenuCommand_Sprite4->SetAlpha(0.5f);
		MenuCommand_Font4->SetAlpha(0.5f);
		//
		MenuCommand_Sprite2->m_spriteSupporter.SpriteMove({ 0.0f,10.0f }, 2, 0, true);
		MenuCommand_Sprite2->m_spriteSupporter.SpriteMove({ 0.0f,-10.0f }, 2, 2, true);
		MenuCommand_Font2->m_fontSupporter.FontMoveSet({ 0.0f,10.0f }, 2, 0, true);
		MenuCommand_Font2->m_fontSupporter.FontMoveSet({ 0.0f,-10.0f }, 2, 2, true);
		break;
	case GameMenu::Library:
		MenuCommand_Sprite1->SetAlpha(0.5f);
		MenuCommand_Font1->SetAlpha(0.5f);
		MenuCommand_Sprite2->SetAlpha(0.5f);
		MenuCommand_Font2->SetAlpha(0.5f);
		MenuCommand_Sprite3->SetAlpha(1.0f);
		MenuCommand_Font3->SetAlpha(1.0f);
		MenuCommand_Sprite4->SetAlpha(0.5f);
		MenuCommand_Font4->SetAlpha(0.5f);
		//
		MenuCommand_Sprite3->m_spriteSupporter.SpriteMove({ 0.0f,10.0f }, 2, 0, true);
		MenuCommand_Sprite3->m_spriteSupporter.SpriteMove({ 0.0f,-10.0f }, 2, 2, true);
		MenuCommand_Font3->m_fontSupporter.FontMoveSet({ 0.0f,10.0f }, 2, 0, true);
		MenuCommand_Font3->m_fontSupporter.FontMoveSet({ 0.0f,-10.0f }, 2, 2, true);
		break;
	case GameMenu::Save:
		MenuCommand_Sprite1->SetAlpha(0.5f);
		MenuCommand_Font1->SetAlpha(0.5f);
		MenuCommand_Sprite2->SetAlpha(0.5f);
		MenuCommand_Font2->SetAlpha(0.5f);
		MenuCommand_Sprite3->SetAlpha(0.5f);
		MenuCommand_Font3->SetAlpha(0.5f);
		MenuCommand_Sprite4->SetAlpha(1.0f);
		MenuCommand_Font4->SetAlpha(1.0f);
		//
		MenuCommand_Sprite4->m_spriteSupporter.SpriteMove({ 0.0f,10.0f }, 2, 0, true);
		MenuCommand_Sprite4->m_spriteSupporter.SpriteMove({ 0.0f,-10.0f }, 2, 2, true);
		MenuCommand_Font4->m_fontSupporter.FontMoveSet({ 0.0f,10.0f }, 2, 0, true);
		MenuCommand_Font4->m_fontSupporter.FontMoveSet({ 0.0f,-10.0f }, 2, 2, true);
		break;
	}

	//説明文の設定
	MenuSetumeiFont->SetText(SetumeiBun[m_nowMenuCommand]);

}

void GameMenu::Update_CommandNow() {

	//そもそもメニュー開いてます？
	if (Game::GetInstance()->GetGameMode() != Game::MenuMode) {
		return;
	}
	//何も実行してないなら中断
	if (m_commandNow == false) {
		return;
	}

	//コマンドに応じて実行すっぞ
	switch (m_nowMenuCommand)
	{
	case GameMenu::Create:

		break;
	case GameMenu::Box_Release:

		break;
	case GameMenu::Library:

		break;
	case GameMenu::Save:

		break;
	}


}