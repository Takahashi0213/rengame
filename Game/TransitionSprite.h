#pragma once
#include "graphics/Shader.h"

class TransitionSprite
{
public:
	TransitionSprite();
	~TransitionSprite();

	//メインスプライト
	void Sprite_Init(const wchar_t* texFilePath, float w, float h);
	void Sprite_Update();
	void Sprite_Draw();

	struct ConstantBuffer {
		CMatrix WVP;	//ワールドビュープロジェクション行列
		float Alpha;	//基準になるアルファ
	};
	struct SpriteData {
		ID3D11ShaderResourceView* Texture = NULL;		//テクスチャ
		CVector3 Position = CVector3::Zero();
		CQuaternion Rotation = CQuaternion().Identity();
		CVector3 Scale = CVector3().One();
		CVector2 Pivot = { 0.5f, 0.5f };
		CMatrix	World = CMatrix::Identity();		//ワールド行列
		CVector2 Size = CVector2::Zero();		//画像のサイズ
	};

	//メンバ変数
	ID3D11Buffer* m_vertexBuffer = NULL;	//頂点バッファ
	ID3D11Buffer* m_indexBuffer = NULL;		//インデックスバッファ

	//シェーダー
	Shader	m_ps;			//!<ピクセルシェーダー。
	Shader	m_vs;		//!<頂点シェーダー。
	ID3D11SamplerState* m_samplerState = NULL;	//サンプラステート

	//スプライトである。
	SpriteData m_mainSprite;
	float m_alpha = 0.0f;	//トランジションの基準

	ID3D11Buffer* m_cb = nullptr;		//定数バッファ
	bool m_isInited = false;	//!<初期化フラグ。

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

	void TransitionSprite::InitConstantBuffer();
	void TransitionSprite::InitCommon(float w, float h, bool cutFlag = false);

};

