#include "stdafx.h"
#include "GameUI.h"

GameUI* GameUI::m_instance = nullptr;

GameUI::GameUI()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�ݒ�I

	Accessory1 = NewGO<SpriteRender>("Accessory1", 0);
	Accessory1->Init(L"Assets/sprite/Accessory1.dds", 340.0f, 340.0f,6);
	Accessory1->SetScale(AccScale);
	Accessory1->SetPosition(AccDefPos);

	Accessory2 = NewGO<SpriteRender>("Accessory2", 0);
	Accessory2->Init(L"Assets/sprite/Accessory2.dds", 600.0f, 300.0f,6);
	Accessory2->SetScale(CVector3().One());
	Accessory2->SetPosition(Acc2DefPos);

	//�}�i�Q�[�W
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

	//�̗� �Ƃ肠�����ő�1000�ˁc
	float X_Hosei = 0.0f;

	Life1_Window = NewGO<SpriteRender>("Life1", 6);
	Life1_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f,6);
	Life1_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life1_Window->SetScale(LifeScale);

	Life1 = NewGO<SpriteRender>("Life1", 0);
	Life1->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life1->SetCutLine(0.0f);
	Life1->SetPosition({ LifeDefPos.x+X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life1->SetScale(LifeScale);
	Life1->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life2_Window = NewGO<SpriteRender>("Life2", 6);
	Life2_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life2_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life2_Window->SetScale(LifeScale);

	Life2 = NewGO<SpriteRender>("Life2", 0);
	Life2->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life2->SetCutLine(0.0f);
	Life2->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life2->SetScale(LifeScale);
	Life2->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life3_Window = NewGO<SpriteRender>("Life3", 6);
	Life3_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life3_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life3_Window->SetScale(LifeScale);

	Life3 = NewGO<SpriteRender>("Life3", 0);
	Life3->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life3->SetCutLine(0.0f);
	Life3->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life3->SetScale(LifeScale);
	Life3->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life4_Window = NewGO<SpriteRender>("Life4", 6);
	Life4_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life4_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life4_Window->SetScale(LifeScale);

	Life4 = NewGO<SpriteRender>("Life4", 0);
	Life4->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life4->SetCutLine(0.0f);
	Life4->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life4->SetScale(LifeScale);
	Life4->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life5_Window = NewGO<SpriteRender>("Life5", 6);
	Life5_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life5_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life5_Window->SetScale(LifeScale);

	Life5 = NewGO<SpriteRender>("Life5", 0);
	Life5->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life5->SetCutLine(0.0f);
	Life5->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life5->SetScale(LifeScale);
	Life5->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life6_Window = NewGO<SpriteRender>("Life6", 6);
	Life6_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life6_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life6_Window->SetScale(LifeScale);

	Life6 = NewGO<SpriteRender>("Life6", 0);
	Life6->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life6->SetCutLine(0.0f);
	Life6->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life6->SetScale(LifeScale);
	Life6->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life7_Window = NewGO<SpriteRender>("Life7", 6);
	Life7_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life7_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life7_Window->SetScale(LifeScale);

	Life7 = NewGO<SpriteRender>("Life7", 0);
	Life7->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life7->SetCutLine(0.0f);
	Life7->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life7->SetScale(LifeScale);
	Life7->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life8_Window = NewGO<SpriteRender>("Life8", 6);
	Life8_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life8_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life8_Window->SetScale(LifeScale);

	Life8 = NewGO<SpriteRender>("Life8", 0);
	Life8->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life8->SetCutLine(0.0f);
	Life8->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life8->SetScale(LifeScale);
	Life8->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life9_Window = NewGO<SpriteRender>("Life9", 6);
	Life9_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life9_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life9_Window->SetScale(LifeScale);

	Life9 = NewGO<SpriteRender>("Life9", 0);
	Life9->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life9->SetCutLine(0.0f);
	Life9->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life9->SetScale(LifeScale);
	Life9->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	X_Hosei += LifeX_Hosei;

	Life10_Window = NewGO<SpriteRender>("Life10", 6);
	Life10_Window->Init(L"Assets/sprite/Life_Waku.dds", 220.0f, 190.0f, 6);
	Life10_Window->SetPosition({ LifeDefPos.x + X_Hosei ,LifeDefPos.y ,LifeDefPos.z });
	Life10_Window->SetScale(LifeScale);

	Life10 = NewGO<SpriteRender>("Life10", 0);
	Life10->SetRenderMode(Sprite_RenderMode::Y_Cut);
	Life10->SetCutLine(0.0f);
	Life10->SetPosition({ LifeDefPos.x + X_Hosei,LifeDefPos.y,LifeDefPos.z });
	Life10->SetScale(LifeScale);
	Life10->Init(L"Assets/sprite/Life.dds", 190.0f, 160.0f, 7);

	//�S���ݒ�
	m_spriteList.push_back(Accessory1);
	m_spriteList.push_back(Accessory2);
	m_spriteList.push_back(GageUnder);
	m_spriteList.push_back(RedGage);
	m_spriteList.push_back(Gage);
	m_spriteList.push_back(MagicWindow);
	m_spriteList.push_back(Life1);
	m_spriteList.push_back(Life2);
	m_spriteList.push_back(Life3);
	m_spriteList.push_back(Life4);
	m_spriteList.push_back(Life5);
	m_spriteList.push_back(Life6);
	m_spriteList.push_back(Life7);
	m_spriteList.push_back(Life8);
	m_spriteList.push_back(Life9);
	m_spriteList.push_back(Life10);
	m_spriteList.push_back(Life1_Window);
	m_spriteList.push_back(Life2_Window);
	m_spriteList.push_back(Life3_Window);
	m_spriteList.push_back(Life4_Window);
	m_spriteList.push_back(Life5_Window);
	m_spriteList.push_back(Life6_Window);
	m_spriteList.push_back(Life7_Window);
	m_spriteList.push_back(Life8_Window);
	m_spriteList.push_back(Life9_Window);
	m_spriteList.push_back(Life10_Window);

}

GameUI::~GameUI()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void GameUI::Update() {

	//�l�X�ȍX�V�ƌv�Z
	m_gameMenu.GameMenuUpdate();
	ManaUpdate();
	LifeUpdate();

}

void GameUI::Render() {

}

void GameUI::ManaUpdate() {

	SceneManager::GameMode NowGameMode = SceneManager::GetInstance()->GetGameMode();
	int MaxMana = GameData::GetInstance()->GetMaxMagic();
	int NowMana = GameData::GetInstance()->GetMagicPower();

	//�܂��͉F���F�̕���
	float Mana = static_cast<float>(NowMana) / static_cast<float>(MaxMana);
	Gage->SetCutLine(Mana);

	//�Ԃ������͌��݃��[�h�ŕ���
	if (NowGameMode == SceneManager::ActionMode) {
		//�A�N�V�������[�h�Ȃ�F���F�̃J�b�g���C���ɋ߂Â��Ă���
		RedGage->SetMulColor({ 10.0f,10.0f,10.0f,1.0f });
		float nowLine = RedGage->GetCutLine();
		nowLine *= RedGageDownSpeed;
		if (Mana > nowLine) {
			nowLine = Mana;
		}
		RedGage->SetCutLine(nowLine);
	}
	else if (NowGameMode == SceneManager::CreateMode) {
		//�N���G�C�g���[�h�Ȃ�F���Ԃ������Œ����͕ω����Ȃ�
		RedGage->SetMulColor(RedGageColor);
	}

}

void GameUI::LifeUpdate() {

	//�擾
	int MaxHP = GameData::GetInstance()->GetMaxHP();
	int NowHP = GameData::GetInstance()->GetHP();

	//�X�V�I

	//�Q�[�W1
	float GageX = (NowHP) / 100.0f;
	if (GageX < 0.0f) {
		GageX = 0.0f;
	}
	if (GageX > 1.0f) {
		GageX = 1.0f;
	}
	GageX = 1.0f - GageX;
	Life1->SetCutLine(GageX);
	//�Q�[�W2
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
		Life2_Window->SetAlpha(1.0f);
		Life2->SetAlpha(1.0f);
	}
	else {
		Life2_Window->SetAlpha(0.0f);
		Life2->SetAlpha(0.0f);
	}
	//�Q�[�W3
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
		Life3_Window->SetAlpha(1.0f);
		Life3->SetAlpha(1.0f);
	}
	else {
		Life3_Window->SetAlpha(0.0f);
		Life3->SetAlpha(0.0f);
	}
	//�Q�[�W4
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
		Life4_Window->SetAlpha(1.0f);
		Life4->SetAlpha(1.0f);
	}
	else {
		Life4_Window->SetAlpha(0.0f);
		Life4->SetAlpha(0.0f);
	}
	//�Q�[�W5
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
		Life5_Window->SetAlpha(1.0f);
		Life5->SetAlpha(1.0f);
	}
	else {
		Life5_Window->SetAlpha(0.0f);
		Life5->SetAlpha(0.0f);
	}
	//�Q�[�W6
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
		Life6_Window->SetAlpha(1.0f);
		Life6->SetAlpha(1.0f);
	}
	else {
		Life6_Window->SetAlpha(0.0f);
		Life6->SetAlpha(0.0f);
	}
	//�Q�[�W7
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
		Life7_Window->SetAlpha(1.0f);
		Life7->SetAlpha(1.0f);
	}
	else {
		Life7_Window->SetAlpha(0.0f);
		Life7->SetAlpha(0.0f);
	}
	//�Q�[�W8
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
		Life8_Window->SetAlpha(1.0f);
		Life8->SetAlpha(1.0f);
	}
	else {
		Life8_Window->SetAlpha(0.0f);
		Life8->SetAlpha(0.0f);
	}
	//�Q�[�W9
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
		Life9_Window->SetAlpha(1.0f);
		Life9->SetAlpha(1.0f);
	}
	else {
		Life9_Window->SetAlpha(0.0f);
		Life9->SetAlpha(0.0f);
	}
	//�Q�[�W10
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
		Life10_Window->SetAlpha(1.0f);
		Life10->SetAlpha(1.0f);
	}
	else {
		Life10_Window->SetAlpha(0.0f);
		Life10->SetAlpha(0.0f);
	}



}