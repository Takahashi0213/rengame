#include "stdafx.h"
#include "SpriteStandby.h"

/// <summary>
/// 頂点バッファの初期化
/// </summary>
/// <param name="vertexBuffer">頂点バッファ</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
extern void InitVertexBuffer(ID3D11Buffer*& vertexBuffer, float w, float h) {

	//準備！
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	//頂点を設定
	SVertex vertex[4] = {
		//頂点1
		{
			-halfW, -halfH, 0.0f, 1.0f, //ポジション
			0.0f, 1.0f, //UV座標
		},
		//頂点2
		{
			halfW, -halfH, 0.0f, 1.0f, //ポジション
			1.0f, 1.0f, //UV座標
		},
		//頂点3
		{
			-halfW, halfH, 0.0f, 1.0f, //ポジション
			0.0f, 0.0f, //UV座標
		},
		//頂点4
		{
			halfW, halfH, 0.0f, 1.0f, //ポジション
			1.0f, 0.0f, //UV座標
		},
	};
	//頂点バッファを作成する
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd)); //0で初期化
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(vertex); //頂点バッファのサイズを設定
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //これから作成するバッファが頂点バッファであることを指定する

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex; //リソースデータのポインタを指定する

	//作りま～～～
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &vertexBuffer);

}

/// <summary>
/// インデックスバッファの初期化
/// </summary>
/// <param name="indexBuffer">インデックスバッファ</param>
extern void InitIndexBuffer(ID3D11Buffer*& indexBuffer) {

	//頂点番号
	int index[6] = {
		0,1,2, //三角形一つ目
		2,1,3 //三角形二つ目
	};
	//インデックスバッファを作成する
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd)); //0で初期化
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index); //インデックスバッファのサイズを設定
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER; //これから作成するバッファがインデックスバッファであることを指定する

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = index; //リソースデータのポインタを指定する

	//作ります
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &indexBuffer);

}

/// <summary>
/// サンプラステートの初期化
/// </summary>
/// <param name="samplerState">サンプラステート</param>
extern void InitSamplerState(ID3D11SamplerState*& samplerState) {

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//作りま～～～
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &samplerState);

}