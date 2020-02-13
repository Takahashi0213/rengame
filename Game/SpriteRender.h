#pragma once
#include "system/CGameObjectManager.h"
#include "Sprite.h"
#include "MaskSprite.h"
#include "SliceSprite.h"
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
	void Init(const wchar_t* texFilePath, float w, float h, CVector3 pos = CVector3().Zero(),
		CVector4 color = CVector4().White(), int priority = 0);

	void InitSub(const wchar_t* texFilePath, float w, float h, int priority = 0);
	void InitSub(const wchar_t* texFilePath, float w, float h, CVector3 pos = CVector3().Zero(),
		CVector4 color = CVector4().White(), int priority = 0);

	/// <summary>
	/// このスプライトをマスクスプライトに指定する場合、Initの前に必ず実行しようね
	/// </summary>
	void ChangeMaskSprite() {

		if (m_sliceSpriteFlag == true) {
			abort();	//浮気じゃん！
		}

		if (m_maskSprite == nullptr) {
			m_maskSprite = new MaskSprite;
		}

		m_subSpriteFlag = true;
	}
	//こっちはスライススプライト
	void ChangeSliceSprite(CVector2 size) {

		if (m_subSpriteFlag == true) {
			abort();	//浮気じゃん！
		}

		if (m_sliceSprite == nullptr) {
			m_sliceSprite = new SliceSprite;
		}
		m_sprite_RenderMode = Sprite_RenderMode::Slice9;
		m_sliceSprite->SetDefSize(size);
		m_sliceSpriteFlag = true;
	}

	//設定色々
	//全てのsubFlagはfalseならメインスプライト、trueならサブスプライトを変更します

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3 pos, int list = -1)
	{
		if (list == -1) {
			m_mainSprite.Position = pos;
		}
		else {
			m_subSprite[list].Position = pos;
		}
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3 GetPosition(int list = -1) const
	{
		if (list == -1) {
			return m_mainSprite.Position;
		}
		else {
			return m_subSprite[list].Position;
		}
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot, int list = -1)
	{
		if (list == -1) {
			m_mainSprite.Rotation = rot;
		}
		else {
			m_subSprite[list].Rotation = rot;
		}
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns>回転</returns>
	const CQuaternion GetRotation(int list = -1) const
	{
		if (list == -1) {
			return m_mainSprite.Rotation;
		}
		else {
			return m_subSprite[list].Rotation;
		}
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scr">拡大率</param>
	void SetScale(const CVector3 scl, int list = -1)
	{
		if (list == -1) {
			m_mainSprite.Scale = scl;
		}
		else {
			m_subSprite[list].Scale = scl;
		}
	}
	void SetScale(const float scl, int list = -1) { //便利Ver
		if (list == -1) {
			m_mainSprite.Scale.x = scl;
			m_mainSprite.Scale.y = scl;
		}
		else {
			m_subSprite[list].Scale.x = scl;
			m_subSprite[list].Scale.y = scl;
		}
	}
	/// <summary>
	/// 拡大率を取得
	/// </summary>
	/// <returns>拡大率</returns>
	const CVector3 GetScale(int list = -1) const
	{
		if (list == -1) {
			return m_mainSprite.Scale;
		}
		else {
			return m_subSprite[list].Scale;
		}
	}
	/// <summary>
	/// ピボットを設定
	/// </summary>
	/// <param name="pivot">ピボット</param>
	void SetPivot(const CVector2 pivot , int list = -1)
	{
		if (list == -1) {
			m_mainSprite.Pivot.x = pivot.x;
			m_mainSprite.Pivot.y = pivot.y;
		}
		else {
			m_subSprite[list].Pivot.x = pivot.x;
			m_subSprite[list].Pivot.y = pivot.y;
		}
	}
	/// <summary>
	/// ピボットを取得
	/// </summary>
	/// <returns>ピボット</returns>
	CVector2 GetPivot(int list = -1)
	{
		if (list == -1) {
			return m_mainSprite.Pivot;
		}
		else {
			return m_subSprite[list].Pivot;
		}
	}

	/// <summary>
	/// 幅を取得
	/// </summary>
	/// <returns>幅</returns>
	float GetWide(int list = -1)
	{
		if (list == -1) {
			return m_mainSprite.Wide;
		}
		else {
			return m_subSprite[list].Wide;
		}
	}
	/// <summary>
	/// 高さを取得
	/// </summary>
	/// <returns>高さ</returns>
	float GetHigh(int list = -1)
	{
		if (list == -1) {
			return m_mainSprite.High;
		}
		else {
			return m_subSprite[list].High;
		}
	}

	/// <summary>
	/// 乗算カラーを設定
	/// </summary>
	/// <param name="mulColor">乗算カラー</param>
	void SetMulColor(const CVector4& mulColor, int list = -1)
	{
		if (list == -1) {
			m_mainSprite.MulColor = mulColor;
			m_sprite.SetMulColor(m_mainSprite.MulColor);
		}
		else {
			m_subSprite[list].MulColor = mulColor;
			m_maskSprite->GetSubList_Sprite(list)->SetMulColor(mulColor);
		}
	}
	/// <summary>
	/// 乗算カラーを取得
	/// </summary>
	/// <returns>乗算カラー</returns>
	CVector4 GetMulColor(int list = -1)
	{
		if (list == -1) {
			return m_mainSprite.MulColor;
		}
		else {
			return m_subSprite[list].MulColor;
		}
	}
	/// <summary>
	/// アルファの設定
	/// </summary>
	/// <param name="Alpha">アルファ</param>
	void SetAlpha(const float Alpha, int list = -1) {

		if (list == -1) {
			m_mainSprite.MulColor.w = Alpha;
			m_sprite.SetMulColor(m_mainSprite.MulColor);
		}
		else {
			m_subSprite[list].MulColor.w = Alpha;
			m_maskSprite->GetSubList_Sprite(list)->SetMulColor(m_subSprite[list].MulColor);
		}
	}
	/// <summary>
	/// アルファの取得
	/// </summary>
	/// <returns>現在の不透明度だ</returns>
	float GetAlpha(int list = -1) {
		if (list == -1) {
			return m_mainSprite.MulColor.w;
		}
		else {
			return m_subSprite[list].MulColor.w;
		}
	}

	//パターン取得関連
	int GetMaxPattern() {
		return m_pattern;
	}
	int GetNowPattern() {
		return m_nowPattern;
	}

	/// <summary>
	/// マスクスプライトの使用フラグ
	/// </summary>
	/// <returns>
	/// falseならマスクスプライトではない
	/// trueならこいつはマスクスプライト
	/// </returns>
	bool GetMaskSpriteFlag() {
		if (m_maskSprite == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}
	/// <summary>
	/// サブスプライトの数を返す
	/// </summary>
	int GetSubSpriteNum() {
		return (int)m_subSprite.size();
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
	float GetCutLine() {
		return m_pos_Cut;
	}

	/// <summary>
	/// SliceSpriteなら3Sliceに変更する
	/// </summary>
	void Set3Slice(float size) {
		if (m_sliceSprite != nullptr) {
			m_sliceSprite->Change3Slice(size);
		}
	}

	/// <summary>
	/// 縦パターンの設定
	/// </summary>
	/// <param name="pt">パターン数</param>
	void SetHighPattern(int pattern,int nowPt = 0) {
		m_sprite.m_renderMode = Sprite_RenderMode::Pattern;
		m_sprite.m_slicePattern = pattern;
		m_pattern = pattern;
		m_defPosition = m_mainSprite.Position;
		m_nowPattern = nowPt;
		ChangePattern(m_nowPattern);
	}

	void ChangePattern(int pattern);

	/// <summary>
	/// マウスが自分に重なってたらTrueを返す
	/// </summary>
	/// <returns>重なってる？？？？？</returns>
	bool MouseOverMouse();

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
	//サブサポーターの取得
	SpriteSupporter* GetSubSpriteSupporter(int No) {
		return m_subSpriteSupporter[No];
	}

private:
	//マスクスプライトなら実行される
	void MaskSpriteDataSet();
	//スプライトサポーターの更新
	void SpriteSp_Update() {
		//メイン
		m_spriteSupporter.SpriteSupporter_Update();
		//サブゥ
		for (int i = 0; i < m_subSpriteSupporter.size(); i++) {
			m_subSpriteSupporter[i]->SpriteSupporter_Update();
		}
	}

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

	Sprite m_sprite;		//!<スプライト。
	MaskSprite* m_maskSprite = nullptr;
	SliceSprite* m_sliceSprite = nullptr;

	SpriteData m_mainSprite;	//メインスプライト
	std::vector<SpriteData> m_subSprite;		//サブスプライト
	std::vector<SpriteSupporter*> m_subSpriteSupporter;		//さぶすぷ・さぽおたあ

	bool m_subSpriteFlag = false;	//サブスプライト使用中？？？
	bool m_sliceSpriteFlag = false;	//slice9スプライト使用中？？？

	Sprite_RenderMode m_sprite_RenderMode = Sprite_RenderMode::Normal;	//レンダーモード
	float m_pos_Cut = 0.0f;				//CutMode時、どこから切る？？？？

	int m_pattern = -1;					//縦パターン数
	int m_nowPattern = 0;				//現在パターン
	CVector3 m_defPosition = CVector3::Zero();	//Pos一時保存
};

