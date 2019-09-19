#pragma once
#include "graphics/Shader.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
	
	void Sprite_Init(const wchar_t* texFilePath, float w, float h);
	void Sprite_Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });
	void Sprite_Draw();

	/// <summary>
	/// 乗算カラーを設定
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	/// <returns>乗算カラー</returns>
	CVector4 GetMulColor()
	{
		return m_mulColor;
	}

	//ワールドビュープロジェクション行列
	struct ConstantBuffer {
		CMatrix WVP;
		CVector4 mulColor;	//乗算カラー
	};
	//メンバ変数
	ID3D11Buffer* m_vertexBuffer = NULL;	//頂点バッファ
	ID3D11Buffer* m_indexBuffer = NULL;		//インデックスバッファ
	Shader	m_ps;		//!<ピクセルシェーダー。
	Shader	m_vs;		//!<頂点シェーダー。
	ID3D11ShaderResourceView* m_texture = NULL;		//テクスチャ
	ID3D11SamplerState* m_samplerState = NULL;	//サンプラステート

	CVector3 m_position = CVector3::Zero();		//座標
	CQuaternion	m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();		//拡大率
	CVector4 m_mulColor = CVector4().White();	//!<乗算カラー。

	CMatrix	m_world = CMatrix::Identity();		//ワールド行列
	CVector2 m_size = CVector2::Zero();		//画像のサイズ
	ID3D11Buffer* m_cb = nullptr;		//定数バッファ
	bool m_isInited = false;	//!<初期化フラグ。
private:
	void Sprite::InitConstantBuffer();

};

