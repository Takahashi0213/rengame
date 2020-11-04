#include "stdafx.h"
#include "GameEffect.h"
#include "GameScene/Game.h"

GameEffect* GameEffect::m_instance = nullptr;

GameEffect::GameEffect()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�������珀��
	m_stand.StandInit();
	m_message.MessageInit();
}

GameEffect::~GameEffect()
{	
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

//��������GameEffect_Stand

void GameEffect_Stand::StandInit() {

	//�ݒ�
	m_standSprite = NewGO<SpriteRender>("StandSprite", StandSpritePriority);
	m_standSprite->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
}

void GameEffect_Stand::StandControl(Stand_Name stand, const Stand_Command command) {

	//���������G��Null�̏ꍇ���݂̗����G�����������Ă���i�ω��Ȃ��j
	if (stand == Stand_Null) {
		stand = m_nowStand;
	}
	m_nowStand = stand;		//stand�ۑ�

	//�R�}���h���e�ŕ���
	switch (command)
	{
	case GameEffect_Stand::New_Stand:	//�����G�̐V�K�\��or�X�V

		m_standSprite->m_spriteSupporter.SpriteDelayReset();	//�f�B���C���Z�b�g

		m_standSprite->Init(Game_Stand_Data[stand].SpriteName,
			Game_Stand_Data[stand].High,
			Game_Stand_Data[stand].Wide,
			StandSpritePriority);
		m_standSprite->SetScale(StandDefScale);
		if (m_standFlag == false) {
			//�V�K�����G
			m_standSprite->SetPosition(StandDefPos_Move);
			m_standSprite->m_spriteSupporter.SpriteMove(StandDefPos, 6, 0);
			m_standSprite->m_spriteSupporter.SpriteMove(StandDefPos2, 4, 6);
			m_standSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, 6, 0);
			m_standFlag = true;
		}
		else {
			//���ɗ����G���\������Ă���̂ōX�V����
			m_standSprite->SetPosition({ StandDefPos2.x,StandDefPos2.y,0.0f });
		}
		break;
	case GameEffect_Stand::Delete_Stand:	//�����G���Ԃ����킠��
		if (m_standFlag == true) {
			m_standSprite->m_spriteSupporter.SpriteDelayReset();	//�f�B���C���Z�b�g
			m_standSprite->m_spriteSupporter.SpriteMove({ StandDefPos_Move.x * 2.0f ,StandDefPos_Move.y }, 12, 4);
			m_standSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, 6, 4);
			m_standFlag = false;
		}
		break;
	case GameEffect_Stand::Jump_Stand:	//�����҂�
		if (m_standFlag == true) {
			m_standSprite->m_spriteSupporter.SpriteDelayReset();	//�f�B���C���Z�b�g
			m_standSprite->SetPosition({ StandDefPos2.x,StandDefPos2.y,0.0f });
			m_standSprite->Init(Game_Stand_Data[stand].SpriteName,
				Game_Stand_Data[stand].High,
				Game_Stand_Data[stand].Wide,
				StandSpritePriority);
			//�W�����v�ړ����f�B���C���݂Őݒ�
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,JumpMove_A }, JumpWait_A, 0, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,-JumpMove_A }, JumpWait_A, JumpWait_A, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,JumpMove_B }, JumpWait_B, JumpWait_A*2, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,-JumpMove_B }, JumpWait_B, (JumpWait_A * 2)+ JumpWait_B, true);
		}
		break;
	case GameEffect_Stand::Shake_Stand:	//����������
		if (m_standFlag == true) {
			m_standSprite->m_spriteSupporter.SpriteDelayReset();	//�f�B���C���Z�b�g
			m_standSprite->SetPosition({ StandDefPos2.x,StandDefPos2.y,0.0f });
			m_standSprite->Init(Game_Stand_Data[stand].SpriteName,
				Game_Stand_Data[stand].High,
				Game_Stand_Data[stand].Wide,
				StandSpritePriority);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,-50.0f }, 4, 0, true);
			m_standSprite->m_spriteSupporter.SpriteShake({ ShakeMove_X ,0.0f }, ShakeCount, 30 / ShakeCount);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,60.0f }, 4, 30, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,-10.0f }, 4, 34, true);
		}
		break;
	}

}

