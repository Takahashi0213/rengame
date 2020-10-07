#pragma once

#include "Title.h"
#include "Game.h"
#include "system/CGameObjectManager.h"

/// <summary>
/// �V�[���؂�ւ�������΂�N���X
/// �E�V���O���g��
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

	//�^�C�g���I�����ɌĂ�
	void EndTitle() {
		m_title = nullptr;
	}

private:

	void TitleUpdate();
	void GameUpdate();

	void TitleCommand(const Title::TitleCommand command);

	NowScene m_nowScene = Title_Scene;
	//�V�[��
	Title* m_title = nullptr;
	Game* m_game = nullptr;

};

