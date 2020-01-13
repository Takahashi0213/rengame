#pragma once
class GameFont
{
public:
	GameFont();
	~GameFont();

	/*!
	* @brief	�`��J�n�B
	*/
	void Begin();
	/*!
	* @brief	�`��I���B
	*/
	void End();
	/*!
	* @brief	�`��B
	*@param[in]	text		�\���������e�L�X�g�B
	*@param[in]	trans		���s�ړ��B
	*@param[in]	color		�J���[�B
	*@param[in]	rot			��]�B
	*@param[in]	scale		�g��B
	*@param[in]	pivot		��_�B
	*						0.5, 0.5�ŉ摜�̒��S����_�B
	*						0.0, 0.0�ŉ摜�̍����B
	*						1.0, 1.0�ŉ摜�̉E��B
	*						Unity��uGUI�ɏ����B
	*/
	void Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4().White(),
		float rotation = 0.0f,
		float scale = 1.0f,
		CVector2 pivot = { 0.5f, 0.5f }
	);

private:
	void InitTranslucentBlendState();

	ID3D11BlendState* m_translucentBlendState = nullptr;	//�����������p�̃u�����h�X�e�[�g�B

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<�X�v���C�g�t�H���g�B

	CMatrix m_scaleMat;

};

