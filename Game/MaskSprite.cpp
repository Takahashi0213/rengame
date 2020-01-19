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
	if (m_depthStencilState2 != nullptr) {
		m_depthStencilState2->Release();
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
	desc.DepthEnable = false;						 
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; 
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	//�f�v�X�X�e���V���X�e�[�g���쐬�B
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState2);

}

void MaskSprite::Draw() {

	//�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState, 0);

	m_subSprite.Sprite_Draw();
	m_mainSprite.Sprite_Draw();

	//�߂�	
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState2, 0);

}