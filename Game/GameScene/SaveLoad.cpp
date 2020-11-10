#include "stdafx.h"
#include "SaveLoad.h"

SaveLoad* SaveLoad::m_instance = nullptr;

SaveLoad::SaveLoad()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//臨時ゲームデータの生成
	m_gameData_Load = new GameData;

	//グラフィック設定

	//背景
	m_BG = NewGO<SpriteRender>("Load_PlayerStand", SpriteNo);
	m_BG->Init(L"Assets/sprite/Load_BG.dds",
		BG_Size.x,
		BG_Size.y,
		SpriteNo);

	FILE* fp = fopen("save.bin", "rb");
	if (fp != NULL) {
		fread(m_gameData_Load, sizeof(GameData), 1, fp);
		fclose(fp);
		m_fifeFlag = true;
	}
	{
		//セーブ情報部分
		m_saveWindow = NewGO<SpriteRender>("SaveWindow", SpriteNo);
		m_saveWindow->ChangeSliceSprite({ 150.0f,150.0f });
		m_saveWindow->Init(L"Assets/sprite/window1.dds",
			SaveWindowSize.x,
			SaveWindowSize.y,
			SpriteNo);
		m_saveWindow->SetPosition(SaveDefPos);
		//マップアイコン
		m_mapIC = NewGO<SpriteRender>("SaveMapIC", SpriteNo);
		const wchar_t* IC_FilePath;
		if (m_fifeFlag == true) {
			IC_FilePath = StageSet::GetInstance()->GetStageIC_Name(m_gameData_Load->GetPlace());
		}
		else {
			IC_FilePath = StageSet::GetInstance()->GetStageIC_Name(GameData::Place_Data::Null_Place);
		}
		m_mapIC->Init(IC_FilePath,
			MapIC_Size.x,
			MapIC_Size.y,
			SpriteNo);
		m_mapIC->SetPosition({ SaveDefPos.x + MapIC_PosHosei.x,SaveDefPos.y + MapIC_PosHosei.y,SaveDefPos.z });
		//プレイヤーレベル
		m_load_PlayerLevel = NewGO<FontRender>("PlayerLevel", SpriteNo);
		m_load_PlayerLevel->SetPivot({ 0.0f,0.5f });	//左
		int PlayerLevel = 0;
		if (m_fifeFlag == true) {
			PlayerLevel = m_gameData_Load->GetLevel();
			wchar_t text[MAX_PATH];
			swprintf(text, MAX_PATH - 1, L"Ｌｖ. %d", PlayerLevel);
			m_load_PlayerLevel->SetText(text);
		}
		else {
			m_load_PlayerLevel->SetText(L"Ｌｖ.　？");
		}
		m_load_PlayerLevel->SetColor(CVector4::White());
		m_load_PlayerLevel->SetScale(SaveDataFontSize);
		m_load_PlayerLevel->SetPosition({ SaveDefPos.x + PlayerLevel_Hosei.x,SaveDefPos.y + PlayerLevel_Hosei.y });
		//プレイヤーHP
		m_load_PlayerHP = NewGO<FontRender>("PlayerHP", SpriteNo);
		m_load_PlayerHP->SetPivot({ 0.0f,0.5f });	//左
		int PlayerMaxHP = 0;
		int PlayerNowHP = 0;
		if (m_fifeFlag == true) {
			PlayerMaxHP = m_gameData_Load->GetMaxHP();
			PlayerNowHP = m_gameData_Load->GetHP();
			wchar_t text[MAX_PATH];
			swprintf(text, MAX_PATH - 1, L"ＨＰ　%d　/%d", PlayerNowHP, PlayerMaxHP);
			m_load_PlayerHP->SetText(text);
		}
		else {
			m_load_PlayerHP->SetText(L"ＨＰ　？　/　？");
		}
		m_load_PlayerHP->SetColor(CVector4::White());
		m_load_PlayerHP->SetScale(SaveDataFontSize);
		m_load_PlayerHP->SetPosition({ SaveDefPos.x + PlayerHP_Hosei.x,SaveDefPos.y + PlayerHP_Hosei.y });
		//プレイヤー場所
		m_load_PlayerPlace = NewGO<FontRender>("PlayerPlace", SpriteNo);
		m_load_PlayerPlace->SetPivot({ 0.0f,0.5f });	//左
		if (m_fifeFlag == true) {
			const wchar_t* StageName;
			StageName = StageSet::GetInstance()->GetStage_HyouziName(m_gameData_Load->GetNowMapLevel());
			m_load_PlayerPlace->SetText(StageName);
		}
		else {
			m_load_PlayerPlace->SetText(L"No　Data");
		}
		m_load_PlayerPlace->SetColor(CVector4::White());
		m_load_PlayerPlace->SetScale(SaveDataFontSize);
		m_load_PlayerPlace->SetPosition({ SaveDefPos.x + PlayerPlace_Hosei.x,SaveDefPos.y + PlayerPlace_Hosei.y });
	}
	//チェックテキスト
	m_loadChackText = NewGO<FontRender>("LoadChackText", SpriteNo);
	if (m_fifeFlag == true) {
		m_loadChackText->SetText(LoadCheckText);
	}
	else {
		m_loadChackText->SetText(LoadCheckText_No);
	}
	m_loadChackText->SetColor(Check_FontColor);
	m_loadChackText->SetScale(Check_FontSize);
	m_loadChackText->SetPosition(LoadChackTextPos);

	//Yes/Noボタン
	ButtonWindow_Left = NewGO<SpriteRender>("MenuCommand_Left", SpriteNo);
	ButtonWindow_Left->ChangeSliceSprite({ 200.0f,60.0f });
	ButtonWindow_Left->Set3Slice(MenuButtonDefSize.x);
	ButtonWindow_Left->Init(L"Assets/sprite/window8.dds",
		MenuButtonDefSize.x,
		MenuButtonDefSize.y,
		SpriteNo);
	ButtonWindow_Left->SetPosition({ SaveDefPos.x - MenuButtonPosHosei.x,
		SaveDefPos.y + MenuButtonPosHosei.y, SaveDefPos.z });
	ButtonWindow_Right = NewGO<SpriteRender>("MenuCommand_Right", SpriteNo);
	ButtonWindow_Right->ChangeSliceSprite({ 200.0f,60.0f });
	ButtonWindow_Right->Set3Slice(MenuButtonDefSize.x);
	ButtonWindow_Right->Init(L"Assets/sprite/window8.dds",
		MenuButtonDefSize.x,
		MenuButtonDefSize.y,
		SpriteNo);
	ButtonWindow_Right->SetPosition({ SaveDefPos.x + MenuButtonPosHosei.x,
		SaveDefPos.y + MenuButtonPosHosei.y, SaveDefPos.z });
	//Yes/Noテキスト
	Yes_Font = NewGO<FontRender>("MenuButtonFont_Yes", SpriteNo);
	Yes_Font->SetText(YesText);
	Yes_Font->SetColor(CVector4::White());
	Yes_Font->SetScale(YesNo_FontSize);
	Yes_Font->SetPosition({ SaveDefPos.x - MenuButtonPosHosei.x + YesNo_Font_Hosei.x + YesFont_XHosei,
		SaveDefPos.y + MenuButtonPosHosei.y + YesNo_Font_Hosei.y });
	No_Font = NewGO<FontRender>("MenuButtonFont_No", SpriteNo);
	No_Font->SetText(NoText);
	No_Font->SetColor(CVector4::White());
	No_Font->SetScale(YesNo_FontSize);
	No_Font->SetPosition({ SaveDefPos.x + MenuButtonPosHosei.x + YesNo_Font_Hosei.x + NoFont_XHosei,
		SaveDefPos.y + MenuButtonPosHosei.y + YesNo_Font_Hosei.y });

}

