#include "stdafx.h"
#include "PostEffect.h"
#include "Game.h"

PostEffect::PostEffect()
{
	//フルスクリーン描画のための四角形プリミティブを初期化。
	InitFullScreenQuadPrimitive();

	//半透明合成のブレンドステートを作成する。
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	auto device = g_graphicsEngine->GetD3DDevice();

	device->CreateBlendState(&blendDesc, &m_blendState);

	//シェーダー
	m_vs.Load("Assets/shader/Blur.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/Blur.fx", "PSMain", Shader::EnType::PS);

}

PostEffect::~PostEffect()
{
	if (m_vertexBuffer != nullptr) {
		m_vertexBuffer->Release();
	}
	if (m_blendState != nullptr) {
		m_blendState->Release();
	}
}


void PostEffect::Init() 
{
	m_farShadow.Init();
	m_dof.Init();
}
void PostEffect::Update()
{
}

void PostEffect::Draw()
{
	//Game::GameMode NowGameMode = Game::GetInstance()->GetGameMode();		//現在のゲームモードを呼び出す
	Game::GameMode NowGameMode = Game::GameMode::ActionMode;

	if (NowGameMode == Game::CreateMode) {
		//遠い場所を暗くする処理（クリエイト限定）
		//m_farShadow.Draw(*this);
	}

	//ブルーム。
	m_bloom.Draw(*this);
	//ドフ。
	m_dof.Draw(*this);

	//画面にブラーをかける
	if (Game::GetInstance() != nullptr) {
		if (Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity > 0.0f) {
			BlurDraw();
		}
	}
}

void PostEffect::InitFullScreenQuadPrimitive()
{
	//頂点バッファを初期化。
	SVertex vertex[4] = {
		//頂点１
		{
			//座標　position[4]
			-1.0f,  -1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 1.0f
		},
		//頂点２
		{
			//座標　position[4]
			1.0f, -1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 1.0f
		},
		//頂点３
		{
			//座標　position[4]
			-1.0f,  1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 0.0f
		},
		//頂点４
		{
			//座標　position[4]
			1.0f,  1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 0.0f
		},
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//構造体を0で初期化する。
	bd.Usage = D3D11_USAGE_DEFAULT;				//バッファーで想定されている読み込みおよび書き込みの方法。
												//取りあえずはD3D11_USAGE_DEFAULTでよい。
	bd.ByteWidth = sizeof(vertex);				//頂点バッファのサイズ。頂点のサイズ×頂点数となる。
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//これから作成するバッファが頂点バッファであることを指定する。

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	//頂点バッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
}

void PostEffect::DrawFullScreenQuadPrimitive(ID3D11DeviceContext* deviceContext, Shader& vsShader, Shader& psShader)
{
	//プリミティブのトポロジーとして、トライアングルストリップを設定する。
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	unsigned int vertexSize = sizeof(SVertex);
	unsigned int offset = 0;
	//輝度抽出用のシェーダーを設定する。
	deviceContext->VSSetShader(
		(ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0
	);
	deviceContext->PSSetShader(
		(ID3D11PixelShader*)psShader.GetBody(), nullptr, 0
	);
	deviceContext->IASetInputLayout(vsShader.GetInputLayout());

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);
	deviceContext->Draw(4, 0);
}

void PostEffect::BlurDraw() {

	//メインレンダリングターゲットを取得。
	auto mainRT = CGameObjectManager::GetInstance()->GetMainRenderTarget();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//ガウシアンブラーの初期化と実行
	if (m_blurInitFlag == false) {
		m_gaussianBlur.Init(CGameObjectManager::GetInstance()->GetMainRenderTarget()->GetRenderTargetSRV(),
			Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity);
		m_blurInitFlag = true;
	}
	m_gaussianBlur.Execute(*this);

	g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());

	//ボケ画像のアドレスをt0レジスタに設定する。
	auto srv = m_gaussianBlur.GetResultTextureSRV();
	deviceContext->PSSetShaderResources(0, 1, &srv);

	ID3D11BlendState* oldBlendState;
	float oldBlendFactor[4];
	UINT oldMask;
	deviceContext->OMGetBlendState(&oldBlendState, oldBlendFactor, &oldMask);
	//半透明合成用のブレンディングステートを設定する。
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(m_blendState, blendFactor, 0xffffffff);
	//フルスクリーン描画。
	DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_ps);

	//ブレンドステートを戻す。
	deviceContext->OMSetBlendState(oldBlendState, oldBlendFactor, oldMask);
	oldBlendState->Release();

}