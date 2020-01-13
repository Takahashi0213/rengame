#pragma once
#include "GameFont.h"
#include "system/CGameObjectManager.h"

class FontRender : public IGameObject
{
public:
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
private:

	void PostRender();

	GameFont m_font;

	std::wstring m_text;						//!<�e�L�X�g�B
	CVector2 m_position = CVector2().Zero();	//!<���W�Bx = 0.0f, y = 0.0f�ŉ�ʂ̒��S�B
	CVector4 m_color = CVector4().White();		//!<�J���[�B
	float m_rotation = 0.0f;					//!<��]�B
	float m_scale = 1.0f;						//!<�g�嗦�B
	CVector2 m_pivot = { 0.5f,0.5f };			//!<�s�{�b�g�B

};

