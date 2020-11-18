#include "stdafx.h"
#include "Game.h"

#include "GameObject/Player.h"
#include "GameSystem/Box/BoxMaker.h"

#include "GameCamera.h"

#include "GameSystem/StageSet/StageSet.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//����
	m_gameData = new GameData;
	m_gameEffect = new GameEffect;

	if (SceneManager::GetInstance()->GetSystemInstance()->m_loadDataFlag == false) {
		//OP�𐶐�
		m_op = new OP;
	}
	else {
		//OP�X�L�b�v
		GameSetUp();
	}

#ifdef _DEBUG
	//���C���[�t���[����\�����܂�
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
		m_op->OP_Update();													//OP�A�b�v�f�[�g
		if (m_op->GetEndFlag() == true) {
			//OP���I�������؂�ւ���
			delete m_op;
			m_op = nullptr;
			GameSetUp();
		}
		break;
	case Game::GamaState_Game:
		//�Q�[������p
		SceneManager::GetInstance()->GetGameEvent()->GameEventUpdate();		//�Q�[���C�x���g�A�b�v�f�[�g
		m_damageSystem->DamageUpdate();										//�_���[�W�V�X�e���A�b�v�f�[�g
		m_itemGet->ItemGetUpdate();											//�A�C�e���Q�b�g�A�b�v�f�[�g
		m_ui_Supporter->UI_Suppoter_Update();								//UI�T�|�[�^�[�A�b�v�f�[�g
		break;
	case Game::GamaState_GameOver:
		m_gameOver->GameOverUpdate();										//�Q�[���I�[�o�[�A�b�v�f�[�g
		break;
	}

	//�Q�[���I�[�o�[�`�F�b�N
	if (m_gameState != Game::GamaState_GameOver &&
		SceneManager::GetInstance()->GetGameMode() == SceneManager::GameOver) {
		m_gameState = Game::GamaState_GameOver;
		m_gameOver = new GameOver;		//�Q�[���I�[�o�[��ʂ𐶐�����
	}

	//�ǂ̃X�e�[�g�ł��G�t�F�N�g�X�V�͂���
	m_gameEffect->GameEffectUpdate();

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
	//�{�b�N�X���C�J�[�ɓn��
	m_box->SetPlayer(pl);
	//UI�̍쐬
	m_ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	m_statusUI = CGameObjectManager::GetInstance()->NewGO<GameStatus_UISystem>("GameStatus_UISystem", 8);
	//�J����
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");
	//�_���[�W�V�X�e��
	m_damageSystem = new DamageSystem;
	//UI�T�|�[�^�[
	m_ui_Supporter = new UI_Supporter;
	m_ui_Supporter->SetPlayer(pl);
	//�A�C�e���Q�b�g
	m_itemGet = new ItemGet;
	if (SceneManager::GetInstance()->GetSystemInstance()->m_loadDataFlag == false) {
		//�X�e�[�W
		StageSet::GetInstance()->InitStage(L"Tutorial");
		//�`���[�g���A��BGM�̍Đ�
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(L"Assets/sound/BGM/Tutorial.wav");
	}
	else {
		//�X�e�[�W
		StageSet::GetInstance()->InitStage(GameData::GetInstance()->GetNowStageNo());
		//�v���C���[�̍��W��ݒ�
		pl->SetPosition(GameData::GetInstance()->GetSavePosition());
		pl->SetRotation(GameData::GetInstance()->GetSaveRotation());
		//BGM�̍Đ�
		wchar_t* bgmName = StageSet::GetInstance()->GetStageBGM_Name(GameData::GetInstance()->GetPlace());
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(bgmName);
		//�g�����W�V����
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox,
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true);
	}
	//�����ύX
	m_gameState = GamaState_Game;
}