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

	void InitSub(const wchar_t* texFilePath, float w, float h, int priority = 0);
	void InitSub(const wchar_t* texFilePath, float w, float h, CVector3 pos = CVector3().Zero(), CVector4 color = CVector4().White(), int priority = 0);

	//設定色々
	//全てのsubFlagはfalseならメインスプライト、trueならサブスプライトを変更します

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3 pos, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.Position = pos;
		}
		else {
			m_subSprite.Position = pos;
		}
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3 GetPosition( bool subFlag = false ) const
	{
		if (subFlag == false) {
			return m_mainSprite.Position;
		}
		else {
			return m_subSprite.Position;
		}
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.Rotation = rot;
		}
		else {
			m_subSprite.Rotation = rot;
		}
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns>回転</returns>
	const CQuaternion GetRotation(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSprite.Rotation;
		}
		else {
			return m_subSprite.Rotation;
		}
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scr">拡大率</param>
	void SetScale(const CVector3 scl, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.Scale = scl;
		}
		else {
			m_subSprite.Scale = scl;
		}
	}
	void SetScale(const float scl, bool subFlag = false) { //便利Ver
		if (subFlag == false) {
			m_mainSprite.Scale.x = scl;
			m_mainSprite.Scale.y = scl;
		}
		else {
			m_subSprite.Scale.x = scl;
			m_subSprite.Scale.y = scl;
		}
	}
	/// <summary>
	/// 拡大率を取得
	/// </summary>
	/// <returns>拡大率</returns>
	const CVector3 GetScale(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSprite.Scale;
		}
		else {
			return m_subSprite.Scale;
		}
	}
	/// <summary>
	/// ピボットを設定
	/// </summary>
	/// <param name="pivot">ピボット</param>
	void SetPivot(const CVector2 pivot , bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.Pivot.x = pivot.x;
			m_mainSprite.Pivot.y = pivot.y;
		}
		else {
			m_subSprite.Pivot.x = pivot.x;
			m_subSprite.Pivot.y = pivot.y;
		}
	}
	/// <summary>
	/// ピボットを取得
	/// </summary>
	/// <returns>ピボット</returns>
	CVector2 GetPivot(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSprite.Pivot;
		}
		else {
			return m_subSprite.Pivot;
		}
	}

	/// <summary>
	/// 幅を取得
	/// </summary>
	/// <returns>幅</returns>
	float GetWide(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSprite.Wide;
		}
		else {
			return m_subSprite.Wide;
		}
	}
	/// <summary>
	/// 高さを取得
	/// </summary>
	/// <returns>高さ</returns>
	float GetHigh(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSprite.High;
		}
		else {
			return m_subSprite.High;
		}
	}

	/// <summary>
	/// 乗算カラーを設定
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const CVector4& mulColor, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.MulColor = mulColor;
			m_sprite.SetMulColor(m_mainSprite.MulColor);
		}
		else {
			m_subSprite.MulColor = mulColor;
			m_sprite.SetMulColor_Sub(m_subSprite.MulColor);
		}
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	/// <returns>乗算カラー</returns>
	CVector4 GetMulColor(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSprite.MulColor;
		}
		else {
			return m_subSprite.MulColor;
		}
	}
	/// <summary>
	/// アルファの設定
	/// </summary>
	/// <param name="Alpha">アルファ</param>
	void SetAlpha(const float Alpha, bool subFlag = false) {
		if (subFlag == false) {
			m_mainSprite.MulColor.w = Alpha;
			m_sprite.SetMulColor(m_mainSprite.MulColor);
		}
		else {
			m_subSprite.MulColor.w = Alpha;
			m_sprite.SetMulColor(m_subSprite.MulColor);
		}
	}
	/// <summary>
	/// アルファの取得
	/// </summary>
	/// <returns>現在の不透明度だ</returns>
	float GetAlpha(bool subFlag = false) {
		if (subFlag == false) {
			return m_mainSprite.MulColor.w;
		}
		else {
			return m_subSprite.MulColor.w;
		}
	}

	//グラフィカルなアレンジを！！

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

	struct SpriteData
	{
		CVector3 Position = CVector3::Zero();
		CQuaternion Rotation = CQuaternion().Identity();
		CVector3 Scale = CVector3().One();
		CVector2 Pivot = { 0.5f, 0.5f };
		float Wide = 0.0f;	//幅！
		float High = 0.0f;	//高さ！
		CVector4 MulColor = { 1.0f,1.0f,1.0f,1.0f };	//!<乗算カラー。
	};

	//ID3D11ShaderResourceView* m_texture;	//!<テクスチャ。
	Sprite m_sprite;		//!<スプライト。

	SpriteData m_mainSprite;	//メインスプライト
	SpriteData m_subSprite;		//サブスプライト（マスクを作るときに使います！）

	bool m_subSpriteFlag = false;	//サブスプライト使用中？？？

	Sprite_RenderMode m_sprite_RenderMode = Sprite_RenderMode::Normal;
	float m_pos_Cut = 0.0f;				//CutMode時、どこから切る？？？？

};

