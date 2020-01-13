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

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]���擾
	/// </summary>
	/// <returns>��]</returns>
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scr">�g�嗦</param>
	void SetScale(const CVector3 scl)
	{
		m_scale = scl;
	}
	void SetScale(const float scl) { //�֗�Ver
		m_scale.x = scl;
		m_scale.y = scl;
	}
	/// <summary>
	/// �g�嗦���擾
	/// </summary>
	/// <returns>�g�嗦</returns>
	const CVector3 GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// �s�{�b�g��ݒ�
	/// </summary>
	/// <param name="pivot">�s�{�b�g</param>
	void SetPivot(const CVector2 pivot)
	{
		m_pivot.x = pivot.x;
		m_pivot.y = pivot.y;
	}
	/// <summary>
	/// �s�{�b�g���擾
	/// </summary>
	/// <returns>�s�{�b�g</returns>
	CVector2 GetPivot()
	{
		return m_pivot;
	}

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns>��</returns>
	float GetWide()
	{
		return m_wide;
	}
	/// <summary>
	/// �������擾
	/// </summary>
	/// <returns>����</returns>
	float GetHigh()
	{
		return m_high;
	}

	/// <summary>
	/// ��Z�J���[��ݒ�
	/// </summary>
	/// <param name="mulColor">��Z�J���[</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;		
		m_sprite.SetMulColor(m_mulColor);
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	/// <returns>��Z�J���[</returns>
	CVector4 GetMulColor()
	{
		return m_mulColor;
	}

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
	//ID3D11ShaderResourceView* m_texture;	//!<�e�N�X�`���B
	Sprite m_sprite;		//!<�X�v���C�g�B
	CVector3 m_position = CVector3::Zero();		//!<���W�B
	CQuaternion m_rotation= CQuaternion().Identity();		//!<��]�B
	CVector3 m_scale = CVector3().One();		//!<�g�嗦�B
	CVector2 m_pivot = { 0.5f, 0.5f };		//!<�s�{�b�g�B
	float m_wide = 0.0f;	//���I
	float m_high = 0.0f;	//�����I
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };	//!<��Z�J���[�B

	Sprite_RenderMode m_sprite_RenderMode = Sprite_RenderMode::Normal;
	float m_pos_Cut = 0.0f;				//CutMode���A�ǂ�����؂�H�H�H�H

};

