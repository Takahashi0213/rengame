#include "stdafx.h"
#include "Menu_Save.h"

Menu_Save::Menu_Save()
{	
	//臨時ゲームデータの生成
	m_gameData_Load = new GameData;

	//メニューのメイン部分
	MenuWindow = NewGO<SpriteRender>("MenuWindow_Save", SpriteNo);
	MenuWindow->ChangeSliceSprite({ 120.0f,120.0f });
	MenuWindow->Init(L"Assets/sprite/window7.dds",
		DefMenuWindowSize.x,
		DefMenuWindowSize.y,
		SpriteNo);
	MenuWindow->SetPosition(MenuDefPos);
	//ヘッダー
	Header_Font = NewGO<FontRender>("MenuHeaderFont_Save", SpriteNo);
	Header_Font->SetText(HeaderText);
	Header_Font->SetColor(CVector4::White());
	Header_Font->SetScale(Header_FontSize);
	Header_Font->SetPosition({ MenuDefPos.x + Header_Font_Hosei.x,MenuDefPos.y + Header_Font_Hosei.y });

	//旧セーブ
	FILE* fp = fopen("save.bin", "rb");
	if (fp != NULL) {
		fread(m_gameData_Load, sizeof(GameData), 1, fp);
		fclose(fp);
		m_fifeFlag = true;
	}
	{	//セーブ情報部分-旧
		OldSaveWindow = NewGO<SpriteRender>("SaveWindow_Old", SpriteNo);
		OldSaveWindow->ChangeSliceSprite({ 150.0f,150.0f });
		OldSaveWindow->Init(L"Assets/sprite/window1.dds",
			SaveWindowSize.x,
			SaveWindowSize.y,
			SpriteNo);
		OldSaveWindow->SetPosition(OldSaveDefPos);
		//マップアイコン-旧
		OldMapIC = NewGO<SpriteRender>("SaveMapIC_Old", SpriteNo);
		const wchar_t* IC_FilePath;
		if (m_fifeFlag == true) {
			IC_FilePath = StageSet::GetInstance()->GetStageIC_Name(m_gameData_Load->GetPlace());
		}
		else {
			IC_FilePath = StageSet::GetInstance()->GetStageIC_Name(GameData::Place_Data::Null_Place);
		}
		OldMapIC->Init(IC_FilePath,
			MapIC_Size.x,
			MapIC_Size.y,
			SpriteNo);
		OldMapIC->SetPosition({ OldSaveDefPos.x + MapIC_PosHosei.x,OldSaveDefPos.y + MapIC_PosHosei.y,OldSaveDefPos.z });
		//プレイヤーレベル-旧
		OldSave_PlayerLevel = NewGO<FontRender>("PlayerLevel_Old", SpriteNo);
		OldSave_PlayerLevel->SetPivot({ 0.0f,0.5f });	//左
		int oldPlayerLevel = 0;
		if (m_fifeFlag == true) {
			oldPlayerLevel = m_gameData_Load->GetLevel();
			wchar_t text[MAX_PATH];
			swprintf(text, MAX_PATH - 1, L"Ｌｖ. %d", oldPlayerLevel);
			OldSave_PlayerLevel->SetText(text);
		}
		else {
			OldSave_PlayerLevel->SetText(L"Ｌｖ.　？");
		}
		OldSave_PlayerLevel->SetColor(CVector4::White());
		OldSave_PlayerLevel->SetScale(NewOld_SaveDataFontSize);
		OldSave_PlayerLevel->SetPosition({ OldSaveDefPos.x + NewOld_PlayerLevel_Hosei.x,OldSaveDefPos.y + NewOld_PlayerLevel_Hosei.y });
		//プレイヤーHP-旧
		OldSave_PlayerHP = NewGO<FontRender>("PlayerHP_Old", SpriteNo);
		OldSave_PlayerHP->SetPivot({ 0.0f,0.5f });	//左
		int oldPlayerMaxHP = 0;
		int oldPlayerNowHP = 0;
		if (m_fifeFlag == true) {
			oldPlayerMaxHP = m_gameData_Load->GetMaxHP();
			oldPlayerNowHP = m_gameData_Load->GetHP();
			wchar_t text[MAX_PATH];
			swprintf(text, MAX_PATH - 1, L"ＨＰ　%d　/%d", oldPlayerNowHP, oldPlayerMaxHP);
			OldSave_PlayerHP->SetText(text);
		}
		else {
			OldSave_PlayerHP->SetText(L"ＨＰ　？　/　？");
		}
		OldSave_PlayerHP->SetColor(CVector4::White());
		OldSave_PlayerHP->SetScale(NewOld_SaveDataFontSize);
		OldSave_PlayerHP->SetPosition({ OldSaveDefPos.x + NewOld_PlayerHP_Hosei.x,OldSaveDefPos.y + NewOld_PlayerHP_Hosei.y });
		//プレイヤー場所-旧
		OldSave_PlayerPlace = NewGO<FontRender>("PlayerPlace_Old", SpriteNo);
		OldSave_PlayerPlace->SetPivot({ 0.0f,0.5f });	//左
		if (m_fifeFlag == true) {
			const wchar_t* StageName;
			StageName = StageSet::GetInstance()->GetStage_HyouziName(m_gameData_Load->GetNowMapLevel());
			OldSave_PlayerPlace->SetText(StageName);
		}
		else {
			OldSave_PlayerPlace->SetText(L"No　Data");
		}
		OldSave_PlayerPlace->SetColor(CVector4::White());
		OldSave_PlayerPlace->SetScale(NewOld_SaveDataFontSize);
		OldSave_PlayerPlace->SetPosition({ OldSaveDefPos.x + NewOld_PlayerPlace_Hosei.x,OldSaveDefPos.y + NewOld_PlayerPlace_Hosei.y });
	}
	//新セーブ
	{
		//セーブ情報部分-新
		NewSaveWindow = NewGO<SpriteRender>("SaveWindow_New", SpriteNo);
		NewSaveWindow->ChangeSliceSprite({ 150.0f,150.0f });
		NewSaveWindow->Init(L"Assets/sprite/window1.dds",
			SaveWindowSize.x,
			SaveWindowSize.y,
			SpriteNo);
		NewSaveWindow->SetPosition(NewSaveDefPos);
		//マップアイコン-新
		NewMapIC = NewGO<SpriteRender>("SaveMapIC_New", SpriteNo);
		const wchar_t* IC_FilePath;
		IC_FilePath = StageSet::GetInstance()->GetStageIC_Name(GameData::GetInstance()->GetPlace());
		NewMapIC->Init(IC_FilePath,
			MapIC_Size.x,
			MapIC_Size.y,
			SpriteNo);
		NewMapIC->SetPosition({ NewSaveDefPos.x + MapIC_PosHosei.x,NewSaveDefPos.y + MapIC_PosHosei.y,NewSaveDefPos.z });
		//プレイヤーレベル-新
		NewSave_PlayerLevel = NewGO<FontRender>("PlayerLevel_New", SpriteNo);
		NewSave_PlayerLevel->SetPivot({ 0.0f,0.5f });	//左
		int newPlayerLevel = 0;
		newPlayerLevel = GameData::GetInstance()->GetLevel();
		wchar_t text[MAX_PATH];
		swprintf(text, MAX_PATH - 1, L"Ｌｖ. %d", newPlayerLevel);
		NewSave_PlayerLevel->SetText(text);
		NewSave_PlayerLevel->SetColor(CVector4::White());
		NewSave_PlayerLevel->SetScale(NewOld_SaveDataFontSize);
		NewSave_PlayerLevel->SetPosition({ NewSaveDefPos.x + NewOld_PlayerLevel_Hosei.x,NewSaveDefPos.y + NewOld_PlayerLevel_Hosei.y });
		//プレイヤーHP-新
		NewSave_PlayerHP = NewGO<FontRender>("PlayerHP_New", SpriteNo);
		NewSave_PlayerHP->SetPivot({ 0.0f,0.5f });	//左
		int newPlayerMaxHP = 0;
		int newPlayerNowHP = 0;
		newPlayerMaxHP = GameData::GetInstance()->GetMaxHP();
		newPlayerNowHP = GameData::GetInstance()->GetHP();
		swprintf(text, MAX_PATH - 1, L"ＨＰ　%d　/%d", newPlayerNowHP, newPlayerMaxHP);
		NewSave_PlayerHP->SetText(text);
		NewSave_PlayerHP->SetColor(CVector4::White());
		NewSave_PlayerHP->SetScale(NewOld_SaveDataFontSize);
		NewSave_PlayerHP->SetPosition({ NewSaveDefPos.x + NewOld_PlayerHP_Hosei.x,NewSaveDefPos.y + NewOld_PlayerHP_Hosei.y });
		//プレイヤー場所-新
		NewSave_PlayerPlace = NewGO<FontRender>("PlayerPlace_New", SpriteNo);
		NewSave_PlayerPlace->SetPivot({ 0.0f,0.5f });	//左
		const wchar_t* StageName;
		StageName = StageSet::GetInstance()->GetStage_HyouziName(GameData::GetInstance()->GetNowMapLevel());
		NewSave_PlayerPlace->SetText(StageName);
		NewSave_PlayerPlace->SetColor(CVector4::White());
		NewSave_PlayerPlace->SetScale(NewOld_SaveDataFontSize);
		NewSave_PlayerPlace->SetPosition({ NewSaveDefPos.x + NewOld_PlayerPlace_Hosei.x,NewSaveDefPos.y + NewOld_PlayerPlace_Hosei.y });

	}

	//新テキスト
	NewSave_Text = NewGO<FontRender>("New_Font", SpriteNo);
	NewSave_Text->SetText(NewText);
	NewSave_Text->SetColor(CVector4::White());
	NewSave_Text->SetScale(NewOld_FontSize);
	NewSave_Text->SetPosition({ NewSaveDefPos.x + NewOld_Font_Hosei.x,NewSaveDefPos.y + NewOld_Font_Hosei.y });
	//旧テキスト
	OldSave_Text = NewGO<FontRender>("Old_Font", SpriteNo);
	OldSave_Text->SetText(OldText);
	OldSave_Text->SetColor(CVector4::White());
	OldSave_Text->SetScale(NewOld_FontSize);
	OldSave_Text->SetPosition({ OldSaveDefPos.x + NewOld_Font_Hosei.x,OldSaveDefPos.y + NewOld_Font_Hosei.y });

	//セーブカーソル
	SaveCursor = NewGO<SpriteRender>("Menu_SaveCursor", SpriteNo);
	SaveCursor->Init(L"Assets/sprite/Menu_SaveCursor.dds",
		DefSaveCursorSize.x,
		DefSaveCursorSize.y,
		SpriteNo);
	SaveCursor->SetPosition(SaveCursorPos);

	//確認メッセージ
	Check_Font = NewGO<FontRender>("MenuCheckFont_Save", SpriteNo);
	Check_Font->SetText(SaveCheckText);
	Check_Font->SetColor(CVector4::White());
	Check_Font->SetScale(Check_FontSize);
	Check_Font->SetPosition({ MenuDefPos.x + Check_Font_Hosei.x,MenuDefPos.y + Check_Font_Hosei.y });

	//Yes/Noボタン
	ButtonWindow_Left = NewGO<SpriteRender>("MenuCommand_Save_Left", SpriteNo);
	ButtonWindow_Left->ChangeSliceSprite({ 200.0f,60.0f });
	ButtonWindow_Left->Set3Slice(MenuButtonDefSize.x);
	ButtonWindow_Left->Init(L"Assets/sprite/window8.dds",
		MenuButtonDefSize.x,
		MenuButtonDefSize.y,
		SpriteNo);
	ButtonWindow_Left->SetPosition({ MenuDefPos.x - MenuButtonPosHosei.x,
		MenuDefPos.y + MenuButtonPosHosei.y, MenuDefPos.z });
	ButtonWindow_Right = NewGO<SpriteRender>("MenuCommand_Save_Right", SpriteNo);
	ButtonWindow_Right->ChangeSliceSprite({ 200.0f,60.0f });
	ButtonWindow_Right->Set3Slice(MenuButtonDefSize.x);
	ButtonWindow_Right->Init(L"Assets/sprite/window8.dds",
		MenuButtonDefSize.x,
		MenuButtonDefSize.y,
		SpriteNo);
	ButtonWindow_Right->SetPosition({ MenuDefPos.x + MenuButtonPosHosei.x,
		MenuDefPos.y + MenuButtonPosHosei.y, MenuDefPos.z });
	//Yes/Noテキスト
	Yes_Font = NewGO<FontRender>("MenuButtonFont_Save_Yes", SpriteNo);
	Yes_Font->SetText(YesText);
	Yes_Font->SetColor(CVector4::White());
	Yes_Font->SetScale(Header_FontSize);
	Yes_Font->SetPosition({ MenuDefPos.x - MenuButtonPosHosei.x + YesNo_Font_Hosei.x + YesFont_XHosei,
		MenuDefPos.y + MenuButtonPosHosei.y + YesNo_Font_Hosei.y });
	No_Font = NewGO<FontRender>("MenuButtonFont_Save_No", SpriteNo);
	No_Font->SetText(NoText);
	No_Font->SetColor(CVector4::White());
	No_Font->SetScale(Header_FontSize);
	No_Font->SetPosition({ MenuDefPos.x + MenuButtonPosHosei.x + YesNo_Font_Hosei.x + NoFont_XHosei,
		MenuDefPos.y + MenuButtonPosHosei.y + YesNo_Font_Hosei.y });

	//リストにぶちこむ
	m_newSave_SpriteRenderList.push_back(NewSaveWindow);
	m_newSave_SpriteRenderList.push_back(NewMapIC);
	//
	m_newSave_FontRenderList.push_back(NewSave_PlayerLevel);
	m_newSave_FontRenderList.push_back(NewSave_PlayerHP);
	m_newSave_FontRenderList.push_back(NewSave_PlayerPlace);
	//
	m_oldSave_SpriteRenderList.push_back(OldSaveWindow);
	m_oldSave_SpriteRenderList.push_back(OldMapIC);
	//
	m_oldSave_FontRenderList.push_back(OldSave_PlayerLevel);
	m_oldSave_FontRenderList.push_back(OldSave_PlayerHP);
	m_oldSave_FontRenderList.push_back(OldSave_PlayerPlace);

}

