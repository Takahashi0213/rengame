/*!
 * @brief	モデルシェーダー。
 */

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);
Texture2D<float4> g_shadowMap : register(t2);		//　シャドウマップ
Texture2D<float4> g_normalMap : register(t3);		//	法線マップ。
Texture2D<float4> g_specMap : register(t4);			//	スペキュラマップ。
Texture2D<float4> g_aoMap : register(t5);			//	AOマップ。
Texture2D<float4> g_kirameki : register(t6);		//	きらめき。

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/// 
static const int MAX_DIRECTION_LIGHT = 5;	//!<ディレクションライトの最大数。
static const int MAX_POINT_LIGHT = 16;		//!<ポイントライトの最大数。

/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
	int isHasNormalMap;		//法線マップある？
	int isHasSpecMap;		//スペキュラマップある？
	int isHasAOMap;			//アンビエントオクリュージョンマップある？
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
	float4 direction[MAX_DIRECTION_LIGHT];
	float4 color[MAX_DIRECTION_LIGHT];
};
struct SPointLight {
	float3 position[MAX_POINT_LIGHT];
	float4 color[MAX_POINT_LIGHT];
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
	SPointLight			pointLight;			//ポイントライト。
	float3				eyePos;				//カメラの視点。
	float				specPow;			//スペキュラライトの絞り。
};

/// <summary>
/// ディザリング用の定数バッファ。
/// </summary>
cbuffer DitheringCb : register(b4) {
	int isDithering;						//ディザリングフラグ。
	float4				playerPos;			//プレイヤーの座標。
}

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
	float4 posInProj	: TEXCOORD4;	//正規化スクリーン座標系の座標
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
	float depthInView	: SV_Target1;	//1番目のレンダリングターゲットに出力される。
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
	psInput.posInProj = pos;
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
		psInput.worldPos = pos;
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	//カメラ空間での座標をピクセルシェーダーで使うので、保存しておく。
	psInput.posInView = pos;

	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;

	psInput.TexCoord = In.TexCoord;
    return psInput;
}

/// <summary>
/// 法線を計算する。
/// </summary>
float3 CalcNormal(float3 normal, float3 tangent, float2 uv)
{
	float3 worldSpaceNormal;
	if (isHasNormalMap == 1) {
		//法線マップがある。
		//法線と接ベクトルの外積を計算して、従ベクトルを計算する。
		float3 biNormal = cross(normal, tangent);
		float3 tangentSpaceNormal = g_normalMap.Sample(Sampler, uv);
		//0.0～1.0の範囲になっているタンジェントスペース法線を
		//-1.0～1.0の範囲に変換する。
		tangentSpaceNormal = (tangentSpaceNormal * 2.0f) - 1.0f;
		//法線をタンジェントスペースから、ワールドスペースに変換する。
		worldSpaceNormal = tangent * tangentSpaceNormal.x + biNormal * tangentSpaceNormal.y + normal * tangentSpaceNormal.z;
	}
	else {
		//ない。
		worldSpaceNormal = normal;
	}
	return worldSpaceNormal;
}

//アンビエントライトを計算
float3 CalcAmbientLight(float4 albedoColor, float2 uv)
{
	float4 Amb = { Ambient_R, Ambient_G, Ambient_B, 1.0f };
	if (isHasAOMap == true) {
		return albedoColor.xyz * Amb * g_aoMap.Sample(Sampler, uv);
	}
	else {
		return albedoColor.xyz * Amb;
	}
}

//ポイントライトを計算
float3 CalcPointLight(float3 normal, float3 worldpos) {
	float3 lig = 0.0f;

	for (int i = 0; i < MAX_POINT_LIGHT; i++) {

		//１．光源からサーフェイスに入射するベクトルを計算。
		float3 ligDir = normalize(worldpos - pointLight.position[i]);
		//２．光源からサーフェイスまでの距離を計算。
		float distance = length(worldpos - pointLight.position[i]);
		//３．光の入射ベクトルとサーフェイスの法線で内積を取って反射の強さを計算する。
		float t = max(0.0f, dot(-ligDir, normal));
		//４．影響率を計算する。影響率は0.0～1.0の範囲で、
		//    指定した距離(pointsLights[i].range)を超えたら、影響率は0.0になる。
		float affect = 1.0f - min(1.0f, distance / pointLight.color[i].w);
		lig += pointLight.color[i] * t * pow( affect, 3.0f);

	}
	return lig;
}

//ディザパターン
static const int pattern[] = {
	0, 32,  8, 40,  2, 34, 10, 42,   /* 8x8 Bayer ordered dithering  */
	48, 16, 56, 24, 50, 18, 58, 26,  /* pattern.  Each input pixel   */
	12, 44,  4, 36, 14, 46,  6, 38,  /* is scaled to the 0..63 range */
	60, 28, 52, 20, 62, 30, 54, 22,  /* before looking in this table */
	3, 35, 11, 43,  1, 33,  9, 41,   /* to determine the action.     */
	51, 19, 59, 27, 49, 17, 57, 25,
	15, 47,  7, 39, 13, 45,  5, 37,
	63, 31, 55, 23, 61, 29, 53, 21
};

