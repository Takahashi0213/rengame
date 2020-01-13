#pragma once
#include "system/CGameObjectManager.h"
#include "Sprite.h"
#include "SpriteSupporter.h"

/// <summary>
/// スプライトレンダー
/// 2Dを描くときに使います
/// </summary>
class SpriteRender : public IGameObject
{
public:

	SpriteRender();
	~SpriteRender();
	void Update()override;
	void Render()override;

	void Init(const wchar_t* texFilePath, float w, float h, int priority = 0);
	void Init(const wchar_t* texFilePath, float w, float h, CVector3 pos = CVector3().Zero(), CVector4 color = CVector4().White(), int priority = 0);

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns>回転</returns>
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scr">拡大率</param>
	void SetScale(const CVector3 scl)
	{
		m_scale = scl;
	}
	void SetScale(const float scl) { //便利Ver
		m_scale.x = scl;
		m_scale.y = scl;
	}
	/// <summary>
	/// 拡大率を取得
	/// </summary>
	/// <returns>拡大率</returns>
	const CVector3 GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// ピボットを設定
	/// </summary>
	/// <param name="pivot">ピボット</param>
	void SetPivot(const CVector2 pivot)
	{
		m_pivot.x = pivot.x;
		m_pivot.y = pivot.y;
	}
	/// <summary>
	/// ピボットを取得
	/// </summary>
	/// <returns>ピボット</returns>
	CVector2 GetPivot()
	{
		return m_pivot;
	}

	/// <summary>
	/// 幅を取得
	/// </summary>
	/// <returns>幅</returns>
	float GetWide()
	{
		return m_wide;
	}
	/// <summary>
	/// 高さを取得
	/// </summary>
	/// <returns>高さ</returns>
	float GetHigh()
	{
		return m_high;
	}

	/// <summary>
	/// 乗算カラーを設定
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;		
		m_sprite.SetMulColor(m_mulColor);
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	/// <returns>乗算カラー</returns>
	CVector4 GetMulColor()
	{
		return m_mulColor;
	}

	/// <summary>
	/// レンダーモードの設定
	/// </summary>
	/// <param name="render_mode">モード</param>
	void SetRenderMode(Sprite_RenderMode render_mode) {
		m_sprite_RenderMode = render_mode;
		m_sprite.m_renderMode = m_sprite_RenderMode;
	}

	/// <summary>
	/// どこから切るか設定
	/// </summary>
	/// <param name="cut">UV座標の境界</param>
	void SetCutLine(float cut) {
		m_pos_Cut = cut;
		m_sprite.m_cut_UV = m_pos_Cut;
	}

	/// <summary>
	/// スプライトを楽に動かすクラスを呼び出せるぞ
	/// </summary>
	/// <remarks>
	/// 
	/// ☆サンプルコード☆
	/// render->m_spriteSupporter.SpriteMove(設定値);
	/// 
	/// </remarks>
	SpriteSupporter m_spriteSupporter;		//スプライトサポーター

private:
	//ID3D11ShaderResourceView* m_texture;	//!<テクスチャ。
	Sprite m_sprite;		//!<スプライト。
	CVector3 m_position = CVector3::Zero();		//!<座標。
	CQuaternion m_rotation= CQuaternion().Identity();		//!<回転。
	CVector3 m_scale = CVector3().One();		//!<拡大率。
	CVector2 m_pivot = { 0.5f, 0.5f };		//!<ピボット。
	float m_wide = 0.0f;	//幅！
	float m_high = 0.0f;	//高さ！
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };	//!<乗算カラー。

	Sprite_RenderMode m_sprite_RenderMode = Sprite_RenderMode::Normal;
	float m_pos_Cut = 0.0f;				//CutMode時、どこから切る？？？？

};

