#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

ModelEffect::ModelEffect()
{
	m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
	m_psMonochrome.Load("Assets/shader/model.fx", "PSMain_Monochrome", Shader::EnType::PS);
	//�V���h�E�}�b�v
	m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", Shader::EnType::PS);
	m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", Shader::EnType::VS);
	//���p�V�F�[�_�[
	m_psShader_Box.Load("Assets/shader/box_model.fx", "PSMain", Shader::EnType::PS);
	//����߂�
	m_psShader_Kirameki.Load("Assets/shader/model.fx", "PSMain_Kirameki", Shader::EnType::PS);

	m_pPSShader = &m_psShader;
	m_pPSSilhouetteShader = &m_psSilhouette;
	m_pPSMonochromeShader = &m_psMonochrome;
	m_vsShadowMapShader = &m_vsShadowMap;
	m_psShadowMapShader = &m_psShadowMap;
	m_pPSShaderBox = &m_psShader_Box;
	m_pPSKiramekiShader = &m_psShader_Kirameki;

	//�f�v�X�X�e���V���̏������B
	InitSilhouettoDepthStepsilState();
	//�u�����h�X�e�[�g�̏�����
	InitTranslucentBlendState();
}

void ModelEffect::InitSilhouettoDepthStepsilState() {

	//D3D�f�o�C�X���擾�B
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //Z�o�b�t�@��Z�l��`�����܂Ȃ��B
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z�l���傫����΃t���[���o�b�t�@�ɕ`�����ށB

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);

	desc = { 0 };
	desc.DepthEnable = true;						   //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //Z�o�b�t�@��Z�l��`�����܂Ȃ��B
	desc.DepthFunc = D3D11_COMPARISON_EQUAL;		   //Z�l���傫����΃t���[���o�b�t�@�ɕ`�����ށB
	pd3d->CreateDepthStencilState(&desc, &m_kiramekiDepthStepsilState);

}

void ModelEffect::InitTranslucentBlendState() {

	CD3D11_DEFAULT defaultSettings;
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	//���u�����f�B���O��L���ɂ���B
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);

}

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//�V�F�[�_�[��K�p����B
	switch (m_renderMode_Shadow) {
	case enRenderMode_Normal:
		//�ʏ�`��B

		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		switch (m_renderMode) {
		case 0:
			//�ʏ�`��B
			deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
			deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
			break;
		case 1:
			//�V���G�b�g�`��B
			deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSSilhouetteShader->GetBody(), NULL, 0);
			//�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
			deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
			break;
		case 2:
			//���m�N���`��B
			deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSMonochromeShader->GetBody(), NULL, 0);
			deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
			break;
		case 3:
			//���p�`��B
			deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShaderBox->GetBody(), NULL, 0);
			deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
			break;
		case 4:
			//����߂�
			auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
			float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			d3dDeviceContext->OMSetBlendState(
				m_translucentBlendState,	//�ݒ肷��u�����f�B���O�X�e�[�g
				blendFactor,				//�u�����f�B���O�t�@�N�^�[�B�C�ɂ��Ȃ��Ă悢
				0xffffffff					//�T���v�����O�}�X�N�B�C�ɂ��Ȃ��Ă悢�B
			);
			//����߂��`��B
			deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSKiramekiShader->GetBody(), NULL, 0);
			//�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
			deviceContext->OMSetDepthStencilState(m_kiramekiDepthStepsilState, 0);
			break;
		}

		break;
	case enRenderMode_CreateShadowMap:
		//todo �V���h�E�}�b�v�����p�̃V�F�[�_�[��ݒ�B
		//�V���h�E�}�b�v�����B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMapShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMapShader->GetBody(), NULL, 0);
		break;
	}

}
