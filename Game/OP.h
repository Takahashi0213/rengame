#pragma once

/// <summary>
/// OP�����s
/// �X�L�b�v�L�[���������Ƌ����I������
/// </summary>
class OP
{
public:
	OP();
	~OP();

	/// <summary>
	/// OP�X�V�iGame�N���X�ɌĂ�ł��炤�j
	/// </summary>
	void OP_Update();

	/// <summary>
	/// OP�I���t���O��Ԃ�
	/// </summary>
	bool GetEndFlag() {
		return m_opEndFlag;
	}

private:

	bool m_opEndFlag = false;		//true�ɂȂ����u�Ԃ�OP�I���̎�

	//OP�i�s�֘A
	int m_opShinkou = 0;			//OP�i�s�x
	bool m_opEffectFlag = false;	//���x�����b�Z�[�W���\������Ȃ��悤�ɂ���t���O

	int m_opTimer = 0;				//OP�����^�C�}�[
	const int OP_TimerLimit = 60;	//OP��������

	//�萔
	const int EndShinkou = 3;		//OP�I���̐i�s�x

};

