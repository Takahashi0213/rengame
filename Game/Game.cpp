#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "BackGround.h"
#include "BoxMaker.h"

#include "GameCamera.h"

Game::Game()
{
	//����

	//���C�g���[�J�[�̐���
	CGameObjectManager::GetInstance()->NewGO<LightMaker>("LightMaker");

	//�J�����T�|�[�^�[�̐���
	CGameObjectManager::GetInstance()->NewGO<CameraSupporter>("CameraSupporter");

	BackGround* bg = CGameObjectManager::GetInstance()->NewGO<BackGround>("BackGround", 0);
	BoxMaker* m_box = CGameObjectManager::GetInstance()->NewGO<BoxMaker>("BoxMaker", 1);
	Player* pl = CGameObjectManager::GetInstance()->NewGO<Player>("Player", 1);
	CGameObjectManager::GetInstance()->NewGO<GameCamera>("GameCamera");

	//�{�b�N�X���C�J�[�ɓn����
	m_box->SetGame(this);
	m_box->SetPlayer(pl);
	//�Q�[���J�����ɓn��
	int a = Hash::MakeHash("GameCamera");
	GameCamera* GC = CGameObjectManager::GetInstance()->FindGO<GameCamera>(a);
	GC->SetGame(this);
	//�v���C���[�ɓn��
	pl->SetGame(this);
	//�w�i�ɓn��
	bg->SetGame(this);
}


Game::~Game()
{
}

void Game::Update() {

}

void Game::Render() {

}