#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。

void Camera::Update()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//プロジェクション行列を計算。
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//画角。
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
		m_near,
		m_far
	);

	//ビュープロジェクション行列の作成。
	m_viewProjectionMatrix.Mul(m_viewMatrix, m_projMatrix);
	//ビュー行列の逆行列を計算。
	m_viewMatrixInv.Inverse(m_viewMatrix);

	/*
	m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
	m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);
	//カメラの回転行列を取得。
	m_cameraRotation = m_viewMatrixInv;
	m_cameraRotation.m[3][0] = 0.0f;
	m_cameraRotation.m[3][1] = 0.0f;
	m_cameraRotation.m[3][2] = 0.0f;
	m_cameraRotation.m[3][3] = 1.0f;
	*/
}

/// <summary>
/// 3D座標を2D座標に変換する
/// </summary>
/// <param name="screenPos">計算された2D座標が返ってくる場所</param>
/// <param name="worldPos">計算する3D座標</param>
void Camera::CalcScreenPositionFromWorldPosition(CVector2& screenPos, const CVector3& worldPos) const
{
	float half_w = FRAME_BUFFER_W * 0.5f;
	float half_h = FRAME_BUFFER_H * 0.5f;
	CVector4 _screenPos;
	_screenPos.Set(worldPos.x, worldPos.y, worldPos.z, 1.0f);
	m_viewProjectionMatrix.Mul(_screenPos);
	screenPos.x = (_screenPos.x / _screenPos.w)*half_w;
	screenPos.y = (_screenPos.y / _screenPos.w)*half_h;
}

/// <summary>
/// 2D座標を3D座標に変換する
/// </summary>
/// <param name="worldPos">計算された3D座標が返ってくる場所</param>
/// <param name="screenPos">計算する2D座標</param>
/// <param name="z">補正的な何か</param>
void Camera::CalcWorldPositionFromScrenPosition(CVector3& worldPos, const CVector2& screenPos, float z) const
{
	float half_w = FRAME_BUFFER_W * 0.5f;
	float half_h = FRAME_BUFFER_H * 0.5f;
	CVector4 _screenPos;
	_screenPos.Set(screenPos.x, screenPos.y, z, 1.0f);
	_screenPos.x /= half_w;
	_screenPos.y /= half_h;
	CMatrix mViewProjInv = m_viewProjectionMatrix;
	mViewProjInv.Inverse();
	mViewProjInv.Mul(_screenPos);
	worldPos.x = _screenPos.x / _screenPos.w;
	worldPos.y = _screenPos.y / _screenPos.w;
	worldPos.z = _screenPos.z / _screenPos.w;
}