SaveLoad::~SaveLoad()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

	//削除
	delete m_gameData_Load;
	DeleteGO(m_BG);
	DeleteGO(ButtonWindow_Left);
	DeleteGO(ButtonWindow_Right);
	DeleteGO(m_saveWindow);
	DeleteGO(m_mapIC);
	DeleteGO(m_loadChackText);
	DeleteGO(Yes_Font);
	DeleteGO(No_Font);
	DeleteGO(m_load_PlayerLevel);
	DeleteGO(m_load_PlayerHP);
	DeleteGO(m_load_PlayerPlace);
}

void SaveLoad::Update() {

	//コマンド受付
	if (m_loadFlag == false && m_noLoadFlag == false) {

		//マウスオーバー演出
		m_nowCommand = NullSelect_Command;
		if (m_fifeFlag == true) {
			if (ButtonWindow_Left->MouseOverMouse() == true) {
				m_nowCommand = Yes_Command;
				ButtonWindow_Left->SetAlpha(1.0f);
				Yes_Font->SetAlpha(1.0f);
				if (m_seFlag == false) {
					SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");	//SE
					m_seFlag = true;
				}
			}
			else {
				ButtonWindow_Left->SetAlpha(NoActiveAlpha);
				Yes_Font->SetAlpha(NoActiveAlpha);
			}
		}
		else {
			ButtonWindow_Left->SetMulColor(CanNotSelect);
			Yes_Font->SetColor(CanNotSelect);
		}
		if (ButtonWindow_Right->MouseOverMouse() == true) {
			m_nowCommand = No_Command;
			ButtonWindow_Right->SetAlpha(1.0f);
			No_Font->SetAlpha(1.0f);
			if (m_seFlag == false) {
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");	//SE
				m_seFlag = true;
			}
		}
		else {
			ButtonWindow_Right->SetAlpha(NoActiveAlpha);
			No_Font->SetAlpha(NoActiveAlpha);
		}
		//SEフラグの初期化
		if (m_nowCommand == NullSelect_Command) {
			m_seFlag = false;
		}

		//決定処理
		int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		if (Left_Key == MouseSupporter::Release_Push) {
			switch (m_nowCommand)
			{
			case SaveLoad::Yes_Command:
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Load.wav");	//SE
				m_loadFlag = true;
				m_saveLoadEnd = LoadSuccess;
			break;
			case SaveLoad::No_Command:
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cancel.wav", 3.0f);	//SE
				m_noLoadFlag = true;
				m_saveLoadEnd = NoLoad;
			break;
			}
		}
	}
	else {
		m_fadeinTimer++;	//閉じるタイマー
	}

	//ロード処理
	if (m_loadFlag == true) {
		if (m_loadDataFlag == false) {
			LoadData();
		}
	}

	//フェードアウト
	m_fadeoutTimer++;
	if (m_fadeoutTimer == FadeOutLimit) {
		//トランジション
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox,
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true);
		//タイトルBGMの再生
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(L"Assets/sound/BGM/GameLoad.wav");
	}
	//フェードイン
	if (m_fadeinTimer == FadeInLimit) {
		//トランジション
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox,
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, false);
		//BGMのフェードアウト
		SceneManager::GetInstance()->GetSoundManagerInstance()->BGM_VolumeFade(0.0f, 60);
	}
	if (m_fadeinTimer == FadeInEndLimit) {
		//終了
		m_endFlag = true;
	}

}

void SaveLoad::Render() {

}

void SaveLoad::LoadData() {

	//ロードする
	FILE* fp = fopen("save.bin", "rb");
	if (fp != NULL) {
		fread(GameData::GetInstance(), sizeof(GameData), 1, fp);
		fclose(fp);
		SceneManager::GetInstance()->GetSystemInstance()->m_loadDataFlag = true;
	}

	//ロード演出
	m_loadChackText->SetText(LoadNowText);
	m_loadChackText->SetPosition({ LoadChackTextPos.x + LoadX_Hosei,LoadChackTextPos.y });

	m_loadDataFlag = true;
}