#include "stdafx.h"
#include "TransitionGenerator.h"

TransitionGenerator* TransitionGenerator::m_instance = nullptr;

TransitionGenerator::TransitionGenerator()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}
	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


TransitionGenerator::~TransitionGenerator()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void TransitionGenerator::Update() {

	if (m_nowTransitionFlag == true) {
		if (m_borderLine < 0.0f) {
			m_nowTransitionFlag = false;
		}
		if (m_borderLine > MoveSpeed) {
			m_nowTransitionFlag = false;
		}

		if (m_transitionMode == false) {
			m_borderLine += (1.0f / m_transitionLimit)*MoveSpeed;
		}
		else {
			m_borderLine -= (1.0f / m_transitionLimit)*MoveSpeed;
		}
		m_transitionSprite.m_alpha = m_borderLine;
	}

	m_transitionSprite.Sprite_Update();

	if (m_loadingSprite != nullptr) {
		m_loadingSprite->Update();
	}

}
void TransitionGenerator::Render() {

	m_transitionSprite.Sprite_Draw();
	if (m_loadingSprite != nullptr) {
		m_loadingSprite->Render();
	}
}

void TransitionGenerator::TransitionInit(
	const TransitionName& name, 
	const int& MoveTime,
	const bool& mode,
	const bool& loadingFlag
) {

	//せってぃんぐ
	m_nowTransitionFlag = true;
	m_transitionLimit = MoveTime;
	m_transitionMode = mode;
	if (mode == false) {
		m_borderLine = 0.0f;
	}
	else {
		m_borderLine = MoveSpeed / 2.0f;
	}
	//ぶちこみます
	m_transitionSprite.Sprite_Init(Transition_DataList[name].SpriteName, FRAME_BUFFER_W, FRAME_BUFFER_H);

	//ローディングアニメーション
	if (loadingFlag == true && m_loadingSprite == nullptr && mode == false) {
		//表示
		m_loadingSprite = new SpriteRender;
		m_loadingSprite->SetPosition(SceneManager::GetInstance()->GetGameGraphicInstance()->LoadingAnimePos);
		m_loadingSprite->Init(L"Assets/sprite/Loading_6F.dds",
			130.0f, 480.0f, 10);
		m_loadingSprite->SetHighPattern(6, 0);
		m_loadingSprite->m_spriteSupporter.SpritePattern(1, true, 0);
		SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = true;	//イベント開始
	}
	if (loadingFlag == true && m_loadingSprite != nullptr && mode == true) {
		//削除
		delete m_loadingSprite;
		m_loadingSprite = nullptr;
		SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = false;	//イベント終了
	}

}