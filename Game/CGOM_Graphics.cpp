#include "stdafx.h"
#include "CGOM_Graphics.h"


CGOM_Graphics::CGOM_Graphics()
{
	//メインとなるレンダリングターゲットを作成する。
	m_mainRenderTarget.Create(
		(unsigned int)FRAME_BUFFER_W,
		(unsigned int)FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	//カメラ空間での深度値の書き込み先となるレンダリングターゲットを作成する。
	//フォーマットはR成分のみの32ビット浮動小数点バッファ。
	m_depthRenderTarget.Create(
		(unsigned int)FRAME_BUFFER_W,
		(unsigned int)FRAME_BUFFER_H,
		DXGI_FORMAT_R32_FLOAT
	);

	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する。
	m_copyMainRtToFrameBufferSprite.Sprite_Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	m_copyMainRtToFrameBufferSprite.m_isInited = true;

	//半透明合成のブレンドステートを初期化する。
	InitTranslucentBlendState();

	//Effekseerの初期化
	InitEffekseer();

}

CGOM_Graphics::~CGOM_Graphics()
{
	if (m_translucentBlendState != nullptr) {
		m_translucentBlendState->Release();
	}
	if (m_effekseerManager != nullptr) {
		m_effekseerManager->Destroy();
	}
	if (m_effekseerRenderer != nullptr) {
		m_effekseerRenderer->Destroy();
	}
}

void CGOM_Graphics::Init() {
	//ポストエフェクトの初期化。
	m_postEffect.Init();
}

void CGOM_Graphics::InitTranslucentBlendState() {

	//例のごとく、作成するブレンドステートの情報を設定する。
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC blendDesc(defaultSettings);

	//αブレンディングを有効にする。
	blendDesc.RenderTarget[0].BlendEnable = true;

	//ソースカラーのブレンディング方法を指定している。
	//ソースカラーとはピクセルシェーダ―からの出力を指している。
	//この指定では、ソースカラーをSRC(rgba)とすると、
	//最終的なソースカラーは下記のように計算される。
	//最終的なソースカラー = SRC.rgb × SRC.a・・・・・・　①
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	//ディスティネーションカラーのブレンディング方法を指定している。
	//ディスティネーションカラーとは、
	//すでに描き込まれているレンダリングターゲットのカラーを指している。
	//この指定では、ディスティネーションカラーをDEST(rgba)、
	//ソースカラーをSRC(RGBA)とすると、最終的なディスティネーションカラーは
	//下記のように計算される。
	//最終的なディスティネーションカラー = DEST.rgb × (1.0f - SRC.a)・・・・・②
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//最終的にレンダリングターゲットに描き込まれるカラーの計算方法を指定している。
	//この指定だと、①＋②のカラーが書き込まれる。
	//つまり、最終的にレンダリングターゲットに描き込まれるカラーは
	//SRC.rgb × SRC.a + DEST.rgb × (1.0f - SRC.a)
	//となる。
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//この設定で、ブレンドステートを作成すると
	//半透明合成を行えるブレンドステートが作成できる。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);

}
void CGOM_Graphics::InitEffekseer()
{
	//レンダラーを初期化。
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
		g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
		20000										//板ポリの最大数。
	);
	//エフェクトマネージャを初期化。
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// 描画用インスタンスから描画機能を設定
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());

}

void CGOM_Graphics::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
		d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}
void CGOM_Graphics::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
{
	ID3D11RenderTargetView* rtTbl[] = {
		renderTarget
	};
	//レンダリングターゲットの切り替え。
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}

void CGOM_Graphics::Standby() {
	//フレームバッファののレンダリングターゲットをバックアップしておく。
	d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&m_frameBufferRenderTargetView,
		&m_frameBufferDepthStencilView
	);
	ID3D11Resource* res;
	m_frameBufferRenderTargetView->GetResource(&res);
	m_frameBufferTexture = (ID3D11Texture2D*)res;
	D3D11_TEXTURE2D_DESC desc;
	m_frameBufferTexture->GetDesc(&desc);
	m_format = desc.Format;

	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);
	//ポストエフェクトの更新。
	m_postEffect.Update();

	//Effekseerカメラ行列を設定。
	//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
	Effekseer::Matrix44 efCameraMat;
	g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	Effekseer::Matrix44 efProjMat;
	g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	//カメラ行列とプロジェクション行列を設定。
	m_effekseerRenderer->SetCameraMatrix(efCameraMat);
	m_effekseerRenderer->SetProjectionMatrix(efProjMat);
	//Effekseerを更新。
	m_effekseerManager->Update();

}

void CGOM_Graphics::PreRender() {

	///////////////////////////////////////////////
	//シャドウマップにレンダリング
	///////////////////////////////////////////////
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//現在のレンダリングターゲットをバックアップしておく。
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	ShadowMap::GetInstance()->RenderToShadowMap();

	//元に戻す。
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();

}

void CGOM_Graphics::ForwordRender() {

	//レンダリングターゲットを複数設定する。
	//     MRT(Multi rendering target)
	ID3D11RenderTargetView* rts[] = {
		m_mainRenderTarget.GetRenderTargetView(),	//0番目はメインレンダリングターゲット
		m_depthRenderTarget.GetRenderTargetView(),	//1番目はカメラ空間での深度値を出力するレンダリングターゲット。
	};
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->OMSetRenderTargets(
		2,											//第一引数はセットするレンダリングターゲットの数。2つ設定するので2を指定する。
		rts,										//第二引数にはレンダリングターゲットの配列を指定する。
		m_mainRenderTarget.GetDepthStensilView()	//第三引数は深度ステンシルバッファ。これは一つしか指定できない。
	);
	deviceContext->RSSetViewports(1, m_mainRenderTarget.GetViewport());

	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
	m_depthRenderTarget.ClearRenderTarget(clearColor);

}

void CGOM_Graphics::PostRender() {

	//ポストエフェクトの描画。
	m_postEffect.Draw();

	//レンダリングターゲットをフレームバッファに戻す。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(
		d3dDeviceContext,
		m_frameBufferRenderTargetView,
		m_frameBufferDepthStencilView,
		&m_frameBufferViewports
	);
	//ドロドロ
	m_copyMainRtToFrameBufferSprite.Sprite_Draw();

	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();

}

void CGOM_Graphics::EffectRender(bool Mode) {

	m_effekseerRenderer->BeginRendering();
	
	for (auto go = EffekseerSupporter::GetInstance()->g_effectList_P->begin();
		go != EffekseerSupporter::GetInstance()->g_effectList_P->end();
		go++) {

		if ( m_effekseerManager->Exists(go->Handle) == true && go->PostFlag == Mode) {
			//描画する
			m_effekseerManager->DrawHandle(go->Handle);
		}

	}

	m_effekseerRenderer->EndRendering();

}

void CGOM_Graphics::EndSet() {
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//半透明合成のブレンドステートを設定する。
	d3dDeviceContext->OMSetBlendState(
		m_translucentBlendState,	//設定するブレンディングステート
		blendFactor,				//ブレンディングファクター。気にしなくてよい
		0xffffffff					//サンプリングマスク。気にしなくてよい。
	);
}