Menu_Save::~Menu_Save()
{
	//削除
	DeleteGO(MenuWindow);
	DeleteGO(Header_Font);
	DeleteGO(Check_Font);
	DeleteGO(ButtonWindow_Left);
	DeleteGO(ButtonWindow_Right);
	DeleteGO(Yes_Font);
	DeleteGO(No_Font);

	for (int i = 0; i < m_newSave_SpriteRenderList.size(); i++) {
		DeleteGO(m_newSave_SpriteRenderList[i]);
	}
	for (int i = 0; i < m_newSave_FontRenderList.size(); i++) {
		DeleteGO(m_newSave_FontRenderList[i]);
	}
	for (int i = 0; i < m_oldSave_SpriteRenderList.size(); i++) {
		DeleteGO(m_oldSave_SpriteRenderList[i]);
	}
	for (int i = 0; i < m_oldSave_FontRenderList.size(); i++) {
		DeleteGO(m_oldSave_FontRenderList[i]);
	}
	DeleteGO(NewSave_Text);
	DeleteGO(OldSave_Text);
	DeleteGO(SaveCursor);
	delete m_gameData_Load;
}

void Menu_Save::SaveUpdate() {

	if (m_saveFlag == false) {

		//マウスオーバー演出
		m_nowCommand = NullSelect_Command;
		if (ButtonWindow_Left->MouseOverMouse() == true) {
			m_nowCommand = Yes_Command;
			ButtonWindow_Left->SetAlpha(1.0f);
			Yes_Font->SetAlpha(1.0f);
		}
		else {
			ButtonWindow_Left->SetAlpha(NoActiveAlpha);
			Yes_Font->SetAlpha(NoActiveAlpha);
		}
		if (ButtonWindow_Right->MouseOverMouse() == true) {
			m_nowCommand = No_Command;
			ButtonWindow_Right->SetAlpha(1.0f);
			No_Font->SetAlpha(1.0f);
		}
		else {
			ButtonWindow_Right->SetAlpha(NoActiveAlpha);
			No_Font->SetAlpha(NoActiveAlpha);
		}

		//決定処理
		int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		if (Left_Key == MouseSupporter::Release_Push) {
			//プレイヤー検索→座標と回転を保存
			Player* m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));
			GameData::GetInstance()->GameSave(m_pl->GetPosition(), m_pl->GetRotation());
			switch (m_nowCommand)
			{
			case Menu_Save::Yes_Command:
				//ここでセーブ処理
				{
					FILE* fp = fopen("save.bin", "wb");
					fwrite(GameData::GetInstance(), sizeof(GameData), 1, fp);
					fwrite(Game::GetInstance()->GetGameEvent()->GetEventSave(), sizeof(EventSave), 1, fp);
					fclose(fp);
				}
				SaveEffect();
				m_saveFlag = true;	//演出が終わるまで待つ
				break;
			case Menu_Save::No_Command:
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cancel.wav", 3.0f);	//SE
				CommandEnd();
				break;
			}
		}

		//カーソル移動
		if (SaveCursor->m_spriteSupporter.GetSpriteMoveListLen() == 0) {
			SaveCursor->m_spriteSupporter.SpriteMove({ 0.0f,-SaveCursorMove }, SaveCursorMoveTime, 0, true);
			SaveCursor->m_spriteSupporter.SpriteMove({ 0.0f,SaveCursorMove }, SaveCursorMoveTime, SaveCursorMoveTime, true);
		}
	}

	//このコマンドを終了
	if (m_saveFlag == true) {
		m_saveTimer++;
		if (m_saveTimer == 6) {
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Save.wav");	//SE
			GameEffect::GetInstance()->GetInstance_SpriteAnime()->
				NewAnimationSprite(GameEffect_AnimationSprite::Anime_Name::Anime_Save,
					EffectPos, CVector3::One(), SpriteNo, 0);
			Check_Font->SetText(SaveNowText);
			Check_Font->SetPosition({ MenuDefPos.x + Check_Font_Hosei2.x,MenuDefPos.y + Check_Font_Hosei2.y });
		}
		if (m_saveTimer >= SaveTimeLimit) {
			CommandEnd();
		}
	}

}

