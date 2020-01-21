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

	if (m_subSpriteFlag == false && m_sliceSpriteFlag == false) {
		m_sprite.Sprite_Init(texFilePath, w, h); //�`�悷��
		m_sprite.SetMulColor(m_mainSprite.MulColor);
	}
	else if (m_sliceSpriteFlag == true) {
		m_sliceSprite->SetTex(texFilePath, w, h); //�`�悷��
		m_sliceSprite->SetColor(m_mainSprite.MulColor);
	}
	else {
		m_maskSprite->GetMainSprite()->Sprite_Init(texFilePath, w, h); //�`�悷��
		m_maskSprite->GetMainSprite()->SetMulColor(m_mainSprite.MulColor);
	}
}
void SpriteRender::InitSub(const wchar_t* texFilePath, float w, float h, int priority)
{
	m_subSprite.Wide = w;
	m_subSprite.High = h;
	m_maskSprite->GetSubSprite()->Sprite_Init(texFilePath, w, h); //�`�悷��
	m_maskSprite->GetSubSprite()->SetMulColor(m_subSprite.MulColor);
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
	m_mainSprite.MulColor = color;
	m_mainSprite.Position = pos;

	if (m_subSpriteFlag == false && m_sliceSpriteFlag == false) {
		m_sprite.Sprite_Init(texFilePath, w, h); //�`�悷��
		m_sprite.SetMulColor(m_mainSprite.MulColor);
	}
	else if (m_sliceSpriteFlag == true) {
		m_sliceSprite->SetTex(texFilePath, w, h); //�`�悷��
		m_sliceSprite->SetColor(m_mainSprite.MulColor);
	}
	else {
		m_maskSprite->GetMainSprite()->Sprite_Init(texFilePath, w, h); //�`�悷��
		m_maskSprite->GetMainSprite()->SetMulColor(m_mainSprite.MulColor);
	}
}
void SpriteRender::InitSub(const wchar_t* texFilePath, float w, float h, CVector3 pos, CVector4 color, int priority) {

	m_subSprite.Wide = w;
	m_subSprite.High = h;
	m_maskSprite->GetSubSprite()->Sprite_Init(texFilePath, w, h); //�`�悷��
	m_subSprite.MulColor = color;
	m_maskSprite->GetSubSprite()->SetMulColor(m_subSprite.MulColor);
	m_subSprite.Position = pos;
}

/// <summary>
/// �X�v���C�g�̏����A�b�v�f�[�g
/// </summary>
void SpriteRender::Update() {

	m_spriteSupporter.SpriteSupporter_Update();

	if (m_maskSprite != nullptr) {	
		//�}�X�N�X�v���C�g�̏���
		MaskSpriteDataSet();

		m_maskSprite->GetMainSprite()->Sprite_Update(m_mainSprite.Position, m_mainSprite.Rotation, m_mainSprite.Scale, m_mainSprite.Pivot);
		m_maskSprite->GetSubSprite()->Sprite_Update(m_subSprite.Position, m_subSprite.Rotation, m_subSprite.Scale, m_subSprite.Pivot);
	}
	else if (m_sliceSprite != nullptr) {
		//����
		m_sliceSprite->SetSliceData(m_mainSprite.Position, m_mainSprite.Rotation, m_mainSprite.Scale,
			m_mainSprite.Pivot, m_mainSprite.Wide, m_mainSprite.High, m_mainSprite.MulColor);
	}
	else {
		m_sprite.Sprite_Update(m_mainSprite.Position, m_mainSprite.Rotation, m_mainSprite.Scale, m_mainSprite.Pivot);
	}
}

/// <summary>
/// �X�v���C�g��`�悷��
/// </summary>
void SpriteRender::Render() {

	if (m_subSpriteFlag == false && m_sliceSpriteFlag == false) {
		m_sprite.Sprite_Draw();		//�ʏ�X�v���C�g
	}	
	else if (m_sliceSpriteFlag == true) {
		m_sliceSprite->SliceSpriteDraw();	//�X���C�X�X�v���C�g
	}
	else {
		m_maskSprite->Draw();		//�}�X�N�X�v���C�g
	}
}

/// <summary>
/// �}�X�N�X�v���C�g�̃f�[�^���X�V����
/// </summary>
void SpriteRender::MaskSpriteDataSet() {

	m_maskSprite->SetPosition(m_mainSprite.Position);
	m_maskSprite->SetPosition(m_subSprite.Position, true);

	m_maskSprite->SetRotation(m_mainSprite.Rotation);
	m_maskSprite->SetRotation(m_subSprite.Rotation, true);

	m_maskSprite->SetScale(m_mainSprite.Scale);
	m_maskSprite->SetScale(m_subSprite.Scale, true);

	m_maskSprite->SetPivot(m_mainSprite.Pivot);
	m_maskSprite->SetPivot(m_subSprite.Pivot, true);

	m_maskSprite->SetSize({ m_mainSprite.Wide,m_mainSprite.High });
	m_maskSprite->SetSize({ m_mainSprite.Wide,m_mainSprite.High }, true);

	m_maskSprite->SetMulColor(m_mainSprite.MulColor);
	m_maskSprite->SetMulColor(m_subSprite.MulColor, true);

}

/// <summary>
/// �p�^�[���̕ύX�Ɠ����ɍ��W���X�V����
/// </summary>
/// <param name="pattern">���݃p�^�[��</param>
void SpriteRender::ChangePattern(int pattern) {

	m_nowPattern = pattern;
	m_sprite.m_nowPattern = pattern;
	m_mainSprite.Pivot.x = 0.5f;
	m_mainSprite.Pivot.y = 1.0f;
	float OneSize = m_mainSprite.High / (float)m_pattern;		//�p�^�[��1�̑傫�����v�Z

	m_mainSprite.Position.y = m_defPosition.y + (OneSize * (float)pattern);
}