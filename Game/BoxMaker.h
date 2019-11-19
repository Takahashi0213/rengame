#pragma once
#include "system/CGameObjectManager.h"
#include "Game.h"
#include "GameBox.h"
#include "Player.h"
#include "GameCamera.h"

/// <summary>
/// ���𐶐������葀�삵����
/// �E�V���O���g��
/// </summary>
class BoxMaker : public IGameObject
{
	static BoxMaker* m_instance;
public:
	enum BoxMakerMode {
		NomalMode,
		FocusMode,
	};

	BoxMaker();
	~BoxMaker();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �Q�[���̃|�C���^���ق����
	/// </summary>
	/// <param name="game">�A�h���X</param>
	void SetGame(Game* game) {
		m_game = game;
	}
	/// <summary>
	/// �v���C���[�̃|�C���^���ق����
	/// </summary>
	/// <param name="game">�A�h���X</param>
	void SetPlayer(Player* pl) {
		m_player = pl;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static BoxMaker* BoxMaker::GetInstance() {
		return m_instance;
	}

private:
	void BoxUpdate();

	Game* m_game = nullptr;
	CVector3 m_boxPos = CVector3().Zero();
	Player* m_player = nullptr;

	BoxMakerMode m_boxMakerMode = NomalMode;		//�{�b�N�X���C�J�[���`�`�h

	//�����X�g
	std::list<GameBox*> m_boxList;
	GameBox* m_nowBox = nullptr;			//���݌��Ă���{�b�N�X����
	GameBox* m_nowBox_Stock = nullptr;		//�ȑO���Ă����{�b�N�X���ꎞ�ۑ��I
	std::list<GameBox*> m_nowBoxList;

	//���g��p
	CVector2 m_mouseMove = { 0.0f,0.0f };	//�}�E�X�̈ړ��ʂ�ۑ��i�}�C�i�X�ɂȂ����烄�o���j
	CVector3 m_boxScale = CVector3().One(); //�g�嗦�I
	CVector3 m_boxScaleDef = CVector3().One();
	//���W
	CVector3 m_boxPoint[4];

	//�萔
	const float PosHoseiY = 200.0f;					//���C���q�b�g���Ȃ��������̕␳

};

