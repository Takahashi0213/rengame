#pragma once
#include "system/CGameObjectManager.h"
#include "GameObject/Player.h"
#include "GameBox.h"

/// <summary>
/// �Q�[���J�����Ƒ���F�X
/// �E�V���O���g��
/// </summary>
class GameCamera final : public IGameObject
{
	static GameCamera* m_instance;
public:
	GameCamera();
	~GameCamera();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �����Ă��锠�̃A�h���X�ł�
	/// </summary>
	/// <param name="gamebox">�A�h���X�ł�</param>
	void SetGameBox(GameBox* gamebox) {
		m_gamebox = gamebox;
	}

	/// <summary>
	/// �N���G�C�g���[�h����A�N�V�������[�h�ɐ؂�ւ�������A�J�����̈ړ��𐧌䂷��t���O��true�ɂ��܂���`
	/// </summary>
	void PlayerCameraMove() {
		m_camera_BoxToPlayer_MoveFlag = true;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static GameCamera* GameCamera::GetInstance() {
		return m_instance;
	}

private:
	void ActionMode();
	void CreateMode();
	void CommonMove();

	CVector3 m_cameraTarget;
	CVector3 m_cameraPos;

	Player* m_player;
	Game* m_game;
	GameBox* m_gamebox = nullptr;

	CVector3 m_cameraHosei = { 0.0f,300.0f,-300.0f };

	//�v���C���[�ɖ߂�J�����̏���
	bool m_camera_BoxToPlayer_MoveFlag = false;

	//�萔
	const float CameraMoveHosei = 10.0f;		//���[�h�`�F���W���A�J�����̈ړ����x�␳
};