//��������GameEffect_Message

void GameEffect_Message::MessageInit() {

	//�����_�[���쐬
	m_windowSprite = NewGO<SpriteRender>("WindowSprite", WindowSpritePriority);
	m_windowOkuriSprite = NewGO<SpriteRender>("WindowOkuriSprite", WindowOkuriSpritePriority);
	m_messageSkipSprite = NewGO<SpriteRender>("MessageSkipSprite", MessageSkipSpritePriority);
	m_messageFont = NewGO<FontRender>("MessageFont", MessageFontPriority);
	m_messageSkipOshiraseFont = NewGO<FontRender>("MessageSkipOshiraseFont", MessageSkipOshiraseFontPriority);
	m_logBlack = NewGO<SpriteRender>("LogBlack", LogWindowSpritePriority);
	m_logWindow = NewGO<SpriteRender>("LogWindow", LogWindowSpritePriority);
	m_logFont = NewGO<FontRender>("LogFont", LogFontPriority);

	//�摜��ݒ�
	m_windowSprite->Init(L"Assets/sprite/fukidasi.dds", 600.0f, 400.0f, WindowSpritePriority);
	m_windowOkuriSprite->Init(L"Assets/sprite/okuri.dds", 50.0f, 50.0f, WindowOkuriSpritePriority);
	m_messageSkipSprite->Init(L"Assets/sprite/skipNow.dds", 400.0f, 100.0f, MessageSkipSpritePriority);

	//���W��ݒ�
	m_windowSprite->SetPosition(WindowDefPos);
	m_windowOkuriSprite->SetPosition(WindowOkuriDefPos);
	m_messageSkipSprite->SetPosition({ 0.0f,0.0f,1.0f });
	m_messageFont->SetPosition(TextDefPos);
	m_messageSkipOshiraseFont->SetPosition({ TextSkipDefPos.x,TextSkipDefPos.y - 200.0f });
	m_logFont->SetPosition(LogFontPosition);

	//�e�L�X�g��ݒ�
	m_messageSkipOshiraseFont->SetText(SkipText);
	m_logFont->SetText(m_logText);

	//���O�E�B���h�E�ƃ��O�e�L�X�g
	m_logBlack->Init(L"Assets/sprite/Black.dds",FRAME_BUFFER_W,FRAME_BUFFER_H,LogWindowSpritePriority);
	m_logWindow->ChangeSliceSprite({ 300.0f,300.0f });
	m_logWindow->Init(L"Assets/sprite/window4.dds",
		LogWindowSize.x,
		LogWindowSize.y,
		LogWindowSpritePriority);

	//�F��ݒ�
	m_messageFont->SetColor(TextColor);
	m_messageSkipOshiraseFont->SetColor(TextColor);
	m_logFont->SetColor(TextColor);

	//���b�Z�[�W����̃V�F�C�N�ݒ�
	m_windowOkuriSprite->m_spriteSupporter.SpriteShake(
		{ 0.0f, MessageOkuriMove },
		MessageOkuriMoveTime, 
		0);

	//�e�L�X�g�ɉe�i�Ƃ������̃t�`�j��ݒ�
	m_messageFont->GetGameFont()->SetShadowParam(true, MessageFontOffset, { 1.0f,1.0f,1.0f,1.0f });

	//�X�P�[������
	m_messageFont->SetScale(0.6f);
	m_messageSkipOshiraseFont->SetScale(0.6f);
	m_logFont->SetScale(LogFontSize);

	//���O�e�L�X�g�̃s�{�b�g��ύX
	m_logFont->SetPivot({ 0.5f,5.0f });		//������

	//�X�v���C�g�ɖłт̔��􎾕��e�i�s�����x��0�ɂ��Ă��邾���ł��c�j
	m_windowSprite->SetAlpha(0.0f);
	m_windowOkuriSprite->SetAlpha(0.0f);
	m_messageSkipSprite->SetAlpha(0.0f);
	m_logBlack->SetAlpha(0.0f);
	m_logWindow->SetAlpha(0.0f);
	m_logFont->SetAlpha(0.0f);
}

