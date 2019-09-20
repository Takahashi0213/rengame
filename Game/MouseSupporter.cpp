#include "stdafx.h"
#include "MouseSupporter.h"

MouseSupporter* MouseSupporter::m_instance = nullptr;

MouseSupporter::MouseSupporter()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


MouseSupporter::~MouseSupporter()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

/// <summary>
/// �X�V�����i���t���[���Ă΂��j
/// </summary>
void MouseSupporter::MouseUpdate() {

	//�J�[�\����Ԃɂ���ĕϐ���ύX
	if (GetAsyncKeyState(VK_LBUTTON)) {
		//���������ꂽ
		m_lestPushTimer++;
		if (m_leftMouse == New_Push) {
			//�����������ꂽ�u�Ԃ������̂ŉ�����Ă����ԂɕύX
			m_leftMouse = Now_Pushing;
		}

		if (m_leftMouse == Not_Push || m_leftMouse == Release_Push) {
			//�����ꂽ�u�ԁI
			m_leftMouse = New_Push;
			m_lestPushTimer = 0;
		}
	}
	else {
		//����������Ă��Ȃ�
		if (m_leftMouse == Release_Push) {
			//�����������ꂽ�u�Ԃ������̂ŗ�����Ă����ԂɕύX
			m_leftMouse = Not_Push;
		}

		if (m_leftMouse == Now_Pushing || m_leftMouse == New_Push) {
			//�����ꂽ�u�ԁI
			m_leftMouse = Release_Push;
		}
	}

	if (GetAsyncKeyState(VK_RBUTTON)) {
		//�E�������ꂽ
		m_rightPushTimer++;
		if (m_rightMouse == New_Push) {
			//�����������ꂽ�u�Ԃ������̂ŉ�����Ă����ԂɕύX
			m_rightMouse = Now_Pushing;
		}

		if (m_rightMouse == Not_Push || m_rightMouse == Release_Push) {
			//�����ꂽ�u�ԁI
			m_rightMouse = New_Push;
			m_rightPushTimer = 0;
		}
	}
	else {
		//�E��������Ă��Ȃ�
		if (m_rightMouse == Release_Push) {
			//�����������ꂽ�u�Ԃ������̂ŗ�����Ă����ԂɕύX
			m_rightMouse = Not_Push;
		}

		if (m_rightMouse == Now_Pushing || m_rightMouse == New_Push) {
			//�����ꂽ�u�ԁI
			m_rightMouse = Release_Push;
		}
	}

	//�z�C�[���̈ړ������i�[
	m_wheelMove = GetAsyncKeyState(WM_MOUSEWHEEL);

	if (m_wheelMove != 0) {
		int a = 0;
	}

}

/// <summary>
/// ���݂̃}�E�X���W���擾
/// </summary>
/// <returns>�}�E�X���W</returns>
CVector2 MouseSupporter::GetMousePos() {

	POINT po;
	CVector2 m_pointPos = CVector2().Zero();
	bool m_result = GetCursorPos(&po);
	if (m_result == true) { //�擾�ɐ�����������s�����
		m_pointPos.x = (float)po.x;
		m_pointPos.y = (float)po.y;
	}
	
	return m_pointPos;
}

/// <summary>
/// ���݂̃}�E�X���W��3D���W�ɕϊ����Ď擾
/// </summary>
/// <returns>3D�}�E�X���W</returns>
CVector3 MouseSupporter::GetMousePos_3D() {

	CVector3 m_pointPos = CVector3().Zero();
	CVector2 m_mousePos = GetMousePos();
	float half_w = FRAME_BUFFER_W * 0.5f;
	float half_h = FRAME_BUFFER_H * 0.5f;

	m_mousePos.x -= half_w;
	m_mousePos.y -= half_h;
	m_mousePos.y *= -1.0f;
	g_camera3D.CalcWorldPositionFromScrenPosition(m_pointPos, m_mousePos, 1.0f);

	return m_pointPos;
}

/// <summary>
/// ���s����x�ɑO��̍��W�ƍ���̍��W�̍��i�x�N�g���j��Ԃ�
/// </summary>
/// <param name="p">�擾����ʒu</param>
/// <returns>��</returns>
CVector2 MouseSupporter::GetBeforeMouse(int p) {
	CVector2 pos = GetMousePos();
	CVector2 return_pos = { 0.0f,0.0f };

	return_pos.x = pos.x - m_beforeMouse[p].x;
	return_pos.y = pos.y - m_beforeMouse[p].y;

	m_beforeMouse[p].x = pos.x;
	m_beforeMouse[p].y = pos.y;

	return return_pos;
}