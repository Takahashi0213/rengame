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
	m_wide = w;
	m_high = h;
	m_sprite.Sprite_Init(texFilePath, w, h); //描画する
	m_sprite.SetMulColor(m_mulColor);
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
	m_wide = w;
	m_high = h;
	m_sprite.Sprite_Init(texFilePath, w, h); //描画する
	m_mulColor = color;
	m_sprite.SetMulColor(m_mulColor);
	m_position = pos;
}

/// <summary>
/// スプライトの情報をアップデート
/// </summary>
void SpriteRender::Update() {
	m_spriteSupporter.SpriteSupporter_Update();
	m_sprite.Sprite_Update(m_position, m_rotation, m_scale, m_pivot);
}

/// <summary>
/// スプライトを描画する
/// </summary>
void SpriteRender::Render() {
	m_sprite.Sprite_Draw();
}
