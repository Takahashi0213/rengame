#include "stdafx.h"
#include "SliceSprite.h"


SliceSprite::SliceSprite()
{
	m_sprite1.m_slicePattern = 1;
	m_sprite2.m_slicePattern = 2;
	m_sprite3.m_slicePattern = 3;
	m_sprite4.m_slicePattern = 4;
	m_sprite5.m_slicePattern = 5;
	m_sprite6.m_slicePattern = 6;
	m_sprite7.m_slicePattern = 7;
	m_sprite8.m_slicePattern = 8;
	m_sprite9.m_slicePattern = 9;
	//
	m_sprite1.m_renderMode = Sprite_RenderMode::Slice9;
	m_sprite2.m_renderMode = Sprite_RenderMode::Slice9;
	m_sprite3.m_renderMode = Sprite_RenderMode::Slice9;
	m_sprite4.m_renderMode = Sprite_RenderMode::Slice9;
	m_sprite5.m_renderMode = Sprite_RenderMode::Slice9;
	m_sprite6.m_renderMode = Sprite_RenderMode::Slice9;
	m_sprite7.m_renderMode = Sprite_RenderMode::Slice9;
	m_sprite8.m_renderMode = Sprite_RenderMode::Slice9;
	m_sprite9.m_renderMode = Sprite_RenderMode::Slice9;
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

void SliceSprite::Change3Slice(float size) {
	m_3sliceFlag = true;
	m_sprite1.m_slicePattern = 100;
	m_sprite2.m_slicePattern = 101;
	m_sprite3.m_slicePattern = 102;
	m_cutSize = size;
}

void SliceSprite::SpriteDataSlice() {

	//�傫���v�Z���Ă����܂����`�`
	float halfX = m_meinSpriteData.Wide / 2.0f;
	float halfY = m_meinSpriteData.High / 2.0f;
	float X_Cut = m_texWide / 3.0f;
	float Y_Cut = m_texHigh / 3.0f;
	X_Cut *= (m_meinSpriteData.Wide / m_texWide);
	Y_Cut *= (m_meinSpriteData.High / m_texHigh);
	float MaxCut = max(X_Cut, Y_Cut);
	//�ł��������
	if (MaxCut > m_meinSpriteData.Wide) {
		MaxCut = m_meinSpriteData.Wide;
	}
	if (MaxCut > m_meinSpriteData.High) {
		MaxCut = m_meinSpriteData.High;
	}

	//�܂��l��(1,3,7,9)�͑傫��������Ŋm�肵�܂�
	m_sprite1.SetSize({ MaxCut,MaxCut });
	m_sprite3.SetSize({ MaxCut,MaxCut });
	m_sprite7.SetSize({ MaxCut,MaxCut });
	m_sprite9.SetSize({ MaxCut,MaxCut });

	//�L�т镔���̑傫�����v�Z
	float LongX = (m_meinSpriteData.Wide * 3.0f) - (MaxCut*2.0f);
	float LongY = (m_meinSpriteData.High * 3.0f) - (MaxCut*2.0f);

	//����ŐL�т�[�i2,4,6,8�j���m��
	m_sprite2.SetSize({ LongX,MaxCut });
	m_sprite4.SetSize({ MaxCut,LongY });
	m_sprite6.SetSize({ MaxCut,LongY });
	m_sprite8.SetSize({ LongX,MaxCut });
	//�����i5�j�����܂�
	m_sprite5.SetSize({ LongX,LongY });

	//����������W�v�Z

	//��_�͍ŏ��ɕύX���Ă���̂Ō�͒�������_�ɏꏊ�����߂邾���I
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

	//������������
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
	
	//���[�̃T�C�Y
	m_sprite1.SetSize({ m_cutSize,m_meinSpriteData.High });
	m_sprite3.SetSize({ m_cutSize,m_meinSpriteData.High });

	//�����̃T�C�Y
	float LongX = (m_meinSpriteData.Wide * 3.0f) - (m_cutSize*2.0f);
	m_sprite2.SetSize({ LongX,m_meinSpriteData.High });

	//���W
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