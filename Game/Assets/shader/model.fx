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
//todo �V���h�E�}�b�v
Texture2D<float4> g_shadowMap : register(t2);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/// 
static const int MAX_DIRECTION_LIGHT = 5;	//!<�f�B���N�V�������C�g�̍ő吔�B

/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//CVector3 emissionColor;
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
};
/*!
*@brief	���C�g�p�̒萔�o�b�t�@�B
*/
struct SDirectionLight{
	float3 direction[MAX_DIRECTION_LIGHT];
	float4 color[MAX_DIRECTION_LIGHT];
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
	float3				eyePos;				//�J�����̎��_�B
	float				specPow;			//�X�y�L�������C�g�̍i��B
};

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
	float depthInView : SV_Target1;	//1�Ԗڂ̃����_�����O�^�[�Q�b�g�ɏo�͂����B
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
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	//�J������Ԃł̍��W���s�N�Z���V�F�[�_�[�Ŏg���̂ŁA�ۑ����Ă����B
	psInput.posInView = pos;


	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
PSOutput PSMain(PSInput In)
{
	PSOutput psOut = (PSOutput)0;

	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//float3 hoge = float3(0.0f, -1.0f, 0.0f);
	//float4 hoge2 = float4( 0.0f,0.8f, 0.0f, 1.0f );

	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	float3 lig = 0;
	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {

		//lig += max(0.0f, dot(In.Normal * -1.0f, dligDirection[i])) * dligColor[i];
		lig = max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i].xyz;

		//�f�B���N�V�������C�g�̋��ʔ��ˌ����v�Z����B
		{
			float3 R = directionLight.direction[i] + (2 * dot(In.Normal, -directionLight.direction[i]))*In.Normal;

			float3 E = normalize(In.worldPos - eyePos);

			float specPower = max(0, dot(R, -E));

			finalColor = float4(directionLight.color[i].xyz*pow(specPower, specPow), 1);

		}

	}

	//���������Ă�B
	lig += float3(Ambient_R, Ambient_G, Ambient_B);

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
			zInLVP > zInShadowMap + 0.01f) {
			//�e�������Ă���̂ŁA�����キ����
			lig *= 0.5f;
		}
	}

	finalColor.xyz += albedoColor.xyz * lig;
	//return finalColor;

	//�J���[���o�́B
	psOut.color = finalColor;
	//�J�������W�n�ł�Z�l���o�́B
	psOut.depthInView = In.posInView.z;
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
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}