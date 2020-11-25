/*!
 * @brief	���f���V�F�[�_�[�B
 */

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);
Texture2D<float4> g_shadowMap : register(t2);		//�@�V���h�E�}�b�v
Texture2D<float4> g_normalMap : register(t3);		//	�@���}�b�v�B
Texture2D<float4> g_specMap : register(t4);			//	�X�y�L�����}�b�v�B
Texture2D<float4> g_aoMap : register(t5);			//	AO�}�b�v�B
Texture2D<float4> g_kirameki : register(t6);		//	����߂��B

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/// 
static const int MAX_DIRECTION_LIGHT = 5;	//!<�f�B���N�V�������C�g�̍ő吔�B
static const int MAX_POINT_LIGHT = 16;		//!<�|�C���g���C�g�̍ő吔�B

/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
	int isHasNormalMap;		//�@���}�b�v����H
	int isHasSpecMap;		//�X�y�L�����}�b�v����H
	int isHasAOMap;			//�A���r�G���g�I�N�����[�W�����}�b�v����H
	int isHasKirameki;		//����߂���ێ����Ă���H
	float mHigh;
	float mWide;			//��ʂ̏c��
	float emissionColor_R;
	float emissionColor_G;
	float emissionColor_B;
};
/*!
*@brief	���C�g�p�̒萔�o�b�t�@�B
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
/// �V���h�E�}�b�v�p�̒萔�o�b�t�@�B
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//���C�g�r���[�v���W�F�N�V�����s��B
}

/*!
*@brief	�����p�̒萔�o�b�t�@�B
*/
cbuffer Ambient_LightCb : register(b2) {
	float Ambient_R;
	float Ambient_G;
	float Ambient_B;
};

/*!
*@brief	���C�g�p�̒萔�o�b�t�@�B
*/
cbuffer LightCb : register(b3) {
	SDirectionLight		directionLight;		//�f�B���N�V�������C�g�B
	SPointLight			pointLight;			//�|�C���g���C�g�B
	float3				eyePos;				//�J�����̎��_�B
	float				specPow;			//�X�y�L�������C�g�̍i��B
};

/// <summary>
/// �f�B�U�����O�p�̒萔�o�b�t�@�B
/// </summary>
cbuffer DitheringCb : register(b4) {
	int isDithering;						//�f�B�U�����O�t���O�B
	float4				playerPos;			//�v���C���[�̍��W�B
}

