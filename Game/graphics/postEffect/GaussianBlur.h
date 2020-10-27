#pragma once

#include "RenderTarget.h"
#include "graphics/Shader.h"
#include "ConstantBufferGPU.h"

class PostEffect;
/// <summary>
/// �K�E�V�A���u���[
/// </summary>
class GaussianBlur
{
public:
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="srcTexture">�u���[��������e�N�X�`����SRV</param>
	/// <param name="blurIntensity">�u���[�̋����B�l���傫���قǋ����u���[��������B</param>
	void Init(ID3D11ShaderResourceView* srcTextureSRV, const float& blurIntensity);
	/// <summary>
	/// �u���[�̎��s
	/// </summary>
	/// <param name="postEffect">
	/// �|�X�g�G�t�F�N�g�̃C���X�^���X�B
	/// �S��ʕ`��̋@�\���g�����������ł��B�B�B
	/// </param>
	/// <remarks>
	/// Init�֐����Ăяo������Ŏ��s����悤�ɂ��Ă��������B
	/// </remarks>
	void Execute(PostEffect& postEffect);
	/// <summary>
	/// �u���[�����������ʂ̃e�N�X�`��SRV���擾�B
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetResultTextureSRV()
	{
		return m_renderTarget[enRenderTarget_YBlur].GetRenderTargetSRV();
	}
	/// <summary>
	/// �u���[�����������ʂ̃e�N�X�`���̕����擾�B
	/// </summary>
	float GetResultTextureWidth() const
	{
		return m_renderTarget[enRenderTarget_YBlur].GetWidth();
	}
	/// <summary>
	/// �u���[�����������ʂ̃e�N�X�`���̍������擾�B
	/// </summary>
	/// <returns></returns>
	float GetResultTextureHeight() const
	{
		return m_renderTarget[enRenderTarget_YBlur].GetHeight();
	}
	/// <summary>
	/// �u���[�����������ʂ̃e�N�X�`���̃t�H�[�}�b�g���擾�B
	/// </summary>
	/// <returns></returns>
	DXGI_FORMAT GetResultTextureFormat() const
	{
		return m_renderTarget[enRenderTarget_YBlur].GetTextureFormat();
	}
private:
	/// <summary>
	/// �u���[�̏d�݂̍X�V�B
	/// </summary>
	void UpdateWeights();
private:
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�B
	/// </summary>
	enum EnRenderTarget {
		enRenderTarget_XBlur,		//X�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		enRenderTarget_YBlur,		//Y�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		enRenderTarget_Num,			//�����_�����O�^�[�Q�b�g�̖����B
	};
	static const int NUM_WEIGHTS = 8;	//�J�E�X�t�B���^�̏d�݂̐��B
	/// <summary>
	/// �u���[�p�̃p�����[�^�o�b�t�@�B
	/// </summary>
	/// <remarks>
	/// �����ύX������AAssets/shader/GaussianBlur.fx��CBBlur�̒��g���ύX����悤�ɁB
	/// </remarks>
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};
	bool m_isInited = false;								//�������ς݃t���O�B
	float m_blurIntensity = 25.0f;							//�u���[�̋����B�u���[�̃E�F�C�g�̌v�Z�Ŏg�p����܂��B
	RenderTarget m_renderTarget[enRenderTarget_Num];		//�����_�����O�^�[�Q�b�g�B
	ID3D11ShaderResourceView* m_srcTextureSRV = nullptr;	//�\�[�X�e�N�X�`����SRV
	unsigned int m_srcTextureWidth = 0;						//�\�[�X�e�N�X�`���̕��B
	unsigned int m_srcTextureHeight = 0;					//�\�[�X�e�N�X�`���̍����B
	Shader m_vsXBlur;										//X�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_vsYBlur;										//Y�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_psBlur;										//�u���[�p�̃s�N�Z���V�F�[�_�[�B
	SBlurParam m_blurParam;									//�u���[�p�̃p�����[�^�B
	ConstantBufferGPU m_blurCbGpu;							//�u���[�p�̒萔�o�b�t�@(GPU��)
};
