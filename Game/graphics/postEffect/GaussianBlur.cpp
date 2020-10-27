#include "stdafx.h"
#include "GaussianBlur.h"
#include "PostEffect.h"

void GaussianBlur::Init(ID3D11ShaderResourceView* srcTextureSRV, const float& blurIntensity)
{
	//�\�[�X�e�N�X�`����SRV���R�s�[�B
	m_srcTextureSRV = srcTextureSRV;
	//UpdateWeight�֐��Ŏg�p����̂ŁA�u���[�̋����������o�ϐ��ɋL�����Ă����B
	m_blurIntensity = blurIntensity;

	//�\�[�X�e�N�X�`���̏����擾�B
	ID3D11Texture2D* tex;
	//�܂��ASRV�Ɋ֘A�t������Ă���e�N�X�`�����擾����B
	srcTextureSRV->GetResource((ID3D11Resource**)&tex);
	//�擾�����e�N�X�`������A�e�N�X�`�������擾����B
	D3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);
	//�e�N�X�`�������擾�ł����̂ŁA�e�N�X�`���̎Q�ƃJ�E���^�����낷�B
	tex->Release();
	//�\�[�X�e�N�X�`���̕��ƍ������L�����Ă����B
	m_srcTextureWidth = texDesc.Width;
	m_srcTextureHeight = texDesc.Height;

	//X�u���[�p�̃����_�����O�^�[�Q�b�g���쐬�B
	m_renderTarget[enRenderTarget_XBlur].Create(
		texDesc.Width / 2,		//���̉𑜓x�𔼕��ɂ���B
		texDesc.Height,
		texDesc.Format );

	//Y�u���[�p�̃����_�����O�^�[�Q�b�g���쐬�B
	m_renderTarget[enRenderTarget_YBlur].Create(
		texDesc.Width / 2,		//���̉𑜓x�𔼕��ɂ���B
		texDesc.Height / 2,		//�c�̉𑜓x�𔼕��ɂ���B
		texDesc.Format
	);

	//�V�F�[�_�[�����[�h�B
	m_vsXBlur.Load("Assets/shader/GaussianBlur.fx", "VSXBlur", Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/GaussianBlur.fx", "VSYBlur", Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/GaussianBlur.fx", "PSBlur", Shader::EnType::PS);

	//VRAM��ɒ萔�o�b�t�@���쐬�B
	m_blurCbGpu.Create(nullptr, sizeof(SBlurParam));

	//�������ς݂̈�B
	m_isInited = true;
}

void GaussianBlur::UpdateWeights()
{
	//�K�E�X�t�B���^�̏d�݂��X�V����B
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurIntensity);
		total += 2.0f*m_blurParam.weights[i];

	}
	// �K�i���B�d�݂̃g�[�^����1.0�ɂȂ�悤�ɁA�S�̂̏d�݂ŏ��Z���Ă���B
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
}
void GaussianBlur::Execute(PostEffect& postEffect)
{
	if (m_isInited == false) {
		//�������ł��ĂȂ����B
		return;
	}
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�K�E�V�A���t�B���^�[�̏d�݃e�[�u�����X�V����B
	UpdateWeights();
	
	//�d�݃e�[�u�����X�V�����̂ŁAVRAM��̒萔�o�b�t�@���X�V����B
	//���C���������̓��e��VRAM�ɃR�s�[�B
	auto d3d11CbGpu = m_blurCbGpu.GetD3D11Buffer();
	deviceContext->UpdateSubresource(
		d3d11CbGpu, 0, nullptr, &m_blurParam, 0, 0);
	//���W�X�^b0��m_blurCbGpu�̃A�h���X��ݒ肷��B
	deviceContext->PSSetConstantBuffers(
		0, 1, &d3d11CbGpu);

	float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	//X�u���[�B
	{
		//X�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_graphicsEngine->ChangeRenderTarget(
			&m_renderTarget[enRenderTarget_XBlur], 
			m_renderTarget[enRenderTarget_XBlur].GetViewport());
		
		m_renderTarget[enRenderTarget_XBlur].ClearRenderTarget(clearColor);
		//�\�[�X�e�N�X�`���̃A�h���X��t0���W�X�^�ɐݒ肷��B
		deviceContext->VSSetShaderResources(0, 1, &m_srcTextureSRV);
		deviceContext->PSSetShaderResources(0, 1, &m_srcTextureSRV);

		//�t���X�N���[���`����s���ău���[�����s�B
		postEffect.DrawFullScreenQuadPrimitive(
			deviceContext, m_vsXBlur, m_psBlur);
	}
	//������Y�u���[
	{
		//Y�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_graphicsEngine->ChangeRenderTarget(
			&m_renderTarget[enRenderTarget_YBlur], 
			m_renderTarget[enRenderTarget_YBlur].GetViewport()
		);
		m_renderTarget[enRenderTarget_YBlur].ClearRenderTarget(clearColor);
		//Y�u���[��������\�[�X�e�N�X�`���̃A�h���X��t0�ɐݒ肷��B
		//Y�u���[��������̂�X�u���[���������e�N�X�`���ɂȂ�B
		auto srcTextureSrv = m_renderTarget[enRenderTarget_XBlur].GetRenderTargetSRV();
		deviceContext->VSSetShaderResources(0, 1, &srcTextureSrv);
		deviceContext->PSSetShaderResources(0, 1, &srcTextureSrv);

		//�t���X�N���[���`����s���ău���[�����s�B
		postEffect.DrawFullScreenQuadPrimitive(
			deviceContext, m_vsYBlur, m_psBlur
		);

	}
}