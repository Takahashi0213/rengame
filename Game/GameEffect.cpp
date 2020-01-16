#include "stdafx.h"
#include "GameEffect.h"

GameEffect* GameEffect::m_instance = nullptr;

GameEffect::GameEffect()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//ここから準備(/・ω・)/
	m_stand.StandInit();
	m_message.MessageInit();
}

GameEffect::~GameEffect()
{	
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

//ここから～～～GameEffect_Stand

void GameEffect_Stand::StandInit() {

	//設定
	m_standSprite = NewGO<SpriteRender>("StandSprite", StandSpritePriority);
	m_standSprite->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
}

void GameEffect_Stand::StandControl(Stand_Name stand, Stand_Command command) {

	//もし立ち絵がNullの場合現在の立ち絵を引っ張ってくる（変化なし）
	if (stand == Stand_Null) {
		stand = m_nowStand;
	}
	m_nowStand = stand;		//stand保存

	//コマンド内容で分岐
	switch (command)
	{
	case GameEffect_Stand::New_Stand:	//立ち絵の新規表示or更新

		m_standSprite->m_spriteSupporter.SpriteDelayReset();	//ディレイリセット

		m_standSprite->Init(Game_Stand_Data[stand].SpriteName,
			Game_Stand_Data[stand].High,
			Game_Stand_Data[stand].Wide,
			StandSpritePriority);
		m_standSprite->SetScale(StandDefScale);
		if (m_standFlag == false) {
			//新規立ち絵
			m_standSprite->SetPosition(StandDefPos_Move);
			m_standSprite->m_spriteSupporter.SpriteMove(StandDefPos, 6, 0);
			m_standSprite->m_spriteSupporter.SpriteMove(StandDefPos2, 4, 6);
			m_standSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, 6, 0);
			m_standFlag = true;
		}
		else {
			//既に立ち絵が表示されているので更新だけ
			m_standSprite->SetPosition({ StandDefPos2.x,StandDefPos2.y,0.0f });
		}
		break;
	case GameEffect_Stand::Delete_Stand:	//立ち絵をぶっこわあす
		if (m_standFlag == true) {
			m_standSprite->m_spriteSupporter.SpriteDelayReset();	//ディレイリセット
			m_standSprite->m_spriteSupporter.SpriteMove({ StandDefPos_Move.x * 2.0f ,StandDefPos_Move.y }, 12, 4);
			m_standSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, 6, 4);
			m_standFlag = false;
		}
		break;
	case GameEffect_Stand::Jump_Stand:	//じゃんぴん
		if (m_standFlag == true) {
			m_standSprite->m_spriteSupporter.SpriteDelayReset();	//ディレイリセット
			m_standSprite->SetPosition({ StandDefPos2.x,StandDefPos2.y,0.0f });
			m_standSprite->Init(Game_Stand_Data[stand].SpriteName,
				Game_Stand_Data[stand].High,
				Game_Stand_Data[stand].Wide,
				StandSpritePriority);
			//ジャンプ移動をディレイ込みで設定
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,JumpMove_A }, JumpWait_A, 0, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,-JumpMove_A }, JumpWait_A, JumpWait_A, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,JumpMove_B }, JumpWait_B, JumpWait_A*2, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,-JumpMove_B }, JumpWait_B, (JumpWait_A * 2)+ JumpWait_B, true);
		}
		break;
	case GameEffect_Stand::Shake_Stand:	//しぇいきん
		if (m_standFlag == true) {
			m_standSprite->m_spriteSupporter.SpriteDelayReset();	//ディレイリセット
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

//ここから～～～GameEffect_Message

void GameEffect_Message::MessageInit() {

	//レンダーを作成
	m_windowSprite = NewGO<SpriteRender>("WindowSprite", WindowSpritePriority);
	m_windowOkuriSprite = NewGO<SpriteRender>("WindowOkuriSprite", WindowOkuriSpritePriority);
	m_messageSkipSprite = NewGO<SpriteRender>("MessageSkipSprite", MessageSkipSpritePriority);
	m_messageFont = NewGO<FontRender>("MessageFont", MessageFontPriority);
	m_messageSkipOshiraseFont = NewGO<FontRender>("MessageSkipOshiraseFont", MessageSkipOshiraseFontPriority);

	//画像を設定
	m_windowSprite->Init(L"Assets/sprite/fukidasi.dds", 600.0f, 400.0f, WindowSpritePriority);
	m_windowOkuriSprite->Init(L"Assets/sprite/okuri.dds", 50.0f, 50.0f, WindowOkuriSpritePriority);
	m_messageSkipSprite->Init(L"Assets/sprite/skipNow.dds", 400.0f, 100.0f, MessageSkipSpritePriority);

	//座標を設定
	m_windowSprite->SetPosition(WindowDefPos);
	m_windowOkuriSprite->SetPosition(WindowOkuriDefPos);
	m_messageSkipSprite->SetPosition({ 0.0f,0.0f,1.0f });
	m_messageFont->SetPosition(TextDefPos);
	m_messageSkipOshiraseFont->SetPosition({ TextSkipDefPos.x,TextSkipDefPos.y - 200.0f });

	//テキストを設定
	m_messageSkipOshiraseFont->SetText(SkipText);

	//色を設定
	m_messageSkipSprite->SetAlpha(0.0f);
	m_messageFont->SetColor(TextColor);
	m_messageSkipOshiraseFont->SetColor(TextColor);

	//メッセージ送りのシェイク設定
	m_windowOkuriSprite->m_spriteSupporter.SpriteShake(
		{ 0.0f, MessageOkuriMove },
		MessageOkuriMoveTime, 
		0);

	//テキストに影（という名のフチ）を設定
	m_messageFont->GetGameFont()->SetShadowParam(true, 2.0f, { 1.0f,1.0f,1.0f,1.0f });

	//スプライトに滅びの爆裂疾風弾（不透明度を0にしているだけです…）
	m_windowSprite->SetAlpha(0.0f);
	m_windowOkuriSprite->SetAlpha(0.0f);

}

void GameEffect_Message::MessageEffect(wchar_t* Message) {

	//メッセージ送り
	m_messageFont->SetTextOkuri(Message, 2);

	//色々と準備が必要です

	m_windowOkuriSprite->SetAlpha(0.0f);

	if (m_windowSprite->GetAlpha() < 1.0f) {
		//初回表示処理
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
		//SPACEが押されていないのでスプライトを消去
		m_messageSkipSprite->m_spriteSupporter.SpriteDelayReset();	//リセットしないとスプライトが残ってしまう
		m_messageSkipSprite->SetAlpha(0.0f);	
		m_skipFlag = false;
	}

	//メッセージ表示中の処理
	if (m_nowMessage == true) {

		int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		//クリック待ち！
		if (key == MouseSupporter::Release_Push || m_skipFlag==true) {
			//押されました
			if (m_messageOkuriWait == true) {
				//表示終了
				m_messageClickFlag = true;
				m_nowMessage = false;
				m_windowOkuriSprite->SetAlpha(0.0f);
				m_messageFont->SetText(L"");
				m_messageTimer = 0;
			}
			else {	//メッセージ表示スキップ
				m_messageFont->TextOkuriEnd();
			}
		}

		//メッセージ送りアイコンの表示
		bool flag = m_messageFont->GetMessageOkuriFlag();
		if (flag == false) {
			m_windowOkuriSprite->SetAlpha(1.0f);
			m_messageOkuriWait = true;
		}

		//スキップスプライトの表示
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
	else { //メッセージ表示中ではない

		//フキダシ消去
		m_messageTimer++;
		if (m_messageTimer == MessageDelateWait) {
			m_windowSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, 6, 0);
			m_windowSprite->m_spriteSupporter.SpriteMove({ 0.0f, 30.0f }, 6, 0, true);
			m_windowOkuriSprite->SetAlpha(0.0f);
			m_messageSkipSprite->m_spriteSupporter.SpriteDelayReset();	//リセットしないとスプライトが残ってしまう
			m_messageSkipSprite->SetAlpha(0.0f);
			m_messageSkipOshiraseFont->m_fontSupporter.FontMoveSet({ TextSkipDefPos.x,TextSkipDefPos.y - 200.0f }, 12, 0, false);
			m_skipFlag = false;
		}
	}
}