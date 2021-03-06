#pragma once

#include "graphics/Shader.h"

/*!
*@brief	モデルエフェクト。
*/
class ModelEffect : public DirectX::IEffect {
protected:
	std::wstring m_materialName;	//!<マテリアル名。

	Shader m_vsShader;
	Shader m_psShader;
	Shader m_psSilhouette;			//シルエット描画用のピクセルシェーダー。
	Shader m_psMonochrome;			//モノクロ描画用のピクセルシェーダー。
	Shader m_vsShadowMap;			//シャドウマップ生成用の頂点シェーダー。
	Shader m_vsShadowMapSkin;		//シャドウマップ生成用の頂点シェーダー(スキンモデル用)
	Shader m_psShadowMap;			//シャドウマップ生成用のピクセルシェーダー。
	Shader m_psShader_Box;			//箱用のピクセルシェーダー
	Shader m_psShader_Kirameki;		//きらめき用のピクセルシェーダー
	Shader m_psShader_NoDithering;	//ディザリングをしないだけのピクセルシェーダー

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
	ID3D11DepthStencilState* m_silhouettoDepthStepsilState = nullptr;	//シルエット描画用のデプスステンシルステート。
	ID3D11DepthStencilState* m_kiramekiDepthStepsilState = nullptr;		//きらめき描画用のデプスステンシルステート。
	ID3D11DepthStencilState* m_depthStencilStateBackup = nullptr;		//デプスステンシルステートのﾊﾞｯｸｱｯﾋﾟ

	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。

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

	//頂点シェーダーのバイトコードとコードの長さを設定する必要がある。
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
	/// レンダーモードを２つ設定。
	/// </summary>
	/// <param name="renderMode">普通のレンダーモード</param>
	/// <param name="renderMode2">シャドウマップ用のレンダーモード</param>
	void SetRenderMode(int renderMode,int renderModeShadow)
	{
		m_renderMode = renderMode;
		m_renderMode_Shadow = renderModeShadow;
	}

private:
	/// <summary>
	/// シルエット描画用のデプスステンシルステートを初期化する。
	/// </summary>
	void InitSilhouettoDepthStepsilState();
	/// <summary>
	/// 半透明合成用のブレンドステートを初期化する
	/// </summary>
	void InitTranslucentBlendState();

};
/*!
*@brief
*  スキンなしモデルエフェクト。
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
*  スキンモデルエフェクト。
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
*  エフェクトファクトリ。
*/
class SkinModelEffectFactory : public DirectX::EffectFactory {
public:
	SkinModelEffectFactory(ID3D11Device* device) :
		EffectFactory(device) {}
	std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
	{
		std::shared_ptr<ModelEffect> effect;
		if (info.enableSkinning) {
			//スキニングあり。
			effect = std::make_shared<SkinModelEffect>();
		}
		else {
			//スキニングなし。
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

