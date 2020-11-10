#pragma once

#include "graphics/Shader.h"

/*!
*@brief	���f���G�t�F�N�g�B
*/
class ModelEffect : public DirectX::IEffect {
protected:
	std::wstring m_materialName;	//!<�}�e���A�����B

	Shader m_vsShader;
	Shader m_psShader;
	Shader m_psSilhouette;			//�V���G�b�g�`��p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psMonochrome;			//���m�N���`��p�̃s�N�Z���V�F�[�_�[�B
	Shader m_vsShadowMap;			//�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
	Shader m_vsShadowMapSkin;		//�V���h�E�}�b�v�����p�̒��_�V�F�[�_�[(�X�L�����f���p)
	Shader m_psShadowMap;			//�V���h�E�}�b�v�����p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psShader_Box;			//���p�̃s�N�Z���V�F�[�_�[
	Shader m_psShader_Kirameki;		//����߂��p�̃s�N�Z���V�F�[�_�[
	Shader m_psShader_NoDithering;	//�f�B�U�����O�����Ȃ������̃s�N�Z���V�F�[�_�[

	Shader* m_pVSShader = nullptr;
	Shader* m_pPSShader = nullptr;
	Shader* m_pPSSilhouetteShader = nullptr;
	Shader* m_pPSMonochromeShader = nullptr;
	Shader* m_vsShadowMapShader = nullptr;
	Shader* m_psShadowMapShader = nullptr;
	Shader* m_pPSShaderBox = nullptr;
	Shader* m_pPSKiramekiShader = nullptr;
	Shader* m_pPSShader_NoDithering = nullptr;

	int m_renderMode = 0;
	int m_renderMode_Shadow = 0;

	bool isSkining;
	ID3D11ShaderResourceView* m_albedoTex = nullptr;
	ID3D11DepthStencilState* m_silhouettoDepthStepsilState = nullptr;	//�V���G�b�g�`��p�̃f�v�X�X�e���V���X�e�[�g�B
	ID3D11DepthStencilState* m_kiramekiDepthStepsilState = nullptr;		//����߂��`��p�̃f�v�X�X�e���V���X�e�[�g�B
	ID3D11DepthStencilState* m_depthStencilStateBackup = nullptr;		//�f�v�X�X�e���V���X�e�[�g���ޯ�����

	ID3D11BlendState* m_translucentBlendState = nullptr;	//�����������p�̃u�����h�X�e�[�g�B

public:
	ModelEffect();

	virtual ~ModelEffect()
	{
		if (m_albedoTex) {
			m_albedoTex->Release();
		}
		if (m_silhouettoDepthStepsilState != nullptr) {
			m_silhouettoDepthStepsilState->Release();
		}
	}
	void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;

	//���_�V�F�[�_�[�̃o�C�g�R�[�h�ƃR�[�h�̒�����ݒ肷��K�v������B
	void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
	{
		*pShaderByteCode = m_vsShader.GetByteCode();
		*pByteCodeLength = m_vsShader.GetByteCodeSize();
	}
	void SetAlbedoTexture(ID3D11ShaderResourceView* tex)
	{
		m_albedoTex = tex;
	}
	void SetMatrialName(const wchar_t* matName)
	{
		m_materialName = matName;
	}
	
	bool EqualMaterialName(const wchar_t* name) const
	{
		return wcscmp(name, m_materialName.c_str()) == 0;
	}
	/// <summary>
	/// �����_�[���[�h���Q�ݒ�B
	/// </summary>
	/// <param name="renderMode">���ʂ̃����_�[���[�h</param>
	/// <param name="renderMode2">�V���h�E�}�b�v�p�̃����_�[���[�h</param>
	void SetRenderMode(int renderMode,int renderModeShadow)
	{
		m_renderMode = renderMode;
		m_renderMode_Shadow = renderModeShadow;
	}

private:
	/// <summary>
	/// �V���G�b�g�`��p�̃f�v�X�X�e���V���X�e�[�g������������B
	/// </summary>
	void InitSilhouettoDepthStepsilState();
	/// <summary>
	/// �����������p�̃u�����h�X�e�[�g������������
	/// </summary>
	void InitTranslucentBlendState();

};
/*!
*@brief
*  �X�L���Ȃ����f���G�t�F�N�g�B
*/
class NonSkinModelEffect : public ModelEffect {
public:
	NonSkinModelEffect()
	{
		m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
		m_pVSShader = &m_vsShader;
		m_vsShadowMapShader = &m_vsShadowMap;
		isSkining = false;
	}
};
/*!
*@brief
*  �X�L�����f���G�t�F�N�g�B
*/
class SkinModelEffect : public ModelEffect {
public:
	SkinModelEffect()
	{
		wchar_t hoge[256];
		GetCurrentDirectoryW(256, hoge);
		m_vsShader.Load("Assets/shader/model.fx", "VSMainSkin", Shader::EnType::VS);
		m_vsShadowMapShader = &m_vsShadowMapSkin;
		m_pVSShader = &m_vsShader;
		isSkining = true;
	}
};

/*!
*@brief
*  �G�t�F�N�g�t�@�N�g���B
*/
class SkinModelEffectFactory : public DirectX::EffectFactory {
public:
	SkinModelEffectFactory(ID3D11Device* device) :
		EffectFactory(device) {}
	std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
	{
		std::shared_ptr<ModelEffect> effect;
		if (info.enableSkinning) {
			//�X�L�j���O����B
			effect = std::make_shared<SkinModelEffect>();
		}
		else {
			//�X�L�j���O�Ȃ��B
			effect = std::make_shared<NonSkinModelEffect>();
		}
		effect->SetMatrialName(info.name);
		if (info.diffuseTexture && *info.diffuseTexture)
		{
			ID3D11ShaderResourceView* texSRV;
			DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
			effect->SetAlbedoTexture(texSRV);
		}
		return effect;
	}

	void __cdecl CreateTexture(const wchar_t* name, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textureView) override
	{
		return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
	}

};

