#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

ModelEffect::ModelEffect()
{
	m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
	m_psMonochrome.Load("Assets/shader/model.fx", "PSMain_Monochrome", Shader::EnType::PS);

	m_pPSShader = &m_psShader;
	m_pPSSilhouetteShader = &m_psSilhouette;
	m_pPSMonochromeShader = &m_psMonochrome;

	//デプスステンシルの初期化。
	InitSilhouettoDepthStepsilState();

}

void ModelEffect::InitSilhouettoDepthStepsilState() {
	//D3Dデバイスを取得。
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//作成する深度ステンシルステートの定義を設定していく。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Zテストが有効。
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //ZバッファにZ値を描き込まない。
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z値が大きければフレームバッファに描き込む。

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);

}

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//シェーダーを適用する。
	deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
	switch (m_renderMode) {
	case 0:
		//通常描画。
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
		break;
	case 1:
		//シルエット描画。
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSSilhouetteShader->GetBody(), NULL, 0);
		//デプスステンシルステートを切り替える。
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;
	case 2:
		//モノクロ描画。
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSMonochromeShader->GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
		break;
	}

	/*
	deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
	deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
	deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
	*/
}
