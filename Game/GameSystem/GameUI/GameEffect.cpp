#include "stdafx.h"
#include "GameEffect.h"
#include "GameScene/Game.h"

GameEffect* GameEffect::m_instance = nullptr;

GameEffect::GameEffect()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//ここから準備
	m_stand.StandInit();
	m_message.MessageInit();
}

GameEffect::~GameEffect()
{	
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

//ここからGameEffect_Stand

void GameEffect_Stand::StandInit() {

	//設定
	m_standSprite = NewGO<SpriteRender>("StandSprite", StandSpritePriority);
	m_standSprite->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
}

void GameEffect_Stand::StandControl(Stand_Name stand, const Stand_Command command) {

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

//ここからGameEffect_Message

void GameEffect_Message::MessageInit() {

	//レンダーを作成
	m_windowSprite = NewGO<SpriteRender>("WindowSprite", WindowSpritePriority);
	m_windowOkuriSprite = NewGO<SpriteRender>("WindowOkuriSprite", WindowOkuriSpritePriority);
	m_messageSkipSprite = NewGO<SpriteRender>("MessageSkipSprite", MessageSkipSpritePriority);
	m_messageFont = NewGO<FontRender>("MessageFont", MessageFontPriority);
	m_messageSkipOshiraseFont = NewGO<FontRender>("MessageSkipOshiraseFont", MessageSkipOshiraseFontPriority);
	m_logBlack = NewGO<SpriteRender>("LogBlack", LogWindowSpritePriority);
	m_logWindow = NewGO<SpriteRender>("LogWindow", LogWindowSpritePriority);
	m_logFont = NewGO<FontRender>("LogFont", LogFontPriority);

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
	m_logFont->SetPosition(LogFontPosition);

	//テキストを設定
	m_messageSkipOshiraseFont->SetText(SkipText);
	m_logFont->SetText(m_logText);

	//ログウィンドウとログテキスト
	m_logBlack->Init(L"Assets/sprite/Black.dds",FRAME_BUFFER_W,FRAME_BUFFER_H,LogWindowSpritePriority);
	m_logWindow->ChangeSliceSprite({ 300.0f,300.0f });
	m_logWindow->Init(L"Assets/sprite/window4.dds",
		LogWindowSize.x,
		LogWindowSize.y,
		LogWindowSpritePriority);

	//色を設定
	m_messageFont->SetColor(TextColor);
	m_messageSkipOshiraseFont->SetColor(TextColor);
	m_logFont->SetColor(TextColor);

	//メッセージ送りのシェイク設定
	m_windowOkuriSprite->m_spriteSupporter.SpriteShake(
		{ 0.0f, MessageOkuriMove },
		MessageOkuriMoveTime, 
		0);

	//テキストに影（という名のフチ）を設定
	m_messageFont->GetGameFont()->SetShadowParam(true, MessageFontOffset, { 1.0f,1.0f,1.0f,1.0f });

	//スケール調整
	m_messageFont->SetScale(0.6f);
	m_messageSkipOshiraseFont->SetScale(0.6f);
	m_logFont->SetScale(LogFontSize);

	//ログテキストのピボットを変更
	m_logFont->SetPivot({ 0.5f,5.0f });		//中央下

	//スプライトに滅びの爆裂疾風弾（不透明度を0にしているだけです…）
	m_windowSprite->SetAlpha(0.0f);
	m_windowOkuriSprite->SetAlpha(0.0f);
	m_messageSkipSprite->SetAlpha(0.0f);
	m_logBlack->SetAlpha(0.0f);
	m_logWindow->SetAlpha(0.0f);
	m_logFont->SetAlpha(0.0f);
}

void GameEffect_Message::MessageEffect(wchar_t* Message) {

	//メッセージ送り
	m_messageFont->SetTextOkuri(Message, GameData::GetInstance()->GetMessageSpeed());

	//色々と準備が必要です
	m_windowOkuriSprite->SetAlpha(0.0f);

if (m_windowSprite->GetAlpha() < 1.0f) {

		//初回表示処理
		m_windowSprite->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, 6, 0);
		m_windowSprite->SetPosition({ WindowDefPos.x,WindowDefPos.y - 30.0f,WindowDefPos.z });
		m_windowSprite->m_spriteSupporter.SpriteMove({ 0.0f, 30.0f }, 6, 0, true);

		m_messageSkipOshiraseFont->SetPosition({ TextSkipDefPos.x,TextSkipDefPos.y - 200.0f });
		m_messageSkipOshiraseFont->m_fontSupporter.FontMoveSet({ TextSkipDefPos.x,TextSkipDefPos.y }, 12, 0, false);

		//邪魔なのでステータスを消しておく
		GameUI* ui = Game::GetInstance()->GetUI();
		if (ui != nullptr && m_uiMoveFlag == false) {
			ui->CloseUI();
			m_uiMoveFlag = true;
		}
		else {
			m_uiMoveFlag = false;
		}

		//イベントフラグをtrueにする
		SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = true;

		//ログ関連の初期化
		for (int i = 0; i < 4096; i++) {
			m_logText[i] = L'\0';
		}
		m_logHigh = 0;
	}

	//行数を計算
	int high = 0;
	wchar_t* MessageStock = Message;
	while (true) {	//改行がなくなるまでループ

		MessageStock = wcsstr(MessageStock, L"\n");
		high++;

		if (MessageStock == NULL) {
			break;
		}
		MessageStock++;
	}
	m_logHigh += high + 2;

	//ログに追加する
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

	//フラグとか
	m_nowMessage = true; 
	m_messageOkuriWait = false;
	m_messageTimer = 0;

}

void GameEffect_Message::MessageUpdate() {

	m_messageClickFlag = false;
	//スキップ機能
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_logFlag == false) {
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

		//ログ機能
		int right_key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Right_Key);
		if (right_key == MouseSupporter::Release_Push) {	//右クリックされたらログフラグ変更
			if (m_logFlag == false) {
				m_logFlag = true;
			}
			else {
				m_logFlag = false;
			}
			LogChange(m_logFlag);	//表示処理
		}

		//ここからメッセージ送り
		int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		//クリック待ち！
		if ( (key == MouseSupporter::Release_Push || m_skipFlag == true) && m_logFlag == false) {
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
			//スキップ中でないなら決定SEを鳴らす
			if (m_skipFlag == false) {
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/OK.wav");
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

		//ログの更新
		if (m_logFlag == true) {	//ログの表示中だけ実行
			LogUpdate();
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
			if (m_eventFlagAutoOff == false) {
				SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = false;
				//消したステータスを戻す
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
		//表示する時の処理
		m_logBlack->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.5f }, LogTime, 0);
		m_logWindow->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, LogTime, 0);
		//ログテキストの調整
		m_logFont->SetText(m_logText);
		m_logFont->SetPosition({ LogFontPosition.x,LogFontPosition.y + (m_logHigh * LogOffsetY) });
		m_logCursorPos = 0;	//初期化
		m_logFont->m_fontSupporter.FontColorSet({ TextColor.x,TextColor.y,TextColor.z,1.0f }, LogTime, 0);
	}
	else {
		//削除するときの処理
		m_logBlack->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, LogTime, 0);
		m_logWindow->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, LogTime, 0);
		m_logFont->m_fontSupporter.FontColorSet({ TextColor.x,TextColor.y,TextColor.z,0.0f }, LogTime, 0);
	}

}

