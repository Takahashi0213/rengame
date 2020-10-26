#include "stdafx.h"
#include "SliceSprite.h"


SliceSprite::SliceSprite()
{
	m_sprite[0] = &m_sprite1;
	m_sprite[1] = &m_sprite2;
	m_sprite[2] = &m_sprite3;
	m_sprite[3] = &m_sprite4;
	m_sprite[4] = &m_sprite5;
	m_sprite[5] = &m_sprite6;
	m_sprite[6] = &m_sprite7;
	m_sprite[7] = &m_sprite8;
	m_sprite[8] = &m_sprite9;

	for (int i = 0; i < 9; i++) {
		m_sprite[i]->m_slicePattern = i+1;
		m_sprite[i]->m_renderMode = Sprite_RenderMode::Slice9;
	}

	//pivot
	m_sprite1.m_mainSprite.Pivot.x = 0.0f;
	m_sprite1.m_mainSprite.Pivot.y = 1.0f;
	m_sprite2.m_mainSprite.Pivot.y = 1.0f;
	m_sprite3.m_mainSprite.Pivot.x = 1.0f;
	m_sprite3.m_mainSprite.Pivot.y = 1.0f;
	m_sprite4.m_mainSprite.Pivot.x = 0.0f;
	m_sprite6.m_mainSprite.Pivot.x = 1.0f;
	m_sprite7.m_mainSprite.Pivot.x = 0.0f;
	m_sprite7.m_mainSprite.Pivot.y = 0.0f;
	m_sprite8.m_mainSprite.Pivot.y = 0.0f;
	m_sprite9.m_mainSprite.Pivot.x = 1.0f;
	m_sprite9.m_mainSprite.Pivot.y = 0.0f;
}

SliceSprite::~SliceSprite()
{
}

void SliceSprite::Change3Slice(const float& size) {
	m_3sliceFlag = true;
	m_sprite1.m_slicePattern = 100;
	m_sprite2.m_slicePattern = 101;
	m_sprite3.m_slicePattern = 102;
	m_cutSize = size;
}

void SliceSprite::SpriteDataSlice() {

	//大きさ計算していきます
	float halfX = m_meinSpriteData.Wide / 2.0f;
	float halfY = m_meinSpriteData.High / 2.0f;
	float X_Cut = m_texWide / 3.0f;
	float Y_Cut = m_texHigh / 3.0f;
	X_Cut *= (m_meinSpriteData.Wide / m_texWide);
	Y_Cut *= (m_meinSpriteData.High / m_texHigh);
	float MaxCut = max(X_Cut, Y_Cut);
	//でかすぎる
	if (MaxCut > m_meinSpriteData.Wide) {
		MaxCut = m_meinSpriteData.Wide;
	}
	if (MaxCut > m_meinSpriteData.High) {
		MaxCut = m_meinSpriteData.High;
	}

	//まず四隅(1,3,7,9)は大きさがこれで確定します
	m_sprite1.SetSize({ MaxCut,MaxCut });
	m_sprite3.SetSize({ MaxCut,MaxCut });
	m_sprite7.SetSize({ MaxCut,MaxCut });
	m_sprite9.SetSize({ MaxCut,MaxCut });

	//伸びる部分の大きさを計算
	float LongX = (m_meinSpriteData.Wide * 3.0f) - (MaxCut*2.0f);
	float LongY = (m_meinSpriteData.High * 3.0f) - (MaxCut*2.0f);

	//これで伸びる端（2,4,6,8）も確定
	m_sprite2.SetSize({ LongX,MaxCut });
	m_sprite4.SetSize({ MaxCut,LongY });
	m_sprite6.SetSize({ MaxCut,LongY });
	m_sprite8.SetSize({ LongX,MaxCut });
	//中央（5）も求まる
	m_sprite5.SetSize({ LongX,LongY });

	//ここから座標計算

	//基点は最初に変更しているので後は中央を基点に場所を決めるだけ！
	m_sprite1.m_mainSprite.Position.x = m_meinSpriteData.Position.x - halfX;
	m_sprite1.m_mainSprite.Position.y = m_meinSpriteData.Position.y + halfY;
	m_sprite1.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite2.m_mainSprite.Position.x = m_meinSpriteData.Position.x;
	m_sprite2.m_mainSprite.Position.y = m_meinSpriteData.Position.y + halfY;
	m_sprite2.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite3.m_mainSprite.Position.x = m_meinSpriteData.Position.x + halfX;
	m_sprite3.m_mainSprite.Position.y = m_meinSpriteData.Position.y + halfY;
	m_sprite3.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite4.m_mainSprite.Position.x = m_meinSpriteData.Position.x - halfX;
	m_sprite4.m_mainSprite.Position.y = m_meinSpriteData.Position.y;
	m_sprite4.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite5.m_mainSprite.Position.x = m_meinSpriteData.Position.x;
	m_sprite5.m_mainSprite.Position.y = m_meinSpriteData.Position.y;
	m_sprite5.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite6.m_mainSprite.Position.x = m_meinSpriteData.Position.x + halfX;
	m_sprite6.m_mainSprite.Position.y = m_meinSpriteData.Position.y;
	m_sprite6.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite7.m_mainSprite.Position.x = m_meinSpriteData.Position.x - halfX;
	m_sprite7.m_mainSprite.Position.y = m_meinSpriteData.Position.y - halfY;
	m_sprite7.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite8.m_mainSprite.Position.x = m_meinSpriteData.Position.x;
	m_sprite8.m_mainSprite.Position.y = m_meinSpriteData.Position.y - halfY;
	m_sprite8.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite9.m_mainSprite.Position.x = m_meinSpriteData.Position.x + halfX;
	m_sprite9.m_mainSprite.Position.y = m_meinSpriteData.Position.y - halfY;
	m_sprite9.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

}

