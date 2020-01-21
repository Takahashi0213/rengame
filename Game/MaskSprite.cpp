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
	desc = { 0 };
	desc.DepthEnable = true;					 //Zテストが有効。
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; //ZバッファにZ値を描き込む。
	desc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;		 //Z値が同じならフレームバッファに描き込む。
	//デプスステンシルステートを作成。
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState_Z);

	//作成する深度ステンシルステートの定義を設定していく。
	desc.DepthEnable = false;						 
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; 
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	//デプスステンシルステートを作成。
	pd3d->CreateDepthStencilState(&desc, &m_depthStencilState_Def);

}

void MaskSprite::Draw() {

	//フレームバッファのZ値を初期化する
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = CGameObjectManager::GetInstance()->GetFrameBufferDepthStencilView();
	g_graphicsEngine->GetD3DDeviceContext()->ClearDepthStencilView(m_frameBufferDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//デプスステンシルステートを切り替える。
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState, 0);

	//マスクをかけられるスプライトの描画
	m_subSprite.Sprite_Draw();

	//デプスステンシルステートを切り替える。
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState_Z, 0);

	//マスクのスプライトの描画
	m_mainSprite.Sprite_Draw();

	//戻す	
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState_Def, 0);

}