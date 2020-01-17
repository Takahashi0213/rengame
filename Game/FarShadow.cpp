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
	//初期化。
	m_vs.Load("Assets/shader/farShadow.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/farShadow.fx", "PSMain", Shader::EnType::PS);

	//半透明合成のブレンドステートを作成する。
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
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
	//メインレンダリングターゲットを取得。
	auto mainRT = CGameObjectManager::GetInstance()->GetMainRenderTarget();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());

	//深度テクスチャをt0レジスタに設定する。
	auto depthTexSrv = CGameObjectManager::GetInstance()->GetDepthInViewRenderTarget()->GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &depthTexSrv);

	ID3D11BlendState* oldBlendState;
	float oldBlendFactor[4];
	UINT oldMask;
	deviceContext->OMGetBlendState(&oldBlendState, oldBlendFactor, &oldMask);
	//半透明合成用のブレンディングステートを設定する。
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
	//フルスクリーン描画。
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_ps);

	//ブレンドステートを戻す。
	deviceContext->OMSetBlendState(oldBlendState, oldBlendFactor, oldMask);
	oldBlendState->Release();

}