void GameEffect_Message::MessageEffect(wchar_t* Message) {

	//���b�Z�[�W����
	m_messageFont->SetTextOkuri(Message, GameData::GetInstance()->GetMessageSpeed());

	//�F�X�Ə������K�v�ł�
	m_windowOkuriSprite->SetAlpha(0.0f);

if (m_windowSprite->GetAlpha() < 1.0f) {

		//����\������
		m_windowSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, 6, 0);
		m_windowSprite->SetPosition({ WindowDefPos.x,WindowDefPos.y - 30.0f,WindowDefPos.z });
		m_windowSprite->m_spriteSupporter.SpriteMove({ 0.0f, 30.0f }, 6, 0, true);

		m_messageSkipOshiraseFont->SetPosition({ TextSkipDefPos.x,TextSkipDefPos.y - 200.0f });
		m_messageSkipOshiraseFont->m_fontSupporter.FontMoveSet({ TextSkipDefPos.x,TextSkipDefPos.y }, 12, 0, false);

		//�ז��Ȃ̂ŃX�e�[�^�X�������Ă���
		GameUI* ui = Game::GetInstance()->GetUI();
		if (ui != nullptr && m_uiMoveFlag == false) {
			ui->CloseUI();
			m_uiMoveFlag = true;
		}
		else {
			m_uiMoveFlag = false;
		}

		//�C�x���g�t���O��true�ɂ���
		SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = true;

		//���O�֘A�̏�����
		for (int i = 0; i < 4096; i++) {
			m_logText[i] = L'\0';
		}
		m_logHigh = 0;
	}

	//�s�����v�Z
	int high = 0;
	wchar_t* MessageStock = Message;
	while (true) {	//���s���Ȃ��Ȃ�܂Ń��[�v

		MessageStock = wcsstr(MessageStock, L"\n");
		high++;

		if (MessageStock == NULL) {
			break;
		}
		MessageStock++;
	}
	m_logHigh += high + 2;

	//���O�ɒǉ�����
	const wchar_t* text = nullptr;
	std::wstring m_text = Message;
	text = m_text.c_str();
	wchar_t character[2];

	for (; *text; text++) {
		character[0] = *text;
		character[1] = L'\0';

		wcscat(m_logText, character);

	}
	character[0] = L'\n';
	character[1] = L'\0';
	wcscat(m_logText, character);
	wcscat(m_logText, character);

	//�t���O�Ƃ�
	m_nowMessage = true; 
	m_messageOkuriWait = false;
	m_messageTimer = 0;

}

