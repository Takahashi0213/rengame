#include "stdafx.h"
#include "SceneManager.h"
#include "system/system.h"

#include "GameCamera.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//サウンドエンジンを初期化。
	m_soundEngine.Init();

	//トランジション
	TransitionGenerator* tg = CGameObjectManager::GetInstance()->NewGO<TransitionGenerator>("TransitionGenerator", 10);
	tg->SetObjectTag(objectTag::t_Sprite);		//とにかく最後に実行されるようにする

	//最初はタイトル！
	m_title = CGameObjectManager::GetInstance()->NewGO<Title>("Game_Title");
	//タイトルがいらない時用
	//{
	//	m_game = CGameObjectManager::GetInstance()->NewGO<Game>("Main_Game");
	//	m_nowScene = Game_Sence;
	//}
}


SceneManager::~SceneManager()
{	
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void SceneManager::Update() {

	//現在のシーンによって違う処理
	switch (m_nowScene)
	{
	case SceneManager::Title_Scene:
		//チェックアンドキリカエ	
		TitleUpdate();
		break;
	case SceneManager::Game_Sence:
		//ゲームなう
		GameUpdate();
		break;
	}

}

void SceneManager::Render() {

}

void SceneManager::TitleUpdate() {

	const Title::TitleCommand& m_command = m_title->GetCommand();
	if (m_command != Title::TitleCommand::No_Select) {
		TitleCommand(m_command);	//シーン切り替え
	}

}

void SceneManager::GameUpdate() {

}

void SceneManager::TitleCommand(const Title::TitleCommand command) {
	switch (command)
	{
	case Title::No_Select:
		//まあここに入ることはないんだけどね
		std::abort(); //一応止めとく！
		break;
	case Title::Game_Start:
		//ニューゲーム
		CGameObjectManager::GetInstance()->DeleteGO(m_title);
		m_title = nullptr;
		m_nowScene = Game_Sence;
		m_game = CGameObjectManager::GetInstance()->NewGO<Game>("Main_Game");
		break;
	case Title::Game_Continue:
		//ロード画面へ

		break;
	case Title::Game_End:
		//おしまいん
		DestroyWindow(g_hWnd);
		break;
	}
}