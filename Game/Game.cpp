#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BoxMaker.h"

#include "GameCamera.h"

#include "StageSet.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//����
	
	//OP�𐶐�
	m_op = new OP;

	//�g�����W�V����
	TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox, 
		SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true);

#ifdef _DEBUG
	//���C���[�t���[����\�����܂���������������
	g_physics->SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
#endif

}


Game::~Game()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void Game::Update() {

	switch (m_gameState)
	{
	case Game::GameState_OP:
		//OP�N���X�A�b�v�f�[�g
		m_op->OP_Update();
		//OP���I�������؂�ւ���
		if (m_op->GetEndFlag() == true) {
			//�؂�ւ�
			delete m_op;
			m_op = nullptr;
			GameSetUp();
		}

		break;
	case Game::GamaState_Game:
		//�Q�[������p

		break;
	}

	//�ǂ̃X�e�[�g�ł��G�t�F�N�g�X�V�͂���
	m_gameEffect.GameEffectUpdate();

}

void Game::Render() {

}

void Game::GameSetUp() {

	//���[�h�ύX
	SceneManager::GetInstance()->SetGameMode(SceneManager::GameMode::ActionMode);
	//Dof��L���ɂ���
	SceneManager::GetInstance()->GetGameGraphicInstance()->m_dofFlag = true;

	//�{�b�N�X���C�J�[�̍쐬
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	//�v���C���[�̍쐬
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	//�{�b�N�X���C�J�[�ɓn����
	m_box->SetPlayer(pl);
	//UI�̍쐬
	m_ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	//�J����
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");
	//�X�e�[�W
	StageSet m_stageSet;
	m_stageSet.InitStage(L"Sougen1");
	//StageSet::GetInstance()->InitStage(L"Tutorial");
	//�����ύX
	m_gameState = GamaState_Game;
}