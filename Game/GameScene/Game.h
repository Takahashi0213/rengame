#pragma once
#include "SystemData.h"
#include "GameGraphic.h"
#include "GameSystem/GameUI/GameUI.h"
#include "GameSystem/GameUI/GameStatusUI.h"
#include "system/CGameObjectManager.h"
#include "Event/GameEvent.h"
#include "OP.h"
#include "GameScene/GameOver.h"
#include "DamageSystem.h"
#include "GameSystem/PlayerSupporter/TutorialSupporter.h"
#include "GameSystem/PlayerSupporter/UI_Supporter.h"

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
		GamaState_GameOver,	//�Q�[���I�[�o�[
	};

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static Game* GetInstance() {
		return m_instance;
	}
	GameUI* GetUI() {
		return m_ui;
	}
	GameEvent* GetGameEvent() {
		return m_gameEvent;
	}
	DamageSystem* GetDamageSystem() {
		return m_damageSystem;
	}

private:

	//OP���I����ăQ�[�����n�܂�Ƃ��̂�[��
	void GameSetUp();

	GameState m_gameState = GameState_OP;		//�ŏ���OP�������܂�

	//��������Q�[���p

	GameData* m_gameData = nullptr;				//�ۑ�����f�[�^�F�X
	GameEffect* m_gameEffect = nullptr;			//�����ŃA�b�v�f�[�g����
	GameUI* m_ui = nullptr;						//UI
	GameStatus_UISystem* m_statusUI = nullptr;	//UI
	GameEvent* m_gameEvent = nullptr;			//�Q�[���C�x���g
	DamageSystem* m_damageSystem = nullptr;		//�_���[�W�̕t�^��Q�[���I�[�o�[�̊Ǘ�
	OP* m_op = nullptr;							//OP���I�������폜�����
	GameOver* m_gameOver = nullptr;				//�Q�[���I�[�o�[�ɂȂ����琶�������
	TutorialSupporter* m_tutorialSupporter = nullptr;	//�`���[�g���A���̉�������
	UI_Supporter* m_ui_Supporter = nullptr;		//������@��\������

};

