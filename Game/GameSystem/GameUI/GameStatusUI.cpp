#include "stdafx.h"
#include "GameStatusUI.h"

GameStatus_UISystem* GameStatus_UISystem::m_instance = nullptr;

GameStatusUI::GameStatusUI()
{
	//初期設定　スターマネー
	m_statusBase_StarMoney = NewGO<SpriteRender>("StatusUI_Base_StarMoney", SpritePriority);
	m_statusBase_StarMoney->ChangeSliceSprite({ 40.0f,40.0f });
	m_statusBase_StarMoney->Init(L"Assets/sprite/window6.dds",
		StarMoneyBaseSize.x,
		StarMoneyBaseSize.y,
		SpritePriority);
	m_statusBase_StarMoney->SetPosition(GameStatusUI_StarMoney_DefPos);

	m_text_StarMoney = NewGO<FontRender>("StatusUI_Font_StarMoney", SpritePriority);
	m_text_StarMoney->SetText(L"",
		{ GameStatusUI_StarMoney_DefPos.x + StarMoneyTextHosei.x,
		GameStatusUI_StarMoney_DefPos.y + StarMoneyTextHosei.y });
	m_text_StarMoney->SetScale(FontSize);
	Status_StarMoneyTextUpdate();	//所持スターマネーを表示
	
	m_starMoneySprite = NewGO<SpriteRender>("StatusUI_StarMoneySprite", SpritePriority);
	m_starMoneySprite->Init(L"Assets/sprite/Jewel.dds", StarMoneySpriteSize.x, StarMoneySpriteSize.y, SpritePriority);
	m_starMoneySprite->SetPosition(CVector3::Zero());

	//初期設定　EXP
	m_statusBase_EXP = NewGO<SpriteRender>("StatusUI_Base_EXP", SpritePriority);
	m_statusBase_EXP->Init(L"Assets/sprite/Gage2_Under.dds", 
		EXP_Bar_Size.x*EXP_SizeHosei.x, EXP_Bar_Size.y*EXP_SizeHosei.y, SpritePriority);
	m_statusBase_EXP->SetPosition(GameStatusUI_EXP_DefPos);

	m_statusBar_EXP = NewGO<SpriteRender>("StatusUI_Bar_EXP", SpritePriority);
	m_statusBar_EXP->SetRenderMode(Sprite_RenderMode::X_Cut);
	m_statusBar_EXP->SetCutLine(1.0);
	m_statusBar_EXP->SetPosition(GameStatusUI_EXP_DefPos);
	m_statusBar_EXP->Init(L"Assets/sprite/Gage2.dds", 
		EXP_Bar_Size.x*EXP_SizeHosei.x, EXP_Bar_Size.y*EXP_SizeHosei.y, SpritePriority);
	Status_EXPBarUpdate();	//経験値バーの更新

	m_statusCover_EXP = NewGO<SpriteRender>("StatusUI_Cover_EXP", SpritePriority);
	m_statusCover_EXP->Init(L"Assets/sprite/exp_Gage.dds", 
		EXP_Cover_Size.x*EXP_SizeHosei.x, EXP_Cover_Size.y*EXP_SizeHosei.y, SpritePriority);
	m_statusCover_EXP->SetPosition(GameStatusUI_EXP_DefPos);

	//全削除！
	Status_SpriteAlphaSet(StarMoney, 0.0f, 1, 0);
	Status_SpriteAlphaSet(EXP, 0.0f, 1, 0);
	m_effectFlag = false;

	//初期設定 レベルアップ
	m_text_Level = NewGO<FontRender>("StatusUI_Font_LevelUp_Level", SpritePriority);
	m_text_Level->SetText(L"Level1　→3",
		{ GameStatusUI_StarMoney_DefPos.x + LevelUp_TextHosei.x - LevelUp_TextMove,
		GameStatusUI_StarMoney_DefPos.y });
	m_text_Level->SetScale(LevelUp_TextSizeLevel);

	m_text_HP = NewGO<FontRender>("StatusUI_Font_LevelUp_HP", SpritePriority);
	m_text_HP->SetText(L"H　P　1　→3",
		{ GameStatusUI_StarMoney_DefPos.x + LevelUp_TextHosei.x - LevelUp_TextMove,
		GameStatusUI_StarMoney_DefPos.y - LevelUp_TextRange - LevelUp_TextHosei.y });
	m_text_HP->SetScale(LevelUp_TextSizeStatus);

	m_text_MP = NewGO<FontRender>("StatusUI_Font_LevelUp_MP", SpritePriority);
	m_text_MP->SetText(L"M　P　1　→3",
		{ GameStatusUI_StarMoney_DefPos.x + LevelUp_TextHosei.x - LevelUp_TextMove,
		GameStatusUI_StarMoney_DefPos.y - (LevelUp_TextRange * 2.0f) - LevelUp_TextHosei.y });
	m_text_MP->SetScale(LevelUp_TextSizeStatus);

}

