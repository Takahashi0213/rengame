#pragma once
#include "system/CGameObjectManager.h"
#include "Game.h"
#include "GameBox.h"
#include "Player.h"
#include "GameCamera.h"

class BoxMaker : public IGameObject
{
public:
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

private:
	void BoxUpdate();

	Game* m_game = nullptr;
	CVector3 m_boxPos = CVector3().Zero();
	Player* m_player = nullptr;

	//�����X�g
	std::list<GameBox*> m_boxList;
	GameBox* m_nowBox = nullptr;		//���݌��Ă���{�b�N�X����
	std::list<GameBox*> m_nowBoxList;

	//���W
	CVector3 m_boxPoint[4];

	//�萔
	const float PosHoseiY = 200.0f;		//���C���q�b�g���Ȃ��������̕␳

};

