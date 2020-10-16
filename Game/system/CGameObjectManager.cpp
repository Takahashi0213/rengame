#include "stdafx.h"
#include "CGameObjectManager.h"

	CGameObjectManager* CGameObjectManager::m_instance = nullptr;

	CGameObjectManager::CGameObjectManager() {
		if (m_instance != nullptr) {
			std::abort(); //���łɏo�Ă��邽�߃N���b�V��
		}

		//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
		m_instance = this;

		m_cgom_Graphics = new CGOM_Graphics;
		m_cgom_Graphics->Init();
	}

	CGameObjectManager::~CGameObjectManager() {

		//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
		m_instance = nullptr;

	}

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void CGameObjectManager::Execute() {

		//�I�A�N�e�B�u�t���O��true���ƍX�V����Ȃ���I

		///////////////////////////////////////////////
		//��������X�V����
		///////////////////////////////////////////////

		//�o�^����Ă���w�i�X�v���C�g�̍X�V�֐����Ăяo��
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_BackSprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�֐����Ăяo��
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		//�o�^����Ă���X�v���C�g�̍X�V�֐����Ăяo��
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}

		///////////////////////////////////////////////
		//��������`�揈��
		///////////////////////////////////////////////

		//��������
		m_cgom_Graphics->Standby();

		{
			//�v�������_�����O
			PreRender();

			//�t�H���[�h�����_�����O
			ForwordRender();

			//�f�o�b�O
			m_cgom_Graphics->DebugDraw();

			//�G�t�F�N�T�[
			m_cgom_Graphics->EffectRender(false);

			//�|�X�g�����_�����O
			PostRender();

		}

		///////////////////////////////////////////////
		//��������ʏ탌���_�����O�B
		///////////////////////////////////////////////

		m_cgom_Graphics->EndSet();

		//�o�^����Ă���X�v���C�g�̕`��֐����Ăяo��
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

		//�G�t�F�N�T�[
		m_cgom_Graphics->EffectRender(true);

		//�G�t�F�N�g�f�[�^�̍폜
		EffekseerSupporter::GetInstance()->EffectClear();
		//�폜���X�g�ɐς܂ꂽ�I�u�W�F�N�g���܂Ƃ߂ď�������
		ExecuteDeleteGameObjects();

	}

	/// <summary>
	/// �폜����\��̃I�u�W�F�N�g���܂Ƃ߂ď�������
	/// </summary>
	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		//�폜���X�g�̗v�f�������[�v����
		for (auto go = m_deleteList.begin();
			go != m_deleteList.end();
			go++) {

			//�����Ŏw�肳�ꂽ�Q�[���I�u�W�F�N�g������
			for (auto it = m_goList.begin();
				it != m_goList.end();
				it++) {

				if (*it == *go) {
					//���������̂ō폜
					delete *it; //���������
					m_goList.erase(it); //�ϒ��z�񂩂珜��
					return;
				}
			}
		}

		//�폜���X�g�����Z�b�g
		m_deleteList.clear();

	}

	void CGameObjectManager::PreRender() {

		m_cgom_Graphics->PreRender();

	}

	void CGameObjectManager::ForwordRender(){

		m_cgom_Graphics->ForwordRender();

		//�o�^����Ă���X�v���C�g�̕`��֐����Ăяo��
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_BackSprite && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

		//�o�^����Ă���Q�[���I�u�W�F�N�g�̕`��֐����Ăяo��
		for (int i = 0; i <= MAX_OBJ_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

	}

	void CGameObjectManager::PostRender() {

		m_cgom_Graphics->PostRender();

	}

