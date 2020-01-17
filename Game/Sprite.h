#pragma once
#include "graphics/Shader.h"

enum Sprite_RenderMode {
	Normal,		//���ʂɕ`��
	X_Cut,		//X���J�b�g����
	Y_Cut,		//Y���J�b�g����
};

class Sprite
{
public:

	Sprite();
	~Sprite();
	
	//���C���X�v���C�g
	void Sprite_Init(const wchar_t* texFilePath, float w, float h);
	void Sprite_Init(ID3D11ShaderResourceView* srv, float w, float h);
	void Sprite_Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });
	//�T�u�X�v���C�g
	void Sprite_Init_Sub(const wchar_t* texFilePath, float w, float h);
	void Sprite_Init_Sub(ID3D11ShaderResourceView* srv, float w, float h);
	void Sprite_Update_Sub(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });

	/// <summary>
	/// ���C���X�v���C�g�ƃT�u�X�v���C�g�̍��킹�Z�iDraw�j���I
	/// </summary>
	void Sprite_Draw();

	/// <summary>
	/// ��Z�J���[��ݒ�
	/// </summary>
	/// <param name="mulColor">��Z�J���[</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mainSprite.MulColor = mulColor;
	}
	void SetMulColor_Sub(const CVector4& mulColor)
	{
		m_subSprite.MulColor = mulColor;
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	/// <returns>��Z�J���[</returns>
	CVector4 GetMulColor()
	{
		return m_mainSprite.MulColor;
	}

	struct ConstantBuffer {
		CMatrix WVP;	//���[���h�r���[�v���W�F�N�V�����s��
		CVector4 mulColor;	//��Z�J���[
		float cut_line;
	};
	struct SpriteData {
		ID3D11ShaderResourceView* Texture = NULL;		//�e�N�X�`��
		CVector3 Position = CVector3::Zero();
		CQuaternion Rotation = CQuaternion().Identity();
		CVector3 Scale = CVector3().One();
		CVector2 Pivot = { 0.5f, 0.5f };
		CVector4 MulColor = CVector4().White();	//!<��Z�J���[�B
		CMatrix	World = CMatrix::Identity();		//���[���h�s��
		CVector2 Size = CVector2::Zero();		//�摜�̃T�C�Y
	};

	//�����o�ϐ�
	ID3D11Buffer* m_vertexBuffer = NULL;	//���_�o�b�t�@
	ID3D11Buffer* m_indexBuffer = NULL;		//�C���f�b�N�X�o�b�t�@

	Shader	m_ps;		//!<�s�N�Z���V�F�[�_�[�B
	Shader	m_ps_X_Cut;	//!<X���J�b�g����s�N�Z���V�F�[�_�[�B
	Shader	m_ps_Y_Cut;	//!<Y���J�b�g����s�N�Z���V�F�[�_�[�B
	Shader	m_vs;		//!<���_�V�F�[�_�[�B
	ID3D11SamplerState* m_samplerState = NULL;	//�T���v���X�e�[�g

	//2�̃X�v���C�g�ł���B
	SpriteData m_mainSprite;
	SpriteData m_subSprite;

	ID3D11Buffer* m_cb = nullptr;		//�萔�o�b�t�@
	bool m_isInited = false;	//!<�������t���O�B

	Sprite_RenderMode m_renderMode = Normal;	//�����_�[���[�h
	float m_cut_UV = 0.5f;

private:
	/// <summary>
	/// 16�̔{���ɐ؂�グ�鏈��
	/// </summary>
	/// <param name="n">�؂�グ��������</param>
	/// <returns>16�̔{���ɐ؂�グ���l</returns>
	int Raundup16(int n)
	{
		return (((n - 1) / 16) + 1) * 16;
	}

	void Sprite::InitConstantBuffer();
	void Sprite::InitCommon(float w, float h);

};

