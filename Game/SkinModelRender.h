#pragma once
#include "system/CGameObjectManager.h"
#include "SkinModelSupporter.h"

/// <summary>
/// スキンモデルレンダー
/// 3Dを描くときに使います
/// </summary>
class SkinModelRender : public IGameObject
{
public:
	typedef std::vector<CVector3>					VertexBuffer;		//頂点バッファ。
	typedef std::vector<unsigned int>				IndexBuffer;		//インデックスバッファ。

	SkinModelRender();
	~SkinModelRender();
	void Update()override;
	void Render()override;

	void Model_Init(const wchar_t* filePath);
	void Model_Init(const wchar_t* filePath, CVector3 pos, CQuaternion rot, CVector3 scl);

	/// <summary>
	/// モデルを返す
	/// </summary>
	/// <returns>モデルのポインタ</returns>
	SkinModel* GetModel() {
		return &m_skinModel;
	}

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns>座標</returns>
	const CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns>回転</returns>
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scr">拡大率</param>
	void SetScale(const CVector3 scr)
	{
		m_scale = scr;
	}
	/// <summary>
	/// 拡大率を取得
	/// </summary>
	/// <returns>拡大率</returns>
	const CVector3 GetScale() const
	{
		return m_scale;
	}

	/// <summary>
	/// レンダーモードを設定する
	/// </summary>
	/// <param name="mode">モードです。</param>
	void SetRenderMode(RenderMode mode) {
		m_renderMode = mode;
		m_skinModel.SetRenderMode(mode);
	}
	/// <summary>
	/// レンダーモードを返す
	/// </summary>
	/// <returns>こいつに設定されてるレンダーモードだ</returns>
	RenderMode GetRenderMode() {
		return m_renderMode;
	}
	
	/// <summary>
	/// シャドウレシーバーフラグの変更
	/// </summary>
	void SetShadowReciever(bool flag) {
		m_skinModel.SetShadowReciever(flag);
	}
	/// <summary>
	/// シャドウキャスターフラグの変更
	/// </summary>
	void SetShadowCasterFlag(bool flag) {
		m_shadowCasterFlag = flag;
	}

	/// <summary>
	/// モデルを楽に動かすクラスを呼び出せるぞ
	/// </summary>
	/// <remarks>
	/// 
	/// ☆サンプルコード☆
	/// render->m_skinModelSupporter.SkinModelMove(設定値);
	/// 
	/// </remarks>
	SkinModelSupporter m_skinModelSupporter;		//スキンモデルサポーター

private:
	struct Polygon {
		CVector3 vertPos[3];	//頂点座標。
		CVector3 normal;		//法線。
	};
	std::vector<Polygon> m_polygonList;

	SkinModel m_skinModel;		//!<スキンモデル
	CVector3 m_position = CVector3::Zero();		//!<座標。
	CQuaternion m_rotation = CQuaternion().Identity();		//!<回転。
	CVector3 m_scale = CVector3().One();		//!<拡大率。
	RenderMode m_renderMode = Default;			//描画モード

	bool m_shadowCasterFlag = false;	//シャドウキャスターに登録する？
};

