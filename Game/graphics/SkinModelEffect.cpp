#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

ModelEffect::ModelEffect()
{
	m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
	m_psMonochrome.Load("Assets/shader/model.fx", "PSMain_Monochrome", Shader::EnType::PS);
	//シャドウマップ
	m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", Shader::EnType::PS);
	m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", Shader::EnType::VS);
	//箱用シェーダー
	m_psShader_Box.Load("Assets/shader/box_model.fx", "PSMain", Shader::EnType::PS);
	//きらめき
	m_psShader_Kirameki.Load("Assets/shader/model.fx", "PSMain_Kirameki", Shader::EnType::PS);

	m_pPSShader = &m_psShader;
	m_pPSSilhouetteShader = &m_psSilhouette;
	m_pPSMonochromeShader = &m_psMonochrome;
	m_vsShadowMapShader = &m_vsShadowMap;
	m_psShadowMapShader = &m_psShadowMap;
	m_pPSShaderBox = &m_psShader_Box;
	m_pPSKiramekiShader = &m_psShader_Kirameki;

	//デプスステンシルの初期化。
	InitSilhouettoDepthStepsilState();
	//ブレンドステートの初期化
	InitTranslucentBlendState();
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

	desc = { 0 };
	desc.DepthEnable = true;						   //Zテストが有効。
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //ZバッファにZ値を描き込まない。
	desc.DepthFunc = D3D11_COMPARISON_EQUAL;		   //Z値が大きければフレームバッファに描き込む。
	pd3d->CreateDepthStencilState(&desc, &m_kiramekiDepthStepsilState);

}

void ModelEffect::InitTranslucentBlendState() {

	CD3D11_DEFAULT defaultSettings;
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	//αブレンディングを有効にする。
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);

}

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//シェーダーを適用する。
	switch (m_renderMode_Shadow) {
	case enRenderMode_Normal:
		//通常描画。

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
		case 3:
			//箱用描画。
			deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShaderBox->GetBody(), NULL, 0);
			deviceContext->PSSetShaderResources(0, 1, &m_albedoTex);
			break;
		case 4:
			//きらめき
			auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
			float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			d3dDeviceContext->OMSetBlendState(
				m_translucentBlendState,	//設定するブレンディングステート
				blendFactor,				//ブレンディングファクター。気にしなくてよい
				0xffffffff					//サンプリングマスク。気にしなくてよい。
			);
			//きらめき描画。
			deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSKiramekiShader->GetBody(), NULL, 0);
			//デプスステンシルステートを切り替える。
			deviceContext->OMSetDepthStencilState(m_kiramekiDepthStepsilState, 0);
			break;
		}

		break;
	case enRenderMode_CreateShadowMap:
		//todo シャドウマップ生成用のシェーダーを設定。
		//シャドウマップ生成。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMapShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMapShader->GetBody(), NULL, 0);
		break;
	}

}
