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
	//D3Dデバイスを取得。
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//作成する深度ステンシルステートの定義を設定していく。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;					 //Zテストが有効。
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //ZバッファにZ値を描き込む。
	desc.DepthFunc = D3D11_COMPARISON_LESS;		 //Z値が小さければフレームバッファに描き込む。
	//デプスステンシルステートを作成。
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState);

	//作成する深度ステンシルステートの定義を設定していく。
	desc.DepthEnable = false;						 
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; 
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	//デプスステンシルステートを作成。
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState2);

}

void MaskSprite::Draw() {

	//デプスステンシルステートを切り替える。
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState, 0);

	m_subSprite.Sprite_Draw();
	m_mainSprite.Sprite_Draw();

	//戻す	
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState2, 0);

}