#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
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
	if (m_subSprite.Texture != NULL) {
		m_subSprite.Texture->Release();
	}
}

/// <summary>
/// 初期化の共通処理。
/// </summary>
void Sprite::InitCommon(float w, float h)
{
	m_mainSprite.Size.x = w;
	m_mainSprite.Size.y = h;
	//頂点バッファの初期化
	InitVertexBuffer(m_vertexBuffer, w, h);
	//インデックスバッファの初期化
	InitIndexBuffer(m_indexBuffer);
	//サンプラステートの初期化
	InitSamplerState(m_samplerState);
	//シェーダーのロード。
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_ps_X_Cut.Load("Assets/shader/sprite.fx", "PSMain_X_Cut", Shader::EnType::PS);
	m_ps_Y_Cut.Load("Assets/shader/sprite.fx", "PSMain_Y_Cut", Shader::EnType::PS);

	//定数バッファを初期化。
	InitConstantBuffer();

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="texFilePath">ファイルパス</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
void Sprite::Sprite_Init(const wchar_t* texFilePath, float w, float h) {

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
void Sprite::Sprite_Init_Sub(const wchar_t* texFilePath, float w, float h) {

	m_subSprite.Size.x = w;
	m_subSprite.Size.y = h;

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
		&m_subSprite.Texture		//読み込んだテクスチャに
									//アクセスするためのインターフェースの格納先。
	);
}
void Sprite::Sprite_Init(ID3D11ShaderResourceView* srv, float w, float h)
{
	//共通の初期化処理を呼び出す。
	InitCommon(w, h);
	m_mainSprite.Texture = srv;
	m_mainSprite.Texture->AddRef();	//参照カウンタを増やす。
}
void Sprite::Sprite_Init_Sub(ID3D11ShaderResourceView* srv, float w, float h)
{
	m_subSprite.Size.x = w;
	m_subSprite.Size.y = h;
	m_subSprite.Texture = srv;
	m_subSprite.Texture->AddRef();	//参照カウンタを増やす。
}

/// <summary>
/// 更新
/// </summary>
/// <param name="pos">平行移動</param>
/// <param name="rot">回転</param>
/// <param name="scale">拡大</param>
/// <param name="pivot">基点</param>
void Sprite::Sprite_Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot) {

	if (m_isInited == false) {
		//初期化されていない
		return;
	}

	//ピボットの計算
	CVector2 localPivot = pivot;
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
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_mainSprite.World.Mul(mPivotTrans, mScale);
	m_mainSprite.World.Mul(m_mainSprite.World, mRot);
	m_mainSprite.World.Mul(m_mainSprite.World, mTrans);

}
void Sprite::Sprite_Update_Sub(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot) {

	if (m_isInited == false) {
		//初期化されていない
		return;
	}
	if (m_subSprite.Texture == NULL) {
		//設定されていない
		return;
	}

	//ピボットの計算
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//画像のハーフサイズを求める
	CVector2 halfSize = m_subSprite.Size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_subSprite.World.Mul(mPivotTrans, mScale);
	m_subSprite.World.Mul(m_subSprite.World, mRot);
	m_subSprite.World.Mul(m_subSprite.World, mTrans);

}

/// <summary>
/// 描画
/// </summary>
void Sprite::Sprite_Draw() {

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
	cb.mulColor = m_mainSprite.MulColor;
	cb.cut_line = m_cut_UV;

	g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	g_graphicsEngine->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m_cb);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetConstantBuffers(0, 1, &m_cb);

	g_graphicsEngine->GetD3DDeviceContext()->IASetInputLayout(m_vs.GetInputLayout());
	g_graphicsEngine->GetD3DDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);

	//ステートによってPSを変更
	switch (m_renderMode)
	{
	case Normal:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
		break;
	case X_Cut:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps_X_Cut.GetBody(), NULL, 0);
		break;
	case Y_Cut:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps_Y_Cut.GetBody(), NULL, 0);
		break;
	}
	//プリミティブのトポロジーは
	//トライアングルストリップを設定する。
	g_graphicsEngine->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_graphicsEngine->GetD3DDeviceContext()->DrawIndexed(	//描画命令。
		6,				//インデックス数。
		0,				//開始インデックス番号。0でいい。
		0				//開始頂点番号。0でいい。
	);


}

/// <summary>
/// 定数バッファの初期化
/// </summary>
void Sprite::InitConstantBuffer() {

	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_cb);

}