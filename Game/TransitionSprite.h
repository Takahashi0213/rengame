#pragma once
#include "graphics/Shader.h"

class TransitionSprite
{
public:
	TransitionSprite();
	~TransitionSprite();

	//���C���X�v���C�g
	void Sprite_Init(const wchar_t* texFilePath, float w, float h);
	void Sprite_Update();
	void Sprite_Draw();

	struct ConstantBuffer {
		CMatrix WVP;	//���[���h�r���[�v���W�F�N�V�����s��
		float Alpha;	//��ɂȂ�A���t�@
	};
	struct SpriteData {
		ID3D11ShaderResourceView* Texture = NULL;		//�e�N�X�`��
		CVector3 Position = CVector3::Zero();
		CQuaternion Rotation = CQuaternion().Identity();
		CVector3 Scale = CVector3().One();
		CVector2 Pivot = { 0.5f, 0.5f };
		CMatrix	World = CMatrix::Identity();		//���[���h�s��
		CVector2 Size = CVector2::Zero();		//�摜�̃T�C�Y
	};

	//�����o�ϐ�
	ID3D11Buffer* m_vertexBuffer = NULL;	//���_�o�b�t�@
	ID3D11Buffer* m_indexBuffer = NULL;		//�C���f�b�N�X�o�b�t�@

	//�V�F�[�_�[
	Shader	m_ps;			//!<�s�N�Z���V�F�[�_�[�B
	Shader	m_vs;		//!<���_�V�F�[�_�[�B
	ID3D11SamplerState* m_samplerState = NULL;	//�T���v���X�e�[�g

	//�X�v���C�g�ł���B
	SpriteData m_mainSprite;
	float m_alpha = 0.0f;	//�g�����W�V�����̊

	ID3D11Buffer* m_cb = nullptr;		//�萔�o�b�t�@
	bool m_isInited = false;	//!<�������t���O�B

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

	void TransitionSprite::InitConstantBuffer();
	void TransitionSprite::InitCommon(float w, float h, bool cutFlag = false);

};

