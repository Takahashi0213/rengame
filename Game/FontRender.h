#pragma once
#include "GameFont.h"
#include "system/CGameObjectManager.h"
#include "FontSupporter.h"

class FontRender : public IGameObject
{
public:
	FontRender();
	~FontRender();

	void Update()override;
	void Render()override;

	/*!
	* @brief	�e�L�X�g��ݒ�B
	*@details
	* ���t���[���ĂԂƏd�����I�I�I\n
	* �d���̂����ɂȂ����瑊�k���Ă�\n
	*@param[in]	text		�e�L�X�g
	*/
	void SetText(const wchar_t* text)
	{
		if (wcscmp(m_text.c_str(), text) != 0) {
			//�����񂪕ς�����B
			m_text = text;
		}

	}
	void SetText(const wchar_t* text , CVector2 pos)
	{
		if (wcscmp(m_text.c_str(), text) != 0) {
			//�����񂪕ς�����B
			m_text = text;
		}
		m_position.x = pos.x;
		m_position.y = pos.y;
	}
	/*!
	* @brief	�t�H���g��\��������W��ݒ�B
	*@details
	* �t�H���g�̍��W�n��2�����ƂȂ��Ă���A��ʂ̒�����0, 0�Ƃ��܂��B\n
	* �E������X+�A�������Y+�̍��W�n�ł��B
	*@param[in]	pos		���W�B
	*/
	void SetPosition(const CVector2& pos)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
	}
	/*!
	* @brief	�t�H���g�̃J���[��ݒ�B
	*@details
	* �t�H���g�̃J���[�͌��̎O���F�Ŏw�肵�܂��B\n
	* ������color.x���ԁAcolor.y���΁Acolor.z���ƂȂ�܂��B\n
	* �e�����ɐݒ�ł���l��0.0�`1.0�ł��B\n
	* �Ⴆ�΁A�^���Ԃ��w�肵�����ꍇ�́A\n
	* color.x = 1.0f�Acolor.y = 0.0f�Acolor.z = 0.0f�ƂȂ�܂��B
	*
	*@param[in]	color	�F�B
	*/
	void SetColor(const CVector4& color)
	{
		m_color = color;
	}
	void SetAlpha(float alpha) {
		m_color.w = alpha;
	}
	/*!
	*@brief	��]��ݒ�B
	*@param[in]	rotation	��]�p�x�B�P�ʂ̓��W�A���B
	*/
	void SetRotation(float rotation)
	{
		m_rotation = rotation;
	}
	/*!
	*@brief	�g�嗦��ݒ�B
	*@param[in]	scale	�g�嗦�B
	*/
	void SetScale(float scale)
	{
		m_scale = scale;
	}
	/*!
	*@brief	�s�{�b�g��ݒ�B
	*@details
	*�@�t�H���g��\������ۂ̊�_���w�肵�܂��B\n
	*�@0.5, 0.5�ŉ摜�̒��S����_�B
	*	0.0, 0.0�ŉ摜�̍����B
	*	1.0, 1.0�ŉ摜�̉E��B
	*  Unity��uGUI�ɏ����B
	*@param[in]	pivot	��_�B
	*/
	void SetPivot(const CVector2& pivot)
	{
		m_pivot.x = pivot.x;
		m_pivot.y = pivot.y;
	}
	/// <summary>
	/// �J�b�g����]�C
	/// </summary>
	/// <param name="cutUp">��������͕`�悵�Ȃ���</param>
	/// <param name="cutDown">������艺���`�悵�Ȃ���</param>
	void SetCut(float cutUp,float cutDown) {
		m_font.SetCut(cutUp, cutDown);
	}
	/*!
	* @brief	���W���擾�B
	*/
	const CVector2& GetPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	�F���擾�B
	*/
	const CVector4& GetColor() const
	{
		return m_color;
	}

	/// <summary>
	/// �Q�[���t�H���g���擾
	/// </summary>
	/// <returns>�ӂ���ƂɁH</returns>
	GameFont* GetGameFont() {
		return &m_font;
	}

	/// <summary>
	/// ���b�Z�[�W���蒆�Ȃ�true��Ԃ�
	/// </summary>
	/// <returns>���b�Z�[�W����t���O</returns>
	bool GetMessageOkuriFlag() {
		return m_okuriFlag;
	}

	/// <summary>
	/// �e�L�X�g���艉�o
	/// </summary>
	/// <param name="text">�\������e�L�X�g</param>
	/// <param name="Interval">1�������Ƃ̃C���^�[�o��</param>
	void SetTextOkuri(const wchar_t* text, int Interval);

	/// <summary>
	/// �e�L�X�g�������u�ōŌ�܂ōs���܂�
	/// </summary>
	/// <remarks>
	/// m_okuriFlag�͂����ł͕ύX���ꂸ�AUpdate�̃e�L�X�g����I�������Ɉ�x����������܂�
	/// </remarks>
	void TextOkuriEnd() {
		m_textOkuri_NowLen = m_textOkuri_Len;
		m_textOkuri_Timer = m_textOkuri_Interval;
	}

	FontSupporter m_fontSupporter;		//�t�H���g�T�|�[�^�[

private:
	enum MessageState {
		Normal,	//�ʏ� \D�Őݒ�
		Red,	//�ԕ��� \R�Őݒ�
		Blue,	//���� \B�Őݒ�
		Green,	//�Ε��� \G�Őݒ�
	};

	void PostRender();

	GameFont m_font;

	std::wstring m_text;						//!<�e�L�X�g�B

	CVector2 m_position = CVector2().Zero();	//!<���W�Bx = 0.0f, y = 0.0f�ŉ�ʂ̒��S�B
	CVector4 m_color = CVector4().White();		//!<�J���[�B
	float m_rotation = 0.0f;					//!<��]�B
	float m_scale = 1.0f;						//!<�g�嗦�B
	CVector2 m_pivot = { 0.5f,0.5f };			//!<�s�{�b�g�B

	//���񂾂�\���V�X�e��
	wchar_t m_text_stock[256] = L"";			//!<�\���e�L�X�g�B
	int m_textOkuri_Interval = 0;				//!<�e�L�X�g����̃C���^�[�o���t���[��
	int m_textOkuri_Timer = 0;					//!<�e�L�X�g����^�C�}�[
	bool m_okuriFlag = false;					//!<���b�Z�[�W���菈���̃t���O
	int m_textOkuri_Len = 0;					//!<�\���e�L�X�g�̕�����
	int m_textOkuri_NowLen = 0;					//!<���݂̕�����

	//���ꕶ���p
	struct MessageSt{
		wchar_t Message[1024];
		MessageState State;
	};
	std::list<MessageSt> m_messageList;		//���f�������͂�ۑ�����

	const CVector4 RED_STATUS = { 0.9f,0.1f,0.1f,m_color.w };
	const CVector4 BLUE_STATUS = { 0.1f,0.9f,0.1f,m_color.w };
	const CVector4 GREEN_STATUS = { 0.1f,0.1f,0.9f,m_color.w };

};

