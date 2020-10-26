#include "stdafx.h"
#include "Menu_BoxAllDelete.h"
#include "BoxMaker.h"

Menu_BoxAllDelete::Menu_BoxAllDelete()
{
	//メニューのメイン部分
	MenuWindow = NewGO<SpriteRender>("MenuWindow_BAD", SpriteNo);
	MenuWindow->ChangeSliceSprite({ 120.0f,120.0f });
	MenuWindow->Init(L"Assets/sprite/window7.dds",
		DefMenuWindowSize.x,
		DefMenuWindowSize.y,
		SpriteNo);
	MenuWindow->SetPosition(MenuDefPos);
	//ヘッダー
	Header_Font = NewGO<FontRender>("MenuHeaderFont_BAD", SpriteNo);
	Header_Font->SetText(HeaderText);
	Header_Font->SetColor(CVector4::White());
	Header_Font->SetScale(Header_FontSize);
	Header_Font->SetPosition({ MenuDefPos.x + Header_Font_Hosei.x,MenuDefPos.y + Header_Font_Hosei.y });
	//確認メッセージ
	Check_Font = NewGO<FontRender>("MenuCheckFont_BAD", SpriteNo);
	Check_Font->SetText(CheckText);
	Check_Font->SetColor(CVector4::White());
	Check_Font->SetScale(Header_FontSize);
	Check_Font->SetPosition({ MenuDefPos.x + Check_Font_Hosei.x,MenuDefPos.y + Check_Font_Hosei.y });
	//Yes/Noボタン
	ButtonWindow_Left = NewGO<SpriteRender>("MenuCommand_BAD_Left", SpriteNo);
	ButtonWindow_Left->ChangeSliceSprite({ 200.0f,60.0f });
	ButtonWindow_Left->Set3Slice(MenuButtonDefSize.x);
	ButtonWindow_Left->Init(L"Assets/sprite/window8.dds",
		MenuButtonDefSize.x,
		MenuButtonDefSize.y,
		SpriteNo);
	ButtonWindow_Left->SetPosition({ MenuDefPos.x - MenuButtonPosHosei.x, 
		MenuDefPos.y + MenuButtonPosHosei.y, MenuDefPos.z });
	ButtonWindow_Right = NewGO<SpriteRender>("MenuCommand_BAD_Right", SpriteNo);
	ButtonWindow_Right->ChangeSliceSprite({ 200.0f,60.0f });
	ButtonWindow_Right->Set3Slice(MenuButtonDefSize.x);
	ButtonWindow_Right->Init(L"Assets/sprite/window8.dds",
		MenuButtonDefSize.x,
		MenuButtonDefSize.y,
		SpriteNo);
	ButtonWindow_Right->SetPosition({ MenuDefPos.x + MenuButtonPosHosei.x,
		MenuDefPos.y + MenuButtonPosHosei.y, MenuDefPos.z });
	//Yes/Noテキスト
	Yes_Font = NewGO<FontRender>("MenuButtonFont_BAD_Yes", SpriteNo);
	Yes_Font->SetText(YesText);
	Yes_Font->SetColor(CVector4::White());
	Yes_Font->SetScale(Header_FontSize);
	Yes_Font->SetPosition({ MenuDefPos.x - MenuButtonPosHosei.x + YesNo_Font_Hosei.x + YesFont_XHosei,
		MenuDefPos.y + MenuButtonPosHosei.y + YesNo_Font_Hosei.y });
	No_Font = NewGO<FontRender>("MenuButtonFont_BAD_No", SpriteNo);
	No_Font->SetText(NoText);
	No_Font->SetColor(CVector4::White());
	No_Font->SetScale(Header_FontSize);
	No_Font->SetPosition({ MenuDefPos.x + MenuButtonPosHosei.x + YesNo_Font_Hosei.x + NoFont_XHosei,
		MenuDefPos.y + MenuButtonPosHosei.y + YesNo_Font_Hosei.y });

}

Menu_BoxAllDelete::~Menu_BoxAllDelete()
{
	//削除
	DeleteGO(MenuWindow);
	DeleteGO(Header_Font);
	DeleteGO(Check_Font);
	DeleteGO(ButtonWindow_Left);
	DeleteGO(ButtonWindow_Right);
	DeleteGO(Yes_Font);
	DeleteGO(No_Font);
}

void Menu_BoxAllDelete::DeleteCheckUpdate() {

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
		switch (m_nowCommand)
		{
		case Menu_BoxAllDelete::Yes_Command:
			BoxMaker::GetInstance()->BoxAllDelete();
			CommandEnd();
			break;
		case Menu_BoxAllDelete::No_Command:
			CommandEnd();
			break;
		}
	}


}

void Menu_BoxAllDelete::CommandEnd() {

	MenuWindow->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	Header_Font->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	Check_Font->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	ButtonWindow_Left->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	ButtonWindow_Right->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	Yes_Font->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);
	No_Font->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,0.0f }, DeleteTime, 0);

	m_deleteFlag = true;	//終了

}