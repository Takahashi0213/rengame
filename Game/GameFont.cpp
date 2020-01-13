#include "stdafx.h"
#include "GameFont.h"


GameFont::GameFont()
{

	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_spriteFont = g_graphicsEngine->GetSpriteFont();

	auto& ge = g_graphicsEngine;
	m_scaleMat.MakeScaling(
		{
			//ge.GetFrameBufferWidth() / static_cast<float>(FRAME_BUFFER_W),
			//ge.GetFrameBufferHeight() / static_cast<float>(FRAME_BUFFER_H),
			FRAME_BUFFER_W / static_cast<float>(FRAME_BUFFER_W),
			FRAME_BUFFER_H / static_cast<float>(FRAME_BUFFER_H),
			1.0f
		}
	);

}


GameFont::~GameFont()
{
	if (m_translucentBlendState != nullptr) {
		m_translucentBlendState->Release();
	}
}

/// <summary>
/// �X�e�[�g�̐ݒ�B
/// </summary>
void GameFont::InitTranslucentBlendState() {

	//��̂��Ƃ��A�쐬����u�����h�X�e�[�g�̏���ݒ肷��B
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�Z�b�e�B���O�ŏ���������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);

	//���u�����f�B���O��L���ɂ���B
	blendDesc.RenderTarget[0].BlendEnable = true;

	//�\�[�X�J���[�̃u�����f�B���O���@���w�肵�Ă���B
	//�\�[�X�J���[�Ƃ̓s�N�Z���V�F�[�_�\����̏o�͂��w���Ă���B
	//���̎w��ł́A�\�[�X�J���[��SRC(rgba)�Ƃ���ƁA
	//�ŏI�I�ȃ\�[�X�J���[�͉��L�̂悤�Ɍv�Z�����B
	//�ŏI�I�ȃ\�[�X�J���[ = SRC.rgb �~ SRC.a�E�E�E�E�E�E�@�@
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	//�f�B�X�e�B�l�[�V�����J���[�̃u�����f�B���O���@���w�肵�Ă���B
	//�f�B�X�e�B�l�[�V�����J���[�Ƃ́A
	//���łɕ`�����܂�Ă��郌���_�����O�^�[�Q�b�g�̃J���[���w���Ă���B
	//���̎w��ł́A�f�B�X�e�B�l�[�V�����J���[��DEST(rgba)�A
	//�\�[�X�J���[��SRC(RGBA)�Ƃ���ƁA�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[��
	//���L�̂悤�Ɍv�Z�����B
	//�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[ = DEST.rgb �~ (1.0f - SRC.a)�E�E�E�E�E�A
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[�̌v�Z���@���w�肵�Ă���B
	//���̎w�肾�ƁA�@�{�A�̃J���[���������܂��B
	//�܂�A�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[��
	//SRC.rgb �~ SRC.a + DEST.rgb �~ (1.0f - SRC.a)
	//�ƂȂ�B
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//���̐ݒ�ŁA�u�����h�X�e�[�g���쐬�����
	//�������������s����u�����h�X�e�[�g���쐬�ł���B
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);

}

void GameFont::Begin()
{
	//�����_�����O�X�e�[�g��ޔ�������B
	//rc.PushRenderState();

	m_spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		m_translucentBlendState,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		m_scaleMat
	);
}

void GameFont::End()
{
	m_spriteBatch->End();
	//�����_�����O�X�e�[�g�𕜊�������B
	//rc.PopRenderState(true);
}

void GameFont::Draw(
	wchar_t const* text,
	const CVector2& position,
	const CVector4& color,
	float rotation,
	float scale,
	CVector2 pivot)
{
	if (text == nullptr) {
		return;
	}
	pivot.y = 1.0f - pivot.y;
	DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
	//���W�n���X�v���C�g�ƍ��킹��B
	CVector2 pos = position;
	float frameBufferHalfWidth = FRAME_BUFFER_W * 0.5f;
	float frameBufferHalfHeight = FRAME_BUFFER_H * 0.5f;
	pos.x += frameBufferHalfWidth;
	pos.y = -pos.y + frameBufferHalfHeight;

	m_spriteFont->DrawString(
		m_spriteBatch,
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		scale
	);
}
