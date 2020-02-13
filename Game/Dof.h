#pragma once

#include "RenderTarget.h"
#include "GaussianBlur.h"

class PostEffect;

/// <summary>
/// �ǂ��ӁA�ǂ�
/// </summary>
class Dof
{
public:
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~Dof();
	/// <summary>
	/// �������B
	/// </summary>
	void Init();
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="postEffect"></param>
	void Draw(PostEffect& postEffect);
private:
	GaussianBlur m_bokeBlur;	//�{�P�e�N�X�`�����ڂ������߂̃K�E�V�A���u���[�B
	ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B

	Shader m_vs;				//���_�V�F�[�_�[�B
	Shader m_psFinal;			//�ŏI�s�N�Z���V�F�[�_�[�B
	Shader m_psFinal2;			//�ŏI�s�N�Z���V�F�[�_�[�B

};
