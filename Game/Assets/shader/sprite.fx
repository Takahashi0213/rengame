
//�X�v���C�g�p�̃V�F�[�_�[

cbuffer cb:register(b0) {
	float4x4 mvp;	//���[���h�r���[�v���W�F�N�V�����s��
	float4 mulColor;	//��Z�J���[�B
	float cut_line;
};

struct VSInput {
	float4 pos : SV_Position;
	float2 uv : TEXCOORD0;
};
struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`��
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) {
	PSInput psIn;
	psIn.pos = mul(mvp, In.pos);
	psIn.uv = In.uv;

	return psIn;
}

float4 PSMain(PSInput In) :SV_Target0{
	//�e�N�X�`���J���[�����̂܂ܕԂ��B
	float4 color = colorTexture.Sample(Sampler, In.uv);

	return color * mulColor;
}

float4 PSMain_X_Cut(PSInput In) :SV_Target0{

	//�e�N�X�`���J���[�����̂܂ܕԂ��B
	float4 color = colorTexture.Sample(Sampler, In.uv);

	//uv.x��cut_line�ȏ�Ȃ�J�b�g�����
	if (In.uv.x > cut_line) {
		color.a = 0.0f;
	}

	return color * mulColor;
}

float4 PSMain_Y_Cut(PSInput In) :SV_Target0{

	//�e�N�X�`���J���[�����̂܂ܕԂ��B
	float4 color = colorTexture.Sample(Sampler, In.uv);

	//uv.y��cut_line�ȉ��Ȃ�J�b�g�����
	if (In.uv.y < cut_line) {
		color.a = 0.0f;
	}

	return color * mulColor;
}