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
void SpriteRender::Init(const wchar_t* texFilePath, const float& w, const float& h, const int& priority)
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
void SpriteRender::InitSub(const wchar_t* texFilePath, const float& w, const float& h, const int& priority)
{
	SpriteData data;
	m_subSprite.push_back(data);
	SpriteSupporter* SS = new SpriteSupporter;
	m_subSpriteSupporter.push_back(SS);
	SS->SpriteRenderSetting(this, (int)m_subSprite.size()-1);
	m_maskSprite->AddSubSprite(texFilePath, w, h);
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
void SpriteRender::Init(const wchar_t* texFilePath, const float& w, const float& h,
	const CVector3& pos, const CVector4& color, const int& priority) {

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
void SpriteRender::InitSub(const wchar_t* texFilePath, const float& w, const float& h, const CVector3& pos,
	const CVector4& color, const int& priority) {

	SpriteData data;
	data.Wide = w;
	data.High = h;
	data.MulColor = color;
	data.Position = pos;
	m_subSprite.push_back(data);
	SpriteSupporter* SS = new SpriteSupporter;
	m_subSpriteSupporter.push_back(SS);
	SS->SpriteRenderSetting(this, (int)m_subSprite.size()-1);

	Sprite* newSp = m_maskSprite->AddSubSprite(texFilePath, w, h);
	newSp->SetMulColor(data.MulColor);
}

/// <summary>
/// �X�v���C�g�̏����A�b�v�f�[�g
/// </summary>
void SpriteRender::Update() {

	SpriteSp_Update();

	if (m_maskSprite != nullptr) {	
		//�}�X�N�X�v���C�g�̏���
		MaskSpriteDataSet();

		m_maskSprite->GetMainSprite()->Sprite_Update(m_mainSprite.Position, m_mainSprite.Rotation, 
			m_mainSprite.Scale, m_mainSprite.Pivot);
		if (m_subSprite.size() > 0) {
			for (int i = 0; i < m_subSprite.size() ; i++) {
				//�T�u�X�V
				m_maskSprite->GetSubList_Sprite(i)->Sprite_Update(m_subSprite[i].Position,
					m_subSprite[i].Rotation, m_subSprite[i].Scale, m_subSprite[i].Pivot);
			}
		}
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

	//���C��
	m_maskSprite->SetPosition(m_mainSprite.Position);
	m_maskSprite->SetRotation(m_mainSprite.Rotation);
	m_maskSprite->SetScale(m_mainSprite.Scale);
	m_maskSprite->SetPivot(m_mainSprite.Pivot);
	m_maskSprite->SetSize({ m_mainSprite.Wide,m_mainSprite.High });
	m_maskSprite->SetMulColor(m_mainSprite.MulColor);
	//�T�u
	if (m_subSprite.size() > 0) {
		for (int i = 0; i < m_subSprite.size(); i++) {
			//�T�u�X�V
			m_maskSprite->SetPosition(m_subSprite[i].Position, i);
			m_maskSprite->SetRotation(m_subSprite[i].Rotation, i);
			m_maskSprite->SetScale(m_subSprite[i].Scale, i);
			m_maskSprite->SetPivot(m_subSprite[i].Pivot, i);
			m_maskSprite->SetSize({ m_subSprite[i].Wide,m_mainSprite.High }, i);
			m_maskSprite->SetMulColor(m_subSprite[i].MulColor, i);
		}
	}

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

bool SpriteRender::MouseOverMouse() {

	bool Flag = false;

	CVector2 MousePos = MouseSupporter::GetInstance()->GetMousePos_Sprite();

	//���W�v�Z
	float PosX = m_mainSprite.Position.x + (m_mainSprite.Wide / 2.0f);
	float PosX2 = m_mainSprite.Position.x - (m_mainSprite.Wide / 2.0f);
	float PosY = m_mainSprite.Position.y + (m_mainSprite.High / 2.0f);
	float PosY2 = m_mainSprite.Position.y - (m_mainSprite.High / 2.0f);

	if (MousePos.x <= PosX && MousePos.x >= PosX2 && MousePos.y <= PosY && MousePos.y >= PosY2) {
		Flag = true;
	}

	return Flag;
}