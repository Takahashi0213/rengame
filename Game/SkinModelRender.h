#pragma once
#include "system/CGameObjectManager.h"
#include "SkinModelSupporter.h"

/// <summary>
/// �X�L�����f�������_�[
/// 3D��`���Ƃ��Ɏg���܂�
/// </summary>
class SkinModelRender : public IGameObject
{
public:
	typedef std::vector<CVector3>					VertexBuffer;		//���_�o�b�t�@�B
	typedef std::vector<unsigned int>				IndexBuffer;		//�C���f�b�N�X�o�b�t�@�B

	SkinModelRender();
	~SkinModelRender();
	void Update()override;
	void Render()override;

	void Model_Init(const wchar_t* filePath);
	void Model_Init(const wchar_t* filePath, CVector3 pos, CQuaternion rot, CVector3 scl);

	/// <summary>
	/// ���f����Ԃ�
	/// </summary>
	/// <returns>���f���̃|�C���^</returns>
	SkinModel* GetModel() {
		return &m_skinModel;
	}

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
	void SetScale(const CVector3 scr)
	{
		m_scale = scr;
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
	/// �����_�[���[�h��ݒ肷��
	/// </summary>
	/// <param name="mode">���[�h�ł��B</param>
	void SetRenderMode(RenderMode mode) {
		m_renderMode = mode;
		m_skinModel.SetRenderMode(mode);
	}
	/// <summary>
	/// �����_�[���[�h��Ԃ�
	/// </summary>
	/// <returns>�����ɐݒ肳��Ă郌���_�[���[�h��</returns>
	RenderMode GetRenderMode() {
		return m_renderMode;
	}
	
	/// <summary>
	/// �V���h�E���V�[�o�[�t���O�̕ύX
	/// </summary>
	void SetShadowReciever(bool flag) {
		m_skinModel.SetShadowReciever(flag);
	}
	/// <summary>
	/// �V���h�E�L���X�^�[�t���O�̕ύX
	/// </summary>
	void SetShadowCasterFlag(bool flag) {
		m_shadowCasterFlag = flag;
	}

	/// <summary>
	/// ���f�����y�ɓ������N���X���Ăяo���邼
	/// </summary>
	/// <remarks>
	/// 
	/// ���T���v���R�[�h��
	/// render->m_skinModelSupporter.SkinModelMove(�ݒ�l);
	/// 
	/// </remarks>
	SkinModelSupporter m_skinModelSupporter;		//�X�L�����f���T�|�[�^�[

private:
	struct Polygon {
		CVector3 vertPos[3];	//���_���W�B
		CVector3 normal;		//�@���B
	};
	std::vector<Polygon> m_polygonList;

	SkinModel m_skinModel;		//!<�X�L�����f��
	CVector3 m_position = CVector3::Zero();		//!<���W�B
	CQuaternion m_rotation = CQuaternion().Identity();		//!<��]�B
	CVector3 m_scale = CVector3().One();		//!<�g�嗦�B
	RenderMode m_renderMode = Default;			//�`�惂�[�h

	bool m_shadowCasterFlag = false;	//�V���h�E�L���X�^�[�ɓo�^����H
};

