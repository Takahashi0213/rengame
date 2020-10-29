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
	void SetFontRender(class FontRender* fr) {
		m_fontRender = fr;
	}

	/// <summary>
	/// �t�H���g�����_�[�̕��ŌĂяo�����I
	/// </summary>
	void FontSupporter_Update();
	//���샊�Z�b�g
	void FontDelayReset();

	//�������牉�o�Z�b�g�p
	void FontMoveSet(const CVector2& move, const int& movespeed, const int& delay, const bool& relative = false);
	void FontColorSet(const CVector4& color, const int& moveTime, const int& moveDelay);

	//��Ԏ擾�p
	//�t�H���g�̈ړ����X�g�v�f�����擾
	//�ړ����̃t�H���g���ǂ����𔻕ʂ��� �Ȃ�
	int GetFontMoveListLen() {
		return static_cast<int>(m_fontMoveList.size());
	}

private:
	class FontRender* m_fontRender;
	//�����ƕЕt��
	void FontDataUpdate();
	void FontDataReturn();
	//�ړ��֐�
	void FontMoveUpdate();
	void FontColorUpdate();

	//�t�H���g�̏��
	CVector2 m_position;							//���W
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };	//��Z�J���[

	//�ړ����
	struct FontMoveData {
		CVector2 m_fontMovePos = { 0.0f,0.0f };		//�t�H���g�̈ړ���
		CVector2 m_fontMoveSpeed = { 0.0f,0.0f };	//�t�H���g�̈ړ���
		int m_fontMoveLimit = -1;					//�t�H���g�̈ړ����ԁi-1�͈ړ����ł͂Ȃ��j
		int m_fontMoveDelay = -1;					//�t�H���g�̈ړ��f�B���C
		int m_fontMoveTimer = -1;					//�t�H���g�̈ړ��^�C�}�[
		bool m_fontMoveRelative = false;			//�t�H���g�̑��Έړ��t���O�itrue�Ȃ瑊�Έړ��j
		bool m_fontMoveDeleteFlag = false;			//�폜�t���O�i������Ȃ��łˁj
	};
	std::list<FontMoveData> m_fontMoveList;			//�ړ��̃��X�g
	//MulColor
	CVector4 m_fontColor = CVector4().White();		//�ڕW�̐F
	CVector4 m_fontColorMove = CVector4().White();	//1�t���[���̕ω���
	int m_fontColorLimit = -1;						//�t�H���g�̐F�ύX���ԁi-1�͕ω����ł͂Ȃ��j
	int m_fontColorDelay = -1;						//�t�H���g�̕ω��f�B���C
	int m_fontColorTimer = -1;						//�t�H���g�̕ω��^�C�}�[


};

