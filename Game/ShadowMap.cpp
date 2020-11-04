#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap* ShadowMap::m_instance = nullptr;

ShadowMap::ShadowMap()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//シャドウマップ生成用のレンダリングターゲットを作成。
	//解像度は2048×2048。
	//テクスチャのフォーマットはR成分のみの32bit浮動小数点型。
	m_shadowMapRT.Create(
		2048,
		2048,
		DXGI_FORMAT_R32_FLOAT
	);
}


ShadowMap::~ShadowMap()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

/// <summary>
/// 更新。
/// </summary>
/// <remarks>
/// ライトビュー行列や、ライトプロジェクション行列を
/// 更新します。毎フレーム呼び出してください。
/// </remarks>
/// <param name="pos">ライトカメラの視点の座標</param>
/// <param name="target">ライトかめらの注視点の座標</param>
void ShadowMap::Update(CVector3 lightCameraPos, CVector3 lightCameraTarget) {

	//ライトの方向を計算する。
	auto lightDir = lightCameraTarget - lightCameraPos;
	if (lightDir.Length() < 0.0001f) {
		//ライトカメラの注視点と視点が近すぎる。
		//恐らくバグなので、クラッシュさせる。
		std::abort();
	}
	//正規化して、方向ベクトルに変換する。
	lightDir.Normalize();
	//ライトの方向によって、ライトカメラの上方向を決める。
	CVector3 lightCameraUpAxis;
	if (fabsf(lightDir.y) > 0.99998f) {
		//ほぼ真上or真下を向いているので、1,0,0を上方向とする。
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		//真上を向いていないときは、0,1,0を上方向とする。
		lightCameraUpAxis = CVector3::AxisY();
	}
	//カメラの上方向が決まったので、ライトビュー行列を計算する。
	m_lightViewMatrix.MakeLookAt(
		lightCameraPos,
		lightCameraTarget,
		lightCameraUpAxis
	);

	//ライトプロジェクション行列を作成する。
	//太陽光からの影を落としたいなら、平行投影行列を作成する。
	m_lightProjMatrix.MakeOrthoProjectionMatrix(
		3000,
		3000,
		0.1f,
		5000.0f
	);

}

/// <summary>
/// シャドウマップにシャドウキャスターをレンダリング。
/// 毎フレーム呼び出して下さい。
/// </summary>
/// <remarks>
/// シャドウマップに描画されるシャドウキャスターは
/// RegistShadowCaster関数を使用して登録されたキャスターのみです。
/// この関数を呼び出すと、シャドウキャスターのリストはクリアされます。
/// </remarks>
void ShadowMap::RenderToShadowMap() {

	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//レンダリングターゲットを切り替える。
	ID3D11RenderTargetView* rts[] = {
		m_shadowMapRT.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());
	//ビューポートを設定。
	d3dDeviceContext->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//シャドウマップをクリア。
	//一番奥のZは1.0なので、1.0で塗りつぶす。
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
	m_shadowMapRT.ClearRenderTarget(clearColor);

	//シャドウキャスターをシャドウマップにレンダリング。
	for (auto& caster : m_shadowCasters) {
		caster->Draw(
			m_lightViewMatrix,
			m_lightProjMatrix,
			enRenderMode_CreateShadowMap
		);
	}
	//キャスターをクリア。
	m_shadowCasters.clear();
}

void ShadowMap::RegistShadowCaster(SkinModel* AddModel) {
	m_shadowCasters.push_back(AddModel);
}