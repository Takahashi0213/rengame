
//�X�v���C�g�p�̃V�F�[�_�[

cbuffer cb:register(b0) {
	float4x4 mvp;	//���[���h�r���[�v���W�F�N�V�����s��
	float4 mulColor;	//��Z�J���[�B
	float cut_line;
	int slice_pattern;
	int nowPattern;
	float mHigh;
	float mWide;			//��ʂ̏c��
};

struct VSInput {
	float4 pos : SV_Position;
	float2 uv : TEXCOORD0;
};
struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);		//�J���[�e�N�X�`��
Texture2D<float4> renderingTarget : register(t1);	//���݂̉��
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

	if(mulColor.a == 0.0f)discard;

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

float4 PSMain_Slice(PSInput In) :SV_Target0{
	//�X���C�X
	float4 color = colorTexture.Sample(Sampler, In.uv);

	if (slice_pattern == 1) {//����
		if (In.uv.x > (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.y > (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
	}
	else if (slice_pattern == 2) {//������
		if (In.uv.x < (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.x > (1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
		if (In.uv.y > (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
	}
	else if (slice_pattern == 3) {//�E��
		if (In.uv.x < (1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
		if (In.uv.y > (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
	}
	else if (slice_pattern == 4) {//������
		if (In.uv.x > (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.y < (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.y > (1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
	}
	else if (slice_pattern == 5) {//����

		if (In.uv.x < (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.x >(1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}

		if (In.uv.y < (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.y >(1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}

	}
	else if (slice_pattern == 6) {//�E����
		if (In.uv.x < (1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
		if (In.uv.y < (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.y >(1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
	}
	else if (slice_pattern == 7) {//����
		if (In.uv.x > (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.y <(1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
	}
	else if (slice_pattern == 8) {//������
		if (In.uv.x < (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.x >(1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
		if (In.uv.y < (1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}

	}
	else if (slice_pattern == 9) {//�E��
		if (In.uv.x < (1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
		if (In.uv.y <(1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
	}

	//��������3Slice�p�i100�`102�j
	if (slice_pattern == 100) {
		if (In.uv.x >(1.0f / 3.0f)) {
			color.a = 0.0f;
		}
	}
	else if (slice_pattern == 101) {
		if (In.uv.x < (1.0f / 3.0f)) {
			color.a = 0.0f;
		}
		if (In.uv.x >(1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
	}
	else if (slice_pattern == 102) {
		if (In.uv.x < (1.0f / 3.0f)*2.0f) {
			color.a = 0.0f;
		}
	}

	return color * mulColor;
}

float4 PSMain_Mask(PSInput In) :SV_Target0{
	//�}�X�N�p�s�N�Z���V�F�[�_�[
	float4 color = colorTexture.Sample(Sampler, In.uv);
	
	clip(color.a - 0.0001); //��<= 0�̃s�N�Z�����o�͂��Ȃ�

	return color * mulColor;
}

float4 PSMain_Pattern(PSInput In) :SV_Target0{
	//�e�N�X�`���J���[�����̂܂ܕԂ��B
	float4 color = colorTexture.Sample(Sampler, In.uv);
	float cut_UV = 1.0f / (float)slice_pattern;

	//��������͕\�����Ȃ���
	if (In.uv.y < (cut_UV  * (float)nowPattern)) {
		color.a = 0.0f;
	}

	//������艺���\�����Ȃ���
	if (In.uv.y > (cut_UV * ((float)nowPattern + 1))) {
		color.a = 0.0f;
	}

	return color * mulColor;
}

float4 PSMain_Monochrome(PSInput In) :SV_Target0{
	//���m�N���ϊ�
	float4 color = colorTexture.Sample(Sampler, In.uv);

	float P = (0.29900 * color.r) + (0.58700 * color.g) + (0.11400 * color.b);
	color.r = P;
	color.g = P;
	color.b = P;

	return color * mulColor;
}

float4 PSMain_Overlay(PSInput In) :SV_Target0{
	//���΂ꂢ
	float4 color = colorTexture.Sample(Sampler, In.uv);

	float2 RT_uv;
	RT_uv.x = In.pos.x / mWide;
	RT_uv.y = In.pos.y / mHigh;

	float4 RTcolor = renderingTarget.Sample(Sampler, RT_uv);
	float TempColor = (RTcolor.r + RTcolor.g + RTcolor.b) / 3.0f;
	float4 FinalColor;
	FinalColor.a = color.a;

	//����
	if (RTcolor.r < 0.5f) {
		FinalColor.r = (color.r * RTcolor.r) * 2.0f;
	}
	else {
		FinalColor.r = 1.0f - (2.0f * ((1.0f - color.r) * (1.0f - RTcolor.r)));
	}

	if (RTcolor.g < 0.5f) {
		FinalColor.g = (color.g * RTcolor.g) * 2.0f;
	}
	else {
		FinalColor.g = 1.0f - (2.0f * ((1.0f - color.g) * (1.0f - RTcolor.g)));
	}

	if (RTcolor.b < 0.5f) {
		FinalColor.b = (color.b * RTcolor.b) * 2.0f;
	}
	else {
		FinalColor.b = 1.0f - (2.0f * ((1.0f - color.b) * (1.0f - RTcolor.b)));
	}

	return FinalColor;
}

float4 PSMain_Add(PSInput In) :SV_Target0{
	//���Z
	float4 color = colorTexture.Sample(Sampler, In.uv);

	float2 RT_uv;
	RT_uv.x = In.pos.x / mWide;
	RT_uv.y = In.pos.y / mHigh;

	float4 RTcolor = renderingTarget.Sample(Sampler, RT_uv);
	float4 FinalColor;
	FinalColor.a = color.a;

	FinalColor.r = RTcolor.r + color.r;
	FinalColor.g = RTcolor.g + color.g;
	FinalColor.b = RTcolor.b + color.b;

	return FinalColor;
}
