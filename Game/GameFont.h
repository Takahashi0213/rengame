#pragma once
class GameFont
{
public:
	GameFont();
	~GameFont();

	/*!
	* @brief	�`��J�n�B
	*/
	void Begin(bool flag = false);
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

	/*!
	*@brief	�e�̃p�����[�^��ݒ�B
	*@param[in]	isDrawShadow		�e��`���H
	*@param[in]	shadowOffset		�e��`���Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB
	*@param[in]	shadowColor			�e�̐F�B
	*/
	void SetShadowParam(bool isDrawShadow, float shadowOffset, const CVector4& shadowColor = { 0.2f,0.2f,0.2f,1.0f })
	{
		m_isDrawShadow = isDrawShadow;
		m_shadowOffset = shadowOffset;
		m_shadowColor = shadowColor;
	}

	void SetCut(float cutUp, float cutDown) {
		m_cutY_Up = cutUp;
		m_cutY_Down = cutDown;
	}

	struct ConstantBuffer {
		float CutUp;
		float CutDown;
	};

private:
	void InitTranslucentBlendState();
	ID3D11Buffer* m_cb = nullptr;		//�萔�o�b�t�@
	ID3D11BlendState* m_translucentBlendState = nullptr;	//�����������p�̃u�����h�X�e�[�g�B

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<�X�v���C�g�t�H���g�B

	const CVector4 ShadowColorDef = { 1.0f,1.0f,1.0f,1.0f };	//�e�̏����F

	bool m_isDrawShadow = false;						//!<�e�������H
	float m_shadowOffset = 0.0f;						//!<�e�������Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB
	CVector4 m_shadowColor = ShadowColorDef;			//!<�e�̐F�B

	//�J�b�g�V�X�e���D�I�I
	float m_cutY_Up = 720.0f;						//!<��������͕`�悵�Ȃ�
	float m_cutY_Down = -720.0f;					//!<������艺�͕`�悵�Ȃ�

	CMatrix m_scaleMat;
	ID3D11DepthStencilState*	m_depthStencilStateBackup = nullptr;	//!<���݂̃f�v�X�X�e���V���X�e�[�g�B
	ID3D11RasterizerState*		m_rasterrizerStateBackup = nullptr;		//!<���݂̃��X�^���C�U�X�e�[�g�B
	ID3D11BlendState*			m_blendStateBackup = nullptr;			//!<���݂̃u�����h�X�e�[�g�B
	Shader m_psShader;													//!<�t�H���g�p�̂҂����邵��
	Shader m_psShader2;													//!<�t�H���g�p�̂҂����邵��
};