GameStatusUI::~GameStatusUI()
{
}

void GameStatusUI::GameStatusUI_Update() {

	//再生状態によって分岐
	if (m_statusEffectFlag == false) {
		//演出を探す

		//そもそもリストに何も入ってないならこの先へ行く必要はなーい！
		if (static_cast<int>(m_statusList.size() == 0)) {
			if (m_effectFlag == true) {
				Status_SpriteAlphaSet(StarMoney, 0.0f, StatusAlphaTime, StatusDeleteDelay);
				Status_SpriteAlphaSet(EXP, 0.0f, StatusAlphaTime, StatusDeleteDelay);
				m_effectFlag = false;
			}
			return;
		}
		//現在の演出と一致しているものを探す（ない場合は先頭）
		std::list<StatusData>::iterator it = m_statusList.begin();
		while (it != m_statusList.end()) {
			if (m_nowStatusAnime == Status_Anime::StatusAnime_NULL) {
				//何も再生していないなら最初で決定
				StatusEffect_StartStandBy(it);
				return;
			}
			else {
				if (m_nowStatusAnime == it->StatusAnime) {
					//現在再生中の演出と一致しているので決定
					StatusEffect_StartStandBy(it);
					return;
				}
			}
		}
		//どれも一致しなかったので先頭を使用
		it = m_statusList.begin();
		StatusEffect_StartStandBy(it);
	}
	else {
		//演出が終わったかチェック
		Status_EffectUpdate();
	}

}

void GameStatusUI::StatusEffect_StartStandBy(const std::list<StatusData>::iterator it) {
	m_statusList_it = it;
	StatusEffect_Start();
	m_statusEffectFlag = true;
}

void GameStatusUI::StatusEffect_Start() {

	Status_Anime NewStatusAnime = m_statusList_it->StatusAnime;
	if (m_nowStatusAnime != NewStatusAnime) {
		//表示を行う
		switch (NewStatusAnime)
		{
		case GameStatusUI::StatusAnime_NULL:
			std::abort();	//異常な値です。
			break;
		case GameStatusUI::StarMoney:
			Status_SpriteAlphaSet(StarMoney, 1.0f, StatusAlphaTime, 0);
			Status_SpriteAlphaSet(EXP, 0.0f, StatusAlphaTime, 0);
			break;
		case GameStatusUI::EXP:
			Status_SpriteAlphaSet(StarMoney, 0.0f, StatusAlphaTime, 0);
			Status_SpriteAlphaSet(EXP, 1.0f, StatusAlphaTime, 0);
			break;
		}
		m_nowStatusAnime = NewStatusAnime;
	}
}

void GameStatusUI::Status_SpriteAlphaSet(const Status_Anime anime, const float alpha, const int time, const int deley) {

	m_effectFlag = true;

	switch (anime)
	{
	case StarMoney:
		//スターマネー
		//m_statusBase_StarMoney->m_spriteSupporter.SpriteDelayReset();
		//m_text_StarMoney->m_fontSupporter.FontDelayReset();
		//m_starMoneySprite->m_spriteSupporter.SpriteDelayReset();
		//
		m_statusBase_StarMoney->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		m_text_StarMoney->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		m_starMoneySprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		break;
	case EXP:
		//経験値
		//m_statusBase_EXP->m_spriteSupporter.SpriteDelayReset();
		//m_statusBar_EXP->m_spriteSupporter.SpriteDelayReset();
		//m_statusCover_EXP->m_spriteSupporter.SpriteDelayReset();
		//
		m_statusBase_EXP->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		m_statusBar_EXP->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		m_statusCover_EXP->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		break;
	}
}

