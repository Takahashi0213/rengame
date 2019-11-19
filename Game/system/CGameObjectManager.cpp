#include "stdafx.h"
#include "CGameObjectManager.h"

	CGameObjectManager* CGameObjectManager::m_instance = nullptr;

	CGameObjectManager::CGameObjectManager() {
		if (m_instance != nullptr) {
			std::abort(); //すでに出ているためクラッシュ
		}

		//このインスタンスを唯一のインスタンスとして記録する
		m_instance = this;

	}

	CGameObjectManager::~CGameObjectManager() {

		//インスタンスが破棄されたので、nullptrを代入
		m_instance = nullptr;

	}

	/// <summary>
	/// 更新関数
	/// </summary>
	void CGameObjectManager::Execute() {

		//！アクティブフラグがtrueだと更新されないよ！

		//登録されているゲームオブジェクトの更新関数を呼び出す
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Update();
				}
			}
		}
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Sprite && go->GetPriority() == i) {
					go->Update();
				}
			}
		}

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

		///////////////////////////////////////////////
		//ここから通常レンダリング。
		///////////////////////////////////////////////

		//登録されているゲームオブジェクトの描画関数を呼び出す
		for (int i = 0; i < MAX_PRIORITY; i++) { //優先度
			for (auto go : m_goList) {
				if (go->GetActiveFlag() == true && go->GetObjectTag() == IGameObject::t_Other && go->GetPriority() == i) {
					go->Render();
				}
			}
		}
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

