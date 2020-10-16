#include "stdafx.h"
#include "SceneManager.h"
#include "system/system.h"

#include "GameCamera.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�T�E���h�G���W�����������B
	m_soundEngine.Init();

	//�g�����W�V����
	TransitionGenerator* tg = CGameObjectManager::GetInstance()->NewGO<TransitionGenerator>("TransitionGenerator", 10);
	tg->SetObjectTag(objectTag::t_Sprite);		//�Ƃɂ����Ō�Ɏ��s�����悤�ɂ���

	//�ŏ��̓^�C�g���I
	m_title = CGameObjectManager::GetInstance()->NewGO<Title>("Game_Title");
	//�^�C�g��������Ȃ����p
	//{
	//	m_game = CGameObjectManager::GetInstance()->NewGO<Game>("Main_Game");
	//	m_nowScene = Game_Sence;
	//}
}


SceneManager::~SceneManager()
{	
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void SceneManager::Update() {

	//���݂̃V�[���ɂ���ĈႤ����
	switch (m_nowScene)
	{
	case SceneManager::Title_Scene:
		//�`�F�b�N�A���h�L���J�G	
		TitleUpdate();
		break;
	case SceneManager::Game_Sence:
		//�Q�[���Ȃ�
		GameUpdate();
		break;
	}

}

void SceneManager::Render() {

}

void SceneManager::TitleUpdate() {

	const Title::TitleCommand& m_command = m_title->GetCommand();
	if (m_command != Title::TitleCommand::No_Select) {
		TitleCommand(m_command);	//�V�[���؂�ւ�
	}

}

void SceneManager::GameUpdate() {

}

void SceneManager::TitleCommand(const Title::TitleCommand command) {
	switch (command)
	{
	case Title::No_Select:
		//�܂������ɓ��邱�Ƃ͂Ȃ��񂾂��ǂ�
		std::abort(); //�ꉞ�~�߂Ƃ��I
		break;
	case Title::Game_Start:
		//�j���[�Q�[��
		CGameObjectManager::GetInstance()->DeleteGO(m_title);
		m_title = nullptr;
		m_nowScene = Game_Sence;
		m_game = CGameObjectManager::GetInstance()->NewGO<Game>("Main_Game");
		break;
	case Title::Game_Continue:
		//���[�h��ʂ�

		break;
	case Title::Game_End:
		//�����܂���
		DestroyWindow(g_hWnd);
		break;
	}
}