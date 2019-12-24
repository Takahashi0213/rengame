#include "stdafx.h"
#include "CGameObjectManager.h"

	CGameObjectManager* CGameObjectManager::m_instance = nullptr;

	CGameObjectManager::CGameObjectManager() {
		if (m_instance != nullptr) {
			std::abort(); //すでに出ているためクラッシュ
		}

		//このインスタンスを唯一のインスタンスとして記録する
		m_instance = this;

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

		//ポストエフェクトの初期化。
		m_postEffect.Init();
		//半透明合成のブレンドステートを初期化する。
		InitTranslucentBlendState();

	}

	CGameObjectManager::~CGameObjectManager() {

		//インスタンスが破棄されたので、nullptrを代入
		m_instance = nullptr;

		if (m_translucentBlendState != nullptr) {
			m_translucentBlendState->Release();
		}
	}

	void CGameObjectManager::InitTranslucentBlendState() {

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

	void CGameObjectManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
	{
		ChangeRenderTarget(
			d3dDeviceContext,
			renderTarget->GetRenderTargetView(),
			renderTarget->GetDepthStensilView(),
			viewport
		);
	}
	void CGameObjectManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
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

	/// <summary>
	/// 更新関数
	/// </summary>
	void CGameObjectManager::Execute() {

		//！アクティブフラグがtrueだと更新されないよ！

		///////////////////////////////////////////////
		//ここから更新処理
		///////////////////////////////////////////////

		//登録されている背景スプライトの更新関数を呼び出す
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_BackSprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		//登録されているゲームオブジェクトの更新関数を呼び出す
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		//登録されているスプライトの更新関数を呼び出す
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}

		///////////////////////////////////////////////
		//ここから描画処理
		///////////////////////////////////////////////

		//フレームバッファののレンダリングターゲットをバックアップしておく。
		auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		d3dDeviceContext->OMGetRenderTargets(
			1,
			&m_frameBufferRenderTargetView,
			&m_frameBufferDepthStencilView
		);
		//ビューポートもバックアップを取っておく。
		unsigned int numViewport = 1;
		d3dDeviceContext->RSGetViewports(&numViewport, &m_frameBufferViewports);
		//ポストエフェクトの更新。
		m_postEffect.Update();

		//プリレンダリング
		PreRender();

		//フォワードレンダリング
		ForwordRender();

		//ポストレンダリング
		PostRender();

		///////////////////////////////////////////////
		//ここから通常レンダリング。
		///////////////////////////////////////////////

		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		//半透明合成のブレンドステートを設定する。
		d3dDeviceContext->OMSetBlendState(
			m_translucentBlendState,	//設定するブレンディングステート
			blendFactor,				//ブレンディングファクター。気にしなくてよい
			0xffffffff					//サンプリングマスク。気にしなくてよい。
		);

		//登録されているスプライトの描画関数を呼び出す
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Render();
				}
			}
		}
		//削除リストに積まれたオブジェクトをまとめて消去する
		ExecuteDeleteGameObjects();

	}

	/// <summary>
	/// 削除する予定のオブジェクトをまとめて消去する
	/// </summary>
	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		//削除リストの要素数分ループする
		for (auto go = m_deleteList.begin();
			go != m_deleteList.end();
			go++) {

			//引数で指定されたゲームオブジェクトを検索
			for (auto it = m_goList.begin();
				it != m_goList.end();
				it++) {

				if (*it == *go) {
					//見つかったので削除
					delete *it; //メモリ解放
					m_goList.erase(it); //可変長配列から除去
					return;
				}
			}
		}

		//削除リストをリセット
		m_deleteList.clear();

	}

	void CGameObjectManager::PreRender() {
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

	void CGameObjectManager::ForwordRender(){

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

		//登録されているスプライトの描画関数を呼び出す
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_BackSprite && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

		//登録されているゲームオブジェクトの描画関数を呼び出す
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Render();
				}
			}
		}

	}

	void CGameObjectManager::PostRender() {

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