void GameStatusUI::Status_EffectUpdate() {

	CVector3 output_point;

	switch (m_nowStatusAnime)
	{
	case GameStatusUI::StatusAnime_NULL:
		std::abort();	//異常な値です。
		break;
	case GameStatusUI::StarMoney:
		//スターマネーの座標を更新

		if (m_kyokusen == 0.0f) {
			//画像準備
			m_starMoneySprite->SetPosition(CVector3::Zero());
			m_starMoneySprite->SetAlpha(1.0f);
			m_starMoneySprite->m_spriteSupporter.SpriteDelayReset();
			m_text_StarMoney->SetColor(CVector4::White());
			//座標計算（ベジェ曲線）
			m_point_2 = m_starMoneySprite->GetPosition();	//始点
			m_point_3 = GameStatusUI_StarMoney_DefPos;		//終点
			CVector3 Vec = m_point_3 - m_point_2;			//始点から終点に伸びるベクトル
			Vec /= 4.0f;
			CVector3 Pos2 = m_starMoneySprite->GetPosition() + Vec;
			Pos2.y += Y_Hosei;
			m_point_4 = Pos2;	//始点寄り
			Pos2 = m_point_3 - Vec;
			Pos2.y = m_point_4.y;
			m_point_1 = Pos2;	//終点寄り
		}

		m_kyokusen += 0.1f;
		output_point = m_point_2 * (1 - m_kyokusen)*(1 - m_kyokusen)*(1 - m_kyokusen) + 3 *
			m_point_4 * m_kyokusen*(1 - m_kyokusen)*(1 - m_kyokusen) + 3 *
			m_point_1 * m_kyokusen*m_kyokusen*(1 - m_kyokusen) +
			m_point_3 * m_kyokusen*m_kyokusen*m_kyokusen;

		//設定する
		m_starMoneySprite->SetPosition(output_point);

		if (m_kyokusen >= 1.0f) {
			//終了
			m_kyokusen = 0.0f;
			m_starMoneySprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, 1, 0);	//念のため1フレーム挟む
			//スターマネー加算＆演出
			GameData::GetInstance()->StarMoneyPlus(m_statusList_it->Add);
			Status_StarMoneyTextUpdate();
			//テキストジャンプ
			m_text_StarMoney->SetColor(StarMoneyTextGetColor);
			m_text_StarMoney->m_fontSupporter.FontMoveSet({ StarMoneyTextJump.x,StarMoneyTextJump.y },
				StarMoneyTextJumpTime, 0, true);
			m_text_StarMoney->m_fontSupporter.FontMoveSet({ StarMoneyTextJump.x,-StarMoneyTextJump.y }, 
				StarMoneyTextJumpTime, StarMoneyTextJumpTime, true);
			//エフェクト終了ということにする
			m_nowStatusAnime = StatusAnime_NULL;
			m_statusList.erase(m_statusList_it);
			m_statusEffectFlag = false;
		}

		break;
	case GameStatusUI::EXP:
		//経験値ゲージが増えます
		if (EXP_Stock == -1) {
			//初期設定
			EXP_Stock = m_statusList_it->Add;
			//開始記録
			m_startLevel = GameData::GetInstance()->GetLevel();
			m_startHP = GameData::GetInstance()->GetMaxHP();
			m_startMana = GameData::GetInstance()->GetMaxMagic();
		}

		//加算処理
		EXP_Stock--;
		GameData::GetInstance()->AddEXP(1);

		//最大なら演出をスキップする
		if (GameData::GetInstance()->GetLevel() < GameData::GetInstance()->GetMaxLevel())
		{
			//経験値バーの更新
			Status_EXPBarUpdate();

			//レベルアップエフェクトチェック
			Status_LevelUpEffect();
		}

		//終了チェック
		if (EXP_Stock <= 0) {
			//エフェクト終了ということにする
			EXP_Stock = -1;
			m_nowStatusAnime = StatusAnime_NULL;
			m_statusList.erase(m_statusList_it);
			m_statusEffectFlag = false;
		}

		break;
	}

}

