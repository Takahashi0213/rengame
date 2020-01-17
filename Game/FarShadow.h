#pragma once
class PostEffect;

/// <summary>
/// 
/// </summary>
class FarShadow
{
public:
	~FarShadow();
	/// <summary>
	/// 初期化。
	/// </summary>
	void Init();
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="postEffect"></param>
	void Draw(PostEffect& postEffect);
private:
	ID3D11BlendState * m_finalBlendState = nullptr;		//最終合成用のブレンディングステート。

	Shader m_vs;				//頂点シェーダー。
	Shader m_ps;				//ピクセルシェーダー。

};

