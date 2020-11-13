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

	//設定
	void Model_Init(const wchar_t* filePath);
	void Model_Init(const wchar_t* filePath, const CVector3& pos, const CQuaternion& rot, const CVector3& scl,
		EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	//アニメーションも同時Ver
	void Model_Init_Anim(const wchar_t* filePath,
		AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0,
		EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);

	/// <summary>
	/// モデルを返す
	/// </summary>
	/// <returns>モデルのポインタ</returns>
	SkinModel GetModel_() {
		return m_skinModel;
	}
	SkinModel* GetModel() {
		return &m_skinModel;
	}

	/// <summary>
	/// 座標を設定
	/// </summary>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	const CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 回転を設定
	/// </summary>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// 拡大率を設定
	/// </summary>
	void SetScale(const CVector3& scr)
	{
		m_scale = scr;
	}
	void SetScale(const float& scr)
	{
		CVector3 Scr = { scr,scr,scr };
		m_scale = Scr;
	}
	/// <summary>
	/// 拡大率を取得
	/// </summary>
	const CVector3 GetScale() const
	{
		return m_scale;
	}

	/// <summary>
	/// まとめてセット
	/// </summary>
	void SetUp(const CVector3& pos, const CQuaternion& rot, const CVector3& scl) {
		SetPosition(pos);
		SetRotation(rot);
		SetScale(scl);
	}

	/// <summary>
	/// レンダーモードを設定する
	/// </summary>
	/// <param name="mode">モードです。</param>
	void SetRenderMode(const RenderMode mode) {
		m_renderMode = mode;
		m_skinModel.SetRenderMode(mode);
	}
	/// <summary>
	/// レンダーモードを返す
	/// </summary>
	RenderMode GetRenderMode() {
		return m_renderMode;
	}
	
	/// <summary>
	/// 描画フラグの変更
	/// </summary>
	void SetDrawFlag(const bool& flag) {
		m_isDraw = flag;
	}

	/// <summary>
	/// シャドウレシーバーフラグの変更
	/// </summary>
	void SetShadowReciever(const bool& flag) {
		m_skinModel.SetShadowReciever(flag);
	}

	/// <summary>
	/// シャドウキャスターフラグの変更
	/// </summary>
	void SetShadowCasterFlag(const bool& flag) {
		m_shadowCasterFlag = flag;
	}

	/// <summary>
	/// アニメーションの再生
	/// </summary>
	/// <param name="animNo">アニメーションクリップの番号。コンストラクタに渡したanimClipListの並びとなる。</param>
	/// <param name="interpolateTime">補完時間(単位：秒)</param>
	void PlayAnimation(const int& animNo, const float& interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	/// <summary>
	/// アニメーションスピードの変更
	/// </summary>
	void SetAnimationSpeed(const float& speed = 20.0f) {
		m_animationSpeed = speed;
	}

	/// <summary>
	/// アニメーションの再生中？
	/// </summary>
	/// <returns>trueなら再生中</returns>
	bool IsPlayingAnimation() const
	{
		return m_animation.IsPlaying();
	}

	/// <summary>
	/// アニメーションを更新する？
	/// falseで停止、trueで再開
	/// </summary>
	void SetIsUpdateAnimation(const bool& flag) {
		m_isUpdateAnimation = flag;
	}

	/// <summary>
	/// スキンモデルサポーターを更新する？
	/// falseで停止、trueで再開
	/// </summary>
	void SetIsUpdateSkinModelSupporter(const bool& flag) {
		m_isUpdateSkinModelSupporter = flag;
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
	/*!
	* @brief	アニメーションの初期化。
	*/
	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

	struct Polygon {
		CVector3 vertPos[3];	//頂点座標。
		CVector3 normal;		//法線。
	};
	std::vector<Polygon> m_polygonList;

	bool m_isDraw = true;											//!<描画する？

	SkinModel m_skinModel;											//!<スキンモデル
	CVector3 m_position = CVector3::Zero();							//!<座標。
	CQuaternion m_rotation = CQuaternion().Identity();				//!<回転。
	CVector3 m_scale = CVector3().One();							//!<拡大率。
	RenderMode m_renderMode = Default;								//!<描画モード

	bool m_isUpdateSkinModelSupporter = true;						//!<スキンモデルサポーターを更新する？

	AnimationClip*				m_animationClips = nullptr;			//!<アニメーションクリップ。
	int							m_numAnimationClips = 0;			//!<アニメーションクリップの数。
	Animation					m_animation;						//!<アニメーション。
	bool						m_isUpdateAnimation = true;			//!<アニメーションを更新する？
	float						m_animationSpeed = 20.0f;			//!<アニメーションを更新するスピード。

	bool m_shadowCasterFlag = false;								//!<シャドウキャスターに登録する？
};

