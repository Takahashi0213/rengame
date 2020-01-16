#include "stdafx.h"
#include "GameEffect.h"

GameEffect* GameEffect::m_instance = nullptr;

GameEffect::GameEffect()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�������珀��(/�E�ցE)/
	m_stand.StandInit();
	m_message.MessageInit();
}

GameEffect::~GameEffect()
{	
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

//��������`�`�`GameEffect_Stand

void GameEffect_Stand::StandInit() {

	//�ݒ�
	m_standSprite = NewGO<SpriteRender>("StandSprite", StandSpritePriority);
	m_standSprite->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
}

void GameEffect_Stand::StandControl(Stand_Name stand, Stand_Command command) {

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

//��������`�`�`GameEffect_Message

void GameEffect_Message::MessageInit() {

	//�����_�[���쐬
	m_windowSprite = NewGO<SpriteRender>("WindowSprite", WindowSpritePriority);
	m_windowOkuriSprite = NewGO<SpriteRender>("WindowOkuriSprite", WindowOkuriSpritePriority);
	m_messageSkipSprite = NewGO<SpriteRender>("MessageSkipSprite", MessageSkipSpritePriority);
	m_messageFont = NewGO<FontRender>("MessageFont", MessageFontPriority);
	m_messageSkipOshiraseFont = NewGO<FontRender>("MessageSkipOshiraseFont", MessageSkipOshiraseFontPriority);

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

	//�e�L�X�g��ݒ�
	m_messageSkipOshiraseFont->SetText(SkipText);

	//�F��ݒ�
	m_messageSkipSprite->SetAlpha(0.0f);
	m_messageFont->SetColor(TextColor);
	m_messageSkipOshiraseFont->SetColor(TextColor);

	//���b�Z�[�W����̃V�F�C�N�ݒ�
	m_windowOkuriSprite->m_spriteSupporter.SpriteShake(
		{ 0.0f, MessageOkuriMove },
		MessageOkuriMoveTime, 
		0);

	//�e�L�X�g�ɉe�i�Ƃ������̃t�`�j��ݒ�
	m_messageFont->GetGameFont()->SetShadowParam(true, 2.0f, { 1.0f,1.0f,1.0f,1.0f });

	//�X�v���C�g�ɖłт̔��􎾕��e�i�s�����x��0�ɂ��Ă��邾���ł��c�j
	m_windowSprite->SetAlpha(0.0f);
	m_windowOkuriSprite->SetAlpha(0.0f);

}

void GameEffect_Message::MessageEffect(wchar_t* Message) {

	//���b�Z�[�W����
	m_messageFont->SetTextOkuri(Message, 2);

	//�F�X�Ə������K�v�ł�

	m_windowOkuriSprite->SetAlpha(0.0f);

	if (m_windowSprite->GetAlpha() < 1.0f) {
		//����\������
		m_windowSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, 6, 0);
		m_windowSprite->SetPosition({ WindowDefPos.x,WindowDefPos.y - 30.0f,WindowDefPos.z });
		m_windowSprite->m_spriteSupporter.SpriteMove({ 0.0f, 30.0f }, 6, 0, true);

		m_messageSkipOshiraseFont->SetPosition({ TextSkipDefPos.x,TextSkipDefPos.y - 200.0f });
		m_messageSkipOshiraseFont->m_fontSupporter.FontMoveSet({ TextSkipDefPos.x,TextSkipDefPos.y }, 12, 0, false);

	}

	m_nowMessage = true;
	m_messageOkuriWait = false;
	m_messageTimer = 0;

}

void GameEffect_Message::MessageUpdate() {

	m_messageClickFlag = false;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
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

		int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		//�N���b�N�҂��I
		if (key == MouseSupporter::Release_Push || m_skipFlag==true) {
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
				m_messageSkipSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, SkipLimit / 2 , 0);
			}
			if (m_skipTimer == SkipLimit / 2) {
				m_messageSkipSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, SkipLimit / 2, 0);
			}

			m_skipTimer++;

			if (m_skipTimer == SkipLimit) {
				m_skipTimer = 0;
			}
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
		}
	}
}