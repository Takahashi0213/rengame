#include "stdafx.h"
#include "GameUI.h"
#include "Game.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//設定！

	Accessory1 = new Sprite;
	Accessory1->Sprite_Init(L"Assets/sprite/Accessory1.dds", 340.0f, 340.0f);
	Accessory1->m_mainSprite.Scale = AccScale;
	Accessory1->m_mainSprite.Position = AccDefPos;

	Accessory2 = new Sprite;
	Accessory2->Sprite_Init(L"Assets/sprite/Accessory2.dds", 600.0f, 300.0f);
	Accessory2->m_mainSprite.Scale = CVector3().One();
	Accessory2->m_mainSprite.Position = Acc2DefPos;

	//マナゲージ
	GageUnder = NewGO<SpriteRender>("GageUnder", 0);
	GageUnder->Init(L"Assets/sprite/Gage1_Under.dds", 400.0f, 60.0f, 7);
	GageUnder->SetPosition(GagePos);

	RedGage = NewGO<SpriteRender>("RedGage", 0);
	RedGage->SetRenderMode(Sprite_RenderMode::X_Cut);
	RedGage->SetMulColor(RedGageColor);
	RedGage->SetCutLine(1.0f);
	RedGage->SetPosition(GagePos);
	RedGage->Init(L"Assets/sprite/Gage1_Under.dds", 350.0f, 60.0f, 7);

	Gage = NewGO<SpriteRender>("MagicGage", 0);
	Gage->SetRenderMode(Sprite_RenderMode::X_Cut);
	Gage->SetCutLine(1.0f);
	Gage->SetPosition(GagePos);
	Gage->Init(L"Assets/sprite/Gage1.dds", 350.0f, 60.0f, 7);

	MagicWindow = NewGO<SpriteRender>("MagicWindow", 0);
	MagicWindow->ChangeSliceSprite({ 120.0f,24.0f });
	MagicWindow->Set3Slice(280.0f);
	MagicWindow->SetPosition(GagePos);
	MagicWindow->Init(L"Assets/sprite/window2.dds", 400.0f, 60.0f, 7);

	//体力 とりあえず最大1000ね…
	float X_Hosei = 0.0f;

	Life1_Window = new Sprite;
	Life1_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life1_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life1_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life1_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life1_Window->m_mainSprite.Scale = LifeScale;

	Life1 = NewGO<SpriteRender>("Life1", 0);
	Life1->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life1->SetCutLine(0.0f);
	Life1->SetPosition({ LifeDefPos.x+X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life1->SetScale(LifeScale);
	Life1->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life2_Window = new Sprite;
	Life2_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life2_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life2_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life2_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life2_Window->m_mainSprite.Scale = LifeScale;

	Life2 = NewGO<SpriteRender>("Life2", 0);
	Life2->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life2->SetCutLine(0.0f);
	Life2->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life2->SetScale(LifeScale);
	Life2->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life3_Window = new Sprite;
	Life3_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life3_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life3_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life3_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life3_Window->m_mainSprite.Scale = LifeScale;

	Life3 = NewGO<SpriteRender>("Life3", 0);
	Life3->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life3->SetCutLine(0.0f);
	Life3->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life3->SetScale(LifeScale);
	Life3->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life4_Window = new Sprite;
	Life4_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life4_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life4_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life4_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life4_Window->m_mainSprite.Scale = LifeScale;

	Life4 = NewGO<SpriteRender>("Life4", 0);
	Life4->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life4->SetCutLine(0.0f);
	Life4->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life4->SetScale(LifeScale);
	Life4->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life5_Window = new Sprite;
	Life5_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life5_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life5_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life5_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life5_Window->m_mainSprite.Scale = LifeScale;

	Life5 = NewGO<SpriteRender>("Life5", 0);
	Life5->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life5->SetCutLine(0.0f);
	Life5->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life5->SetScale(LifeScale);
	Life5->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life6_Window = new Sprite;
	Life6_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life6_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life6_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life6_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life6_Window->m_mainSprite.Scale = LifeScale;

	Life6 = NewGO<SpriteRender>("Life6", 0);
	Life6->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life6->SetCutLine(0.0f);
	Life6->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life6->SetScale(LifeScale);
	Life6->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life7_Window = new Sprite;
	Life7_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life7_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life7_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life7_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life7_Window->m_mainSprite.Scale = LifeScale;

	Life7 = NewGO<SpriteRender>("Life7", 0);
	Life7->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life7->SetCutLine(0.0f);
	Life7->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life7->SetScale(LifeScale);
	Life7->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life8_Window = new Sprite;
	Life8_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life8_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life8_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life8_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life8_Window->m_mainSprite.Scale = LifeScale;

	Life8 = NewGO<SpriteRender>("Life8", 0);
	Life8->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life8->SetCutLine(0.0f);
	Life8->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life8->SetScale(LifeScale);
	Life8->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life9_Window = new Sprite;
	Life9_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life9_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life9_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life9_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life9_Window->m_mainSprite.Scale = LifeScale;

	Life9 = NewGO<SpriteRender>("Life9", 0);
	Life9->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life9->SetCutLine(0.0f);
	Life9->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life9->SetScale(LifeScale);
	Life9->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life10_Window = new Sprite;
	Life10_Window->Sprite_Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f);
	Life10_Window->m_mainSprite.Position.x = LifeDefPos.x + X_Hosei;
	Life10_Window->m_mainSprite.Position.y = LifeDefPos.y;
	Life10_Window->m_mainSprite.Position.z = LifeDefPos.z;
	Life10_Window->m_mainSprite.Scale = LifeScale;

	Life10 = NewGO<SpriteRender>("Life10", 0);
	Life10->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life10->SetCutLine(0.0f);
	Life10->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life10->SetScale(LifeScale);
	Life10->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

}

