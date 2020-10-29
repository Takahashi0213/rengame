#include "stdafx.h"
#include "FontRender.h"
#include <wchar.h>

FontRender::FontRender() {

	//優先度をスプライトに変更
	this->SetObjectTag(t_Sprite);
	//アドレスをサポーターに登録
	m_fontSupporter.SetFontRender(this);

}

FontRender::~FontRender() {

}

void FontRender::Update() {
	
	//サポーターの更新
	m_fontSupporter.FontSupporter_Update();

	//メッセージ送りフラグがtrueなら更新処理を行う
	if (m_okuriFlag == true) {

		m_textOkuri_Timer++;
		if (m_textOkuri_Interval <= m_textOkuri_Timer) {

			//レッツ更新！
			m_textOkuri_NowLen++;

			//移植
			wchar_t hoge[256] = L"";
			for (int n = 0; n < m_textOkuri_NowLen + 1; n++) {
				hoge[n] = m_text_stock[n];
			}
			m_text = hoge;

			//フォント内でSEを鳴らすのはあまり好ましくないと思う…
			if (m_textOkuriSE == true) {
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Speak.wav");
			}

			//後始末
			m_textOkuri_Timer = 0;
			if (m_textOkuri_NowLen >= m_textOkuri_Len) {
				m_okuriFlag = false;		//終了
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
	//文字列を分断
	const wchar_t* text = nullptr;
	m_messageList.clear();
	if (m_text.c_str() != nullptr) {
		text = m_text.c_str();
		MessageSt SetPackage;		//Vectorにぶっこむ枠				
		wcscpy(SetPackage.Message, L"");	//初期化！
		SetPackage.State = Normal;	//最初は普通色

		for (; *text; text++) {
			wchar_t character[2];
			character[0] = *text;
			character[1] = L'\0';

			switch (character[0])
			{
			case '\D':
				//デフォルト色
				m_messageList.push_back(SetPackage);

				wcscpy(SetPackage.Message, L"");	//クリアクリーン
				SetPackage.State = Normal;	//ここから通常色
				continue;
			case '\R':
				//赤色
				m_messageList.push_back(SetPackage);

				wcscpy(SetPackage.Message, L"");
				SetPackage.State = Red;		//ここから赤色
				continue;
			case '\G':
				//緑色
				m_messageList.push_back(SetPackage);

				wcscpy(SetPackage.Message, L"");
				SetPackage.State = Green;	//ここから緑色
				continue;
			case '\B':
				//青色
				m_messageList.push_back(SetPackage);

				wcscpy(SetPackage.Message, L"");
				SetPackage.State = Blue;	//ここから青色
				continue;
			default:
				//そのままイン	SetPackage.Message += character;
				wcscat(SetPackage.Message, character);
				break;
			}

		}

		//最終セット
		m_messageList.push_back(SetPackage);

	}

	//描画開始
	MessageSt GetPackage;		//取得したやつを入れる場所

	for (int i = 0; i < m_messageList.size(); i++) {

		//前から引っ張り出す
		GetPackage = m_messageList.front();
		m_messageList.pop_front();

		GameFont* gf = new GameFont;

		//色の変更
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

	//初期化と設定
	m_text = { L"" };

	m_textOkuri_Len = (int)wcslen(text);	//文字数を取得
	for (int n = 0; n < m_textOkuri_Len + 1; n++) {
		m_text_stock[n] = text[n];
	}

	m_textOkuri_Interval = Interval;
	m_textOkuri_Timer = 0;
	m_okuriFlag = true;
	m_textOkuri_NowLen = -1;
	m_textOkuriSE = TextOkuriSE_Flag;

}