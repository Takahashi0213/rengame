#pragma once
#include "RenderTarget.h"
#include "Sprite.h"
#include "PostEffect.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̃O���t�B�b�N�֘A
/// </summary>
class CGOM_Graphics
{
public:
	CGOM_Graphics();
	~CGOM_Graphics();
	void Init();

	/// <summary>
	/// ����
	/// </summary>
	void Standby();
	/// <summary>
	/// �v�������_�[
	/// </summary>
	void CGOM_Graphics::PreRender();
	/// <summary>
	/// �t�H���[�h�����_�[
	/// </summary>
	void CGOM_Graphics::ForwordRender();
	/// <summary>
	/// �|�X�g�����_�[
	/// </summary>
	void CGOM_Graphics::PostRender();
	/// <summary>
	/// �����_�[�Q���I�������ɌĂ�
	/// </summary>
	void EndSet();

	/// <summary>
	/// ���C�������_�����O�^�[�Q�b�g���擾
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetMainRenderTarget()
	{
		return &m_mainRenderTarget;
	}
	/// <summary>
	/// �J������Ԃł̐[�x�l����������ł��郌���_�����O�^�[�Q�b�g���擾�B
	/// </summary>
	/// <returns></returns>
	RenderTarget* GetDepthInViewRenderTarget()
	{
		return &m_depthRenderTarget;
	}

	/// <summary>
	/// �t���[���o�b�t�@�̃f�v�X�X�e���V���r���[���擾
	/// </summary>
	/// <returns></returns>
	ID3D11DepthStencilView* GetFrameBufferDepthStencilView() {
		return m_frameBufferDepthStencilView;
	}

private:
	/// <summary>
	/// �����������̃u�����h�X�e�[�g���������B
	/// </summary>
	void InitTranslucentBlendState();

	RenderTarget m_mainRenderTarget;									//���C�������_�����O�^�[�Q�b�g�B
	RenderTarget m_depthRenderTarget;									//�[�x�l�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B

	Sprite m_copyMainRtToFrameBufferSprite;								//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B
	ID3D11DeviceContext* d3dDeviceContext;

	ID3D11BlendState* m_translucentBlendState = nullptr;	//�����������p�̃u�����h�X�e�[�g�B

	PostEffect m_postEffect;		//�|�X�g�G�t�F�N�g

	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̐؂�ւ��B
	/// </summary>
	/// <param name="d3dDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
	/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
	/// <param name="viewport">�r���[�|�[�g</param>
	void CGOM_Graphics::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void CGOM_Graphics::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

};