//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
PSOutput PSMain(PSInput In)
{
	PSOutput psOut = (PSOutput)0;

	if (isDithering == 1) {
		//ディザリングを行う。
		//書き込もうとしているピクセルの座標(0.0～1.0の範囲)で求める。
		uint2 index = (uint2)In.Position.xy;
		index = fmod(index, 8.0f);
		//プレイヤーの座標をカメラ空間に変換
		float4 player_pos = mul(mView, playerPos);

		float4 origin = (0.0f, 0.0f, 0.0f, 0.0f);
		float2 t = In.posInProj.xy / In.posInProj.w;
		t.y /= 16.0f / 9.0f;
		float dis = length(t);
		int disThreshold = lerp (40, 0, pow( min( dis / 0.8f, 1.0f), 5.0f));
		if (player_pos.z > In.posInView.z) {
			if (pattern[index.y * 8 + index.x] < disThreshold) {
				clip(-1);
			}
		}
	}

	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//法線を計算する。
	float3 normal = CalcNormal(In.Normal, In.Tangent, In.TexCoord);

	//ディレクションライトの拡散反射光を計算する。
	float3 lig = 0;

	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {

		//lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
		//lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;
		lig = max(0.0f, dot(normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;

		//ディレクションライトの鏡面反射光を計算する。
		{
			float3 R = directionLight.direction[i] + (2 * dot(In.Normal, -directionLight.direction[i]))*In.Normal;

			float3 E = normalize(In.worldPos - eyePos);

			float specPower = max(0, dot(R, -E));
			if (isHasSpecMap) {
				specPower *= g_specMap.Sample(Sampler, In.TexCoord).r;
				//specPower *= 1.2f;
			}

			finalColor = float4(directionLight.color[i].xyz*pow(specPower, specPow), 1);

		}

	}

	//ポイントライトの拡散反射光を計算する。
	lig += CalcPointLight(normal, In.worldPos);

	//環境光をあてる。
	//lig += float3(Ambient_R, Ambient_G, Ambient_B);
	lig += CalcAmbientLight(albedoColor, In.TexCoord);

	//法線が上を向いているかチェック
	float angle = abs(acos(normal.y));
	float PI = PI = 3.14159265358979323846f;

	if (isShadowReciever == 1 && angle < 10.0f * (PI / 180.0f)) {	//シャドウレシーバー。
		
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
			zInLVP > zInShadowMap + 0.0001f) {
			//影が落ちているので、光を弱くする
			float2 tmp = (shadowMapUV - 0.5f) * 2.0f;
			float t = pow( min( 1.0f, length(tmp) ), 0.7f );
			lig = lerp(lig * 0.5f, lig, t );
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

//ディザリングをしないVer
PSOutput PSMain_NoDithering(PSInput In)
{
	PSOutput psOut = (PSOutput)0;

	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//法線を計算する。
	float3 normal = CalcNormal(In.Normal, In.Tangent, In.TexCoord);

	//ディレクションライトの拡散反射光を計算する。
	float3 lig = 0;

	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {

		//lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
		//lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;
		lig = max(0.0f, dot(normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;

		//ディレクションライトの鏡面反射光を計算する。
		{
			float3 R = directionLight.direction[i] + (2 * dot(In.Normal, -directionLight.direction[i]))*In.Normal;

			float3 E = normalize(In.worldPos - eyePos);

			float specPower = max(0, dot(R, -E));
			if (isHasSpecMap) {
				specPower *= g_specMap.Sample(Sampler, In.TexCoord).r;
				//specPower *= 1.2f;
			}

			finalColor = float4(directionLight.color[i].xyz*pow(specPower, specPow), 1);

		}

	}

	//ポイントライトの拡散反射光を計算する。
	lig += CalcPointLight(normal, In.worldPos);

	//環境光をあてる。
	//lig += float3(Ambient_R, Ambient_G, Ambient_B);
	lig += CalcAmbientLight(albedoColor, In.TexCoord);

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
			zInLVP > zInShadowMap + 0.0001f) {
			//影が落ちているので、光を弱くする
			float2 tmp = (shadowMapUV - 0.5f) * 2.0f;
			float t = pow(min(1.0f, length(tmp)), 0.7f);
			lig = lerp(lig * 0.5f, lig, t);
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
// シルエット描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

//--------------------------------------------------------------------------------------
// モノクロ描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Monochrome(PSInput In) : SV_Target0
{
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	float P = (0.29900 * albedoColor.r) + (0.58700 * albedoColor.g) + (0.11400 * albedoColor.b);
	albedoColor.r = P;
	albedoColor.g = P;
	albedoColor.b = P;

	return albedoColor;
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
// シャドウマップ生成用(スキンモデル)の頂点シェーダー。
//--------------------------------------------------------------------------------------
PSInput_ShadowMap VSMainSkin_ShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;	///////////////////////////////////////////////////
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

//--------------------------------------------------------------------------------------
// きらめきのピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Kirameki(PSInput In) : SV_Target0
{
	float4 finalColor;

	if (isHasKirameki == 1) {
		//UV座標の計算
		float2 uv;
		uv.x = In.Position.x / mWide;
		uv.y = In.Position.y / mHigh;
		finalColor = g_kirameki.Sample(Sampler, uv);
		finalColor.w = 0.5f;
		//finalColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		finalColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	return finalColor;
}
