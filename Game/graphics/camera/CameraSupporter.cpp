#include "stdafx.h"
#include "CameraSupporter.h"

CameraSupporter* CameraSupporter::m_instance = nullptr;

CameraSupporter::CameraSupporter()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}

CameraSupporter::~CameraSupporter()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void CameraSupporter::Update() {
	
	//�J�����ړ��t���O���m�F
	if (m_cameraMoveFlag == true) {
		CameraMoveUpdate();
	}
	//�J������]�ړ��t���O���m�F
	if (m_cameraMoveFlag_Rot == true) {
		CameraMoveUpdate_Rot();
	}
	//�J�����V�F�C�N�t���O���m�F
	if (m_cameraMoveFlag_Bure == true) {
		CameraMoveUpdate_Bure();
	}
	//�J�����Y�[���t���O���m�F
	if (m_cameraMoveFlag_Zoom == true) {
		CameraMoveUpdate_Zoom();
	}
	//�����_�ړ��t���O���m�F
	if (m_cameraTargetMoveFlag == true) {
		CameraTargetMoveUpdate();
	}
}

void CameraSupporter::Render() {
	//�`��͂��Ȃ�
}

/// <summary>
/// �J�����̏ꏊ���ړ����鏀��
/// </summary>
/// <param name="move">�ړ����镪�̃x�N�g��</param>
/// <param name="moveTime">�ړ�����</param>
/// <param name="moveDelay">�ړ��f�B���C</param>
void CameraSupporter::CameraMove(const CVector3& move, const float& moveTime, const float& moveDelay) {

	//�����o�ϐ����Z�b�g
	m_cameraMoveFlag = true;
	m_cameraMoveTimer = 0.0f;

	//�F�X�Z�b�g
	m_cameraMoveSpeed = move;
	m_cameraMoveTime = moveTime;
	m_cameraMoveDelay = moveDelay;

}

/// <summary>
/// ���_�𒆐S�ɃJ��������]�����鏀��
/// </summary>
/// <param name="moveTime">�ړ�����</param>
/// <param name="moveDelay">�ړ��f�B���C</param>
void CameraSupporter::CameraMove_Rot(const float& move, const float& moveTime, const float& moveDelay) {

	//�����o�ϐ����Z�b�g
	m_cameraMoveFlag_Rot = true;
	m_cameraMoveTimer_Rot = 0.0f;

	//�F�X�Z�b�g
	m_cameraMoveSpeed_Rot = move;
	m_cameraMoveTime_Rot = moveTime;
	m_cameraMoveDelay_Rot = moveDelay;

}

/// <summary>
/// �J�������V�F�C�N�����鏀��
/// </summary>
/// <param name="bure">�u����傫���i�ő�l�j</param>
/// <param name="speed">�u���鑬��</param>
/// <param name="moveTime">���쎞�� ��-1.0f��ݒ肷��ƒ�~����܂ő����܂�</param>
/// <param name="moveDelay">����f�B���C</param>
void CameraSupporter::CameraMove_Bure(const CVector2& bure, const float& speed, const float& moveTime, const float& moveDelay) {

	//�����o�ϐ����Z�b�g
	m_cameraMoveFlag_Bure = true;
	m_cameraMoveTimer_Bure = 0.0f;

	//�F�X�Z�b�g
	m_cameraBure.x = bure.x;
	m_cameraBure.y = bure.y;
	m_cameraMoveSpeed_Bure = speed;
	m_cameraMoveTime_Bure = moveTime;
	m_cameraMoveDelay_Bure = moveDelay;

	m_cameraDefPos_Bure = g_camera3D.GetPosition();

}

/// <summary>
/// �J�������Y�[�������鏀��
/// </summary>
/// <param name="angle">�ڕW��p</param>
/// <param name="moveTime">�Y�[������</param>
/// <param name="moveDelay">�Y�[���E�F�C�g</param>
/// <param name="boundFlag">true�ɂ���ƖڕW�������ʂ�߂��ăo�E���h���܂�</param>
void CameraSupporter::CameraMove_Zoom(const float& angle, const float& moveTime, const float& moveDelay, const bool& boundFlag) {

	//�����o�ϐ����Z�b�g
	m_cameraMoveFlag_Zoom = true;
	m_cameraMoveTimer_Zoom = 0.0f;
	m_cameraMoveSpeed_ZoomBound = 0.0f;

	//�F�X�Z�b�g
	m_cameraAngle_Zoom = CMath::DegToRad(angle);
	m_cameraMoveTime_Zoom = moveTime;
	m_cameraMoveDelay_Zoom = moveDelay;
	m_cameraZoomBound = boundFlag;

}

