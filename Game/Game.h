#pragma once
#include "SystemData.h"
#include "GameGraphic.h"
#include "GameUI.h"
#include "PhysicsGhostObject.h"
#include "system/CGameObjectManager.h"

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

	//��������Q�[���p

	GameData m_gameData;
	GameEffect m_gameEffect;

	GameUI* m_ui = nullptr;

	CharacterController* m_charaCon;
	PhysicsGhostObject m_ghostObject;						//�S�[�X�g�I�u�W�F�N�g�Ƃ��S�B
};

