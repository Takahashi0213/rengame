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
	m_text_StarMoney->SetText(L"100pt",
		{ GameStatusUI_StarMoney_DefPos.x + StarMoneyTextHosei.x,
		GameStatusUI_StarMoney_DefPos.y + StarMoneyTextHosei.y });
	m_text_StarMoney->SetScale(FontSize);

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
	m_statusBar_EXP->SetCutLine(0.5f);
	m_statusBar_EXP->SetPosition(GameStatusUI_EXP_DefPos);
	m_statusBar_EXP->Init(L"Assets/sprite/Gage2.dds", 
		EXP_Bar_Size.x*EXP_SizeHosei.x, EXP_Bar_Size.y*EXP_SizeHosei.y, SpritePriority);

	m_statusCover_EXP = NewGO<SpriteRender>("StatusUI_Cover_EXP", SpritePriority);
	m_statusCover_EXP->Init(L"Assets/sprite/exp_Gage.dds", 
		EXP_Cover_Size.x*EXP_SizeHosei.x, EXP_Cover_Size.y*EXP_SizeHosei.y, SpritePriority);
	m_statusCover_EXP->SetPosition(GameStatusUI_EXP_DefPos);

	//全削除！
	Status_SpriteAlphaSet(StarMoney, 0.0f, 0);
	Status_SpriteAlphaSet(EXP, 0.0f, 0);

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
				Status_SpriteAlphaSet(StarMoney, 0.0f, StatusAlphaTime);
				Status_SpriteAlphaSet(EXP, 0.0f, StatusAlphaTime);
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
			Status_SpriteAlphaSet(StarMoney, 1.0f, StatusAlphaTime);
			Status_SpriteAlphaSet(EXP, 0.0f, StatusAlphaTime);
			break;
		case GameStatusUI::EXP:
			Status_SpriteAlphaSet(StarMoney, 0.0f, StatusAlphaTime);
			Status_SpriteAlphaSet(EXP, 1.0f, StatusAlphaTime);
			break;
		}
		m_nowStatusAnime = NewStatusAnime;
	}
}

void GameStatusUI::Status_SpriteAlphaSet(const Status_Anime anime, const float alpha, const int time) {

	m_effectFlag = true;
	switch (anime)
	{
	case StarMoney:
		//スターマネー
		m_statusBase_StarMoney->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, 0);
		m_text_StarMoney->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,alpha }, time, 0);
		m_starMoneySprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, 0);
		break;
	case EXP:
		//経験値
		m_statusBase_EXP->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, 0);
		m_statusBar_EXP->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, 0);
		m_statusCover_EXP->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, 0);
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
			//座標計算
			m_point_2 = m_starMoneySprite->GetPosition();	//始点
			m_point_3 = GameStatusUI_StarMoney_DefPos;	//終点
			CVector3 Vec = m_point_3 - m_point_2;	//始点から終点に伸びるベクトル
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
			m_statusList.erase(m_statusList_it);
			m_starMoneySprite->SetAlpha(0.0f);
			m_starMoneySprite->SetPosition(CVector3::Zero());
			m_nowStatusAnime = StatusAnime_NULL;
			m_statusEffectFlag = false;
		}

		break;
	case GameStatusUI::EXP:
		//経験値ゲージが増えます
		break;
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
