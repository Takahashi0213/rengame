#pragma once
class GameFont
{
public:
	GameFont();
	~GameFont();

	/*!
	* @brief	描画開始。
	*/
	void Begin(bool flag = false);
	/*!
	* @brief	描画終了。
	*/
	void End();
	/*!
	* @brief	描画。
	*@param[in]	text		表示したいテキスト。
	*@param[in]	trans		平行移動。
	*@param[in]	color		カラー。
	*@param[in]	rot			回転。
	*@param[in]	scale		拡大。
	*@param[in]	pivot		基点。
	*						0.5, 0.5で画像の中心が基点。
	*						0.0, 0.0で画像の左下。
	*						1.0, 1.0で画像の右上。
	*						UnityのuGUIに準拠。
	*/
	void Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4().White(),
		float rotation = 0.0f,
		float scale = 1.0f,
		CVector2 pivot = { 0.5f, 0.5f }
	);

	/*!
	*@brief	影のパラメータを設定。
	*@param[in]	isDrawShadow		影を描く？
	*@param[in]	shadowOffset		影を描くときのピクセルのオフセット量。
	*@param[in]	shadowColor			影の色。
	*/
	void SetShadowParam(bool isDrawShadow, float shadowOffset, const CVector4& shadowColor = { 0.2f,0.2f,0.2f,1.0f })
	{
		m_isDrawShadow = isDrawShadow;
		m_shadowOffset = shadowOffset;
		m_shadowColor = shadowColor;
	}

	void SetCut(float cutUp, float cutDown) {
		m_cutY_Up = cutUp;
		m_cutY_Down = cutDown;
	}

	struct ConstantBuffer {
		float CutUp;
		float CutDown;
	};

private:
	void InitTranslucentBlendState();
	ID3D11Buffer* m_cb = nullptr;		//定数バッファ
	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<スプライトバッチ。
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<スプライトフォント。

	const CVector4 ShadowColorDef = { 1.0f,1.0f,1.0f,1.0f };	//影の初期色

	bool m_isDrawShadow = false;						//!<影を書く？
	float m_shadowOffset = 0.0f;						//!<影を書くときのピクセルのオフセット量。
	CVector4 m_shadowColor = ShadowColorDef;			//!<影の色。

	//カットシステムゥ！！
	float m_cutY_Up = 720.0f;						//!<ここより上は描画しない
	float m_cutY_Down = -720.0f;					//!<ここより下は描画しない

	CMatrix m_scaleMat;
	ID3D11DepthStencilState*	m_depthStencilStateBackup = nullptr;	//!<現在のデプスステンシルステート。
	ID3D11RasterizerState*		m_rasterrizerStateBackup = nullptr;		//!<現在のラスタライザステート。
	ID3D11BlendState*			m_blendStateBackup = nullptr;			//!<現在のブレンドステート。
	Shader m_psShader;													//!<フォント用のぴくせるしぇ
	Shader m_psShader2;													//!<フォント用のぴくせるしぇ
};