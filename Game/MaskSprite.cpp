#include "stdafx.h"
#include "MaskSprite.h"

MaskSprite::MaskSprite()
{
	CreateDepthStencilState();
	m_subSprite.m_renderMode = Sprite_RenderMode::Mask;
}

MaskSprite::~MaskSprite()
{
	if (m_depthStencilState != nullptr) {
		m_depthStencilState->Release();
	}	
	if (m_depthStencilState_Def != nullptr) {
		m_depthStencilState_Def->Release();
	}
	if (m_depthStencilState_Z != nullptr) {
		m_depthStencilState_Z->Release();
	}
}

void MaskSprite::CreateDepthStencilState()
{
	//D3D�f�o�C�X���擾�B
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;					 //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //Z�o�b�t�@��Z�l��`�����ށB
	desc.DepthFunc = D3D11_COMPARISON_LESS;		 //Z�l����������΃t���[���o�b�t�@�ɕ`�����ށB
	//�f�v�X�X�e���V���X�e�[�g���쐬�B
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState);

	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	desc = { 0 };
	desc.DepthEnable = true;					 //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //Z�o�b�t�@��Z�l��`�����ށB
	desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;		 //Z�l�������Ȃ�t���[���o�b�t�@�ɕ`�����ށB
	//�f�v�X�X�e���V���X�e�[�g���쐬�B
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState_Z);

	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	desc.DepthEnable = false;						 
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; 
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	//�f�v�X�X�e���V���X�e�[�g���쐬�B
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState_Def);

}

void MaskSprite::Draw() {

	//�t���[���o�b�t�@��Z�l������������
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = CGameObjectManager::GetInstance()->GetFrameBufferDepthStencilView();
	g_graphicsEngine->GetD3DDeviceContext()->ClearDepthStencilView(m_frameBufferDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState, 0);

	//�}�X�N����������X�v���C�g�̕`��
	m_subSprite.Sprite_Draw();

	//�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState_Z, 0);

	//�}�X�N�̃X�v���C�g�̕`��
	m_mainSprite.Sprite_Draw();

	//�߂�	
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState_Def, 0);

}