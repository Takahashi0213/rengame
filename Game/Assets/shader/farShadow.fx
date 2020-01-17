/*!
 *@brief	�����ł�
 */

/*!
 *@brief	���_�V�F�[�_�[�̓��́B
 */
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

/*!
 *@brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> depthInViewTexture : register(t0);	//�J������Ԃ̐[�x�e�N�X�`���B
sampler Sampler : register(s0);


/*!
 * @brief	���_�V�F�[�_�[�B
 */
PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

/////////////////////////////////////////////////////////
// �e�p�̃s�N�Z���V�F�[�_�[�B
/////////////////////////////////////////////////////////
float4 PSMain(PSInput psIn) : SV_Target0
{
	float depth = depthInViewTexture.Sample(Sampler, psIn.uv);
	if (depth < 800.0f) {
		depth = 0.0f;
	}
	else {
		depth /= 2000.0f;
	}
	float4 color = { 0.0f,0.0f,0.0f,depth };

	return color;
}
