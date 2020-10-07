#pragma once

#include "Title.h"
#include "Game.h"
#include "system/CGameObjectManager.h"

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

	//タイトル終了時に呼ぶ
	void EndTitle() {
		m_title = nullptr;
	}

private:

	void TitleUpdate();
	void GameUpdate();

	void TitleCommand(const Title::TitleCommand command);

	NowScene m_nowScene = Title_Scene;
	//シーン
	Title* m_title = nullptr;
	Game* m_game = nullptr;

};

