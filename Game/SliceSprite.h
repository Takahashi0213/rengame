#pragma once

/*

���X�v���C�g�ԍ��̈ʒu�֌W

�@�A�B
�C�D�E
�F�G�H

*/

class SliceSprite
{
public:
	SliceSprite();
	~SliceSprite();

	/// <summary>
	/// ��{�T�C�Y��ݒ�
	/// </summary>
	void SetDefSize(CVector2 size) {
		m_texWide = size.x;
		m_texHigh = size.y;
	}

	/// <summary>
	/// Init�p
	/// </summary>
	void SetTex(const wchar_t* tex,float w,float h) { //�߂�ǂ������ȃR��
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
	void SetColor(CVector4 col) {
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
	/// �ݒ肵�܂�
	/// </summary>
	void SetSliceData(
		CVector3 pos,
		CQuaternion rot,
		CVector3 scale,
		CVector2 Pivot,
		float wide,
		float high,
		CVector4 color
	) {
		m_meinSpriteData.Position = pos;
		m_meinSpriteData.Rotation = rot;
		m_meinSpriteData.Scale = scale;
		m_meinSpriteData.Pivot.x = Pivot.x;
		m_meinSpriteData.Pivot.y = Pivot.y;
		m_meinSpriteData.Wide = wide;
		m_meinSpriteData.High = high;
		m_meinSpriteData.MulColor = color;
		
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
	/// 3�X���C�X�ɕύX
	/// </summary>
	void Change3Slice(float size);

private:
	/// <summary>
	/// ���C���X�v���C�g�f�[�^���Q�l��9�̃X�v���C�g��ݒ肵�܂�
	/// </summary>
	void SpriteDataSlice();
	void SpriteDataSlice3();
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
		float Wide = 0.0f;	//���I
		float High = 0.0f;	//�����I
		CVector4 MulColor = { 1.0f,1.0f,1.0f,1.0f };	//!<��Z�J���[�B
	};
	SpriteData m_meinSpriteData;	//5�Ԗڂ̂���

	//�X�v���C�g�ǂ�
	Sprite m_sprite1;
	Sprite m_sprite2;
	Sprite m_sprite3;
	Sprite m_sprite4;
	Sprite m_sprite5;
	Sprite m_sprite6;
	Sprite m_sprite7;
	Sprite m_sprite8;
	Sprite m_sprite9;

	//�f�[�^
	float m_texWide = 0.0f;		//���X�̉摜�̉��T�C�Y
	float m_texHigh = 0.0f;		//���X�̉摜�̏c�T�C�Y

	bool m_3sliceFlag = false;	//true�Ȃ�3slice�Ƃ��Ĉ�����isprite1�`3�̂ݎg�p�j
	float m_cutSize = 0.0f;		//3Slice�p���T�C�Y�i�������Ăˁj

};

