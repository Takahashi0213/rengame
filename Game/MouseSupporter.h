#pragma once

/// <summary>
/// �}�E�X�̐F�X���y�ɂ���
/// �E�V���O���g��
/// </summary>
class MouseSupporter
{
	static MouseSupporter* m_instance;
public:
	MouseSupporter();
	~MouseSupporter();

	//�J�[�\���̏��
	enum mouse_state {
		Not_Push,	//������Ă��Ȃ�
		Now_Pushing,	//������Ă���
		New_Push,	//�V�K�ɉ����ꂽ
		Release_Push,	//�����Ă�����Ԃ��痣���ꂽ
	};
	//�L�[�̎��
	enum mouse_key {
		Left_Key,
		Right_Key,
		Center_Key,
	};

	void MouseSupporter::MouseUpdate();

	/// <summary>
	/// �}�E�X�̏�Ԃ�Ԃ�
	/// </summary>
	/// <param name="key">�擾�������L�[�̎��</param>
	/// <returns>�L�[�̏��</returns>
	mouse_state MouseSupporter::GetMouseKey(mouse_key key) {
		mouse_state re;
		switch (key)
		{
		case MouseSupporter::Left_Key:
			re = m_leftMouse;
			break;
		case MouseSupporter::Right_Key:
			re = m_rightMouse;
			break;
		case MouseSupporter::Center_Key:
			re = m_centerMouse;
			break;
		}
		return re;
	}

	/// <summary>
	/// �}�E�X�𒷉������Ă����t���[������Ԃ�
	/// </summary>
	/// <param name="key">�擾�������L�[�̎��</param>
	/// <returns>�t���[����</returns>
	int MouseSupporter::GetMouseTimer(mouse_key key) {
		int re;
		switch (key)
		{
		case MouseSupporter::Left_Key:
			re = m_lestPushTimer;
			break;
		case MouseSupporter::Right_Key:
			re = m_rightPushTimer;
			break;
		}
		return re;
	}

	/// <summary>
	/// �O�t���[���Ɣ�r�����}�E�X�̈ړ��ʂ�Ԃ��I�I
	/// </summary>
	/// <returns>�ړ���</returns>
	CVector2 MouseSupporter::GetMouseMove() {
		return m_mouseMove;
	}

	CVector2 MouseSupporter::GetMousePos();
	CVector3 MouseSupporter::GetMousePos_3D();
	CVector2 MouseSupporter::GetBeforeMouse(int p = 0);

	/// <summary>
	/// �}�E�X�ړ��ʂ�ݒ�
	/// </summary>
	/// <remarks>
	/// 
	/// system.cpp�ȊO�ŌĂ΂Ȃ��ŁI�I�I
	/// 
	/// </remarks>
	/// <param name="move">�ړ���</param>
	void MouseSupporter::SetWheelMove(int move) {
		m_wheelMove = move;
	}
	/// <summary>
	/// �}�E�X�ړ��ʂ�Ԃ�
	/// </summary>
	/// <returns>�ړ���</returns>
	int MouseSupporter::GetWheelMove() {
		return m_wheelMove;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static MouseSupporter* MouseSupporter::GetInstance() {
		return m_instance;
	}

private:
	//�J�[�\���̉����ꂽ��Ԃ�ۑ�����
	mouse_state m_leftMouse = Not_Push;
	mouse_state m_rightMouse = Not_Push;
	mouse_state m_centerMouse = Not_Push;
	//�J�[�\���̉�����Ă������Ԃ�ۑ�����
	int m_lestPushTimer = 0;
	int m_rightPushTimer = 0;
	int m_centerPushTimer = 0;
	//�z�C�[���̈ړ�����ۑ�����
	int m_wheelMove = 0;
	//�O��̃}�E�X���W��ۑ�����
	CVector2 m_beforeMouse[2] = { {0.0f,0.0f},{0.0f,0.0f} };	//2�ڂ̓J��������p
	CVector2 m_mouseMove = { 0.0f,0.0f };
};

