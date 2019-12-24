#include "stdafx.h"
#include "GameCamera.h"

GameCamera* GameCamera::m_instance = nullptr;

GameCamera::GameCamera()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�����ʂ�ݒ肷��
	g_camera3D.SetFar(30000.0f);
	//��p��ύX
	g_camera3D.SetViewAngle(CMath::DegToRad(60.0f));

	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
	m_game = Game::GetInstance();

}


GameCamera::~GameCamera()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void GameCamera::Update() {

	//���ʂ̃J��������
	CommonMove();

	Game::GameMode NowGameMode = m_game->GetGameMode();		//���݂̃Q�[�����[�h���Ăяo��

	if (NowGameMode == Game::ActionMode) {
		ActionMode();
	}
	else if (NowGameMode == Game::CreateMode) {
		CreateMode();
	}

	//�����_���J�����ɓ`����
	g_camera3D.SetTarget(m_cameraTarget);
	g_camera3D.SetPosition(m_cameraPos);

	g_camera3D.Update();
}

void GameCamera::Render() {

}

void GameCamera::ActionMode() {

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
	CVector3 Camera_Position = g_camera3D.GetTarget();

	if (m_camera_BoxToPlayer_MoveFlag == true) {

		Camera_Position.y -= 100.0f;
		CVector3 Move = (P_Position - Camera_Position) / CameraMoveHosei;
		P_Position = Camera_Position + Move;
	}

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

}

void GameCamera::CreateMode() {

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

	//�����_�𓮂���
	CVector3 P_Position = m_player->Getm_Position();
	if (m_gamebox != nullptr) {
		CVector3 Box_Position = m_gamebox->GetPosition();
		CVector3 Camera_Position = g_camera3D.GetTarget();
		CVector3 Move = (Box_Position - Camera_Position) / CameraMoveHosei;
		P_Position = Camera_Position + Move;

		m_cameraTarget.x = P_Position.x;
		m_cameraTarget.y = P_Position.y;	//�v���C���[�̂�����Ə�ɂ���
		m_cameraTarget.z = P_Position.z;
	}

	//���_���J�����ɓ`����
	m_cameraPos.x = P_Position.x + m_cameraHosei.x;
	m_cameraPos.y = P_Position.y + m_cameraHosei.y;
	m_cameraPos.z = P_Position.z + m_cameraHosei.z;

}

void GameCamera::CommonMove() {

	int now_delta = MouseSupporter::GetInstance()->GetWheelMove();
	float Angle = g_camera3D.GetViewAngle();

	if (now_delta > 0) {
		Angle -= 0.1f;
		if (Angle < 0.5f) {
			Angle = 0.5f;
		}
	}
	else if (now_delta < 0) {
		Angle += 0.1f;
		if (Angle > 1.7f) {
			Angle = 1.7f;
		}
	}
	g_camera3D.SetViewAngle(Angle);

}