#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "BoxMaker.h"

#include "GameCamera.h"
#include "GameUI.h"

Game* Game::m_instance = nullptr;

Game::Game()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�T�E���h�G���W�����������B
	m_soundEngine.Init();

	//����

	//���C�g���[�J�[�̐���
	CGameObjectManager::GetInstance()->NewGO<LightMaker>("LightMaker");

	//�J�����T�|�[�^�[�̐���
	CGameObjectManager::GetInstance()->NewGO<CameraSupporter>("CameraSupporter");

	BackGround* bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");
	GameUI* ui = CGameObjectManager::GetInstance()->NewGO<GameUI>("GameUI", 8);
	m_ui = ui;

	TransitionGenerator* tg = CGameObjectManager::GetInstance()->NewGO<TransitionGenerator>("TransitionGenerator", 10);
	tg->SetObjectTag(objectTag::t_Sprite);		//�Ƃɂ����Ō�Ɏ��s�����悤�ɂ���

	//�{�b�N�X���C�J�[�ɓn����
	m_box->SetPlayer(pl);
	//�w�i�ɓn��
	bg->SetGame(this);
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