#pragma once

/// <summary>
/// 頂点バッファの初期化
/// </summary>
/// <param name="vertexBuffer">頂点バッファ</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
extern void InitVertexBuffer(ID3D11Buffer*& vertexBuffer, float w, float h);

/// <summary>
/// インデックスバッファの初期化
/// </summary>
/// <param name="indexBuffer">インデックスバッファ</param>
extern void InitIndexBuffer(ID3D11Buffer*& indexBuffer);

/// <summary>
/// サンプラステートの初期化
/// </summary>
/// <param name="samplerState">サンプラステート</param>
extern void InitSamplerState(ID3D11SamplerState*& samplerState);

struct SVertex {
	float position[4];		//頂点座標
	float uv[2];			//UV座標。これがテクスチャ座標
};