GameUI::~GameUI()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void GameUI::Update() {

	//様々な更新と計算
	m_gameMenu.GameMenuUpdate();
	ManaUpdate();
	LifeUpdate();

	//スプライトの更新
	Accessory2->Sprite_Update();
	Accessory1->Sprite_Update();
	Life1_Window->Sprite_Update();
	Life2_Window->Sprite_Update();
	Life3_Window->Sprite_Update();
	Life4_Window->Sprite_Update();
	Life5_Window->Sprite_Update();
	Life6_Window->Sprite_Update();
	Life7_Window->Sprite_Update();
	Life8_Window->Sprite_Update();
	Life9_Window->Sprite_Update();
	Life10_Window->Sprite_Update();
}

void GameUI::Render() {

	Accessory2->Sprite_Draw();
	Accessory1->Sprite_Draw();
	Life1_Window->Sprite_Draw();
	Life2_Window->Sprite_Draw();
	Life3_Window->Sprite_Draw();
	Life4_Window->Sprite_Draw();
	Life5_Window->Sprite_Draw();
	Life6_Window->Sprite_Draw();
	Life7_Window->Sprite_Draw();
	Life8_Window->Sprite_Draw();
	Life9_Window->Sprite_Draw();
	Life10_Window->Sprite_Draw();

}

void GameUI::ManaUpdate() {

	Game::GameMode NowGameMode = Game::GetInstance()->GetGameMode();
	int MaxMana = GameData::GetInstance()->GetMaxMagic();
	int NowMana = GameData::GetInstance()->GetMagicPower();

	//まずは宇宙色の部分
	float Mana = (float)NowMana / (float)MaxMana;
	Gage->SetCutLine(Mana);

	//赤い部分は現在モードで分岐
	if (NowGameMode == Game::ActionMode) {
		//アクションモードなら宇宙色のカットラインに近づけていく
		RedGage->SetMulColor({ 10.0f,10.0f,10.0f,1.0f });
		float nowLine = RedGage->GetCutLine();
		nowLine *= RedGageDownSpeed;
		if (Mana > nowLine) {
			nowLine = Mana;
		}
		RedGage->SetCutLine(nowLine);
	}
	else if (NowGameMode == Game::CreateMode) {
		//クリエイトモードなら色が赤いだけで長さは変化しない
		RedGage->SetMulColor(RedGageColor);
	}

}