void GameEffect_Message::MessageUpdate() {

	m_messageClickFlag = false;
	//�X�L�b�v�@�\
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_logFlag == false) {
		m_skipFlag = true;
	}
	else {
		//SPACE��������Ă��Ȃ��̂ŃX�v���C�g������
		m_messageSkipSprite->m_spriteSupporter.SpriteDelayReset();	//���Z�b�g���Ȃ��ƃX�v���C�g���c���Ă��܂�
		m_messageSkipSprite->SetAlpha(0.0f);
		m_skipFlag = false;
	}

	//���b�Z�[�W�\�����̏���
	if (m_nowMessage == true) {

		//���O�@�\
		int right_key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Right_Key);
		if (right_key == MouseSupporter::Release_Push) {	//�E�N���b�N���ꂽ�烍�O�t���O�ύX
			if (m_logFlag == false) {
				m_logFlag = true;
			}
			else {
				m_logFlag = false;
			}
			LogChange(m_logFlag);	//�\������
		}

		//�������烁�b�Z�[�W����
		int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		//�N���b�N�҂��I
		if ( (key == MouseSupporter::Release_Push || m_skipFlag == true) && m_logFlag == false) {
			//������܂���
			if (m_messageOkuriWait == true) {
				//�\���I��
				m_messageClickFlag = true;
				m_nowMessage = false;
				m_windowOkuriSprite->SetAlpha(0.0f);
				m_messageFont->SetText(L"");
				m_messageTimer = 0;
			}
			else {	//���b�Z�[�W�\���X�L�b�v
				m_messageFont->TextOkuriEnd();
			}
			//�X�L�b�v���łȂ��Ȃ猈��SE��炷
			if (m_skipFlag == false) {
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/OK.wav");
			}
		}

		//���b�Z�[�W����A�C�R���̕\��
		bool flag = m_messageFont->GetMessageOkuriFlag();
		if (flag == false) {
			m_windowOkuriSprite->SetAlpha(1.0f);
			m_messageOkuriWait = true;
		}

		//�X�L�b�v�X�v���C�g�̕\��
		if (m_skipFlag == true) {

			if (m_skipTimer == 0) {
				m_messageSkipSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, SkipLimit / 2, 0);
			}
			if (m_skipTimer == SkipLimit / 2) {
				m_messageSkipSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, SkipLimit / 2, 0);
			}

			m_skipTimer++;

			if (m_skipTimer == SkipLimit) {
				m_skipTimer = 0;
			}
		}

		//���O�̍X�V
		if (m_logFlag == true) {	//���O�̕\�����������s
			LogUpdate();
		}

	}
	else { //���b�Z�[�W�\�����ł͂Ȃ�

		//�t�L�_�V����
		m_messageTimer++;
		if (m_messageTimer == MessageDelateWait) {
			m_windowSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, 6, 0);
			m_windowSprite->m_spriteSupporter.SpriteMove({ 0.0f, 30.0f }, 6, 0, true);
			m_windowOkuriSprite->SetAlpha(0.0f);
			m_messageSkipSprite->m_spriteSupporter.SpriteDelayReset();	//���Z�b�g���Ȃ��ƃX�v���C�g���c���Ă��܂�
			m_messageSkipSprite->SetAlpha(0.0f);
			m_messageSkipOshiraseFont->m_fontSupporter.FontMoveSet({ TextSkipDefPos.x,TextSkipDefPos.y - 200.0f }, 12, 0, false);
			m_skipFlag = false;
			if (m_eventFlagAutoOff == false) {
				SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = false;
				//�������X�e�[�^�X��߂�
				GameUI* ui = Game::GetInstance()->GetUI();
				if (ui != nullptr && m_uiMoveFlag == true) {
					ui->OpenUI();
				}
			}
		}
	}
}

void GameEffect_Message::LogChange(const bool& Flag) {

	if (Flag == true) {
		//�\�����鎞�̏���
		m_logBlack->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.5f }, LogTime, 0);
		m_logWindow->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, LogTime, 0);
		//���O�e�L�X�g�̒���
		m_logFont->SetText(m_logText);
		m_logFont->SetPosition({ LogFontPosition.x,LogFontPosition.y + (m_logHigh * LogOffsetY) });
		m_logCursorPos = 0;	//������
		m_logFont->m_fontSupporter.FontColorSet({ TextColor.x,TextColor.y,TextColor.z,1.0f }, LogTime, 0);
	}
	else {
		//�폜����Ƃ��̏���
		m_logBlack->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, LogTime, 0);
		m_logWindow->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, LogTime, 0);
		m_logFont->m_fontSupporter.FontColorSet({ TextColor.x,TextColor.y,TextColor.z,0.0f }, LogTime, 0);
	}

}

void GameEffect_Message::LogUpdate() {

	//�z�C�[���ňړ�������
	int now_delta = MouseSupporter::GetInstance()->GetWheelMove();

	//�␳���I�I�I�I
	m_logCursorPos += -(now_delta / DeltaHoseiY);

	//�������
	if (m_logCursorPos < 0) {
		m_logCursorPos = 0;
	}

	//���W�ύX
	m_logFont->SetPosition({ LogFontPosition.x,
		LogFontPosition.y + (m_logHigh * LogOffsetY) - (m_logCursorPos * (LogOffsetY / DeltaHoseiY)) });

}