void GameStatusUI::Status_StarMoneyTextUpdate() {

	//所持スターマネーの表示更新
	wchar_t text[MAX_PATH];
	swprintf(text, MAX_PATH-1, L"%d　pt", GameData::GetInstance()->GetStarMoney());
	m_text_StarMoney->SetText(text);
}

void GameStatusUI::Status_EXPBarUpdate() {

	//取得
	int NowEXP = GameData::GetInstance()->GetNowEXP();
	int NextEXP = GameData::GetInstance()->GetNextEXP();
	//計算
	float gage = static_cast<float>(NowEXP) / static_cast<float>(NextEXP);
	m_statusBar_EXP->SetCutLine(gage);
	//SE
	SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/EXP_Gage.wav");

}

void GameStatusUI::Status_LevelUpEffect() {

	//レベルアップ
	int NowLevel = GameData::GetInstance()->GetLevel();
	
	if (NowLevel != m_startLevel) {
		//レベルアップ処理
		if (m_levelUpSprite != nullptr) {	//すでに表示されていたら削除する
			GameEffect::GetInstance()->GetInstance_SpriteAnime()->DeleteAnimationSprite(m_levelUpSprite);
		}
		m_levelUpSprite = GameEffect::GetInstance()->GetInstance_SpriteAnime()->
			NewAnimationSprite_pt(GameEffect_AnimationSprite::Anime_Name::Anime_LevelUp,
			GameStatusUI_LevelUp_DefPos, CVector3::One(), SpritePriority);
		//SE
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/LevelUP.wav");

		//表示更新
		int NowMaxHP = GameData::GetInstance()->GetMaxHP();
		int NowMaxMP = GameData::GetInstance()->GetMaxMagic();

		wchar_t text[MAX_PATH];
		swprintf(text, MAX_PATH - 1, L"Level%d　→%d", m_startLevel, NowLevel);
		m_text_Level->SetText(text);
		swprintf(text, MAX_PATH - 1, L"H　P　%d　→%d", m_startHP, NowMaxHP);
		m_text_HP->SetText(text);
		if (m_startHP != NowMaxHP) {
			m_text_HP->SetColor(StarMoneyTextGetColor);
		}
		else {
			m_text_HP->SetColor(CVector4::White());
		}
		swprintf(text, MAX_PATH - 1, L"M　P　%d　→%d", m_startMana, NowMaxMP);
		m_text_MP->SetText(text);
		if (m_startMana != NowMaxMP) {
			m_text_MP->SetColor(StarMoneyTextGetColor);
		}
		else {
			m_text_MP->SetColor(CVector4::White());
		}

		if (m_text_Level->m_fontSupporter.GetFontMoveListLen() == 0) {
			//移動処理 右へ
			m_text_Level->m_fontSupporter.FontMoveSet({ LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, 0, true);
			m_text_HP->m_fontSupporter.FontMoveSet({ LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, 0, true);
			m_text_MP->m_fontSupporter.FontMoveSet({ LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, 0, true);
			//移動処理 左へ（予約）
			m_text_Level->m_fontSupporter.FontMoveSet({ -LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, LevelUp_TextMoveDelay, true);
			m_text_HP->m_fontSupporter.FontMoveSet({ -LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, LevelUp_TextMoveDelay, true);
			m_text_MP->m_fontSupporter.FontMoveSet({ -LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, LevelUp_TextMoveDelay, true);
		}

		m_startLevel = NowLevel;
	}

}

/// <summary>
/// ここからGameStatus_UISystem
/// </summary>

GameStatus_UISystem::GameStatus_UISystem() {
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}
	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

GameStatus_UISystem::~GameStatus_UISystem() {
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void GameStatus_UISystem::Update() {
	m_gameStatusUI.GameStatusUI_Update();
}

void GameStatus_UISystem::Render() {

}
