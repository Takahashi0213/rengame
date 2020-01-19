#include "stdafx.h"
#include "SpriteRender.h"

SpriteRender::SpriteRender()
{
	//タグをスプライトに変更
	this->SetObjectTag(IGameObject::t_Sprite);
	//スプライトサポーターにアドレスを渡しておく
	m_spriteSupporter.SpriteRenderSetting(this);
}


SpriteRender::~SpriteRender()
{
}

/// <summary>
/// スプライトを初期化する
/// </summary>
/// <remarks>
/// ☆サンプルコード☆
/// 
/// 	SpriteRender* r = NewGO<SpriteRender>(名前);
///		r->Init(L"ファイルパス", 100.0f, 100.0f);
/// 
/// </remarks>
/// <param name="texFilePath">ファイルパス</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
/// <param name="priority">優先度（大きい方が上に表示される）
/// 指定しなかった場合は0</param>
void SpriteRender::Init(const wchar_t* texFilePath, float w, float h, int priority)
{
	m_mainSprite.Wide = w;
	m_mainSprite.High = h;

	if (m_subSpriteFlag == false && m_sliceSpriteFlag == false) {
		m_sprite.Sprite_Init(texFilePath, w, h); //描画する
		m_sprite.SetMulColor(m_mainSprite.MulColor);
	}
	else if (m_sliceSpriteFlag == true) {
		m_sliceSprite->SetTex(texFilePath, w, h); //描画する
		m_sliceSprite->SetColor(m_mainSprite.MulColor);
	}
	else {
		m_maskSprite->GetMainSprite()->Sprite_Init(texFilePath, w, h); //描画する
		m_maskSprite->GetMainSprite()->SetMulColor(m_mainSprite.MulColor);
		//サブスプライトも設定
		m_maskSprite->GetSubSprite()->Sprite_InitSub(texFilePath);
	}
}
void SpriteRender::InitSub(const wchar_t* texFilePath, float w, float h, int priority)
{
	m_subSprite.Wide = w;
	m_subSprite.High = h;
	m_maskSprite->GetSubSprite()->Sprite_Init(texFilePath, w, h); //描画する
	m_maskSprite->GetSubSprite()->SetMulColor(m_subSprite.MulColor);
}

/// <summary>
/// スプライトを初期化する（便利Ver）
/// </summary>
/// <remarks>
/// ☆サンプルコード☆
/// 
/// 	SpriteRender* r = NewGO<SpriteRender>(名前);
///		r->Init(L"ファイルパス", 100.0f, 100.0f);
/// 
/// </remarks>
/// <param name="texFilePath">ファイルパス</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
/// <param name="pos">初期座標</param>
/// <param name="priority">優先度（大きい方が上に表示される）
/// 指定しなかった場合は0</param>
void SpriteRender::Init(const wchar_t* texFilePath, float w, float h, CVector3 pos, CVector4 color, int priority) {

	m_mainSprite.Wide = w;
	m_mainSprite.High = h;
	m_mainSprite.MulColor = color;
	m_mainSprite.Position = pos;

	if (m_subSpriteFlag == false && m_sliceSpriteFlag == false) {
		m_sprite.Sprite_Init(texFilePath, w, h); //描画する
		m_sprite.SetMulColor(m_mainSprite.MulColor);
	}
	else if (m_sliceSpriteFlag == true) {
		m_sliceSprite->SetTex(texFilePath, w, h); //描画する
		m_sliceSprite->SetColor(m_mainSprite.MulColor);
	}
	else {
		m_maskSprite->GetMainSprite()->Sprite_Init(texFilePath, w, h); //描画する
		m_maskSprite->GetMainSprite()->SetMulColor(m_mainSprite.MulColor);
		//サブスプライトも設定
		m_maskSprite->GetSubSprite()->Sprite_InitSub(texFilePath);
	}
}
void SpriteRender::InitSub(const wchar_t* texFilePath, float w, float h, CVector3 pos, CVector4 color, int priority) {

	m_subSprite.Wide = w;
	m_subSprite.High = h;
	m_maskSprite->GetSubSprite()->Sprite_Init(texFilePath, w, h); //描画する
	m_subSprite.MulColor = color;
	m_maskSprite->GetSubSprite()->SetMulColor(m_subSprite.MulColor);
	m_subSprite.Position = pos;
}

/// <summary>
/// スプライトの情報をアップデート
/// </summary>
void SpriteRender::Update() {

	m_spriteSupporter.SpriteSupporter_Update();

	if (m_maskSprite != nullptr) {	
		//マスクスプライトの処理
		MaskSpriteDataSet();

		m_maskSprite->GetMainSprite()->Sprite_Update(m_mainSprite.Position, m_mainSprite.Rotation, m_mainSprite.Scale, m_mainSprite.Pivot);
		m_maskSprite->GetSubSprite()->Sprite_Update(m_subSprite.Position, m_subSprite.Rotation, m_subSprite.Scale, m_subSprite.Pivot);
	}
	else if (m_sliceSprite != nullptr) {
		//準備
		m_sliceSprite->SetSliceData(m_mainSprite.Position, m_mainSprite.Rotation, m_mainSprite.Scale,
			m_mainSprite.Pivot, m_mainSprite.Wide, m_mainSprite.High, m_mainSprite.MulColor);
	}
	else {
		m_sprite.Sprite_Update(m_mainSprite.Position, m_mainSprite.Rotation, m_mainSprite.Scale, m_mainSprite.Pivot);
	}
}

/// <summary>
/// スプライトを描画する
/// </summary>
void SpriteRender::Render() {

	if (m_subSpriteFlag == false && m_sliceSpriteFlag == false) {
		m_sprite.Sprite_Draw();		//通常スプライト
	}	
	else if (m_sliceSpriteFlag == true) {
		m_sliceSprite->SliceSpriteDraw();	//スライススプライト
	}
	else {
		m_maskSprite->Draw();		//マスクスプライト
	}
}

/// <summary>
/// マスクスプライトのデータを更新する
/// </summary>
void SpriteRender::MaskSpriteDataSet() {

	m_maskSprite->SetPosition(m_mainSprite.Position);
	m_maskSprite->SetPosition(m_subSprite.Position, true);

	m_maskSprite->SetRotation(m_mainSprite.Rotation);
	m_maskSprite->SetRotation(m_subSprite.Rotation, true);

	m_maskSprite->SetScale(m_mainSprite.Scale);
	m_maskSprite->SetScale(m_subSprite.Scale, true);

	m_maskSprite->SetPivot(m_mainSprite.Pivot);
	m_maskSprite->SetPivot(m_subSprite.Pivot, true);

	m_maskSprite->SetSize({ m_mainSprite.Wide,m_mainSprite.High });
	m_maskSprite->SetSize({ m_mainSprite.Wide,m_mainSprite.High }, true);

	m_maskSprite->SetMulColor(m_mainSprite.MulColor);
	m_maskSprite->SetMulColor(m_subSprite.MulColor, true);

}

/// <summary>
/// パターンの変更と同時に座標も更新する
/// </summary>
/// <param name="pattern">現在パターン</param>
void SpriteRender::ChangePattern(int pattern) {

	m_nowPattern = pattern;
	m_sprite.m_nowPattern = pattern;
	m_mainSprite.Pivot.x = 0.5f;
	m_mainSprite.Pivot.y = 1.0f;
	float OneSize = m_mainSprite.High / (float)m_pattern;		//パターン1つの大きさを計算

	m_mainSprite.Position.y = m_defPosition.y + (OneSize * (float)pattern);
}