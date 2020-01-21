#pragma once
#include "RenderTarget.h"
#include "Sprite.h"
#include "PostEffect.h"

/// <summary>
/// ゲームオブジェクトマネージャーのグラフィック関連
/// </summary>
class CGOM_Graphics
{
public:
	CGOM_Graphics();
	~CGOM_Graphics();
	void Init();

	/// <summary>
	/// 準備
	/// </summary>
	void Standby();
	/// <summary>
	/// プリレンダー
	/// </summary>
	void CGOM_Graphics::PreRender();
	/// <summary>
	/// フォワードレンダー
	/// </summary>
	void CGOM_Graphics::ForwordRender();
	/// <summary>
	/// ポストレンダー
	/// </summary>
	void CGOM_Graphics::PostRender();
	/// <summary>
	/// レンダー群が終わった後に呼ぶ
	/// </summary>
	void EndSet();

	/// <summary>
	/// メインレンダリングターゲットを取得
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	/// <summary>
	/// カメラ空間での深度値を書き込んでいるレンダリングターゲットを取得。
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetDepthInViewRenderTarget()
	{
		return &m_depthRenderTarget;
	}

	/// <summary>
	/// フレームバッファのデプスステンシルビューを取得
	/// </summary>
	/// <returns></returns>
	ID3D11DepthStencilView* GetFrameBufferDepthStencilView() {
		return m_frameBufferDepthStencilView;
	}

private:
	/// <summary>
	/// 半透明合成のブレンドステートを初期化。
	/// </summary>
	void InitTranslucentBlendState();

	RenderTarget m_mainRenderTarget;									//メインレンダリングターゲット。
	RenderTarget m_depthRenderTarget;									//深度値の書き込み先となるレンダリングターゲット。

	Sprite m_copyMainRtToFrameBufferSprite;								//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	ID3D11DeviceContext* d3dDeviceContext;

	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。

	PostEffect m_postEffect;		//ポストエフェクト

	/// <summary>
	/// レンダリングターゲットの切り替え。
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void CGOM_Graphics::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void CGOM_Graphics::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

};

