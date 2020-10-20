#pragma once
#include "SystemData.h"
#include "GameGraphic.h"
#include "GameUI.h"
#include "GameStatusUI.h"
#include "system/CGameObjectManager.h"
#include "OP.h"

/// <summary>
/// �Q�[���I
/// �E�V���O���g��
/// </summary>
class Game : public IGameObject
{
	static Game* m_instance;
public:

	Game();
	~Game();
	void Update()override;
	void Render()override;

	enum GameState {	//OP����Q�[���J�n�܂�
		GameState_OP,		//�I�[�v�j���O
		GamaState_Game,		//�Q�[���J�n�I
	};

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static Game* Game::GetInstance() {
		return m_instance;
	}
	GameUI* Game::GetUI() {
		return m_ui;
	}

private:

	//OP���I����ăQ�[�����n�܂�Ƃ��̂�[��
	void GameSetUp();

	GameState m_gameState = GameState_OP;		//�ŏ���OP�������܂�

	//��������Q�[���p

	GameData m_gameData;		//�ۑ�����f�[�^�F�X
	GameEffect m_gameEffect;	//�����ŃA�b�v�f�[�g����
	GameUI* m_ui = nullptr;
	GameStatus_UISystem* m_statusUI;
	OP* m_op = nullptr;			//OP���I�������폜�����

};

