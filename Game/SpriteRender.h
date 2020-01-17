#pragma once
#include "system/CGameObjectManager.h"
#include "Sprite.h"
#include "SpriteSupporter.h"

/// <summary>
/// �X�v���C�g�����_�[
/// 2D��`���Ƃ��Ɏg���܂�
/// </summary>
class SpriteRender : public IGameObject
{
public:

	SpriteRender();
	~SpriteRender();
	void Update()override;
	void Render()override;

	void Init(const wchar_t* texFilePath, float w, float h, int priority = 0);
	void Init(const wchar_t* texFilePath, float w, float h, CVector3 pos = CVector3().Zero(), CVector4 color = CVector4().White(), int priority = 0);

	void InitSub(const wchar_t* texFilePath, float w, float h, int priority = 0);
	void InitSub(const wchar_t* texFilePath, float w, float h, CVector3 pos = CVector3().Zero(), CVector4 color = CVector4().White(), int priority = 0);

	//�ݒ�F�X
	//�S�Ă�subFlag��false�Ȃ烁�C���X�v���C�g�Atrue�Ȃ�T�u�X�v���C�g��ύX���܂�

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3 pos, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.Position = pos;
		}
		else {
			m_subSprite.Position = pos;
		}
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3 GetPosition( bool subFlag = false ) const
	{
		if (subFlag == false) {
			return m_mainSprite.Position;
		}
		else {
			return m_subSprite.Position;
		}
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.Rotation = rot;
		}
		else {
			m_subSprite.Rotation = rot;
		}
	}
	/// <summary>
	/// ��]���擾
	/// </summary>
	/// <returns>��]</returns>
	const CQuaternion GetRotation(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSprite.Rotation;
		}
		else {
			return m_subSprite.Rotation;
		}
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scr">�g�嗦</param>
	void SetScale(const CVector3 scl, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.Scale = scl;
		}
		else {
			m_subSprite.Scale = scl;
		}
	}
	void SetScale(const float scl, bool subFlag = false) { //�֗�Ver
		if (subFlag == false) {
			m_mainSprite.Scale.x = scl;
			m_mainSprite.Scale.y = scl;
		}
		else {
			m_subSprite.Scale.x = scl;
			m_subSprite.Scale.y = scl;
		}
	}
	/// <summary>
	/// �g�嗦���擾
	/// </summary>
	/// <returns>�g�嗦</returns>
	const CVector3 GetScale(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSprite.Scale;
		}
		else {
			return m_subSprite.Scale;
		}
	}
	/// <summary>
	/// �s�{�b�g��ݒ�
	/// </summary>
	/// <param name="pivot">�s�{�b�g</param>
	void SetPivot(const CVector2 pivot , bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.Pivot.x = pivot.x;
			m_mainSprite.Pivot.y = pivot.y;
		}
		else {
			m_subSprite.Pivot.x = pivot.x;
			m_subSprite.Pivot.y = pivot.y;
		}
	}
	/// <summary>
	/// �s�{�b�g���擾
	/// </summary>
	/// <returns>�s�{�b�g</returns>
	CVector2 GetPivot(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSprite.Pivot;
		}
		else {
			return m_subSprite.Pivot;
		}
	}

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns>��</returns>
	float GetWide(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSprite.Wide;
		}
		else {
			return m_subSprite.Wide;
		}
	}
	/// <summary>
	/// �������擾
	/// </summary>
	/// <returns>����</returns>
	float GetHigh(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSprite.High;
		}
		else {
			return m_subSprite.High;
		}
	}

	/// <summary>
	/// ��Z�J���[��ݒ�
	/// </summary>
	/// <param name="mulColor">��Z�J���[</param>
	void SetMulColor(const CVector4& mulColor, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSprite.MulColor = mulColor;
			m_sprite.SetMulColor(m_mainSprite.MulColor);
		}
		else {
			m_subSprite.MulColor = mulColor;
			m_sprite.SetMulColor_Sub(m_subSprite.MulColor);
		}
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	/// <returns>��Z�J���[</returns>
	CVector4 GetMulColor(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSprite.MulColor;
		}
		else {
			return m_subSprite.MulColor;
		}
	}
	/// <summary>
	/// �A���t�@�̐ݒ�
	/// </summary>
	/// <param name="Alpha">�A���t�@</param>
	void SetAlpha(const float Alpha, bool subFlag = false) {
		if (subFlag == false) {
			m_mainSprite.MulColor.w = Alpha;
			m_sprite.SetMulColor(m_mainSprite.MulColor);
		}
		else {
			m_subSprite.MulColor.w = Alpha;
			m_sprite.SetMulColor(m_subSprite.MulColor);
		}
	}
	/// <summary>
	/// �A���t�@�̎擾
	/// </summary>
	/// <returns>���݂̕s�����x��</returns>
	float GetAlpha(bool subFlag = false) {
		if (subFlag == false) {
			return m_mainSprite.MulColor.w;
		}
		else {
			return m_subSprite.MulColor.w;
		}
	}

	//�O���t�B�J���ȃA�����W���I�I

	/// <summary>
	/// �����_�[���[�h�̐ݒ�
	/// </summary>
	/// <param name="render_mode">���[�h</param>
	void SetRenderMode(Sprite_RenderMode render_mode) {
		m_sprite_RenderMode = render_mode;
		m_sprite.m_renderMode = m_sprite_RenderMode;
	}

	/// <summary>
	/// �ǂ�����؂邩�ݒ�
	/// </summary>
	/// <param name="cut">UV���W�̋��E</param>
	void SetCutLine(float cut) {
		m_pos_Cut = cut;
		m_sprite.m_cut_UV = m_pos_Cut;
	}

	/// <summary>
	/// �X�v���C�g���y�ɓ������N���X���Ăяo���邼
	/// </summary>
	/// <remarks>
	/// 
	/// ���T���v���R�[�h��
	/// render->m_spriteSupporter.SpriteMove(�ݒ�l);
	/// 
	/// </remarks>
	SpriteSupporter m_spriteSupporter;		//�X�v���C�g�T�|�[�^�[

private:

	struct SpriteData
	{
		CVector3 Position = CVector3::Zero();
		CQuaternion Rotation = CQuaternion().Identity();
		CVector3 Scale = CVector3().One();
		CVector2 Pivot = { 0.5f, 0.5f };
		float Wide = 0.0f;	//���I
		float High = 0.0f;	//�����I
		CVector4 MulColor = { 1.0f,1.0f,1.0f,1.0f };	//!<��Z�J���[�B
	};

	//ID3D11ShaderResourceView* m_texture;	//!<�e�N�X�`���B
	Sprite m_sprite;		//!<�X�v���C�g�B

	SpriteData m_mainSprite;	//���C���X�v���C�g
	SpriteData m_subSprite;		//�T�u�X�v���C�g�i�}�X�N�����Ƃ��Ɏg���܂��I�j

	bool m_subSpriteFlag = false;	//�T�u�X�v���C�g�g�p���H�H�H

	Sprite_RenderMode m_sprite_RenderMode = Sprite_RenderMode::Normal;
	float m_pos_Cut = 0.0f;				//CutMode���A�ǂ�����؂�H�H�H�H

};