/// <summary>
/// �J�����̒����_���ړ����鏀��
/// </summary>
/// <param name="move">�ړ����镪�̃x�N�g��</param>
/// <param name="moveTime">�ړ�����</param>
/// <param name="moveDelay">�ړ��f�B���C</param>
/// <param name="posMoveFlag">true�Ȃ瓯���ɃJ�����̍��W���ړ�����</param>
void CameraSupporter::CameraTargetMove(const CVector3& move, const float& moveTime, const float& moveDelay, const bool& posMoveFlag) {

	//�����o�ϐ����Z�b�g
	m_cameraTargetMoveFlag = true;
	m_cameraTargetMoveTimer = 0.0f;

	//�F�X�Z�b�g
	m_cameraTargetMoveSpeed = move;
	m_cameraTargetMoveTime = moveTime;
	m_cameraTargetMoveDelay = moveDelay;
	m_cameraTargetMove_PosMove = posMoveFlag;

}

/// <summary>
/// �J�����ړ������s
/// </summary>
void CameraSupporter::CameraMoveUpdate() {

	if (m_cameraMoveTimer >= m_cameraMoveDelay) {

		//1�t���[���̈ړ��������v�Z
		CVector3 move = m_cameraMoveSpeed / m_cameraMoveTime;
		CVector3 cameraPos = g_camera3D.GetPosition();
		cameraPos += move;
		g_camera3D.SetPosition(cameraPos);

		if (m_cameraMoveTimer >= m_cameraMoveTime + m_cameraMoveDelay) {
			//�����I��
			m_cameraMoveFlag = false;
		}
	}

	m_cameraMoveTimer += 1.0f;

}

/// <summary>
/// �J������]�����s
/// </summary>
void CameraSupporter::CameraMoveUpdate_Rot() {

	if (m_cameraMoveTimer_Rot == 0.0f) {
		m_targetToPos = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	}

	if (m_cameraMoveTimer_Rot >= m_cameraMoveDelay_Rot) {

		//�����_���王�_�Ɍ������x�N�g������

		//Y������̉�]
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3().AxisY(), m_cameraMoveSpeed_Rot);
		qRot.Multiply(m_targetToPos);
		// X������̉�]
		CVector3 axisX;
		//�O�ς��g���ĉ�]�������߂�B
		axisX.Cross(CVector3().AxisY(), m_targetToPos);
		//�O�ς̌��ʂ͑傫���P�ł͂Ȃ��̂ŁA���K������B�@
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 0.0f);
		//�����_���王�_�ɐL�т�x�N�g�����񂷁B
		qRot.Multiply(m_targetToPos);

		//���_�𓮂���
		CVector3 cameraPos = g_camera3D.GetTarget() + m_targetToPos;
		g_camera3D.SetPosition(cameraPos);

		if (m_cameraMoveTimer_Rot >= m_cameraMoveTime_Rot + m_cameraMoveDelay_Rot) {
			//�����I��
			m_cameraMoveFlag_Rot = false;
		}
	}

	m_cameraMoveTimer_Rot += 1.0f;


}

/// <summary>
/// �J�����u�������s
/// </summary>
void CameraSupporter::CameraMoveUpdate_Bure() {

	if (m_cameraMoveTimer_Bure >= m_cameraMoveDelay_Bure) {

		//�u����^�C�~���O�Ŏ��s
		int bure = (int)m_cameraMoveTimer_Bure % (int)m_cameraMoveSpeed_Bure;
		if (bure == 0) {

			g_camera3D.SetPosition(m_cameraDefPos_Bure);
			CVector3 cameraPos = g_camera3D.GetPosition();

			//�傫����ݒ�
			float bure_x = 0.0f;
			float bure_y = 0.0f;
			if (m_cameraBure.x > 0.0f) {
				bure_x = (float)(rand() % (int)m_cameraBure.x);
			}
			else {
				bure_x = 0.0f;
			}
			if (m_cameraBure.y > 0.0f) {
				bure_y = (float)(rand() % (int)m_cameraBure.y);
			}
			else {
				bure_y = 0.0f;
			}

			//2����1�Ŕ��]
			if (rand() % 2 == 0) {
				bure_x *= -1.0f;
			}
			if (rand() % 2 == 0) {
				bure_y *= -1.0f;
			}

			cameraPos.x += bure_x;
			cameraPos.y += bure_y;

			g_camera3D.SetPosition(cameraPos);

		}

		if (m_cameraMoveTime_Bure != -1.0f) {
			if (m_cameraMoveTimer_Bure >= m_cameraMoveTime_Bure + m_cameraMoveDelay_Bure) {
				//�����I��
				CameraBure_Stop();
			}
		}
	}

	m_cameraMoveTimer_Bure += 1.0f;

}

