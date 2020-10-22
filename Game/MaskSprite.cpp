#include "stdafx.h"
#include "MaskSprite.h"

MaskSprite::MaskSprite()
{
	CreateDepthStencilState();
	m_mainSprite.m_renderMode = Sprite_RenderMode::Mask;
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
	m_mainSprite.Sprite_Draw();

	//デプスステンシルステートを切り替える。
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState_Z, 0);

	//サブ（マスク）の描画
	if (m_subSpriteList.size() > 0) {
		for (int i = 0; i < m_subSpriteList.size(); i++) {
			m_subSpriteList[i].sprite->Sprite_Draw();
		}
	}

	//戻す	
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState_Def, 0);

}

Sprite* MaskSprite::AddSubSprite(const wchar_t* texFilePath, float w, float h) {

	//スプライトの生成
	SubSpriteData Data;
	Data.sprite = new Sprite;
	//設定する
	Data.sprite->Sprite_Init(texFilePath, w, h);
	Data.sprite->SetMulColor(m_mainSpriteData.MulColor);
	//データ設定
	Data.subData.Position = m_mainSpriteData.Position;
	Data.subData.Wide = w;
	Data.subData.High = h;
	Data.subData.Rotation = m_mainSpriteData.Rotation;
	Data.subData.Scale = CVector3::One();
	Data.subData.MulColor = m_mainSpriteData.MulColor;
	//Vectorにぶちこみます
	m_subSpriteList.push_back(Data);

	return Data.sprite;
}