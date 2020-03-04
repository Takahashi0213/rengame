#include "stdafx.h"
#include "CCamera2D.h"

CCamera2D g_camera2D;		//!<2D�J�����B

/// <summary>
/// �X�V
/// </summary>
void CCamera2D::Camera2D_Update() {

	//�r���[�s����v�Z
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//�v���W�F�N�V�����s����v�Z
	m_projMatrix.MakeOrthoProjectionMatrix(
		m_viewVolumeWidth,		//�r���[�{�����[���̕�
		m_viewVolumeHeight,		//�r���[�{�����[���̍���
		m_near,
		m_far
	);

	//�r���[�v���W�F�N�V�����s��̍쐬�B
	m_viewProjectionMatrix.Mul(m_viewMatrix, m_projMatrix);

}
