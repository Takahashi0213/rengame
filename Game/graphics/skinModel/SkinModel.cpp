#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "SkinModelEffect.h"

SkinModel::~SkinModel()
{
	//定数バッファを解放。
	if (m_cb != nullptr) {
		m_cb->Release();
	}
	//ライト用の定数バッファの解放。
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
	//環境光用の定数バッファの解放。
	if (m_ambientlightCb != nullptr) {
		m_ambientlightCb->Release();
	}
	//ポジション用の定数バッファの解放。
	if (m_positionCb != nullptr) {
		m_positionCb->Release();
	}
	//サンプラステートを解放。
	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
}

/// <summary>
/// 環境光の初期化
/// </summary>
void SkinModel::LoadAmbientLight() {
	CVector3 a_color = LightMaker::GetInstance()->GetAmbientColor();
	m_AmbientLight.Ambient_R = a_color.x;
	m_AmbientLight.Ambient_G = a_color.y;
	m_AmbientLight.Ambient_B = a_color.z;
}

/// <summary>
/// ディレクションライトを更新する
/// </summary>
void SkinModel::D_LightUpdate() {

	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
		m_light.directionLight.direction[i] = LightMaker::GetInstance()->D_Light_GetDirection(i);
		m_light.directionLight.direction[i].Normalize();	//正規化。
		m_light.directionLight.color[i] = LightMaker::GetInstance()->D_Light_GetColer(i);
		m_light.directionLight.color[i].w = LightMaker::GetInstance()->D_Light_GetSpec(i);
	}

}

/// <summary>
/// ポイントライトを更新する
/// </summary>
void SkinModel::P_LightUpdate() {

	for (int i = 0; i < MAX_POINT_LIGHT; i++) {
		m_light.pointLight.position[i] = LightMaker::GetInstance()->P_Light_GetPos(i);
		m_light.pointLight.color[i] = LightMaker::GetInstance()->P_Light_GetColor(i);
		m_light.pointLight.color[i].w = LightMaker::GetInstance()->P_Light_GetRange(i);
	}
}

void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();
	
	//サンプラステートの初期化。
	InitSamplerState();

	//ディレクションライトの初期化。
	D_LightUpdate();
	//ポイントライトの初期化。
	P_LightUpdate();

	LoadAmbientLight();

	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}

void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);

	//続いて、ライト用の定数バッファを作成。
	//作成するバッファのサイズを変更するだけ。
	bufferDesc.ByteWidth = Raundup16(sizeof(SLight));
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);

	//環境光用の定数バッファを作成。
	bufferDesc.ByteWidth = Raundup16(sizeof(AmbientLight));
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_ambientlightCb);

	//ポジション用の定数バッファを作成。
	bufferDesc.ByteWidth = Raundup16(sizeof(SDithering));
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_positionCb);

}
void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
	//ライトの更新！
	D_LightUpdate();
	P_LightUpdate();
	//環境光の更新！
	LoadAmbientLight();
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix ,EnRenderMode renderMode)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());
	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	auto shadowMap = ShadowMap::GetInstance();

	//定数バッファの内容を更新。
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	//todo ライトカメラのビュー、プロジェクション行列を送る。
	vsCb.mLightProj = shadowMap->GetLightProjMatrix();
	vsCb.mLightView = shadowMap->GetLighViewMatrix();
	if (m_isShadowReciever == true) {
		vsCb.isShadowReciever = 1;
	}
	else {
		vsCb.isShadowReciever = 0;
	}
	//法線マップを使用するかどうかのフラグを送る。
	if (m_normalMapSRV != nullptr) {
		vsCb.isHasNormalMap = true;
	}
	else {
		vsCb.isHasNormalMap = false;
	}
	//スペキュラマップを使用するかどうかのフラグを送る。
	if (m_specMapSRV != nullptr) {
		vsCb.isHasSpecMap = true;
	}
	else {
		vsCb.isHasSpecMap = false;
	}
	//AOマップを使用するかどうかのフラグを送る。
	if (m_aoMapSRV != nullptr) {
		vsCb.isHasAOMap = true;
	}
	else {
		vsCb.isHasAOMap = false;
	}
	//きらめきテクスチャを使用するかどうかのフラグを送る。
	if (m_kiramekiTextureSRV != nullptr) {
		vsCb.isHasKirameki = true;
	}
	else {
		vsCb.isHasKirameki = false;
	}

	//縦横
	vsCb.mHigh = FRAME_BUFFER_H;
	vsCb.mWide = FRAME_BUFFER_W;

	//色
	vsCb.emissionColor_R = m_emissionColor.x;
	vsCb.emissionColor_G = m_emissionColor.y;
	vsCb.emissionColor_B = m_emissionColor.z;

	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);

	//ライト用の定数バッファを更新。
	m_light.eyePos = g_camera3D.GetPosition();
	m_light.specPow = 1.0f;

	//プレイヤーの座標を取得
	m_dithering.playerPos = SceneManager::GetInstance()->GetGameGraphicInstance()->m_playerPos;
	m_dithering.playerPos.w = 1.0f;
	//ディザリングフラグ
	m_dithering.isDithering = m_isDithering;

	d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);
	d3dDeviceContext->UpdateSubresource(m_ambientlightCb, 0, nullptr, &m_AmbientLight, 0, 0);
	d3dDeviceContext->UpdateSubresource(m_positionCb, 0, nullptr, &m_dithering, 0, 0);

	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);

	//定数バッファをシェーダースロットに設定。
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_ambientlightCb);
	d3dDeviceContext->PSSetConstantBuffers(3, 1, &m_lightCb);
	d3dDeviceContext->PSSetConstantBuffers(4, 1, &m_positionCb);

	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//エフェクトにクエリを行う。
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
			//マテリアルの名前が「Ground」ならディザリングを絶対しない
			if (m_isGround == true &&
				( modelMaterial->EqualMaterialName(L"Ground") ||
					modelMaterial->EqualMaterialName(L"Ground2") || 
					modelMaterial->EqualMaterialName(L"Ground3")))
			{
				modelMaterial->SetRenderMode(RenderMode::Default_NoDithering, EnRenderMode::enRenderMode_Normal);
			}
			else {
				modelMaterial->SetRenderMode(m_renderMode, renderMode);
			}
			});

		if (m_normalMapSRV != nullptr) {
			//法線マップが設定されていたらレジスタt3に設定する。
			d3dDeviceContext->PSSetShaderResources(3, 1, &m_normalMapSRV);
		}
		if (m_specMapSRV != nullptr) {
			//スペキュラマップが設定されていたらレジスタt4に設定する。
			d3dDeviceContext->PSSetShaderResources(4, 1, &m_specMapSRV);
		}
		if (m_aoMapSRV != nullptr) {
			//AOが設定されていたらレジスタt5に設定する。
			d3dDeviceContext->PSSetShaderResources(5, 1, &m_aoMapSRV);
		}
		if (m_kiramekiTextureSRV != nullptr) {
			//きらめきテクスチャが設定されていたらレジスタt6に設定する。
			d3dDeviceContext->PSSetShaderResources(6, 1, &m_kiramekiTextureSRV);
		}

	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU();

	//アルベドテクスチャを設定する。
	ID3D11ShaderResourceView* SRV = ShadowMap::GetInstance()->GetShadowMapSRV();
	d3dDeviceContext->PSSetShaderResources(0, 1, &m_albedoTextureSRV);
	d3dDeviceContext->PSSetShaderResources(2, 1, &SRV);

	//描画。
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}