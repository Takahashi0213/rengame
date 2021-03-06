/*!
 * @brief	箱用モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
//todo シャドウマップ
Texture2D<float4> g_shadowMap : register(t2);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/// 
static const int MAX_DIRECTION_LIGHT = 5;	//!<ディレクションライトの最大数。

/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
	int isHasNormalMap;	//法線マップある？
	int isHasSpecMap;	//スペキュラマップある？
	int isHasAOMap;		//アンビエントオクリュージョンマップある？
	int isHasKirameki;		//きらめきを保持している？
	float mHigh;
	float mWide;			//画面の縦横
	float emissionColor_R;
	float emissionColor_G;
	float emissionColor_B;
};
/*!
*@brief	ライト用の定数バッファ。
*/
struct SDirectionLight{
	float3 direction[MAX_DIRECTION_LIGHT];
	float4 color[MAX_DIRECTION_LIGHT];
};

/// <summary>
/// シャドウマップ用の定数バッファ。
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
}

/*!
*@brief	環境光用の定数バッファ。
*/
cbuffer Ambient_LightCb : register(b2) {
	float Ambient_R;
	float Ambient_G;
	float Ambient_B;
};

/*!
*@brief	ライト用の定数バッファ。
*/
cbuffer LightCb : register(b3) {
	SDirectionLight		directionLight;		//ディレクションライト。
	float3				eyePos;				//カメラの視点。
	float				specPow;			//スペキュラライトの絞り。
};

/// /////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
	float4 posInView	: TEXCOORD3;	//カメラ空間での座標。
};
/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};
///複数のレンダリングターゲットに出力するために、構造体を用意。
/// <summary>
/// ピクセルシェーダーからの出力構造体。
/// </summary>
struct PSOutput {
	float4 color		: SV_Target0;	//0番目のレンダリングターゲットに出力される。
	float depthInView : SV_Target1;	//1番目のレンダリングターゲットに出力される。
};
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);

	psInput.worldPos = pos;
	pos = mul(mView, pos);
	//カメラ空間での座標をピクセルシェーダーで使うので、保存しておく。
	psInput.posInView = pos;

	pos = mul(mProj, pos);
	psInput.Position = pos;
	float4 worldPos_ = mul(mWorld, In.Position);

	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, worldPos_);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;

	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	//カメラ空間での座標をピクセルシェーダーで使うので、保存しておく。
	psInput.posInView = pos;


	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
PSOutput PSMain(PSInput In)
{
	PSOutput psOut = (PSOutput)0;

	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//float3 hoge = float3(0.0f, -1.0f, 0.0f);
	//float4 hoge2 = float4( 0.0f,0.8f, 0.0f, 1.0f );

	//ディレクションライトの拡散反射光を計算する。
	float3 lig = 0;
	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {

		//lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
		lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;

		//ディレクションライトの鏡面反射光を計算する。
		{
			float3 R = directionLight.direction[i] + (2 * dot(In.Normal, -directionLight.direction[i]))*In.Normal;

			float3 E = normalize(In.worldPos - eyePos);

			float specPower = max(0, dot(R, -E));

			finalColor = float4(directionLight.color[i].xyz*pow(specPower, specPow), 1);

		}

	}

	//環境光をあてる。
	lig += float3(Ambient_R, Ambient_G, Ambient_B);

	if (isShadowReciever == 1) {	//シャドウレシーバー。
		
		//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//シャドウマップの範囲内かどうかを判定する。

		///LVP空間での深度値を計算。
		float zInLVP = In.posInLVP.z / In.posInLVP.w;
		//シャドウマップに書き込まれている深度値を取得。
		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

		if (shadowMapUV.x > 0.0f &&
			shadowMapUV.x < 1.0f &&
			shadowMapUV.y > 0.0f &&
			shadowMapUV.y < 1.0f &&
			zInLVP > zInShadowMap + 0.01f) {
			//影が落ちているので、光を弱くする
			lig *= 0.5f;
		}
	}

	finalColor.xyz += albedoColor.xyz * lig;
	//return finalColor;

	//カラーを出力。
	psOut.color = finalColor;
	//カメラ座標系でのZ値を出力。
	psOut.depthInView = In.posInView.z;

	//色変更
	psOut.color.r += emissionColor_R;
	psOut.color.g += emissionColor_G;
	psOut.color.b += emissionColor_B;

	return psOut;

}

//--------------------------------------------------------------------------------------
// シャドウマップ生成用の頂点シェーダー。
//--------------------------------------------------------------------------------------
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}

//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}