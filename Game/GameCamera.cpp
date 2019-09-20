#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{
	//�����ʂ�ݒ肷��
	g_camera3D.SetFar(30000.0f);
	//��p��ύX
	g_camera3D.SetViewAngle(CMath::DegToRad(60.0f));

	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}


GameCamera::~GameCamera()
{
}

void GameCamera::Update() {

	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Right_Key);
	if (key == MouseSupporter::Now_Pushing) {
			//�J��������
			CVector2 move_c = MouseSupporter::GetInstance()->GetBeforeMouse(1);
			CVector3 move_cc = CVector3().Zero();
			move_cc.x = move_c.x;
			move_cc.y = move_c.y;
			move_cc.y *= -1.0f;
			move_cc.Normalize();

			CVector3 toCameraPosOld = m_cameraHosei;
			float x = move_cc.x;
			float y = move_cc.y;
			x *= 2.0f;
			y *= 2.0f;
			//Y������̉�]
			CQuaternion qRot;
			qRot.SetRotationDeg(CVector3().AxisY(), 3.0f * x);
			qRot.Multiply(m_cameraHosei);
			//X������̉�]�B
			CVector3 axisX;
			axisX.Cross(CVector3().AxisY(), m_cameraHosei);
			axisX.Normalize();
			qRot.SetRotationDeg(axisX, 3.0f * y);
			qRot.Multiply(m_cameraHosei);

			//�J�����̉�]�̏�����`�F�b�N����B
			CVector3 toPosDir = m_cameraHosei;
			toPosDir.Normalize();
			if (toPosDir.y < 0.1f) {
				//�J����������������B
				m_cameraHosei = toCameraPosOld;
			}
			else if (toPosDir.y > 0.98f) {
				//�J�����������������B
				m_cameraHosei = toCameraPosOld;
			}

	}

	CVector3 P_Position = m_player->Getm_Position();
	CQuaternion P_qRot = m_player->Getm_Rotation();
	CVector3 vBase = { 0.0f,0.0f,1.0f };
	//�����_�𓮂���
	m_cameraTarget.x = P_Position.x;
	m_cameraTarget.y = P_Position.y + 100.0f;	//�v���C���[�̂�����Ə�ɂ���
	m_cameraTarget.z = P_Position.z;

	//���_���J�����ɓ`����
	m_cameraPos.x = P_Position.x + m_cameraHosei.x;
	m_cameraPos.y = P_Position.y + m_cameraHosei.y;
	m_cameraPos.z = P_Position.z + m_cameraHosei.z;

	/*
	P_qRot.Multiply(vBase);
	//�v���C���[�̐^���ɂ��Ă�����
	CVector3 vpos = vBase * -300.0f;
	m_cameraPos = vpos + m_cameraTarget;
	m_cameraPos.y = m_cameraPos.y + 200.0f;
	*/

	//�����_���J�����ɓ`����
	g_camera3D.SetTarget(m_cameraTarget);
	g_camera3D.SetPosition(m_cameraPos);

	g_camera3D.Update();
}

void GameCamera::Render() {

}