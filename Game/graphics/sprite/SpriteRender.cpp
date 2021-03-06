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

void SpriteRender::Init(const wchar_t* texFilePath, const float& w, const float& h, const int& priority)
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
	}
}

void SpriteRender::InitSub(const wchar_t* texFilePath, const float& w, const float& h, const int& priority)
{
	SpriteData data;
	m_subSprite.push_back(data);
	SpriteSupporter* SS = new SpriteSupporter;
	m_subSpriteSupporter.push_back(SS);
	SS->SpriteRenderSetting(this, (int)m_subSprite.size()-1);
	m_maskSprite->AddSubSprite(texFilePath, w, h);
}

void SpriteRender::Init(const wchar_t* texFilePath, const float& w, const float& h,
	const CVector3& pos, const CVector4& color, const int& priority) {

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
	}
}
void SpriteRender::InitSub(const wchar_t* texFilePath, const float& w, const float& h, const CVector3& pos,
	const CVector4& color, const int& priority) {

	SpriteData data;
	data.Wide = w;
	data.High = h;
	data.MulColor = color;
	data.Position = pos;
	m_subSprite.push_back(data);
	SpriteSupporter* SS = new SpriteSupporter;
	m_subSpriteSupporter.push_back(SS);
	SS->SpriteRenderSetting(this, (int)m_subSprite.size()-1);

	Sprite* newSp = m_maskSprite->AddSubSprite(texFilePath, w, h);
	newSp->SetMulColor(data.MulColor);
}

void SpriteRender::Update() {

	SpriteSp_Update();

	if (m_maskSprite != nullptr) {	
		//マスクスプライトの処理
		MaskSpriteDataSet();

		m_maskSprite->GetMainSprite()->Sprite_Update(m_mainSprite.Position, m_mainSprite.Rotation, 
			m_mainSprite.Scale, m_mainSprite.Pivot);
		if (m_subSprite.size() > 0) {
			for (int i = 0; i < m_subSprite.size() ; i++) {
				//サブ更新
				m_maskSprite->GetSubList_Sprite(i)->Sprite_Update(m_subSprite[i].Position,
					m_subSprite[i].Rotation, m_subSprite[i].Scale, m_subSprite[i].Pivot);
			}
		}
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

void SpriteRender::MaskSpriteDataSet() {

	//メイン
	m_maskSprite->SetPosition(m_mainSprite.Position);
	m_maskSprite->SetRotation(m_mainSprite.Rotation);
	m_maskSprite->SetScale(m_mainSprite.Scale);
	m_maskSprite->SetPivot(m_mainSprite.Pivot);
	m_maskSprite->SetSize({ m_mainSprite.Wide,m_mainSprite.High });
	m_maskSprite->SetMulColor(m_mainSprite.MulColor);
	//サブ
	if (m_subSprite.size() > 0) {
		for (int i = 0; i < m_subSprite.size(); i++) {
			//サブ更新
			m_maskSprite->SetPosition(m_subSprite[i].Position, i);
			m_maskSprite->SetRotation(m_subSprite[i].Rotation, i);
			m_maskSprite->SetScale(m_subSprite[i].Scale, i);
			m_maskSprite->SetPivot(m_subSprite[i].Pivot, i);
			m_maskSprite->SetSize({ m_subSprite[i].Wide,m_mainSprite.High }, i);
			m_maskSprite->SetMulColor(m_subSprite[i].MulColor, i);
		}
	}

}

void SpriteRender::ChangePattern(const int& pattern) {

	m_nowPattern = pattern;
	m_sprite.m_nowPattern = pattern;
	m_mainSprite.Pivot.x = 0.5f;
	m_mainSprite.Pivot.y = 1.0f;
	float OneSize = m_mainSprite.High / (float)m_pattern;		//パターン1つの大きさを計算

	m_mainSprite.Position.y = m_defPosition.y + (OneSize * (float)pattern);
}

bool SpriteRender::MouseOverMouse() {

	bool Flag = false;

	//アルファが0なら強制終了
	if (m_mainSprite.MulColor.w == 0.0f) {
		return Flag;
	}

	CVector2 MousePos = MouseSupporter::GetInstance()->GetMousePos_Sprite();

	//座標計算
	float PosX = m_mainSprite.Position.x + (m_mainSprite.Wide / 2.0f);
	float PosX2 = m_mainSprite.Position.x - (m_mainSprite.Wide / 2.0f);
	float PosY = m_mainSprite.Position.y + (m_mainSprite.High / 2.0f);
	float PosY2 = m_mainSprite.Position.y - (m_mainSprite.High / 2.0f);

	if (MousePos.x <= PosX && MousePos.x >= PosX2 && MousePos.y <= PosY && MousePos.y >= PosY2) {
		Flag = true;
	}

	return Flag;
}