#include "stdafx.h"
#include "SpriteRender.h"

SpriteRender::SpriteRender()
{
	//�^�O���X�v���C�g�ɕύX
	this->SetObjectTag(IGameObject::t_Sprite);
	//�X�v���C�g�T�|�[�^�[�ɃA�h���X��n���Ă���
	m_spriteSupporter.SpriteRenderSetting(this);
}


SpriteRender::~SpriteRender()
{
}

/// <summary>
/// �X�v���C�g������������
/// </summary>
/// <remarks>
/// ���T���v���R�[�h��
/// 
/// 	SpriteRender* r = NewGO<SpriteRender>(���O);
///		r->Init(L"�t�@�C���p�X", 100.0f, 100.0f);
/// 
/// </remarks>
/// <param name="texFilePath">�t�@�C���p�X</param>
/// <param name="w">��</param>
/// <param name="h">����</param>
/// <param name="priority">�D��x�i�傫��������ɕ\�������j
/// �w�肵�Ȃ������ꍇ��0</param>
void SpriteRender::Init(const wchar_t* texFilePath, float w, float h, int priority)
{
	m_wide = w;
	m_high = h;
	m_sprite.Sprite_Init(texFilePath, w, h); //�`�悷��
	m_sprite.SetMulColor(m_mulColor);
}

/// <summary>
/// �X�v���C�g������������i�֗�Ver�j
/// </summary>
/// <remarks>
/// ���T���v���R�[�h��
/// 
/// 	SpriteRender* r = NewGO<SpriteRender>(���O);
///		r->Init(L"�t�@�C���p�X", 100.0f, 100.0f);
/// 
/// </remarks>
/// <param name="texFilePath">�t�@�C���p�X</param>
/// <param name="w">��</param>
/// <param name="h">����</param>
/// <param name="pos">�������W</param>
/// <param name="priority">�D��x�i�傫��������ɕ\�������j
/// �w�肵�Ȃ������ꍇ��0</param>
	void SpriteRender::Init(const wchar_t* texFilePath, float w, float h, CVector3 pos, CVector4 color, int priority) {
	m_wide = w;
	m_high = h;
	m_sprite.Sprite_Init(texFilePath, w, h); //�`�悷��
	m_mulColor = color;
	m_sprite.SetMulColor(m_mulColor);
	m_position = pos;
}

/// <summary>
/// �X�v���C�g�̏����A�b�v�f�[�g
/// </summary>
void SpriteRender::Update() {
	m_spriteSupporter.SpriteSupporter_Update();
	m_sprite.Sprite_Update(m_position, m_rotation, m_scale, m_pivot);
}

/// <summary>
/// �X�v���C�g��`�悷��
/// </summary>
void SpriteRender::Render() {
	m_sprite.Sprite_Draw();
}
