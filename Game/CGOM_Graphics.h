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
	/// エフェクサー描画
	/// </summary>
	void EffectRender(bool Mode);

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void CGOM_Graphics::DebugDraw();

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

	/// <summary>
	/// エフェクサーマネージャーを取得
	/// </summary>
	Effekseer::Manager* GetEffekseerManager() {
		return m_effekseerManager;
	}
	EffekseerRenderer::Renderer* GetEffekseerRender() {
		return m_effekseerRenderer;
	}

	ID3D11Texture2D* GetFrameBufferTexture() {
		return m_frameBufferTexture;
	}
	DXGI_FORMAT GetFormat() {
		return m_format;
	}


private:
	/// <summary>
	/// 半透明合成のブレンドステートを初期化。
	/// </summary>
	void InitTranslucentBlendState();

	/// <summary>
	/// Effekseerの初期化。
	/// </summary>
	void InitEffekseer();

	RenderTarget m_mainRenderTarget;									//メインレンダリングターゲット。
	RenderTarget m_depthRenderTarget;									//深度値の書き込み先となるレンダリングターゲット。

	ID3D11Texture2D* m_frameBufferTexture = nullptr;
	DXGI_FORMAT m_format;

	Sprite m_copyMainRtToFrameBufferSprite;								//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
	ID3D11DeviceContext* d3dDeviceContext;

	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。

	PostEffect m_postEffect;		//ポストエフェクト

	//Effekseerマネージャ管理。
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	/// <summary>
	/// レンダリングターゲットの切り替え。
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void CGOM_Graphics::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void CGOM_Graphics::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

};

