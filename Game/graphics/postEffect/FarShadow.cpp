#include "stdafx.h"
#include "FarShadow.h"


FarShadow::~FarShadow()
{
	if (m_finalBlendState != nullptr) {
		m_finalBlendState->Release();
	}
}

void FarShadow::Init()
{
	//�������B
	m_vs.Load("Assets/shader/farShadow.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/farShadow.fx", "PSMain", Shader::EnType::PS);

	//�����������̃u�����h�X�e�[�g���쐬����B
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�Z�b�e�B���O�ŏ���������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	auto device = g_graphicsEngine->GetD3DDevice();

	device->CreateBlendState(&blendDesc, &m_finalBlendState);
}

void FarShadow::Draw(PostEffect& postEffect)
{
	//���C�������_�����O�^�[�Q�b�g���擾�B
	auto mainRT = CGameObjectManager::GetInstance()->GetMainRenderTarget();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());

	//�[�x�e�N�X�`����t0���W�X�^�ɐݒ肷��B
	const auto& depthTexSrv = CGameObjectManager::GetInstance()->GetDepthInViewRenderTarget()->GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &depthTexSrv);

	ID3D11BlendState* oldBlendState;
	float oldBlendFactor[4];
	UINT oldMask;
	deviceContext->OMGetBlendState(&oldBlendState, oldBlendFactor, &oldMask);
	//�����������p�̃u�����f�B���O�X�e�[�g��ݒ肷��B
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
	//�t���X�N���[���`��B
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_ps);

	//�u�����h�X�e�[�g��߂��B
	deviceContext->OMSetBlendState(oldBlendState, oldBlendFactor, oldMask);
	oldBlendState->Release();

}