/// /////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;
	float4 posInLVP		: TEXCOORD2;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
	float4 posInView	: TEXCOORD3;	//�J������Ԃł̍��W�B
	float4 posInProj	: TEXCOORD4;	//���K���X�N���[�����W�n�̍��W
};
/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�ւ̓��͍\���́B
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//���W�B
};
///�����̃����_�����O�^�[�Q�b�g�ɏo�͂��邽�߂ɁA�\���̂�p�ӁB
/// <summary>
/// �s�N�Z���V�F�[�_�[����̏o�͍\���́B
/// </summary>
struct PSOutput {
	float4 color		: SV_Target0;	//0�Ԗڂ̃����_�����O�^�[�Q�b�g�ɏo�͂����B
	float depthInView	: SV_Target1;	//1�Ԗڂ̃����_�����O�^�[�Q�b�g�ɏo�͂����B
};
/*!
 *@brief	�X�L���s����v�Z�B
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
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);

	psInput.worldPos = pos;
	pos = mul(mView, pos);
	//�J������Ԃł̍��W���s�N�Z���V�F�[�_�[�Ŏg���̂ŁA�ۑ����Ă����B
	psInput.posInView = pos;

	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;

	float4 worldPos_ = mul(mWorld, In.Position);

	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(mLightView, worldPos_);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));

	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;

	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
	    pos = mul(skinning, In.Position);
		psInput.worldPos = pos;
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	//�J������Ԃł̍��W���s�N�Z���V�F�[�_�[�Ŏg���̂ŁA�ۑ����Ă����B
	psInput.posInView = pos;

	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;

	psInput.TexCoord = In.TexCoord;
    return psInput;
}

/// <summary>
/// �@�����v�Z����B
/// </summary>
float3 CalcNormal(float3 normal, float3 tangent, float2 uv)
{
	float3 worldSpaceNormal;
	if (isHasNormalMap == 1) {
		//�@���}�b�v������B
		//�@���Ɛڃx�N�g���̊O�ς��v�Z���āA�]�x�N�g�����v�Z����B
		float3 biNormal = cross(normal, tangent);
		float3 tangentSpaceNormal = g_normalMap.Sample(Sampler, uv);
		//0.0�`1.0�͈̔͂ɂȂ��Ă���^���W�F���g�X�y�[�X�@����
		//-1.0�`1.0�͈̔͂ɕϊ�����B
		tangentSpaceNormal = (tangentSpaceNormal * 2.0f) - 1.0f;
		//�@�����^���W�F���g�X�y�[�X����A���[���h�X�y�[�X�ɕϊ�����B
		worldSpaceNormal = tangent * tangentSpaceNormal.x + biNormal * tangentSpaceNormal.y + normal * tangentSpaceNormal.z;
	}
	else {
		//�Ȃ��B
		worldSpaceNormal = normal;
	}
	return worldSpaceNormal;
}

//�A���r�G���g���C�g���v�Z
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

//�|�C���g���C�g���v�Z
float3 CalcPointLight(float3 normal, float3 worldpos) {
	float3 lig = 0.0f;

	for (int i = 0; i < MAX_POINT_LIGHT; i++) {

		//�P�D��������T�[�t�F�C�X�ɓ��˂���x�N�g�����v�Z�B
		float3 ligDir = normalize(worldpos - pointLight.position[i]);
		//�Q�D��������T�[�t�F�C�X�܂ł̋������v�Z�B
		float distance = length(worldpos - pointLight.position[i]);
		//�R�D���̓��˃x�N�g���ƃT�[�t�F�C�X�̖@���œ��ς�����Ĕ��˂̋������v�Z����B
		float t = max(0.0f, dot(-ligDir, normal));
		//�S�D�e�������v�Z����B�e������0.0�`1.0�͈̔͂ŁA
		//    �w�肵������(pointsLights[i].range)�𒴂�����A�e������0.0�ɂȂ�B
		float affect = 1.0f - min(1.0f, distance / pointLight.color[i].w);
		lig += pointLight.color[i] * t * pow( affect, 3.0f);

	}
	return lig;
}

//�f�B�U�p�^�[��
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
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
PSOutput PSMain(PSInput In)
{
	PSOutput psOut = (PSOutput)0;

	if (isDithering == 1) {
		//�f�B�U�����O���s���B
		//�����������Ƃ��Ă���s�N�Z���̍��W(0.0�`1.0�͈̔�)�ŋ��߂�B
		uint2 index = (uint2)In.Position.xy;
		index = fmod(index, 8.0f);
		//�v���C���[�̍��W���J������Ԃɕϊ�
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

	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//�@�����v�Z����B
	float3 normal = CalcNormal(In.Normal, In.Tangent, In.TexCoord);

	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	float3 lig = 0;

	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {

		//lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
		//lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;
		lig = max(0.0f, dot(normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;

		//�f�B���N�V�������C�g�̋��ʔ��ˌ����v�Z����B
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

	//�|�C���g���C�g�̊g�U���ˌ����v�Z����B
	lig += CalcPointLight(normal, In.worldPos);

	//���������Ă�B
	//lig += float3(Ambient_R, Ambient_G, Ambient_B);
	lig += CalcAmbientLight(albedoColor, In.TexCoord);

	//�@������������Ă��邩�`�F�b�N
	float angle = abs(acos(normal.y));
	float PI = PI = 3.14159265358979323846f;

	if (isShadowReciever == 1 && angle < 10.0f * (PI / 180.0f)) {	//�V���h�E���V�[�o�[�B
		
		//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B

		///LVP��Ԃł̐[�x�l���v�Z�B
		float zInLVP = In.posInLVP.z / In.posInLVP.w;
		//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

		if (shadowMapUV.x > 0.0f &&
			shadowMapUV.x < 1.0f &&
			shadowMapUV.y > 0.0f &&
			shadowMapUV.y < 1.0f &&
			zInLVP > zInShadowMap + 0.0001f) {
			//�e�������Ă���̂ŁA�����キ����
			float2 tmp = (shadowMapUV - 0.5f) * 2.0f;
			float t = pow( min( 1.0f, length(tmp) ), 0.7f );
			lig = lerp(lig * 0.5f, lig, t );
		}
	}

	finalColor.xyz += albedoColor.xyz * lig;
	//return finalColor;
	
	//�J���[���o�́B
	psOut.color = finalColor;
	//�J�������W�n�ł�Z�l���o�́B
	psOut.depthInView = In.posInView.z;

	//�F�ύX
	psOut.color.r += emissionColor_R;
	psOut.color.g += emissionColor_G;
	psOut.color.b += emissionColor_B;

	return psOut;

}

//�f�B�U�����O�����Ȃ�Ver
PSOutput PSMain_NoDithering(PSInput In)
{
	PSOutput psOut = (PSOutput)0;

	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//�@�����v�Z����B
	float3 normal = CalcNormal(In.Normal, In.Tangent, In.TexCoord);

	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	float3 lig = 0;

	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {

		//lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
		//lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;
		lig = max(0.0f, dot(normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;

		//�f�B���N�V�������C�g�̋��ʔ��ˌ����v�Z����B
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

	//�|�C���g���C�g�̊g�U���ˌ����v�Z����B
	lig += CalcPointLight(normal, In.worldPos);

	//���������Ă�B
	//lig += float3(Ambient_R, Ambient_G, Ambient_B);
	lig += CalcAmbientLight(albedoColor, In.TexCoord);

	if (isShadowReciever == 1) {	//�V���h�E���V�[�o�[�B

									//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		//�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B

		///LVP��Ԃł̐[�x�l���v�Z�B
		float zInLVP = In.posInLVP.z / In.posInLVP.w;
		//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
		float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

		if (shadowMapUV.x > 0.0f &&
			shadowMapUV.x < 1.0f &&
			shadowMapUV.y > 0.0f &&
			shadowMapUV.y < 1.0f &&
			zInLVP > zInShadowMap + 0.0001f) {
			//�e�������Ă���̂ŁA�����キ����
			float2 tmp = (shadowMapUV - 0.5f) * 2.0f;
			float t = pow(min(1.0f, length(tmp)), 0.7f);
			lig = lerp(lig * 0.5f, lig, t);
		}
	}

	finalColor.xyz += albedoColor.xyz * lig;
	//return finalColor;

	//�J���[���o�́B
	psOut.color = finalColor;
	//�J�������W�n�ł�Z�l���o�́B
	psOut.depthInView = In.posInView.z;

	//�F�ύX
	psOut.color.r += emissionColor_R;
	psOut.color.g += emissionColor_G;
	psOut.color.b += emissionColor_B;

	return psOut;

}

//--------------------------------------------------------------------------------------
// �V���G�b�g�`��p�̃s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

//--------------------------------------------------------------------------------------
// ���m�N���`��p�̃s�N�Z���V�F�[�_�[�̃G���g���֐��B
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
// �V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
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
// �V���h�E�}�b�v�����p(�X�L�����f��)�̒��_�V�F�[�_�[�B
//--------------------------------------------------------------------------------------
PSInput_ShadowMap VSMainSkin_ShadowMap(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;

		for (int i = 0; i < 3; i++)
		{
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//�Ō�̃{�[�����v�Z����B
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
		pos = mul(skinning, In.Position);
	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}

//--------------------------------------------------------------------------------------
// ����߂��̃s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain_Kirameki(PSInput In) : SV_Target0
{
	float4 finalColor;

	if (isHasKirameki == 1) {
		//UV���W�̌v�Z
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
