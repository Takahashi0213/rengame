#pragma once

/// <summary>
/// �Q�[���I
/// �E�V���O���g��
/// </summary>
class Game : public IGameObject
{
	static Game* m_instance;
public:
	enum GameMode {
		Title,
		ActionMode,
		CreateMode,
		Menu,
	};

	Game();
	~Game();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �Q�[�����[�h���Z�b�g
	/// </summary>
	/// <param name="mode">���[�h</param>
	void SetGameMode(GameMode mode) {
		m_gameMode = mode;
	}
	/// <summary>
	/// �Q�[�����[�h���擾
	/// </summary>
	/// <returns>���[�h</returns>
	GameMode GetGameMode() {
		return m_gameMode;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static Game* Game::GetInstance() {
		return m_instance;
	}

	/// <summary>
	/// PhysicsWorld���擾
	/// </summary>
	/// <returns>PhysicsWorld</returns>
	PhysicsWorld GetPhysicsWorld() {
		return m_physicsWorld;
	}

private:
	GameMode m_gameMode = ActionMode;
	
	PhysicsWorld m_physicsWorld;

};

