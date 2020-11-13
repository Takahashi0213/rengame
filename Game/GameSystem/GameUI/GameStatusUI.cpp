#include "stdafx.h"
#include "GameStatusUI.h"

GameStatus_UISystem* GameStatus_UISystem::m_instance = nullptr;

GameStatusUI::GameStatusUI()
{
	//�����ݒ�@�X�^�[�}�l�[
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
	Status_StarMoneyTextUpdate();	//�����X�^�[�}�l�[��\��
	
	m_starMoneySprite = NewGO<SpriteRender>("StatusUI_StarMoneySprite", SpritePriority);
	m_starMoneySprite->Init(L"Assets/sprite/Jewel.dds", StarMoneySpriteSize.x, StarMoneySpriteSize.y, SpritePriority);
	m_starMoneySprite->SetPosition(CVector3::Zero());

	//�����ݒ�@EXP
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
	Status_EXPBarUpdate();	//�o���l�o�[�̍X�V

	m_statusCover_EXP = NewGO<SpriteRender>("StatusUI_Cover_EXP", SpritePriority);
	m_statusCover_EXP->Init(L"Assets/sprite/exp_Gage.dds", 
		EXP_Cover_Size.x*EXP_SizeHosei.x, EXP_Cover_Size.y*EXP_SizeHosei.y, SpritePriority);
	m_statusCover_EXP->SetPosition(GameStatusUI_EXP_DefPos);

	//�S�폜�I
	Status_SpriteAlphaSet(StarMoney, 0.0f, 1, 0);
	Status_SpriteAlphaSet(EXP, 0.0f, 1, 0);
	m_effectFlag = false;

	//�����ݒ� ���x���A�b�v
	m_text_Level = NewGO<FontRender>("StatusUI_Font_LevelUp_Level", SpritePriority);
	m_text_Level->SetText(L"Level1�@��3",
		{ GameStatusUI_StarMoney_DefPos.x + LevelUp_TextHosei.x - LevelUp_TextMove,
		GameStatusUI_StarMoney_DefPos.y });
	m_text_Level->SetScale(LevelUp_TextSizeLevel);

	m_text_HP = NewGO<FontRender>("StatusUI_Font_LevelUp_HP", SpritePriority);
	m_text_HP->SetText(L"H�@P�@1�@��3",
		{ GameStatusUI_StarMoney_DefPos.x + LevelUp_TextHosei.x - LevelUp_TextMove,
		GameStatusUI_StarMoney_DefPos.y - LevelUp_TextRange - LevelUp_TextHosei.y });
	m_text_HP->SetScale(LevelUp_TextSizeStatus);

	m_text_MP = NewGO<FontRender>("StatusUI_Font_LevelUp_MP", SpritePriority);
	m_text_MP->SetText(L"M�@P�@1�@��3",
		{ GameStatusUI_StarMoney_DefPos.x + LevelUp_TextHosei.x - LevelUp_TextMove,
		GameStatusUI_StarMoney_DefPos.y - (LevelUp_TextRange * 2.0f) - LevelUp_TextHosei.y });
	m_text_MP->SetScale(LevelUp_TextSizeStatus);

}

GameStatusUI::~GameStatusUI()
{
}