void SliceSprite::SliceSpriteDraw() {

	//おえかき
	m_sprite1.Sprite_Draw();
	m_sprite2.Sprite_Draw();
	m_sprite3.Sprite_Draw();
	if (m_3sliceFlag == false) {
		m_sprite4.Sprite_Draw();
		m_sprite5.Sprite_Draw();
		m_sprite6.Sprite_Draw();
		m_sprite7.Sprite_Draw();
		m_sprite8.Sprite_Draw();
		m_sprite9.Sprite_Draw();
	}
}

void SliceSprite::SpriteDataSlice3() {

	m_sprite1.m_mainSprite.Pivot.x = 0.0f;
	m_sprite1.m_mainSprite.Pivot.y = 0.5f;
	m_sprite2.m_mainSprite.Pivot.x = 0.5f;
	m_sprite2.m_mainSprite.Pivot.y = 0.5f;
	m_sprite3.m_mainSprite.Pivot.x = 1.0f;
	m_sprite3.m_mainSprite.Pivot.y = 0.5f;

	float halfX = m_meinSpriteData.Wide / 2.0f;
	float halfY = m_meinSpriteData.High / 2.0f;
	
	//両端のサイズ
	m_sprite1.SetSize({ m_cutSize,m_meinSpriteData.High });
	m_sprite3.SetSize({ m_cutSize,m_meinSpriteData.High });

	//中央のサイズ
	float LongX = (m_meinSpriteData.Wide * 3.0f) - (m_cutSize*2.0f);
	m_sprite2.SetSize({ LongX,m_meinSpriteData.High });

	//座標
	m_sprite1.m_mainSprite.Position.x = m_meinSpriteData.Position.x - halfX;
	m_sprite1.m_mainSprite.Position.y = m_meinSpriteData.Position.y;
	m_sprite1.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite2.m_mainSprite.Position.x = m_meinSpriteData.Position.x;
	m_sprite2.m_mainSprite.Position.y = m_meinSpriteData.Position.y;
	m_sprite2.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

	m_sprite3.m_mainSprite.Position.x = m_meinSpriteData.Position.x + halfX;
	m_sprite3.m_mainSprite.Position.y = m_meinSpriteData.Position.y;
	m_sprite3.m_mainSprite.Position.z = m_meinSpriteData.Position.z;

}