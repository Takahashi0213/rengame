#include "stdafx.h"
#include "FontRender.h"
#include <wchar.h>

FontRender::FontRender() {

	//�D��x���X�v���C�g�ɕύX
	this->SetObjectTag(t_Sprite);
	//�A�h���X���T�|�[�^�[�ɓo�^
	m_fontSupporter.SetFontRender(this);

}

FontRender::~FontRender() {

}

void FontRender::Update() {
	
	//�T�|�[�^�[�̍X�V
	m_fontSupporter.FontSupporter_Update();

	//���b�Z�[�W����t���O��true�Ȃ�X�V�������s��
	if (m_okuriFlag == true) {

		m_textOkuri_Timer++;
		if (m_textOkuri_Interval <= m_textOkuri_Timer) {

			//���b�c�X�V�I
			m_textOkuri_NowLen++;

			//�ڐA
			wchar_t hoge[256] = L"";
			for (int n = 0; n < m_textOkuri_NowLen + 1; n++) {
				hoge[n] = m_text_stock[n];
			}
			m_text = hoge;

			//�t�H���g����SE��炷�̂͂��܂�D�܂����Ȃ��Ǝv���c
			if (m_textOkuriSE == true) {
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Speak.wav");
			}

			//��n��
			m_textOkuri_Timer = 0;
			if (m_textOkuri_NowLen >= m_textOkuri_Len) {
				m_okuriFlag = false;		//�I��
			}

		}

	}

}

void FontRender::Render() {
	PostRender();
}

void FontRender::PostRender()
{
	/*
	//������𕪒f
	const wchar_t* text = nullptr;
	m_messageList.clear();
	if (m_text.c_str() != nullptr) {
		text = m_text.c_str();
		MessageSt SetPackage;		//Vector�ɂԂ����ޘg				
		wcscpy(SetPackage.Message, L"");	//�������I
		SetPackage.State = Normal;	//�ŏ��͕��ʐF

		for (; *text; text++) {
			wchar_t character[2];
			character[0] = *text;
			character[1] = L'\0';

			switch (character[0])
			{
			case '\D':
				//�f�t�H���g�F
				m_messageList.push_back(SetPackage);

				wcscpy(SetPackage.Message, L"");	//�N���A�N���[��
				SetPackage.State = Normal;	//��������ʏ�F
				continue;
			case '\R':
				//�ԐF
				m_messageList.push_back(SetPackage);

				wcscpy(SetPackage.Message, L"");
				SetPackage.State = Red;		//��������ԐF
				continue;
			case '\G':
				//�ΐF
				m_messageList.push_back(SetPackage);

				wcscpy(SetPackage.Message, L"");
				SetPackage.State = Green;	//��������ΐF
				continue;
			case '\B':
				//�F
				m_messageList.push_back(SetPackage);

				wcscpy(SetPackage.Message, L"");
				SetPackage.State = Blue;	//��������F
				continue;
			default:
				//���̂܂܃C��	SetPackage.Message += character;
				wcscat(SetPackage.Message, character);
				break;
			}

		}

		//�ŏI�Z�b�g
		m_messageList.push_back(SetPackage);

	}

	//�`��J�n
	MessageSt GetPackage;		//�擾�����������ꏊ

	for (int i = 0; i < m_messageList.size(); i++) {

		//�O�����������o��
		GetPackage = m_messageList.front();
		m_messageList.pop_front();

		GameFont* gf = new GameFont;

		//�F�̕ύX
		CVector4 color;
		switch (GetPackage.State)
		{
		case Normal:
			color = m_color;
			continue;
		case Red:
			color = RED_STATUS;
			continue;
		case Blue:
			color = BLUE_STATUS;
			continue;
		case Green:
			color = GREEN_STATUS;
			continue;
		}

		gf->Begin();

		gf->Draw(
			GetPackage.Message,
			m_position,
			color,
			m_rotation,
			m_scale,
			m_pivot);

		gf->End();

	}

	*/

	m_font.Begin();

	const wchar_t* text = nullptr;
	if (m_text.c_str() != nullptr) {
		text = m_text.c_str();
	}

	m_font.Draw(
		text,
		m_position,
		m_color,
		m_rotation,
		m_scale,
		m_pivot);

	m_font.End();


}

void FontRender::SetTextOkuri(const wchar_t* text, const int& Interval, const bool& TextOkuriSE_Flag) {

	//�������Ɛݒ�
	m_text = { L"" };

	m_textOkuri_Len = (int)wcslen(text);	//���������擾
	for (int n = 0; n < m_textOkuri_Len + 1; n++) {
		m_text_stock[n] = text[n];
	}

	m_textOkuri_Interval = Interval;
	m_textOkuri_Timer = 0;
	m_okuriFlag = true;
	m_textOkuri_NowLen = -1;
	m_textOkuriSE = TextOkuriSE_Flag;

}