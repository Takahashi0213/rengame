#pragma once

/// <summary>
/// 2D�J����
/// ���s���e�s����g��
/// </summary>
class CCamera2D
{
public:
	void Camera2D_Update();

	/// <summary>
	/// �J�����s����擾
	/// </summary>
	/// <returns>�J�����s��</returns>
	CMatrix GetViewMatrix() {
		return m_viewMatrix;
	}
	/// <summary>
	/// �v���W�F�N�V�����s����擾
	/// </summary>
	/// <returns>�v���W�F�N�V�����s��</returns>
	CMatrix GetProjectionMatrix() {
		return m_projMatrix;
	}
	/// <summary>
	/// ���_���擾
	/// </summary>
	/// <returns>�J�����̏ꏊ</returns>
	CVector3 GetPosition() {
		return m_position;
	}
	/// <summary>
	/// �����_���擾
	/// </summary>
	/// <returns>�����_</returns>
	CVector3 GetTarget() {
		return m_target;
	}
	/// <summary>
	/// �J�����̏�������擾
	/// </summary>
	/// <returns>�J�����̏����</returns>
	CVector3 GetUp()
	{
		return m_up;
	}
	/// <summary>
	/// ���_��ݒ�
	/// </summary>
	/// <param name="pos">�V�������W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �����_��ݒ�
	/// </summary>
	/// <param name="target">���_</param>
	void SetTarget(CVector3 target)
	{
		m_target = target;
	}
	/// <summary>
	/// �J�����̏������ݒ�
	/// </summary>
	/// <param name="up">�����</param>
	void SetUp(CVector3 up)
	{
		m_up = up;
	}
	/// <summary>
	/// �����ʂ�ݒ�
	/// </summary>
	/// <param name="f">������</param>
	void SetFar(float f)
	{
		m_far = f;
	}
	/// <summary>
	/// �ߕ��ʂ�ݒ�
	/// </summary>
	/// <param name="n">�ߕ���</param>
	void SetNear(float n)
	{
		m_near = n;
	}
	/// <summary>
	/// ��p��ݒ�
	/// </summary>
	/// <param name="angle">��p</param>
	void SetViewAngle(float angle)
	{
		m_viewAngle = angle;
	}
	/// <summary>
	/// �r���[�{�����[���̕���ݒ�
	/// </summary>
	/// <param name="w">��</param>
	void SetViewVolumeWidth(float w)
	{
		m_viewVolumeWidth = w;
	}
	/// <summary>
	/// �r���[�{�����[���̍�����ݒ�
	/// </summary>
	/// <param name="h">����</param>
	void SetViewVolumeHeight(float h)
	{
		m_viewVolumeHeight = h;
	}

private:
	CMatrix	m_viewMatrix = CMatrix::Identity();		//�r���[�s��B
	CMatrix m_projMatrix = CMatrix::Identity();		//�v���W�F�N�V�����s��B
	CMatrix	m_viewProjectionMatrix;					//�r���[�v���W�F�N�V�����s��B
	CVector3 m_target = CVector3::Zero();			//�����_�B
	CVector3 m_position = CVector3::Zero();			//���_�B
	CVector3 m_up = CVector3::Up();					//������B
	float m_viewAngle = CMath::DegToRad(60.0f);		//��p�B
	float m_far = 10000.0f;							//�������ʂ܂ł̋����B
	float m_near = 1.0f;							//�ߕ��ʂ܂ł̋����B
	float m_viewVolumeWidth = 1280.0f;				//�r���[�{�����[���̕��B
	float m_viewVolumeHeight = 720.0f;				//�r���[�{�����[���̍����B
};

extern CCamera2D g_camera2D;		//!<2D�J�����B