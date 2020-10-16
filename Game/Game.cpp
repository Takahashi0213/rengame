#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BoxMaker.h"
#include "TestEnemy.h"

#include "GameCamera.h"
#include "GameUI.h"

#include "Switch.h"
#include "StageSet.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//���݂��Q�[���i�A�N�V�������[�h�j�ɂ���
	SceneManager::GetInstance()->SetGameMode(SceneManager::ActionMode);
	//Dof��L���ɂ���
	SceneManager::GetInstance()->GetGameGraphicInstance()->m_dofFlag = true;

	//����
	
	//���C�g���[�J�[
	if(LightMaker::GetInstance() == nullptr) {
		CGameObjectManager::GetInstance()->NewGO<LightMaker>("LightMaker");
	}
	//�A���r�G���g���C�g������������
	LightMaker::GetInstance()->ResetAmbientColor();

	//�J�����T�|�[�^�[�̐���
	CGameObjectManager::GetInstance()->NewGO<CameraSupporter>("CameraSupporter");

	//BackGround* bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	GameUI* ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	m_ui = ui;

	//�J����
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");

	//�{�b�N�X���C�J�[�ɓn����
	m_box->SetPlayer(pl);

	//�g�����W�V����
	TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox, 
		SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true);

	//���C���[�t���[����\�����܂���������������
	g_physics->SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	//�X�e�[�W
	StageSet m_stageSet;
	m_stageSet.CriateStage(L"Assets/modelData/0_0.cmo",L"Assets/level/stage_00.tkl");
	m_stageSet.SetGame(this);

}


Game::~Game()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void Game::Update() {

	m_gameEffect.GameEffectUpdate();

}

void Game::Render() {

}