void Menu_Save::CommandEnd() {

	MenuWindow->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	Header_Font->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	Check_Font->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	ButtonWindow_Left->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	ButtonWindow_Right->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	Yes_Font->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	No_Font->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);

	for (int i = 0; i < m_newSave_SpriteRenderList.size(); i++) {
		m_newSave_SpriteRenderList[i]->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	}
	for (int i = 0; i < m_newSave_FontRenderList.size(); i++) {
		m_newSave_FontRenderList[i]->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	}
	for (int i = 0; i < m_oldSave_SpriteRenderList.size(); i++) {
		m_oldSave_SpriteRenderList[i]->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	}
	for (int i = 0; i < m_oldSave_FontRenderList.size(); i++) {
		m_oldSave_FontRenderList[i]->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	}
	NewSave_Text->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	OldSave_Text->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	SaveCursor->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);

	m_deleteFlag = true;	//終了

}

void Menu_Save::SaveEffect() {

	//新しい方
	for (int i = 0; i < m_newSave_SpriteRenderList.size(); i++) {

		m_newSave_SpriteRenderList[i]->m_spriteSupporter.SpriteMove({ 0.0f,SaveMove_1 },
			MoveTime_1, 0, true);
		m_newSave_SpriteRenderList[i]->m_spriteSupporter.SpriteMove({ 0.0f,SaveMove_2 },
			MoveTime_2, MoveTime_1, true);
		m_newSave_SpriteRenderList[i]->m_spriteSupporter.SpriteMove({ 0.0f,SaveMove_1 },
			MoveTime_1, MoveTime_1 + MoveTime_2, true);
		m_newSave_SpriteRenderList[i]->m_spriteSupporter.SpriteMove({ 0.0f,SaveMove_3 },
			MoveTime_3, MoveTime_1 + MoveTime_2 + MoveTime_3, true);

	}
	for (int i = 0; i < m_newSave_FontRenderList.size(); i++) {

		m_newSave_FontRenderList[i]->m_fontSupporter.FontMoveSet({ 0.0f,SaveMove_1 },
			MoveTime_1, 0, true);
		m_newSave_FontRenderList[i]->m_fontSupporter.FontMoveSet({ 0.0f,SaveMove_2 },
			MoveTime_2, MoveTime_1, true);
		m_newSave_FontRenderList[i]->m_fontSupporter.FontMoveSet({ 0.0f,SaveMove_1 },
			MoveTime_1, MoveTime_1 + MoveTime_2, true);
		m_newSave_FontRenderList[i]->m_fontSupporter.FontMoveSet({ 0.0f,SaveMove_3 },
			MoveTime_3, MoveTime_1 + MoveTime_2 + MoveTime_3, true);
	}
	//古い方
	for (int i = 0; i < m_oldSave_SpriteRenderList.size(); i++) {
		m_oldSave_SpriteRenderList[i]->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, MoveTime_1, MoveTime_2);
	}
	for (int i = 0; i < m_oldSave_FontRenderList.size(); i++) {
		m_oldSave_FontRenderList[i]->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, MoveTime_1, MoveTime_2);
	}
	//その他
	NewSave_Text->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, MoveTime_1, 0);
	OldSave_Text->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, MoveTime_1, 0);
	SaveCursor->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, MoveTime_1, 0);

}