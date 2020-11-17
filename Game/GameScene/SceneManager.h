#pragma once

#include "Title.h"
#include "Game.h"
#include "SaveLoad.h"

#include "system/CGameObjectManager.h"
#include "GameSystem/StageSet/StageSet.h"
#include "sound/SoundManager.h"
#include "ItemSave.h"
#include "Event/GameEvent.h"

/// <summary>
/// シーン切り替えをがんばるクラス
/// ・シングルトン
/// </summary>
class SceneManager final : public IGameObject
{
	static SceneManager* m_instance;
public:
	SceneManager();
	~SceneManager();
	void Update()override;
	void Render()override;

	enum NowScene {
		Title_Scene,	//タイトル
		Game_Sence,		//ゲーム
		Load_Sence,		//ロード
	};
	enum GameMode {	//ゲーム中です
		Null_Mode,	//ダミーモード（初期用）
		TitleMode,
		ActionMode,
		CreateMode,
		MenuMode,
		GameOver,
		LoadMode,
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
	GameEvent* GetGameEvent() {
		return m_gameEvent;
	}
	ItemSave* GetItemSave() {
		return m_itemSave;
	}

private:

	void TitleUpdate();
	void GameUpdate();
	void LoadUpdate();

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
	GameEvent* m_gameEvent = nullptr;					//ゲームイベント
	ItemSave* m_itemSave = nullptr;						//アイテムセーブ

	//シーン
	Title* m_title = nullptr;
	Game* m_game = nullptr;
	SaveLoad* m_saveLoad = nullptr;

};

