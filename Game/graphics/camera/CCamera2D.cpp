#include "stdafx.h"
#include "CCamera2D.h"

CCamera2D g_camera2D;		//!<2Dカメラ。

/// <summary>
/// 更新
/// </summary>
void CCamera2D::Camera2D_Update() {

	//ビュー行列を計算
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//プロジェクション行列を計算
	m_projMatrix.MakeOrthoProjectionMatrix(
		m_viewVolumeWidth,		//ビューボリュームの幅
		m_viewVolumeHeight,		//ビューボリュームの高さ
		m_near,
		m_far
	);

	//ビュープロジェクション行列の作成。
	m_viewProjectionMatrix.Mul(m_viewMatrix, m_projMatrix);

}
