#pragma once

/// <summary>
/// 2Dカメラ
/// 平行投影行列を使う
/// </summary>
class CCamera2D
{
public:
	void Camera2D_Update();

	/// <summary>
	/// カメラ行列を取得
	/// </summary>
	/// <returns>カメラ行列</returns>
	CMatrix GetViewMatrix() {
		return m_viewMatrix;
	}
	/// <summary>
	/// プロジェクション行列を取得
	/// </summary>
	/// <returns>プロジェクション行列</returns>
	CMatrix GetProjectionMatrix() {
		return m_projMatrix;
	}
	/// <summary>
	/// 視点を取得
	/// </summary>
	/// <returns>カメラの場所</returns>
	CVector3 GetPosition() {
		return m_position;
	}
	/// <summary>
	/// 注視点を取得
	/// </summary>
	/// <returns>注視点</returns>
	CVector3 GetTarget() {
		return m_target;
	}
	/// <summary>
	/// カメラの上方向を取得
	/// </summary>
	/// <returns>カメラの上方向</returns>
	CVector3 GetUp()
	{
		return m_up;
	}
	/// <summary>
	/// 視点を設定
	/// </summary>
	/// <param name="pos">新しい座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 注視点を設定
	/// </summary>
	/// <param name="target">視点</param>
	void SetTarget(CVector3 target)
	{
		m_target = target;
	}
	/// <summary>
	/// カメラの上方向を設定
	/// </summary>
	/// <param name="up">上方向</param>
	void SetUp(CVector3 up)
	{
		m_up = up;
	}
	/// <summary>
	/// 遠平面を設定
	/// </summary>
	/// <param name="f">遠平面</param>
	void SetFar(float f)
	{
		m_far = f;
	}
	/// <summary>
	/// 近平面を設定
	/// </summary>
	/// <param name="n">近平面</param>
	void SetNear(float n)
	{
		m_near = n;
	}
	/// <summary>
	/// 画角を設定
	/// </summary>
	/// <param name="angle">画角</param>
	void SetViewAngle(float angle)
	{
		m_viewAngle = angle;
	}
	/// <summary>
	/// ビューボリュームの幅を設定
	/// </summary>
	/// <param name="w">幅</param>
	void SetViewVolumeWidth(float w)
	{
		m_viewVolumeWidth = w;
	}
	/// <summary>
	/// ビューボリュームの高さを設定
	/// </summary>
	/// <param name="h">高さ</param>
	void SetViewVolumeHeight(float h)
	{
		m_viewVolumeHeight = h;
	}

private:
	CMatrix	m_viewMatrix = CMatrix::Identity();		//ビュー行列。
	CMatrix m_projMatrix = CMatrix::Identity();		//プロジェクション行列。
	CMatrix	m_viewProjectionMatrix;					//ビュープロジェクション行列。
	CVector3 m_target = CVector3::Zero();			//注視点。
	CVector3 m_position = CVector3::Zero();			//視点。
	CVector3 m_up = CVector3::Up();					//上方向。
	float m_viewAngle = CMath::DegToRad(60.0f);		//画角。
	float m_far = 10000.0f;							//遠い平面までの距離。
	float m_near = 1.0f;							//近平面までの距離。
	float m_viewVolumeWidth = 1280.0f;				//ビューボリュームの幅。
	float m_viewVolumeHeight = 720.0f;				//ビューボリュームの高さ。
};

extern CCamera2D g_camera2D;		//!<2Dカメラ。