void GameStatusUI::GameStatusUI_Update() {

	//�Đ���Ԃɂ���ĕ���
	if (m_statusEffectFlag == false) {
		//���o��T��

		//�����������X�g�ɉ��������ĂȂ��Ȃ炱�̐�֍s���K�v�͂ȁ[���I
		if (static_cast<int>(m_statusList.size() == 0)) {
			if (m_effectFlag == true) {
				Status_SpriteAlphaSet(StarMoney, 0.0f, StatusAlphaTime, StatusDeleteDelay);
				Status_SpriteAlphaSet(EXP, 0.0f, StatusAlphaTime, StatusDeleteDelay);
				m_effectFlag = false;
			}
			return;
		}
		//���݂̉��o�ƈ�v���Ă�����̂�T���i�Ȃ��ꍇ�͐擪�j
		std::list<StatusData>::iterator it = m_statusList.begin();
		while (it != m_statusList.end()) {
			if (m_nowStatusAnime == Status_Anime::StatusAnime_NULL) {
				//�����Đ����Ă��Ȃ��Ȃ�ŏ��Ō���
				StatusEffect_StartStandBy(it);
				return;
			}
			else {
				if (m_nowStatusAnime == it->StatusAnime) {
					//���ݍĐ����̉��o�ƈ�v���Ă���̂Ō���
					StatusEffect_StartStandBy(it);
					return;
				}
			}
		}
		//�ǂ����v���Ȃ������̂Ő擪���g�p
		it = m_statusList.begin();
		StatusEffect_StartStandBy(it);
	}
	else {
		//���o���I��������`�F�b�N
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
		//�\�����s��
		switch (NewStatusAnime)
		{
		case GameStatusUI::StatusAnime_NULL:
			std::abort();	//�ُ�Ȓl�ł��B
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
		//�X�^�[�}�l�[
		//m_statusBase_StarMoney->m_spriteSupporter.SpriteDelayReset();
		//m_text_StarMoney->m_fontSupporter.FontDelayReset();
		//m_starMoneySprite->m_spriteSupporter.SpriteDelayReset();
		//
		m_statusBase_StarMoney->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		m_text_StarMoney->m_fontSupporter.FontColorSet({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		m_starMoneySprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,alpha }, time, deley);
		break;
	case EXP:
		//�o���l
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
		std::abort();	//�ُ�Ȓl�ł��B
		break;
	case GameStatusUI::StarMoney:
		//�X�^�[�}�l�[�̍��W���X�V

		if (m_kyokusen == 0.0f) {
			//�摜����
			m_starMoneySprite->SetPosition(CVector3::Zero());
			m_starMoneySprite->SetAlpha(1.0f);
			m_starMoneySprite->m_spriteSupporter.SpriteDelayReset();
			m_text_StarMoney->SetColor(CVector4::White());
			//���W�v�Z�i�x�W�F�Ȑ��j
			m_point_2 = m_starMoneySprite->GetPosition();	//�n�_
			m_point_3 = GameStatusUI_StarMoney_DefPos;		//�I�_
			CVector3 Vec = m_point_3 - m_point_2;			//�n�_����I�_�ɐL�т�x�N�g��
			Vec /= 4.0f;
			CVector3 Pos2 = m_starMoneySprite->GetPosition() + Vec;
			Pos2.y += Y_Hosei;
			m_point_4 = Pos2;	//�n�_���
			Pos2 = m_point_3 - Vec;
			Pos2.y = m_point_4.y;
			m_point_1 = Pos2;	//�I�_���
		}

		m_kyokusen += 0.1f;
		output_point = m_point_2 * (1 - m_kyokusen)*(1 - m_kyokusen)*(1 - m_kyokusen) + 3 *
			m_point_4 * m_kyokusen*(1 - m_kyokusen)*(1 - m_kyokusen) + 3 *
			m_point_1 * m_kyokusen*m_kyokusen*(1 - m_kyokusen) +
			m_point_3 * m_kyokusen*m_kyokusen*m_kyokusen;

		//�ݒ肷��
		m_starMoneySprite->SetPosition(output_point);

		if (m_kyokusen >= 1.0f) {
			//�I��
			m_kyokusen = 0.0f;
			m_starMoneySprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, 1, 0);	//�O�̂���1�t���[������
			//�X�^�[�}�l�[���Z�����o
			GameData::GetInstance()->StarMoneyPlus(m_statusList_it->Add);
			Status_StarMoneyTextUpdate();
			//�e�L�X�g�W�����v
			m_text_StarMoney->SetColor(StarMoneyTextGetColor);
			m_text_StarMoney->m_fontSupporter.FontMoveSet({ StarMoneyTextJump.x,StarMoneyTextJump.y },
				StarMoneyTextJumpTime, 0, true);
			m_text_StarMoney->m_fontSupporter.FontMoveSet({ StarMoneyTextJump.x,-StarMoneyTextJump.y }, 
				StarMoneyTextJumpTime, StarMoneyTextJumpTime, true);
			//�G�t�F�N�g�I���Ƃ������Ƃɂ���
			m_nowStatusAnime = StatusAnime_NULL;
			m_statusList.erase(m_statusList_it);
			m_statusEffectFlag = false;
		}

		break;
	case GameStatusUI::EXP:
		//�o���l�Q�[�W�������܂�
		if (EXP_Stock == -1) {
			//�����ݒ�
			EXP_Stock = m_statusList_it->Add;
			//�J�n�L�^
			m_startLevel = GameData::GetInstance()->GetLevel();
			m_startHP = GameData::GetInstance()->GetMaxHP();
			m_startMana = GameData::GetInstance()->GetMaxMagic();
		}

		//���Z����
		EXP_Stock--;
		GameData::GetInstance()->AddEXP(1);

		//�ő�Ȃ牉�o���X�L�b�v����
		if (GameData::GetInstance()->GetLevel() < GameData::GetInstance()->GetMaxLevel())
		{
			//�o���l�o�[�̍X�V
			Status_EXPBarUpdate();

			//���x���A�b�v�G�t�F�N�g�`�F�b�N
			Status_LevelUpEffect();
		}

		//�I���`�F�b�N
		if (EXP_Stock <= 0) {
			//�G�t�F�N�g�I���Ƃ������Ƃɂ���
			EXP_Stock = -1;
			m_nowStatusAnime = StatusAnime_NULL;
			m_statusList.erase(m_statusList_it);
			m_statusEffectFlag = false;
		}

		break;
	}

}

