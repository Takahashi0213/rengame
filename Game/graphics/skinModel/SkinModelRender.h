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

	//�ݒ�
	void Model_Init(const wchar_t* filePath);
	void Model_Init(const wchar_t* filePath, const CVector3& pos, const CQuaternion& rot, const CVector3& scl,
		EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	//�A�j���[�V����������Ver
	void Model_Init_Anim(const wchar_t* filePath,
		AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0,
		EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);

	/// <summary>
	/// ���f����Ԃ�
	/// </summary>
	/// <returns>���f���̃|�C���^</returns>
	SkinModel GetModel_() {
		return m_skinModel;
	}
	SkinModel* GetModel() {
		return &m_skinModel;
	}

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	const CVector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// ��]���擾
	/// </summary>
	const CQuaternion GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	void SetScale(const CVector3& scr)
	{
		m_scale = scr;
	}
	void SetScale(const float& scr)
	{
		CVector3 Scr = { scr,scr,scr };
		m_scale = Scr;
	}
	/// <summary>
	/// �g�嗦���擾
	/// </summary>
	const CVector3 GetScale() const
	{
		return m_scale;
	}

	/// <summary>
	/// �܂Ƃ߂ăZ�b�g
	/// </summary>
	void SetUp(const CVector3& pos, const CQuaternion& rot, const CVector3& scl) {
		SetPosition(pos);
		SetRotation(rot);
		SetScale(scl);
	}

	/// <summary>
	/// �����_�[���[�h��ݒ肷��
	/// </summary>
	/// <param name="mode">���[�h�ł��B</param>
	void SetRenderMode(const RenderMode mode) {
		m_renderMode = mode;
		m_skinModel.SetRenderMode(mode);
	}
	/// <summary>
	/// �����_�[���[�h��Ԃ�
	/// </summary>
	RenderMode GetRenderMode() {
		return m_renderMode;
	}
	
	/// <summary>
	/// �`��t���O�̕ύX
	/// </summary>
	void SetDrawFlag(const bool& flag) {
		m_isDraw = flag;
	}

	/// <summary>
	/// �V���h�E���V�[�o�[�t���O�̕ύX
	/// </summary>
	void SetShadowReciever(const bool& flag) {
		m_skinModel.SetShadowReciever(flag);
	}

	/// <summary>
	/// �V���h�E�L���X�^�[�t���O�̕ύX
	/// </summary>
	void SetShadowCasterFlag(const bool& flag) {
		m_shadowCasterFlag = flag;
	}

	/// <summary>
	/// �A�j���[�V�����̍Đ�
	/// </summary>
	/// <param name="animNo">�A�j���[�V�����N���b�v�̔ԍ��B�R���X�g���N�^�ɓn����animClipList�̕��тƂȂ�B</param>
	/// <param name="interpolateTime">�⊮����(�P�ʁF�b)</param>
	void PlayAnimation(const int& animNo, const float& interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	/// <summary>
	/// �A�j���[�V�����X�s�[�h�̕ύX
	/// </summary>
	void SetAnimationSpeed(const float& speed = 20.0f) {
		m_animationSpeed = speed;
	}

	/// <summary>
	/// �A�j���[�V�����̍Đ����H
	/// </summary>
	/// <returns>true�Ȃ�Đ���</returns>
	bool IsPlayingAnimation() const
	{
		return m_animation.IsPlaying();
	}

	/// <summary>
	/// �A�j���[�V�������X�V����H
	/// false�Œ�~�Atrue�ōĊJ
	/// </summary>
	void SetIsUpdateAnimation(const bool& flag) {
		m_isUpdateAnimation = flag;
	}

	/// <summary>
	/// �X�L�����f���T�|�[�^�[���X�V����H
	/// false�Œ�~�Atrue�ōĊJ
	/// </summary>
	void SetIsUpdateSkinModelSupporter(const bool& flag) {
		m_isUpdateSkinModelSupporter = flag;
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
	/*!
	* @brief	�A�j���[�V�����̏������B
	*/
	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

	struct Polygon {
		CVector3 vertPos[3];	//���_���W�B
		CVector3 normal;		//�@���B
	};
	std::vector<Polygon> m_polygonList;

	bool m_isDraw = true;											//!<�`�悷��H

	SkinModel m_skinModel;											//!<�X�L�����f��
	CVector3 m_position = CVector3::Zero();							//!<���W�B
	CQuaternion m_rotation = CQuaternion().Identity();				//!<��]�B
	CVector3 m_scale = CVector3().One();							//!<�g�嗦�B
	RenderMode m_renderMode = Default;								//!<�`�惂�[�h

	bool m_isUpdateSkinModelSupporter = true;						//!<�X�L�����f���T�|�[�^�[���X�V����H

	AnimationClip*				m_animationClips = nullptr;			//!<�A�j���[�V�����N���b�v�B
	int							m_numAnimationClips = 0;			//!<�A�j���[�V�����N���b�v�̐��B
	Animation					m_animation;						//!<�A�j���[�V�����B
	bool						m_isUpdateAnimation = true;			//!<�A�j���[�V�������X�V����H
	float						m_animationSpeed = 20.0f;			//!<�A�j���[�V�������X�V����X�s�[�h�B

	bool m_shadowCasterFlag = false;								//!<�V���h�E�L���X�^�[�ɓo�^����H
};

