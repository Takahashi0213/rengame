#pragma once

/*

↓スプライト番号の位置関係

①②③
④⑤⑥
⑦⑧⑨

*/

class SliceSprite
{
public:
	SliceSprite();
	~SliceSprite();

	/// <summary>
	/// 基本サイズを設定
	/// </summary>
	void SetDefSize(const CVector2& size) {
		m_texWide = size.x;
		m_texHigh = size.y;
	}

	/// <summary>
	/// Init用
	/// </summary>
	void SetTex(const wchar_t* tex, const float& w, const float& h) {
		//面倒な処理
		m_sprite1.Sprite_Init(tex, w, h);
		m_sprite2.Sprite_Init(tex, w, h);
		m_sprite3.Sprite_Init(tex, w, h);
		m_sprite4.Sprite_Init(tex, w, h);
		m_sprite5.Sprite_Init(tex, w, h);
		m_sprite6.Sprite_Init(tex, w, h);
		m_sprite7.Sprite_Init(tex, w, h);
		m_sprite8.Sprite_Init(tex, w, h);
		m_sprite9.Sprite_Init(tex, w, h);
	}
	void SetColor(const CVector4& col) {
		m_sprite1.SetMulColor(col);
		m_sprite2.SetMulColor(col);
		m_sprite3.SetMulColor(col);
		m_sprite4.SetMulColor(col);
		m_sprite5.SetMulColor(col);
		m_sprite6.SetMulColor(col);
		m_sprite7.SetMulColor(col);
		m_sprite8.SetMulColor(col);
		m_sprite9.SetMulColor(col);
	}

	/// <summary>
	/// 設定します
	/// </summary>
	void SetSliceData(
		const CVector3& pos,
		const CQuaternion& rot,
		const CVector3& scale,
		const CVector2& Pivot,
		const float& wide,
		const float& high,
		const CVector4& color
	) {
		m_meinSpriteData.Position = pos;
		m_meinSpriteData.Rotation = rot;
		m_meinSpriteData.Scale = scale;
		m_meinSpriteData.Pivot.x = Pivot.x;
		m_meinSpriteData.Pivot.y = Pivot.y;
		m_meinSpriteData.Wide = wide;
		m_meinSpriteData.High = high;
		m_meinSpriteData.MulColor = color;
		
		SetMulColor();

		if (m_3sliceFlag == false) {
			SpriteDataSlice();
		}
		else {
			SpriteDataSlice3();
		}
		SpriteUpdate();
	}

	void SliceSpriteDraw();

	/// <summary>
	/// 3スライスに変更
	/// </summary>
	void Change3Slice(const float& size);

private:
	/// <summary>
	/// メインスプライトデータを参考に9つのスプライトを設定します
	/// </summary>
	void SpriteDataSlice();
	void SpriteDataSlice3();

	void SetMulColor() {
		for (int i = 0; i < 9; i++) {
			m_sprite[i]->SetMulColor(m_meinSpriteData.MulColor);
		}
	}

	void SpriteUpdate() {

		m_sprite1.Sprite_Update(m_sprite1.m_mainSprite.Position,
			m_sprite1.m_mainSprite.Rotation,
			m_sprite1.m_mainSprite.Scale,
			m_sprite1.m_mainSprite.Pivot);
		m_sprite2.Sprite_Update(m_sprite2.m_mainSprite.Position,
			m_sprite2.m_mainSprite.Rotation,
			m_sprite2.m_mainSprite.Scale,
			m_sprite2.m_mainSprite.Pivot);
		m_sprite3.Sprite_Update(m_sprite3.m_mainSprite.Position,
			m_sprite3.m_mainSprite.Rotation,
			m_sprite3.m_mainSprite.Scale,
			m_sprite3.m_mainSprite.Pivot);
		m_sprite4.Sprite_Update(m_sprite4.m_mainSprite.Position,
			m_sprite4.m_mainSprite.Rotation,
			m_sprite4.m_mainSprite.Scale,
			m_sprite4.m_mainSprite.Pivot);
		m_sprite5.Sprite_Update(m_sprite5.m_mainSprite.Position,
			m_sprite5.m_mainSprite.Rotation,
			m_sprite5.m_mainSprite.Scale,
			m_sprite5.m_mainSprite.Pivot);
		m_sprite6.Sprite_Update(m_sprite6.m_mainSprite.Position,
			m_sprite6.m_mainSprite.Rotation,
			m_sprite6.m_mainSprite.Scale,
			m_sprite6.m_mainSprite.Pivot);
		m_sprite7.Sprite_Update(m_sprite7.m_mainSprite.Position,
			m_sprite7.m_mainSprite.Rotation,
			m_sprite7.m_mainSprite.Scale,
			m_sprite7.m_mainSprite.Pivot);
		m_sprite8.Sprite_Update(m_sprite8.m_mainSprite.Position,
			m_sprite8.m_mainSprite.Rotation,
			m_sprite8.m_mainSprite.Scale,
			m_sprite8.m_mainSprite.Pivot);
		m_sprite9.Sprite_Update(m_sprite9.m_mainSprite.Position,
			m_sprite9.m_mainSprite.Rotation,
			m_sprite9.m_mainSprite.Scale,
			m_sprite9.m_mainSprite.Pivot);
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
	SpriteData m_meinSpriteData;	//5番目のこと

	//スプライトども
	Sprite* m_sprite[9];
	Sprite m_sprite1;
	Sprite m_sprite2;
	Sprite m_sprite3;
	Sprite m_sprite4;
	Sprite m_sprite5;
	Sprite m_sprite6;
	Sprite m_sprite7;
	Sprite m_sprite8;
	Sprite m_sprite9;

	//データ
	float m_texWide = 0.0f;		//元々の画像の横サイズ
	float m_texHigh = 0.0f;		//元々の画像の縦サイズ

	bool m_3sliceFlag = false;	//trueなら3sliceとして扱われる（sprite1～3のみ使用）
	float m_cutSize = 0.0f;		//3Slice用横サイズ（調整してね）

};

