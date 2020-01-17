#pragma once
#include "graphics/Shader.h"

enum Sprite_RenderMode {
	Normal,		//普通に描画
	X_Cut,		//Xをカットする
	Y_Cut,		//Yをカットする
};

class Sprite
{
public:

	Sprite();
	~Sprite();
	
	//メインスプライト
	void Sprite_Init(const wchar_t* texFilePath, float w, float h);
	void Sprite_Init(ID3D11ShaderResourceView* srv, float w, float h);
	void Sprite_Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });
	//サブスプライト
	void Sprite_Init_Sub(const wchar_t* texFilePath, float w, float h);
	void Sprite_Init_Sub(ID3D11ShaderResourceView* srv, float w, float h);
	void Sprite_Update_Sub(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });

	/// <summary>
	/// メインスプライトとサブスプライトの合わせ技（Draw）だ！
	/// </summary>
	void Sprite_Draw();

	/// <summary>
	/// 乗算カラーを設定
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mainSprite.MulColor = mulColor;
	}
	void SetMulColor_Sub(const CVector4& mulColor)
	{
		m_subSprite.MulColor = mulColor;
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	/// <returns>乗算カラー</returns>
	CVector4 GetMulColor()
	{
		return m_mainSprite.MulColor;
	}

	struct ConstantBuffer {
		CMatrix WVP;	//ワールドビュープロジェクション行列
		CVector4 mulColor;	//乗算カラー
		float cut_line;
	};
	struct SpriteData {
		ID3D11ShaderResourceView* Texture = NULL;		//テクスチャ
		CVector3 Position = CVector3::Zero();
		CQuaternion Rotation = CQuaternion().Identity();
		CVector3 Scale = CVector3().One();
		CVector2 Pivot = { 0.5f, 0.5f };
		CVector4 MulColor = CVector4().White();	//!<乗算カラー。
		CMatrix	World = CMatrix::Identity();		//ワールド行列
		CVector2 Size = CVector2::Zero();		//画像のサイズ
	};

	//メンバ変数
	ID3D11Buffer* m_vertexBuffer = NULL;	//頂点バッファ
	ID3D11Buffer* m_indexBuffer = NULL;		//インデックスバッファ

	Shader	m_ps;		//!<ピクセルシェーダー。
	Shader	m_ps_X_Cut;	//!<Xをカットするピクセルシェーダー。
	Shader	m_ps_Y_Cut;	//!<Yをカットするピクセルシェーダー。
	Shader	m_vs;		//!<頂点シェーダー。
	ID3D11SamplerState* m_samplerState = NULL;	//サンプラステート

	//2つのスプライトである。
	SpriteData m_mainSprite;
	SpriteData m_subSprite;

	ID3D11Buffer* m_cb = nullptr;		//定数バッファ
	bool m_isInited = false;	//!<初期化フラグ。

	Sprite_RenderMode m_renderMode = Normal;	//レンダーモード
	float m_cut_UV = 0.5f;

private:
	/// <summary>
	/// 16の倍数に切り上げる処理
	/// </summary>
	/// <param name="n">切り上げたい整数</param>
	/// <returns>16の倍数に切り上げた値</returns>
	int Raundup16(int n)
	{
		return (((n - 1) / 16) + 1) * 16;
	}

	void Sprite::InitConstantBuffer();
	void Sprite::InitCommon(float w, float h);

};

