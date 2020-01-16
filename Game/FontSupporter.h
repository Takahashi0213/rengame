#pragma once

/// <summary>
/// �t�H���g���y�ɓ������}�X�B�[��
/// </summary>
class FontSupporter
{
public:
	FontSupporter();
	~FontSupporter();

	/// <summary>
	/// �A�h���X��ݒ�
	/// </summary>
	/// <param name="fr">�t�H���g�����_�[</param>
	void SetFontRender(class FontRender* fr) {
		m_fontRender = fr;
	}

	/// <summary>
	/// �t�H���g�����_�[�̕��ŌĂяo�����I
	/// </summary>
	void FontSupporter_Update();

	//�������牉�o�Z�b�g�p
	void FontMoveSet(CVector2 move, int movespeed, int delay, bool relative = false);

private:
	class FontRender* m_fontRender;
	//�����ƕЕt��
	void FontDataUpdate();
	void FontDataReturn();
	//�ړ��֐�
	void FontMoveUpdate();

	//�t�H���g�̏��
	CVector2 m_position;

	//�ړ����
	CVector2 m_moveSpeed = { 0.0f,0.0f };			//1�t���[���̈ړ���
	int m_moveLimit = 0;							//�ړ��t���[��
	int m_moveDelay = 0;							//�ړ��f�B���C
	int m_moveTimer = 0;							//�ړ��^�C�}�[
	bool m_moveRelative = false;					//���Έړ�
	bool m_moveFlag = false;						//�ړ���


};