//��������GameEffect_AnimationSprite

void GameEffect_AnimationSprite::NewAnimationSprite(const Anime_Name m_animeName, 
	const CVector3& pos, const CVector3& m_scale, const int& priority){

	char RenderName[MAX_PATH];
	//�C���X�^���X�̖��O���쐬�B
	AnimationNom++;
	sprintf(RenderName, "SpriteAnime%d", AnimationNom);
	SpriteRender* sr = NewGO<SpriteRender>(RenderName, priority);
	sr->SetPosition(pos);
	sr->SetScale(m_scale);
	//�A�j���[�V���������������ōs���Ă����
	sr->Init(Game_SpriteAnime_Data[m_animeName].SpriteName,
		Game_SpriteAnime_Data[m_animeName].High, Game_SpriteAnime_Data[m_animeName].Wide, priority);
	sr->SetHighPattern(Game_SpriteAnime_Data[m_animeName].Pattern, 0);
	sr->m_spriteSupporter.SpritePattern(1, Game_SpriteAnime_Data[m_animeName].Loop, 6);

	SpriteRenderList srl;
	srl.SpriteRender_pt = sr;

	m_spriteRenderList.push_back(srl);
}

SpriteRender* GameEffect_AnimationSprite::NewAnimationSprite_pt(const Anime_Name m_animeName,
	const CVector3& pos, const CVector3& m_scale, const int& priority) {

	char RenderName[MAX_PATH];
	//�C���X�^���X�̖��O���쐬�B
	AnimationNom++;
	sprintf(RenderName, "SpriteAnime%d", AnimationNom);
	SpriteRender* sr = NewGO<SpriteRender>(RenderName, priority);
	sr->SetPosition(pos);
	sr->SetScale(m_scale);
	//�A�j���[�V���������������ōs���Ă����
	sr->Init(Game_SpriteAnime_Data[m_animeName].SpriteName,
		Game_SpriteAnime_Data[m_animeName].High, Game_SpriteAnime_Data[m_animeName].Wide, priority);
	sr->SetHighPattern(Game_SpriteAnime_Data[m_animeName].Pattern, 0);
	sr->m_spriteSupporter.SpritePattern(1, Game_SpriteAnime_Data[m_animeName].Loop, 6);

	SpriteRenderList srl;
	srl.SpriteRender_pt = sr;

	m_spriteRenderList.push_back(srl);

	return sr;
}

void GameEffect_AnimationSprite::SpriteAnimationUpdate() {

	//����ɍ폜����

	for (auto go = m_spriteRenderList.begin();
		go != m_spriteRenderList.end();
		go++) {

		//�A���t�@��0�Ȃ�폜�t���O���I��
		if (go->SpriteRender_pt->GetAlpha() == 0.0f) {
			go->DeleteFlag = true;
		}

	}

	//���ۂɍ폜
	std::list<SpriteRenderList>::iterator it;
	it = m_spriteRenderList.begin();
	while (it != m_spriteRenderList.end()) {
		if (it->DeleteFlag == true) {
			DeleteGO(it->SpriteRender_pt);
			it = m_spriteRenderList.erase(it); //erase�֐��͍폜���ꂽ�C�e���[�^�̎���Ԃ��Ă���̂ŁAerase�̖߂�l���g���B
		}
		else {
			it++; //����ȊO�͎��ցB
		}
	}

}

void GameEffect_AnimationSprite::DeleteAnimationSprite(SpriteRender* sr) {

	for (auto go = m_spriteRenderList.begin();
		go != m_spriteRenderList.end();
		go++) {

		//�A���t�@��0�Ȃ�폜�t���O���I��
		if (go->SpriteRender_pt == sr) {
			go->DeleteFlag = true;
		}

	}

}