/// <summary>
/// �Y�[�������s
/// </summary>
void CameraSupporter::CameraMoveUpdate_Zoom() {

	//���񏀔�
	if (m_cameraMoveTimer_Zoom == 0.0f) {
		//1�t���[���̈ړ��������v�Z
		m_cameraMoveSpeed_Zoom = ( m_cameraAngle_Zoom - g_camera3D.GetViewAngle()) / m_cameraMoveTime_Zoom;
		if (m_cameraZoomBound == true) { //�o�E���h����ꍇ�]���ɂ���
			m_cameraMoveSpeed_Zoom *= m_zoomHosei;
		}

	}

	if (m_cameraMoveTimer_Zoom >= m_cameraMoveDelay_Zoom) {

		//�Y�[���C���A�E�g���܂����
		float angle = g_camera3D.GetViewAngle();

		if (m_cameraZoomBound == true && m_cameraMoveTimer_Zoom >= m_cameraMoveTime_Zoom + m_cameraMoveDelay_Zoom) {
			//�o�E���h�A���Ńo�E���h���Ԓ��Ȃ���s
			if (m_cameraMoveSpeed_ZoomBound == 0.0f) {
				//�ړ������v�Z
				m_cameraMoveSpeed_ZoomBound = (m_cameraAngle_Zoom - g_camera3D.GetViewAngle()) / m_cameraZoomOverLimit;
				//m_cameraMoveSpeed_ZoomBound = CMath::DegToRad(m_cameraMoveSpeed_ZoomBound);
			}
			angle += m_cameraMoveSpeed_ZoomBound;
		}
		else {
			angle += m_cameraMoveSpeed_Zoom;
		}

		g_camera3D.SetViewAngle(angle);

		if (m_cameraZoomBound == false) {
			if (m_cameraMoveTimer_Zoom >= m_cameraMoveTime_Zoom + m_cameraMoveDelay_Zoom) {
				//�����I��
				m_cameraMoveFlag_Zoom = false;
				g_camera3D.SetViewAngle(m_cameraAngle_Zoom);
			}
		}
		else {
			if (m_cameraMoveTimer_Zoom >= m_cameraMoveTime_Zoom + m_cameraMoveDelay_Zoom + m_cameraZoomOverLimit) {
				//�����I��
				m_cameraMoveFlag_Zoom = false;
				g_camera3D.SetViewAngle(m_cameraAngle_Zoom);
			}
		}
	}

	m_cameraMoveTimer_Zoom += 1.0f;

}

/// <summary>
/// �����_�ړ������s
/// </summary>
void CameraSupporter::CameraTargetMoveUpdate() {

	if (m_cameraTargetMoveTimer >= m_cameraTargetMoveDelay) {

		//1�t���[���̈ړ��������v�Z
		CVector3 move = m_cameraTargetMoveSpeed / m_cameraTargetMoveTime;
		CVector3 cameraPos = g_camera3D.GetTarget();
		cameraPos += move;
		g_camera3D.SetTarget(cameraPos);
		//�t���O��true�Ȃ�J�����̍��W���ړ�������
		if (m_cameraTargetMove_PosMove == true) {
			cameraPos = g_camera3D.GetPosition();
			cameraPos += move;
			g_camera3D.SetPosition(cameraPos);
		}

		if (m_cameraTargetMoveTimer >= m_cameraTargetMoveTime + m_cameraTargetMoveDelay) {
			//�����I��
			m_cameraTargetMoveFlag = false;
		}
	}

	m_cameraTargetMoveTimer += 1.0f;

}