void GameEffect_Message::LogUpdate() {

	//ホイールで移動させる
	int now_delta = MouseSupporter::GetInstance()->GetWheelMove();

	//補正っ！！！！
	m_logCursorPos += -(now_delta / DeltaHoseiY);

	//上限下限
	if (m_logCursorPos < 0) {
		m_logCursorPos = 0;
	}

	//座標変更
	m_logFont->SetPosition({ LogFontPosition.x,
		LogFontPosition.y + (m_logHigh * LogOffsetY) - (m_logCursorPos * (LogOffsetY / DeltaHoseiY)) });

}

//ここからGameEffect_AnimationSprite

void GameEffect_AnimationSprite::NewAnimationSprite(const Anime_Name m_animeName, 
	const CVector3& pos, const CVector3& m_scale, const int& priority){

	char RenderName[MAX_PATH];
	//インスタンスの名前を作成。
	AnimationNom++;
	sprintf(RenderName, "SpriteAnime%d", AnimationNom);
	SpriteRender* sr = NewGO<SpriteRender>(RenderName, priority);
	sr->SetPosition(pos);
	sr->SetScale(m_scale);
	//アニメーション処理を自動で行ってくれる
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
	//インスタンスの名前を作成。
	AnimationNom++;
	sprintf(RenderName, "SpriteAnime%d", AnimationNom);
	SpriteRender* sr = NewGO<SpriteRender>(RenderName, priority);
	sr->SetPosition(pos);
	sr->SetScale(m_scale);
	//アニメーション処理を自動で行ってくれる
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

	//勝手に削除処理

	for (auto go = m_spriteRenderList.begin();
		go != m_spriteRenderList.end();
		go++) {

		//アルファが0なら削除フラグをオン
		if (go->SpriteRender_pt->GetAlpha() == 0.0f) {
			go->DeleteFlag = true;
		}

	}

	//実際に削除
	std::list<SpriteRenderList>::iterator it;
	it = m_spriteRenderList.begin();
	while (it != m_spriteRenderList.end()) {
		if (it->DeleteFlag == true) {
			DeleteGO(it->SpriteRender_pt);
			it = m_spriteRenderList.erase(it); //erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++; //それ以外は次へ。
		}
	}

}

void GameEffect_AnimationSprite::DeleteAnimationSprite(SpriteRender* sr) {

	for (auto go = m_spriteRenderList.begin();
		go != m_spriteRenderList.end();
		go++) {

		//アルファが0なら削除フラグをオン
		if (go->SpriteRender_pt == sr) {
			go->DeleteFlag = true;
		}

	}

}