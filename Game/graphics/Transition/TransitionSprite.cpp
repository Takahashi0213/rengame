#include "stdafx.h"
#include "TransitionSprite.h"


TransitionSprite::TransitionSprite()
{
}

TransitionSprite::~TransitionSprite()
{
	//削除するときにメモリを解放する
	if (m_vertexBuffer != NULL) {
		m_vertexBuffer->Release();
	}
	if (m_indexBuffer != NULL) {
		m_indexBuffer->Release();
	}
	if (m_samplerState != NULL) {
		m_samplerState->Release();
	}
	if (m_mainSprite.Texture != NULL) {
		m_mainSprite.Texture->Release();
	}
}

void TransitionSprite::InitCommon(
	const float& w,
	const float& h,
	const bool& cutFlag
){
	m_mainSprite.Size.x = w;
	m_mainSprite.Size.y = h;
	//頂点バッファの初期化
	InitVertexBuffer(m_vertexBuffer, w, h);

	//ここで中断
	if (cutFlag == true) {
		return;
	}

	//インデックスバッファの初期化
	InitIndexBuffer(m_indexBuffer);
	//サンプラステートの初期化
	InitSamplerState(m_samplerState);
	//シェーダーのロード。
	m_vs.Load("Assets/shader/Transition.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/Transition.fx", "PSMain", Shader::EnType::PS);

	//定数バッファを初期化。
	InitConstantBuffer();

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="texFilePath">ファイルパス</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
void TransitionSprite::Sprite_Init(const wchar_t* texFilePath, const float& w, const float& h) {

	InitCommon(w, h);

	//テクスチャをロード。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),				//D3Dデバイス。
		texFilePath,				//読み込む画像データのファイルパス。
		0,                          //今は気にしなくてよい。
		D3D11_USAGE_DEFAULT,		//今は気にしなくてよい。
		D3D11_BIND_SHADER_RESOURCE,	//今は気にしなくてよい。
		0,							//今は気にしなくてよい。
		0,							//今は気にしなくてよい。
		false,						//今は気にしなくてよい。
		nullptr,					//今は気にしなくてよい。
		&m_mainSprite.Texture		//読み込んだテクスチャに
									//アクセスするためのインターフェースの格納先。
	);

	m_isInited = true;
}

/// <summary>
/// 更新
/// </summary>
void TransitionSprite::Sprite_Update() {
	if (m_isInited == false) {
		//初期化されていない
		return;
	}

	//ピボットの計算
	CVector2 localPivot = m_mainSprite.Pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//画像のハーフサイズを求める
	CVector2 halfSize = m_mainSprite.Size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(m_mainSprite.Position);
	mRot.MakeRotationFromQuaternion(m_mainSprite.Rotation);
	mScale.MakeScaling(m_mainSprite.Scale);
	m_mainSprite.World.Mul(mPivotTrans, mScale);
	m_mainSprite.World.Mul(m_mainSprite.World, mRot);
	m_mainSprite.World.Mul(m_mainSprite.World, mTrans);

}

/// <summary>
/// 描画
/// </summary>
void TransitionSprite::Sprite_Draw() {

	if (m_isInited == false) {
		//初期化されていない
		return;
	}

	unsigned int vertexSize = sizeof(SVertex);	//頂点のサイズ。
	unsigned int offset = 0;
	g_graphicsEngine->GetD3DDeviceContext()->IASetVertexBuffers(	//頂点バッファを設定。
		0,					//StartSlot番号。今は0でいい。
		1,					//バッファの数。今は1でいい。
		&m_vertexBuffer,	//頂点バッファ。
		&vertexSize,		//頂点のサイズ。
		&offset				//気にしなくてよい。
	);
	g_graphicsEngine->GetD3DDeviceContext()->IASetIndexBuffer(	//インデックスバッファを設定。
		m_indexBuffer,			//インデックスバッファ。
		DXGI_FORMAT_R32_UINT,	//インデックスのフォーマット。
								//今回は32bitなので、DXGI_FORMAT_R32_UINTでいい。
		0						//オフセット0でいい。
	);

	//テクスチャを設定。
	g_graphicsEngine->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &m_mainSprite.Texture);
	//サンプラステートを設定。
	g_graphicsEngine->GetD3DDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

	//ワールドビュープロジェクション行列を作成。
	ConstantBuffer cb;
	cb.WVP = m_mainSprite.World;
	cb.WVP.Mul(cb.WVP, g_camera2D.GetViewMatrix());
	cb.WVP.Mul(cb.WVP, g_camera2D.GetProjectionMatrix());
	cb.Alpha = m_alpha;

	g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	g_graphicsEngine->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m_cb);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetConstantBuffers(0, 1, &m_cb);

	g_graphicsEngine->GetD3DDeviceContext()->IASetInputLayout(m_vs.GetInputLayout());
	g_graphicsEngine->GetD3DDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);

	g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);

	//プリミティブのトポロジーは
	//トライアングルストリップを設定する。
	g_graphicsEngine->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_graphicsEngine->GetD3DDeviceContext()->DrawIndexed(	//描画命令。
		6,				//インデックス数。
		0,				//開始インデックス番号。0でいい。
		0				//開始頂点番号。0でいい。
	);

}

void TransitionSprite::InitConstantBuffer() {

	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_cb);

}