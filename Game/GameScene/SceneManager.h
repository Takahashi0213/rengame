#pragma once

#include "Title.h"
#include "Game.h"
#include "system/CGameObjectManager.h"
#include "StageSet.h"
#include "sound/SoundManager.h"

/// <summary>
/// シーン切り替えをがんばるクラス
/// ・シングルトン
/// </summary>
class SceneManager : public IGameObject
{
	static SceneManager* m_instance;
public:
	SceneManager();
	~SceneManager();
	void Update()override;
	void Render()override;

	enum NowScene {
		Title_Scene,
		Game_Sence
	};
	enum GameMode {	//ゲーム中です
		Null_Mode,	//ダミーモード（初期用）
		TitleMode,
		ActionMode,
		CreateMode,
		MenuMode,
		GameOver,
	};

	/// <summary>
	/// 現在シーンの取得
	/// 今がタイトルかゲーム中かを確認できる
	/// </summary>
	NowScene GetNowScene() {
		return m_nowScene;
	}

	/// <summary>
	/// ゲームモードをセット
	/// </summary>
	/// <param name="mode">モード</param>
	void SetGameMode(const GameMode mode) {
		m_gameMode = mode;
	}
	/// <summary>
	/// ゲームモードを取得
	/// </summary>
	/// <returns>モード</returns>
	GameMode GetGameMode() {
		return m_gameMode;
	}

	//タイトル終了時に呼ぶ
	void EndTitle() {
		m_title = nullptr;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static SceneManager* GetInstance() {
		return m_instance;
	}
	SystemData* GetSystemInstance() {
		return &m_systemData;
	}
	GameGraphic* GetGameGraphicInstance() {
		return &m_gameGraphic;
	}
	SoundManager* GetSoundManagerInstance() {
		return &m_soundManager;
	}

private:

	void TitleUpdate();
	void GameUpdate();

	void TitleCommand(const Title::TitleCommand command);

	//状況
	NowScene m_nowScene = Title_Scene;		//こっちはSceneManager専用
	GameMode m_gameMode = Null_Mode;		//こっちは外部から変更可能

	//全体で使うもの
	SystemData m_systemData;
	GameGraphic m_gameGraphic;
	CSoundEngine m_soundEngine;				//サウンドエンジン。
	StageSet m_stageSet;
	SoundManager m_soundManager;

	//シーン
	Title* m_title = nullptr;
	Game* m_game = nullptr;

};

