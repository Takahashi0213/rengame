
//スプライト用のシェーダー

cbuffer cb:register(b0) {
	float4x4 mvp;	//ワールドビュープロジェクション行列
	float4 mulColor;	//乗算カラー。
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

Texture2D<float4> colorTexture : register(t0);	//カラーテクスチャ
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) {
	PSInput psIn;
	psIn.pos = mul(mvp, In.pos);
	psIn.uv = In.uv;

	return psIn;
}

float4 PSMain(PSInput In) :SV_Target0{
	//テクスチャカラーをそのまま返す。
	float4 color = colorTexture.Sample(Sampler, In.uv);

	return color * mulColor;
}

float4 PSMain_X_Cut(PSInput In) :SV_Target0{

	//テクスチャカラーをそのまま返す。
	float4 color = colorTexture.Sample(Sampler, In.uv);

	//uv.xがcut_line以上ならカットされる
	if (In.uv.x > cut_line) {
		color.a = 0.0f;
	}

	return color * mulColor;
}

float4 PSMain_Y_Cut(PSInput In) :SV_Target0{

	//テクスチャカラーをそのまま返す。
	float4 color = colorTexture.Sample(Sampler, In.uv);

	//uv.yがcut_line以下ならカットされる
	if (In.uv.y < cut_line) {
		color.a = 0.0f;
	}

	return color * mulColor;
}