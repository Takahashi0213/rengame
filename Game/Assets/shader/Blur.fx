/*!
 *@brief	ブラーー
 */

/*!
 *@brief	頂点シェーダーの入力。
 */
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

/*!
 *@brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> bokeTexture : register(t0);			//ボケテクスチャ。
sampler Sampler : register(s0);


/*!
 * @brief	頂点シェーダー。
 */
PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

/////////////////////////////////////////////////////////
// 最終合成用のピクセルシェーダー。
/////////////////////////////////////////////////////////
float4 PSMain(PSInput psIn) : SV_Target0
{
	return float4(bokeTexture.Sample(Sampler, psIn.uv).xyz, 1.0f);
}

