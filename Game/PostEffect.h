#pragma once
#include "Bloom.h"
#include "Dof.h"
#include "GaussianBlur.h"
#include "FarShadow.h"

/// <summary>
/// �|�X�g�G�t�F�N�g�N���X�B
/// </summary>
class PostEffect
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	PostEffect();
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~PostEffect();
	/// <summary>
	/// �������B
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �h���[�B
	/// </summary>
	void Draw();
	/// <summary>
	/// �t���X�N���[���`��B
	/// </summary>
	void DrawFullScreenQuadPrimitive( ID3D11DeviceContext* deviceContext, Shader& vsShader, Shader& psShader );
private:
	/// <summary>
	/// �t���X�N���[���`��p�̎l�p�`�v���~�e�B�u�̏������B
	/// </summary>
	void InitFullScreenQuadPrimitive();
private:
	FarShadow m_farShadow;	//�����̉e
	Bloom m_bloom;	//�u���[���B
	Dof m_dof;			//DoF
	GaussianBlur m_gaussianBlur;	//�u���[�␳
	//�t���X�N���[���`��p�̃����o�ϐ��B
	ID3D11Buffer*	m_vertexBuffer = nullptr;		//���_�o�b�t�@�B
	ID3D11InputLayout* m_inputLayout = nullptr;		//���̓��C�A�E�g�B

	void BlurDraw();
	ID3D11BlendState* m_blendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B
	Shader m_vs;			//���_�V�F�[�_�[�B
	Shader m_ps;			//�s�N�Z���V�F�[�_�[�B

	bool m_blurInitFlag = false;

};

