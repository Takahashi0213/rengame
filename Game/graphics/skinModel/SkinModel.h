#pragma once

#include "graphics/Skeleton.h"

#include "graphics/light/DirectionLight.h"
#include "graphics/light/PointLight.h"

/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
enum RenderMode {
	Default = 0,		//普通
	Silhouette = 1,		//シルエット
	Monochrome = 2,		//モノクロ
	Box = 3,			//箱です。	
	Kirameki = 4,		//宝石の輝き
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*/
	void Draw(CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode renderMode = enRenderMode_Normal);
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/// <summary>
	/// 自己発光色を設定
	/// </summary>
	/// <param name="color">自己発光色</param>
	void SetEmissionColor(const CVector3& color)
	{
		m_emissionColor = color;
	}
	/// <summary>
	/// 自己発光色を取得
	/// </summary>
	/// <returns>自己発光色</returns>
	CVector3 GetEmissionColor() {
		return m_emissionColor;
	}
	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};

	/// <summary>
	/// レンダーモードを変更
	/// </summary>
	/// <param name="mode">モード</param>
	void SetRenderMode(const int& mode) {
		m_renderMode = mode;
	}

	/// <summary>
	/// シャドウレシーバーのフラグを設定する。
	/// </summary>
	/// <param name="flag">trueを渡すとシャドウレシーバーになる</param>
	/// <remarks>
	/// シャドウレシーバーとは影を落とされるオブジェクトのことです。
	/// シャドウキャスターによって生成された、シャドウマップを利用して
	/// 自身に影を落とします。
	/// オブジェクトがシャドウレシーバーかつシャドウキャスターになっている場合は
	/// セルフシャドウ(自分の影が自分に落ちる)を行うことができます。
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}
	/// <summary>
	/// World行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetWorldMatrix() const
	{
		return m_worldMatrix;
	}

	/// <summary>
	/// 法線マップの設定。
	/// </summary>
	void SetNormalMap(ID3D11ShaderResourceView* srv)
	{
		m_normalMapSRV = srv;
	}
	/// <summary>
	/// スペキュラマップの設定。
	/// </summary>
	void SetSpecMap(ID3D11ShaderResourceView* srv)
	{
		m_specMapSRV = srv;
	}
	/// <summary>
	/// アンビエントオクリュージョンマップの設定。
	/// </summary>
	void SetAOMap(ID3D11ShaderResourceView* srv)
	{
		m_aoMapSRV = srv;
	}
	/// <summary>
	/// きらめきテクスチャの設定
	/// </summary>
	void SetKirameki(ID3D11ShaderResourceView* srv) {
		m_kiramekiTextureSRV = srv;
	}

private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
	
	//ディレクションライトをセット
	void D_LightUpdate();
	//ディレクションライトをセット
	void P_LightUpdate();

private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		//todo ライトビュー行列。
		CMatrix mLightProj;		//todo ライトプロジェクション行列。
		int isShadowReciever;	//todo シャドウレシーバーのフラグ。
		int isHasNormalMap;		//法線マップを保持している？
		int isHasSpecMap;		//スペキュラマップを保持している？
		int isHasAOMap;			//AOマップを保持している？
		int isHasKirameki;		//きらめきを保持している？
		float mHigh;
		float mWide;			//画面の縦横
		float emissionColor_R;
		float emissionColor_G;
		float emissionColor_B;
	};

	//環境光の定数バッファ
	struct AmbientLight {
		float Ambient_R;
		float Ambient_G;
		float Ambient_B;
	};

	/*!
	*@brief	ライト構造体。
	*/
	struct SLight {
		SDirectionLight		directionLight;		//ディレクションライト
		SPointLight			pointLight;			//ポイントライト
		CVector4			eyePos;				//視点の座標。
		float				specPow;			//鏡面反射の絞り。
	};

	/// <summary>
	/// 環境光の初期化
	/// </summary>
	void LoadAmbientLight();

	/// <summary>
	/// 16の倍数に切り上げる処理
	/// </summary>
	/// <param name="n">切り上げたい整数</param>
	/// <returns>16の倍数に切り上げた値</returns>
	int Raundup16(int n)
	{
		return (((n - 1) / 16) + 1) * 16;
	}

	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	ID3D11Buffer*		m_lightCb = nullptr;			//!<ライト用の定数バッファ。
	ID3D11Buffer*		m_ambientlightCb = nullptr;		//!<ライト用の定数バッファ。
	AmbientLight		m_AmbientLight;					//!<ライト構造体。
	SLight				m_light;						//!<ライト構造体。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	CVector3 m_emissionColor = CVector3().Zero();		//!<自己発光カラー。
	ID3D11ShaderResourceView* m_albedoTextureSRV = nullptr;	//!<アルベドテクスチャのSRV
	int					m_renderMode = 0;				//!<レンダーモード
	bool m_isShadowReciever = false;						//シャドウレシーバーのフラグ。

	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;		//法線マップのSRV
	ID3D11ShaderResourceView* m_specMapSRV = nullptr;		//スペキュラマップのSRV
	ID3D11ShaderResourceView* m_aoMapSRV = nullptr;			//AOマップのSRV
	ID3D11ShaderResourceView* m_kiramekiTextureSRV = nullptr;//きらめきテクスチャのSRV

};

