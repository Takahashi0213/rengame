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
	m_mainSprite.Wide = w;
	m_mainSprite.High = h;
	m_sprite.Sprite_Init(texFilePath, w, h); //�`�悷��
	m_sprite.SetMulColor(m_mainSprite.MulColor);
}
void SpriteRender::InitSub(const wchar_t* texFilePath, float w, float h, int priority)
{
	m_subSprite.Wide = w;
	m_subSprite.High = h;
	m_sprite.Sprite_Init_Sub(texFilePath, w, h); //�`�悷��
	m_sprite.SetMulColor_Sub(m_subSprite.MulColor);
	m_subSpriteFlag = true;
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
	m_mainSprite.Wide = w;
	m_mainSprite.High = h;
	m_sprite.Sprite_Init(texFilePath, w, h); //�`�悷��
	m_mainSprite.MulColor = color;
	m_sprite.SetMulColor(m_mainSprite.MulColor);
	m_mainSprite.Position = pos;
}
void SpriteRender::InitSub(const wchar_t* texFilePath, float w, float h, CVector3 pos, CVector4 color, int priority) {
	m_subSprite.Wide = w;
	m_subSprite.High = h;
	m_sprite.Sprite_Init_Sub(texFilePath, w, h); //�`�悷��
	m_subSprite.MulColor = color;
	m_sprite.SetMulColor_Sub(m_subSprite.MulColor);
	m_subSprite.Position = pos;
	m_subSpriteFlag = true;
}

/// <summary>
/// �X�v���C�g�̏����A�b�v�f�[�g
/// </summary>
void SpriteRender::Update() {
	m_spriteSupporter.SpriteSupporter_Update();
	m_sprite.Sprite_Update(m_mainSprite.Position, m_mainSprite.Rotation, m_mainSprite.Scale, m_mainSprite.Pivot);
	m_sprite.Sprite_Update_Sub(m_subSprite.Position, m_subSprite.Rotation, m_subSprite.Scale, m_subSprite.Pivot);
}

/// <summary>
/// �X�v���C�g��`�悷��
/// </summary>
void SpriteRender::Render() {
	m_sprite.Sprite_Draw();		//�����̓��C���X�v���C�g�ƃT�u�X�v���C�g����
}
