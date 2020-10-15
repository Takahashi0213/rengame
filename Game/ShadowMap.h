#pragma once
#include "RenderTarget.h"
#include "graphics/skinModel/SkinModel.h"

//・シングルトン
class ShadowMap
{
	static ShadowMap* m_instance;
public:
	ShadowMap();
	~ShadowMap();
	void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	void RenderToShadowMap();
	void RegistShadowCaster(SkinModel* AddModel);

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static ShadowMap* ShadowMap::GetInstance() {

		if (m_instance == nullptr) { //オブジェクトが作られていなければ作る
			m_instance = new ShadowMap;
		}
		return m_instance;
	}

	/// <summary>
	/// ライトビュー行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}

	/// <summary>
	/// ライトプロジェクション行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}

	/// <summary>
	/// シャドウマップのSRVを取得。
	/// </summary>
	/// <returns>シャドウマップのSRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}

private:
	CMatrix m_lightViewMatrix;					//ライトビュー行列。
	CMatrix m_lightProjMatrix;					//ライトプロジェクション行列。
	RenderTarget m_shadowMapRT;					//シャドウマップを描画するレンダリングターゲット。

	std::vector<SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。

};

