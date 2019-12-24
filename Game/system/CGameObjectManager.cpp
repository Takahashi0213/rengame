#include "stdafx.h"
#include "CGameObjectManager.h"

	CGameObjectManager* CGameObjectManager::m_instance = nullptr;

	CGameObjectManager::CGameObjectManager() {
		if (m_instance != nullptr) {
			std::abort(); //���łɏo�Ă��邽�߃N���b�V��
		}

		//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
		m_instance = this;

		//���C���ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
		m_mainRenderTarget.Create(
			(unsigned int)FRAME_BUFFER_W,
			(unsigned int)FRAME_BUFFER_H,
			DXGI_FORMAT_R16G16B16A16_FLOAT
		);
		//�J������Ԃł̐[�x�l�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g���쐬����B
		//�t�H�[�}�b�g��R�����݂̂�32�r�b�g���������_�o�b�t�@�B
		m_depthRenderTarget.Create(
			(unsigned int)FRAME_BUFFER_W,
			(unsigned int)FRAME_BUFFER_H,
			DXGI_FORMAT_R32_FLOAT
		);

		//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
		//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
		m_copyMainRtToFrameBufferSprite.Sprite_Init(
			m_mainRenderTarget.GetRenderTargetSRV(),
			FRAME_BUFFER_W,
			FRAME_BUFFER_H
		);
		m_copyMainRtToFrameBufferSprite.m_isInited = true;

		//�|�X�g�G�t�F�N�g�̏������B
		m_postEffect.Init();
		//�����������̃u�����h�X�e�[�g������������B
		InitTranslucentBlendState();

	}

	CGameObjectManager::~CGameObjectManager() {

		//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
		m_instance = nullptr;

		if (m_translucentBlendState != nullptr) {
			m_translucentBlendState->Release();
		}
	}

	void CGameObjectManager::InitTranslucentBlendState() {

		//��̂��Ƃ��A�쐬����u�����h�X�e�[�g�̏���ݒ肷��B
		CD3D11_DEFAULT defaultSettings;
		//�f�t�H���g�Z�b�e�B���O�ŏ���������B
		CD3D11_BLEND_DESC blendDesc(defaultSettings);

		//���u�����f�B���O��L���ɂ���B
		blendDesc.RenderTarget[0].BlendEnable = true;

		//�\�[�X�J���[�̃u�����f�B���O���@���w�肵�Ă���B
		//�\�[�X�J���[�Ƃ̓s�N�Z���V�F�[�_�\����̏o�͂��w���Ă���B
		//���̎w��ł́A�\�[�X�J���[��SRC(rgba)�Ƃ���ƁA
		//�ŏI�I�ȃ\�[�X�J���[�͉��L�̂悤�Ɍv�Z�����B
		//�ŏI�I�ȃ\�[�X�J���[ = SRC.rgb �~ SRC.a�E�E�E�E�E�E�@�@
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

		//�f�B�X�e�B�l�[�V�����J���[�̃u�����f�B���O���@���w�肵�Ă���B
		//�f�B�X�e�B�l�[�V�����J���[�Ƃ́A
		//���łɕ`�����܂�Ă��郌���_�����O�^�[�Q�b�g�̃J���[���w���Ă���B
		//���̎w��ł́A�f�B�X�e�B�l�[�V�����J���[��DEST(rgba)�A
		//�\�[�X�J���[��SRC(RGBA)�Ƃ���ƁA�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[��
		//���L�̂悤�Ɍv�Z�����B
		//�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[ = DEST.rgb �~ (1.0f - SRC.a)�E�E�E�E�E�A
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		//�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[�̌v�Z���@���w�肵�Ă���B
		//���̎w�肾�ƁA�@�{�A�̃J���[���������܂��B
		//�܂�A�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[��
		//SRC.rgb �~ SRC.a + DEST.rgb �~ (1.0f - SRC.a)
		//�ƂȂ�B
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		//���̐ݒ�ŁA�u�����h�X�e�[�g���쐬�����
		//�������������s����u�����h�X�e�[�g���쐬�ł���B
		auto d3dDevice = g_graphicsEngine->GetD3DDevice();
		d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);

	}

	void CGameObjectManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
	{
		ChangeRenderTarget(
			d3dDeviceContext,
			renderTarget->GetRenderTargetView(),
			renderTarget->GetDepthStensilView(),
			viewport
		);
	}
	void CGameObjectManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
	{
		ID3D11RenderTargetView* rtTbl[] = {
			renderTarget
		};
		//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
		d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
		if (viewport != nullptr) {
			//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
			d3dDeviceContext->RSSetViewports(1, viewport);
		}
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
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_BackSprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�֐����Ăяo��
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		//�o�^����Ă���X�v���C�g�̍X�V�֐����Ăяo��
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}

		///////////////////////////////////////////////
		//��������`�揈��
		///////////////////////////////////////////////

		//�t���[���o�b�t�@�̂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->OMGetRenderTargets(
			1,
			&m_frameBufferRenderTargetView,
			&m_frameBufferDepthStencilView
		);
		//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
		unsigned int numViewport = 1;
		d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);
		//�|�X�g�G�t�F�N�g�̍X�V�B
		m_postEffect.Update();

		//�v�������_�����O
		PreRender();

		//�t�H���[�h�����_�����O
		ForwordRender();

		//�|�X�g�����_�����O
		PostRender();

		///////////////////////////////////////////////
		//��������ʏ탌���_�����O�B
		///////////////////////////////////////////////

		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		//�����������̃u�����h�X�e�[�g��ݒ肷��B
		d3dDeviceContext->OMSetBlendState(
			m_translucentBlendState,	//�ݒ肷��u�����f�B���O�X�e�[�g
			blendFactor,				//�u�����f�B���O�t�@�N�^�[�B�C�ɂ��Ȃ��Ă悢
			0xffffffff					//�T���v�����O�}�X�N�B�C�ɂ��Ȃ��Ă悢�B
		);

		//�o�^����Ă���X�v���C�g�̕`��֐����Ăяo��
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

	void CGameObjectManager::PreRender() {
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

	}

	void CGameObjectManager::ForwordRender(){

		//�����_�����O�^�[�Q�b�g�𕡐��ݒ肷��B
		//     MRT(Multi rendering target)
		ID3D11RenderTargetView* rts[] = {
			m_mainRenderTarget.GetRenderTargetView(),	//0�Ԗڂ̓��C�������_�����O�^�[�Q�b�g
			m_depthRenderTarget.GetRenderTargetView(),	//1�Ԗڂ̓J������Ԃł̐[�x�l���o�͂��郌���_�����O�^�[�Q�b�g�B
		};
		auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
		deviceContext->OMSetRenderTargets(
			2,											//�������̓Z�b�g���郌���_�����O�^�[�Q�b�g�̐��B2�ݒ肷��̂�2���w�肷��B
			rts,										//�������ɂ̓����_�����O�^�[�Q�b�g�̔z����w�肷��B
			m_mainRenderTarget.GetDepthStensilView()	//��O�����͐[�x�X�e���V���o�b�t�@�B����͈�����w��ł��Ȃ��B
		);
		deviceContext->RSSetViewports(1, m_mainRenderTarget.GetViewport());
		//���C�������_�����O�^�[�Q�b�g���N���A����B
		float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_mainRenderTarget.ClearRenderTarget(clearColor);
		m_depthRenderTarget.ClearRenderTarget(clearColor);

		//�o�^����Ă���X�v���C�g�̕`��֐����Ăяo��
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_BackSprite && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

		//�o�^����Ă���Q�[���I�u�W�F�N�g�̕`��֐����Ăяo��
		for (int i = 0; i < MAX_PRIORITY; i++) { //�D��x
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

	}

	void CGameObjectManager::PostRender() {

		//�|�X�g�G�t�F�N�g�̕`��B
		m_postEffect.Draw();

		//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		ChangeRenderTarget(
			d3dDeviceContext,
			m_frameBufferRenderTargetView,
			m_frameBufferDepthStencilView,
			&m_frameBufferViewports
		);
		//�h���h��
		m_copyMainRtToFrameBufferSprite.Sprite_Draw();

		m_frameBufferRenderTargetView->Release();
		m_frameBufferDepthStencilView->Release();

	}

