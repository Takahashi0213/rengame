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
	//カメラサポーターの生成
	CGameObjectManager::GetInstance()->NewGO<CameraSupporter>("CameraSupporter");
	//ライトメーカーの生成
	CGameObjectManager::GetInstance()->NewGO<LightMaker>("LightMaker");

	//最初はタイトル！
	m_title = CGameObjectManager::GetInstance()->NewGO<Title>("Game_Title");
	//タイトルがいらない時用（↑のタイトル生成はコメントアウトしてください）
	//{
	//	m_game = CGameObjectManager::GetInstance()->NewGO<Game>("Main_Game");
	//	m_nowScene = Game_Sence;
	//  GameData::GetInstance()->SetBoxMakerFlag(true);

	//	//音楽がいらない時用
	//	GameData::GetInstance()->Set_BGMVolume(0.0f);
	//	//効果音がいらない時用
	//	GameData::GetInstance()->Set_SEVolume(0.0f);

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
	case SceneManager::Load_Sence:
		//ロード画面
		LoadUpdate();
		break;
	}

	//共通アップデート
	m_soundManager.SoundManagerUpdate();
	m_soundEngine.Update();

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

void SceneManager::LoadUpdate() {

	if (m_saveLoad->GetEndFlag() == true) {
		const SaveLoad::SaveLoadEnd& m_command = m_saveLoad->Get_SaveLoadEnd();
		if (m_command == SaveLoad::SaveLoadEnd::LoadSuccess) {
			//ロード成功
			CGameObjectManager::GetInstance()->DeleteGO(m_saveLoad);
			m_saveLoad = nullptr;
			m_nowScene = Game_Sence;
			m_game = CGameObjectManager::GetInstance()->NewGO<Game>("Main_Game");
		}
		if (m_command == SaveLoad::SaveLoadEnd::NoLoad) {
			//タイトルに戻る
			CGameObjectManager::GetInstance()->DeleteGO(m_saveLoad);
			m_saveLoad = nullptr;
			m_nowScene = Title_Scene;
			m_title = CGameObjectManager::GetInstance()->NewGO<Title>("Game_Title");
			TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox,
				0, true);
		}
	}
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
		CGameObjectManager::GetInstance()->DeleteGO(m_title);
		m_title = nullptr;
		m_nowScene = Load_Sence;
		m_saveLoad = CGameObjectManager::GetInstance()->NewGO<SaveLoad>("SaveLoad");
		break;
	case Title::Game_End:
		//おしまいん
		DestroyWindow(g_hWnd);
		break;
	}
}