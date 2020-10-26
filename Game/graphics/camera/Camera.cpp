#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B

void Camera::Update()
{
	//�r���[�s����v�Z�B
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//�v���W�F�N�V�����s����v�Z�B
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//��p�B
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//�A�X�y�N�g��B
		m_near,
		m_far
	);

	//�r���[�v���W�F�N�V�����s��̍쐬�B
	m_viewProjectionMatrix.Mul(m_viewMatrix, m_projMatrix);
	//�r���[�s��̋t�s����v�Z�B
	m_viewMatrixInv.Inverse(m_viewMatrix);

	/*
	m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
	m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);
	//�J�����̉�]�s����擾�B
	m_cameraRotation = m_viewMatrixInv;
	m_cameraRotation.m[3][0] = 0.0f;
	m_cameraRotation.m[3][1] = 0.0f;
	m_cameraRotation.m[3][2] = 0.0f;
	m_cameraRotation.m[3][3] = 1.0f;
	*/
}

/// <summary>
/// 3D���W��2D���W�ɕϊ�����
/// </summary>
/// <param name="screenPos">�v�Z���ꂽ2D���W���Ԃ��Ă���ꏊ</param>
/// <param name="worldPos">�v�Z����3D���W</param>
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
/// 2D���W��3D���W�ɕϊ�����
/// </summary>
/// <param name="worldPos">�v�Z���ꂽ3D���W���Ԃ��Ă���ꏊ</param>
/// <param name="screenPos">�v�Z����2D���W</param>
/// <param name="z">�␳�I�ȉ���</param>
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