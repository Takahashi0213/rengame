#pragma once
#include "system/CGameObjectManager.h"

//IGameObject���p�����Ă���̂ŊJ�n����NewGO���Ă��������B

/// <summary>
/// ���s����ƃJ�������y�ɓ�������B
/// �E�V���O���g��
/// </summary>
class CameraSupporter : public IGameObject
{
	static CameraSupporter* m_instance;
public:
	CameraSupporter();
	~CameraSupporter();
	void Update()override;
	void Render()override;

	//�J��������֐�
	void CameraMove(const CVector3& move, const float& moveTime, const float& moveDelay);
	void CameraMove_Rot(const float& move, const float& moveTime, const float& moveDelay);
	void CameraMove_Bure(const CVector2& bure, const float& speed, const float& moveTime, const float& moveDelay);
	void CameraMove_Zoom(const float& angle, const float& moveTime, const float& moveDelay, const bool& boundFlag = false);
	void CameraTargetMove(const CVector3& move, const float& moveTime, const float& moveDelay, const bool& posMoveFlag = false);

	/// <summary>
	/// �J�����o�b�N�A�b�v
	/// CameraBackup�Ō��݂̃J�������W�A�����_�A��p��ۑ�
	/// CameraBackup_Restore�ōŌ�ɕۑ�������L�̏��𕜌�����
	/// CameraBackup_RestoreSet�͈ړ�������u�ŃZ�b�g����
	/// 
	/// �C�x���g�ŃJ�����𓮂�������T�N�b�ƌ��̏�Ԃɖ߂��������Ȃǂ�
	/// moveTime��ݒ肷��ƃX���[�Y�ɓ���
	/// 
	/// </summary>
	void CameraBackup() {
		m_cameraPosBackup = g_camera3D.GetPosition();
		m_cameraTargetBackup = g_camera3D.GetTarget();
		//m_cameraViewAngleBackup = g_camera3D.GetViewAngle();
	}
	void CameraBackup_Restore(const float& moveTime = 1) {
		CameraMove(m_cameraPosBackup - g_camera3D.GetPosition(), moveTime, 0);
		CameraTargetMove(m_cameraTargetBackup - g_camera3D.GetTarget(), moveTime, 0);
		//CameraMove_Zoom(m_cameraViewAngleBackup, moveTime, 0);
	}
	void CameraBackup_RestoreSet() {
		g_camera3D.SetPosition(m_cameraPosBackup);
		g_camera3D.SetTarget(m_cameraTargetBackup);
	}

	/// <summary>
	/// �J�����̃u�����~
	/// </summary>
	void CameraBure_Stop() {
		m_cameraMoveFlag_Bure = false;
		g_camera3D.SetPosition(m_cameraDefPos_Bure);
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static CameraSupporter* CameraSupporter::GetInstance() {
		return m_instance;
	}

private:
	void CameraSupporter::CameraMoveUpdate();
	void CameraSupporter::CameraMoveUpdate_Rot();
	void CameraSupporter::CameraMoveUpdate_Bure();
	void CameraSupporter::CameraMoveUpdate_Zoom();
	void CameraSupporter::CameraTargetMoveUpdate();

	//�����o�ϐ� ���ʂɈړ�
	bool m_cameraMoveFlag = false;					//�J�����͈ړ����H
	CVector3 m_cameraMoveSpeed = CVector3().Zero(); //�J�����̈ړ����x
	float m_cameraMoveTime = 0.0f;					//�J�����̈ړ�����
	float m_cameraMoveDelay = 0.0f;					//�J�����̈ړ��E�F�C�g
	float m_cameraMoveTimer = 0.0f;					//�J�����̈ړ��^�C�}�[
	//�����o�ϐ� ���_�𒆐S�ɉ��
	bool m_cameraMoveFlag_Rot = false;				//�J�����͉�]�ړ����H
	float m_cameraMoveSpeed_Rot = 0.0f;				//�J�����̉�]�ړ����x
	float m_cameraMoveTime_Rot = 0.0f;				//�J�����̉�]�ړ�����
	float m_cameraMoveDelay_Rot = 0.0f;				//�J�����̉�]�ړ��E�F�C�g
	float m_cameraMoveTimer_Rot = 0.0f;				//�J�����̉�]�ړ��^�C�}�[
	CVector3 m_targetToPos = CVector3().Zero();		//�x�N�g���ۑ��p
	//�����o�ϐ� �J�����u��
	bool m_cameraMoveFlag_Bure = false;				//�J�����u�����H
	CVector2 m_cameraBure = CVector2().Zero();		//�u����ő�l
	float m_cameraMoveSpeed_Bure = 0.0f;			//�J�����̃u�����x
	float m_cameraMoveTime_Bure = 0.0f;				//�J�����̃u���鎞��
	float m_cameraMoveDelay_Bure = 0.0f;			//�J�����̃u����E�F�C�g
	float m_cameraMoveTimer_Bure = 0.0f;			//�J�����u���^�C�}�[
	CVector3 m_cameraDefPos_Bure = CVector3().Zero(); //�J�����̏����ʒu�ۑ�
	//�����o�ϐ� �Y�[���C���E�A�E�g
	bool m_cameraMoveFlag_Zoom = false;				//�Y�[�����H
	float m_cameraAngle_Zoom = 0.0f;				//�J�����̖ڕW��p
	float m_cameraMoveSpeed_Zoom = 0.0f;			//1�t���[���̈ړ�����
	float m_cameraMoveTime_Zoom = 0.0f;				//�J�����̃Y�[������
	float m_cameraMoveDelay_Zoom = 0.0f;			//�J�����̃Y�[���E�F�C�g
	float m_cameraMoveTimer_Zoom = 0.0f;			//�J�����Y�[���^�C�}�[
	bool m_cameraZoomBound = false;					//�J�����Y�[�����̃o�E���h�t���O
	float m_cameraMoveSpeed_ZoomBound = 0.0f;		//�o�E���h����1�t���[���̈ړ�����
	const float m_cameraZoomOverLimit = 2.0f;		//�J�������o�E���h�����Ė߂�܂ł̎���
	const float m_zoomHosei = 1.1f;					//�Y�[���o�E���h���̕␳
	//�����o�ϐ� �����_�ړ�
	bool m_cameraTargetMoveFlag = false;			//�����_�͈ړ����H
	CVector3 m_cameraTargetMoveSpeed = CVector3().Zero(); //�����_�̈ړ����x
	float m_cameraTargetMoveTime = 0.0f;			//�����_�̈ړ�����
	float m_cameraTargetMoveDelay = 0.0f;			//�����_�̈ړ��E�F�C�g
	float m_cameraTargetMoveTimer = 0.0f;			//�����_�̈ړ��^�C�}�[
	bool m_cameraTargetMove_PosMove = false;		//�^�[�Q�b�g���ړ��������A�J�����̍��W�����������ړ�������H
	//�����o�ϐ� �J�����o�b�N�A�b�v
	CVector3 m_cameraPosBackup = CVector3::Zero();	//�o�b�N�A�b�v�p �J�����ʒu
	CVector3 m_cameraTargetBackup = CVector3::Zero();	//�o�b�N�A�b�v�p �J���������_
	float m_cameraViewAngleBackup = 0.0f;			//�o�b�N�A�b�v�p �J������p

};