void GameUI::LifeUpdate() {

	int MaxHP = GameData::GetInstance()->GetMaxHP();
	int NowHP = GameData::GetInstance()->GetHP();

	//更新！

	//ゲージ1
	float GageX = (NowHP) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life1->SetCutLine(GageX);
	//ゲージ2
	GageX = (NowHP - 100) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life2->SetCutLine(GageX);
	if (MaxHP >= 200) {
		Life2_Window->m_mainSprite.MulColor.w = 1.0f;
		Life2->SetAlpha(1.0f);
	}
	else {
		Life2_Window->m_mainSprite.MulColor.w = 0.0f;
		Life2->SetAlpha(0.0f);
	}
	//ゲージ3
	GageX = (NowHP - 200) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life3->SetCutLine(GageX);
	if (MaxHP >= 300) {
		Life3_Window->m_mainSprite.MulColor.w = 1.0f;
		Life3->SetAlpha(1.0f);
	}
	else {
		Life3_Window->m_mainSprite.MulColor.w = 0.0f;
		Life3->SetAlpha(0.0f);
	}
	//ゲージ4
	GageX = (NowHP - 300) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life4->SetCutLine(GageX);
	if (MaxHP >= 400) {
		Life4_Window->m_mainSprite.MulColor.w = 1.0f;
		Life4->SetAlpha(1.0f);
	}
	else {
		Life4_Window->m_mainSprite.MulColor.w = 0.0f;
		Life4->SetAlpha(0.0f);
	}
	//ゲージ5
	GageX = (NowHP - 400) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life5->SetCutLine(GageX);
	if (MaxHP >= 500) {
		Life5_Window->m_mainSprite.MulColor.w = 1.0f;
		Life5->SetAlpha(1.0f);
	}
	else {
		Life5_Window->m_mainSprite.MulColor.w = 0.0f;
		Life5->SetAlpha(0.0f);
	}
	//ゲージ6
	GageX = (NowHP - 500) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life6->SetCutLine(GageX);
	if (MaxHP >= 600) {
		Life6_Window->m_mainSprite.MulColor.w = 1.0f;
		Life6->SetAlpha(1.0f);
	}
	else {
		Life6_Window->m_mainSprite.MulColor.w = 0.0f;
		Life6->SetAlpha(0.0f);
	}
	//ゲージ7
	GageX = (NowHP - 600) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life7->SetCutLine(GageX);
	if (MaxHP >= 700) {
		Life7_Window->m_mainSprite.MulColor.w = 1.0f;
		Life7->SetAlpha(1.0f);
	}
	else {
		Life7_Window->m_mainSprite.MulColor.w = 0.0f;
		Life7->SetAlpha(0.0f);
	}
	//ゲージ8
	GageX = (NowHP - 700) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life8->SetCutLine(GageX);
	if (MaxHP >= 800) {
		Life8_Window->m_mainSprite.MulColor.w = 1.0f;
		Life8->SetAlpha(1.0f);
	}
	else {
		Life8_Window->m_mainSprite.MulColor.w = 0.0f;
		Life8->SetAlpha(0.0f);
	}
	//ゲージ9
	GageX = (NowHP - 800) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life9->SetCutLine(GageX);
	if (MaxHP >= 900) {
		Life9_Window->m_mainSprite.MulColor.w = 1.0f;
		Life9->SetAlpha(1.0f);
	}
	else {
		Life9_Window->m_mainSprite.MulColor.w = 0.0f;
		Life9->SetAlpha(0.0f);
	}
	//ゲージ10
	GageX = (NowHP - 900) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life10->SetCutLine(GageX);
	if (MaxHP >= 1000) {
		Life10_Window->m_mainSprite.MulColor.w = 1.0f;
		Life10->SetAlpha(1.0f);
	}
	else {
		Life10_Window->m_mainSprite.MulColor.w = 0.0f;
		Life10->SetAlpha(0.0f);
	}



}