void GameStatusUI::Status_StarMoneyTextUpdate() {

	//�����X�^�[�}�l�[�̕\���X�V
	wchar_t text[MAX_PATH];
	swprintf(text, MAX_PATH-1, L"%d�@pt", GameData::GetInstance()->GetStarMoney());
	m_text_StarMoney->SetText(text);
}

void GameStatusUI::Status_EXPBarUpdate() {

	//�擾
	int NowEXP = GameData::GetInstance()->GetNowEXP();
	int NextEXP = GameData::GetInstance()->GetNextEXP();
	//�v�Z
	float gage = static_cast<float>(NowEXP) / static_cast<float>(NextEXP);
	m_statusBar_EXP->SetCutLine(gage);
	//SE
	SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/EXP_Gage.wav");

}

void GameStatusUI::Status_LevelUpEffect() {

	//���x���A�b�v
	int NowLevel = GameData::GetInstance()->GetLevel();
	
	if (NowLevel != m_startLevel) {
		//���x���A�b�v����
		if (m_levelUpSprite != nullptr) {	//���łɕ\������Ă�����폜����
			GameEffect::GetInstance()->GetInstance_SpriteAnime()->DeleteAnimationSprite(m_levelUpSprite);
		}
		m_levelUpSprite = GameEffect::GetInstance()->GetInstance_SpriteAnime()->
			NewAnimationSprite_pt(GameEffect_AnimationSprite::Anime_Name::Anime_LevelUp,
			GameStatusUI_LevelUp_DefPos, CVector3::One(), SpritePriority);
		//SE
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/LevelUP.wav");

		//�\���X�V
		int NowMaxHP = GameData::GetInstance()->GetMaxHP();
		int NowMaxMP = GameData::GetInstance()->GetMaxMagic();

		wchar_t text[MAX_PATH];
		swprintf(text, MAX_PATH - 1, L"Level%d�@��%d", m_startLevel, NowLevel);
		m_text_Level->SetText(text);
		swprintf(text, MAX_PATH - 1, L"H�@P�@%d�@��%d", m_startHP, NowMaxHP);
		m_text_HP->SetText(text);
		if (m_startHP != NowMaxHP) {
			m_text_HP->SetColor(StarMoneyTextGetColor);
		}
		else {
			m_text_HP->SetColor(CVector4::White());
		}
		swprintf(text, MAX_PATH - 1, L"M�@P�@%d�@��%d", m_startMana, NowMaxMP);
		m_text_MP->SetText(text);
		if (m_startMana != NowMaxMP) {
			m_text_MP->SetColor(StarMoneyTextGetColor);
		}
		else {
			m_text_MP->SetColor(CVector4::White());
		}

		if (m_text_Level->m_fontSupporter.GetFontMoveListLen() == 0) {
			//�ړ����� �E��
			m_text_Level->m_fontSupporter.FontMoveSet({ LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, 0, true);
			m_text_HP->m_fontSupporter.FontMoveSet({ LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, 0, true);
			m_text_MP->m_fontSupporter.FontMoveSet({ LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, 0, true);
			//�ړ����� ���ցi�\��j
			m_text_Level->m_fontSupporter.FontMoveSet({ -LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, LevelUp_TextMoveDelay, true);
			m_text_HP->m_fontSupporter.FontMoveSet({ -LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, LevelUp_TextMoveDelay, true);
			m_text_MP->m_fontSupporter.FontMoveSet({ -LevelUp_TextMove ,0.0f }, LevelUp_TextMoveTime, LevelUp_TextMoveDelay, true);
		}

		m_startLevel = NowLevel;
	}

}

/// <summary>
/// ��������GameStatus_UISystem
/// </summary>

GameStatus_UISystem::GameStatus_UISystem() {
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}
	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}

GameStatus_UISystem::~GameStatus_UISystem() {
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void GameStatus_UISystem::Update() {
	m_gameStatusUI.GameStatusUI_Update();
}

void GameStatus_UISystem::Render() {

}
