#include "stdafx.h"
#include "GameFont.h"


GameFont::GameFont()
{

	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_spriteFont = g_graphicsEngine->GetSpriteFont();

	auto& ge = g_graphicsEngine;
	m_scaleMat.MakeScaling(
		{
			//ge.GetFrameBufferWidth() / static_cast<float>(FRAME_BUFFER_W),
			//ge.GetFrameBufferHeight() / static_cast<float>(FRAME_BUFFER_H),
			FRAME_BUFFER_W / static_cast<float>(FRAME_BUFFER_W),
			FRAME_BUFFER_H / static_cast<float>(FRAME_BUFFER_H),
			1.0f
		}
	);

}


GameFont::~GameFont()
{
	if (m_translucentBlendState != nullptr) {
		m_translucentBlendState->Release();
	}
}

/// <summary>
/// ステートの設定。
/// </summary>
void GameFont::InitTranslucentBlendState() {

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
	//最終的なソースカラー = SRC.rgb × SRC.a・・・・・・　�@
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	//ディスティネーションカラーのブレンディング方法を指定している。
	//ディスティネーションカラーとは、
	//すでに描き込まれているレンダリングターゲットのカラーを指している。
	//この指定では、ディスティネーションカラーをDEST(rgba)、
	//ソースカラーをSRC(RGBA)とすると、最終的なディスティネーションカラーは
	//下記のように計算される。
	//最終的なディスティネーションカラー = DEST.rgb × (1.0f - SRC.a)・・・・・�A
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//最終的にレンダリングターゲットに描き込まれるカラーの計算方法を指定している。
	//この指定だと、�@＋�Aのカラーが書き込まれる。
	//つまり、最終的にレンダリングターゲットに描き込まれるカラーは
	//SRC.rgb × SRC.a + DEST.rgb × (1.0f - SRC.a)
	//となる。
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//この設定で、ブレンドステートを作成すると
	//半透明合成を行えるブレンドステートが作成できる。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);

}

void GameFont::Begin()
{
	//InitTranslucentBlendState();

	//レンダリングステートを退避させる。
	//rc.PushRenderState();

	m_spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		m_translucentBlendState,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		m_scaleMat
	);
}

void GameFont::End()
{
	m_spriteBatch->End();
	//レンダリングステートを復活させる。
	//rc.PopRenderState(true);
}

void GameFont::Draw(
	wchar_t const* text,
	const CVector2& position,
	const CVector4& color,
	float rotation,
	float scale,
	CVector2 pivot)
{
	if (text == nullptr) {
		return;
	}
	pivot.y = 1.0f - pivot.y;
	DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
	//座標系をスプライトと合わせる。
	CVector2 pos = position;
	float frameBufferHalfWidth = FRAME_BUFFER_W * 0.5f;
	float frameBufferHalfHeight = FRAME_BUFFER_H * 0.5f;
	pos.x += frameBufferHalfWidth;
	pos.y = -pos.y + frameBufferHalfHeight;

	if (m_isDrawShadow) {
		//影を書く。
		CVector2 offsetTbl[] = {
			{ m_shadowOffset , 0.0f },
		{ -m_shadowOffset , 0.0f },
		{ 0.0f , m_shadowOffset },
		{ 0.0f , -m_shadowOffset },

		{ m_shadowOffset ,  m_shadowOffset },
		{ m_shadowOffset ,  -m_shadowOffset },
		{ -m_shadowOffset , m_shadowOffset },
		{ -m_shadowOffset , -m_shadowOffset },
		};
		for (auto offset : offsetTbl) {

			CVector2 sPos = pos;
			sPos.x += offset.x;
			sPos.y += offset.y;
			m_spriteFont->DrawString(
				m_spriteBatch,
				text,
				sPos.vec,
				m_shadowColor,
				rotation,
				DirectX::XMFLOAT2(pivot.x, pivot.y),
				scale
			);
		}

	}

	m_spriteFont->DrawString(
		m_spriteBatch,
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		scale
	);
}
