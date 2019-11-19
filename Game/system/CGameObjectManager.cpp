#include "stdafx.h"
#include "CGameObjectManager.h"

	CGameObjectManager* CGameObjectManager::m_instance = nullptr;

	CGameObjectManager::CGameObjectManager() {
		if (m_instance != nullptr) {
			std::abort(); //���łɏo�Ă��邽�߃N���b�V��
		}

		//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
		m_instance = this;

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

		//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�֐����Ăяo��
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}

		///////////////////////////////////////////////
		//�V���h�E�}�b�v�Ƀ����_�����O
		///////////////////////////////////////////////
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
		ID3D11RenderTargetView* oldRenderTargetView;
		ID3D11DepthStencilView* oldDepthStencilView;
		d3dDeviceContext->OMGetRenderTargets(
			1,
			&oldRenderTargetView,
			&oldDepthStencilView
		);
		//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
		unsigned int numViewport = 1;
		D3D11_VIEWPORT oldViewports;
		d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

		ShadowMap::GetInstance()->RenderToShadowMap();

		//���ɖ߂��B
		d3dDeviceContext->OMSetRenderTargets(
			1,
			&oldRenderTargetView,
			oldDepthStencilView
		);
		d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
		//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
		oldRenderTargetView->Release();
		oldDepthStencilView->Release();

		///////////////////////////////////////////////
		//��������ʏ탌���_�����O�B
		///////////////////////////////////////////////

		//�o�^����Ă���Q�[���I�u�W�F�N�g�̕`��֐����Ăяo��
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Render();
				}
			}
		}
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Render();
				}
			}
		}
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

