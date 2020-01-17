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
	m_sprite.Sprite_Init(texFilePath, w, h); //描画する
	m_sprite.SetMulColor(m_mainSprite.MulColor);
}
void SpriteRender::InitSub(const wchar_t* texFilePath, float w, float h, int priority)
{
	m_subSprite.Wide = w;
	m_subSprite.High = h;
	m_sprite.Sprite_Init_Sub(texFilePath, w, h); //描画する
	m_sprite.SetMulColor_Sub(m_subSprite.MulColor);
	m_subSpriteFlag = true;
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
	m_sprite.Sprite_Init(texFilePath, w, h); //描画する
	m_mainSprite.MulColor = color;
	m_sprite.SetMulColor(m_mainSprite.MulColor);
	m_mainSprite.Position = pos;
}
void SpriteRender::InitSub(const wchar_t* texFilePath, float w, float h, CVector3 pos, CVector4 color, int priority) {
	m_subSprite.Wide = w;
	m_subSprite.High = h;
	m_sprite.Sprite_Init_Sub(texFilePath, w, h); //描画する
	m_subSprite.MulColor = color;
	m_sprite.SetMulColor_Sub(m_subSprite.MulColor);
	m_subSprite.Position = pos;
	m_subSpriteFlag = true;
}

/// <summary>
/// スプライトの情報をアップデート
/// </summary>
void SpriteRender::Update() {
	m_spriteSupporter.SpriteSupporter_Update();
	m_sprite.Sprite_Update(m_mainSprite.Position, m_mainSprite.Rotation, m_mainSprite.Scale, m_mainSprite.Pivot);
	m_sprite.Sprite_Update_Sub(m_subSprite.Position, m_subSprite.Rotation, m_subSprite.Scale, m_subSprite.Pivot);
}

/// <summary>
/// スプライトを描画する
/// </summary>
void SpriteRender::Render() {
	m_sprite.Sprite_Draw();		//ここはメインスプライトとサブスプライト同時
}
