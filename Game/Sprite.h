#pragma once
#include "graphics/Shader.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
	
	void Sprite_Init(const wchar_t* texFilePath, float w, float h);
	void Sprite_Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });
	void Sprite_Draw();

	/// <summary>
	/// ��Z�J���[��ݒ�
	/// </summary>
	/// <param name="mulColor">��Z�J���[</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	/// <returns>��Z�J���[</returns>
	CVector4 GetMulColor()
	{
		return m_mulColor;
	}

	//���[���h�r���[�v���W�F�N�V�����s��
	struct ConstantBuffer {
		CMatrix WVP;
		CVector4 mulColor;	//��Z�J���[
	};
	//�����o�ϐ�
	ID3D11Buffer* m_vertexBuffer = NULL;	//���_�o�b�t�@
	ID3D11Buffer* m_indexBuffer = NULL;		//�C���f�b�N�X�o�b�t�@
	Shader	m_ps;		//!<�s�N�Z���V�F�[�_�[�B
	Shader	m_vs;		//!<���_�V�F�[�_�[�B
	ID3D11ShaderResourceView* m_texture = NULL;		//�e�N�X�`��
	ID3D11SamplerState* m_samplerState = NULL;	//�T���v���X�e�[�g

	CVector3 m_position = CVector3::Zero();		//���W
	CQuaternion	m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();		//�g�嗦
	CVector4 m_mulColor = CVector4().White();	//!<��Z�J���[�B

	CMatrix	m_world = CMatrix::Identity();		//���[���h�s��
	CVector2 m_size = CVector2::Zero();		//�摜�̃T�C�Y
	ID3D11Buffer* m_cb = nullptr;		//�萔�o�b�t�@
	bool m_isInited = false;	//!<�������t���O�B
private:
	void Sprite::InitConstantBuffer();

};

