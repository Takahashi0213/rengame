#pragma once
#include "system/CGameObjectManager.h"
#include "Sprite.h"
#include "MaskSprite.h"
#include "SliceSprite.h"
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
	/// <summary>
	/// �X�v���C�g�̏����A�b�v�f�[�g
	/// </summary>
	void Update()override;
	/// <summary>
	/// �X�v���C�g��`�悷��
	/// </summary>
	void Render()override;

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
	void Init(const wchar_t* texFilePath, const float& w, const float& h, const int& priority = 0);

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
	void Init(const wchar_t* texFilePath, const float& w, const float& h, const CVector3& pos = CVector3().Zero(),
		const CVector4& color = CVector4().White(), const int& priority = 0);

	/// <summary>
	/// �T�u�X�v���C�g�p�̐ݒ�
	/// </summary>
	void InitSub(const wchar_t* texFilePath, const float& w, const float& h, const int& priority = 0);
	void InitSub(const wchar_t* texFilePath, const float& w, const float& h, const CVector3& pos = CVector3().Zero(),
		const CVector4& color = CVector4().White(), const int& priority = 0);

	/// <summary>
	/// ���̃X�v���C�g���}�X�N�X�v���C�g�Ɏw�肷��ꍇ�AInit�̑O�ɕK�����s���悤��
	/// </summary>
	void ChangeMaskSprite() {

		if (m_sliceSpriteFlag == true) {
			abort();	//���C�����I
		}

		if (m_maskSprite == nullptr) {
			m_maskSprite = new MaskSprite;
		}

		m_subSpriteFlag = true;
	}
	//�������̓X���C�X�X�v���C�g
	void ChangeSliceSprite(const CVector2& size) {

		if (m_subSpriteFlag == true) {
			abort();	//���C�����I
		}

		if (m_sliceSprite == nullptr) {
			m_sliceSprite = new SliceSprite;
		}
		m_sprite_RenderMode = Sprite_RenderMode::Slice9;
		m_sliceSprite->SetDefSize(size);
		m_sliceSpriteFlag = true;
	}

	//�ݒ�F�X
	//�S�Ă�subFlag��false�Ȃ烁�C���X�v���C�g�Atrue�Ȃ�T�u�X�v���C�g��ύX���܂�

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	void SetPosition(const CVector3& pos, const int& list = -1)
	{
		if (list == -1) {
			m_mainSprite.Position = pos;
		}
		else {
			m_subSprite[list].Position = pos;
		}
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	const CVector3 GetPosition(const int& list = -1) const
	{
		if (list == -1) {
			return m_mainSprite.Position;
		}
		else {
			return m_subSprite[list].Position;
		}
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	void SetRotation(const CQuaternion& rot, const int& list = -1)
	{
		if (list == -1) {
			m_mainSprite.Rotation = rot;
		}
		else {
			m_subSprite[list].Rotation = rot;
		}
	}
	/// <summary>
	/// ��]���擾
	/// </summary>
	const CQuaternion GetRotation(const int& list = -1) const
	{
		if (list == -1) {
			return m_mainSprite.Rotation;
		}
		else {
			return m_subSprite[list].Rotation;
		}
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	void SetScale(const CVector3& scl, const int& list = -1)
	{
		if (list == -1) {
			m_mainSprite.Scale = scl;
		}
		else {
			m_subSprite[list].Scale = scl;
		}
	}
	void SetScale(const float& scl, const int& list = -1) { //�֗�Ver
		if (list == -1) {
			m_mainSprite.Scale.x = scl;
			m_mainSprite.Scale.y = scl;
		}
		else {
			m_subSprite[list].Scale.x = scl;
			m_subSprite[list].Scale.y = scl;
		}
	}
	/// <summary>
	/// �g�嗦���擾
	/// </summary>
	const CVector3 GetScale(const int& list = -1) const
	{
		if (list == -1) {
			return m_mainSprite.Scale;
		}
		else {
			return m_subSprite[list].Scale;
		}
	}
	/// <summary>
	/// �s�{�b�g��ݒ�
	/// </summary>
	void SetPivot(const CVector2& pivot , const int& list = -1)
	{
		if (list == -1) {
			m_mainSprite.Pivot.x = pivot.x;
			m_mainSprite.Pivot.y = pivot.y;
		}
		else {
			m_subSprite[list].Pivot.x = pivot.x;
			m_subSprite[list].Pivot.y = pivot.y;
		}
	}
	/// <summary>
	/// �s�{�b�g���擾
	/// </summary>
	CVector2 GetPivot(const int& list = -1)
	{
		if (list == -1) {
			return m_mainSprite.Pivot;
		}
		else {
			return m_subSprite[list].Pivot;
		}
	}

	/// <summary>
	/// �����擾
	/// </summary>
	float GetWide(const int& list = -1)
	{
		if (list == -1) {
			return m_mainSprite.Wide;
		}
		else {
			return m_subSprite[list].Wide;
		}
	}
	/// <summary>
	/// �������擾
	/// </summary>
	float GetHigh(const int& list = -1)
	{
		if (list == -1) {
			return m_mainSprite.High;
		}
		else {
			return m_subSprite[list].High;
		}
	}

	/// <summary>
	/// ��Z�J���[��ݒ�
	/// </summary>
	void SetMulColor(const CVector4& mulColor, const int& list = -1)
	{
		if (list == -1) {
			m_mainSprite.MulColor = mulColor;
			m_sprite.SetMulColor(m_mainSprite.MulColor);
		}
		else {
			m_subSprite[list].MulColor = mulColor;
			m_maskSprite->GetSubList_Sprite(list)->SetMulColor(mulColor);
		}
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	CVector4 GetMulColor(const int& list = -1)
	{
		if (list == -1) {
			return m_mainSprite.MulColor;
		}
		else {
			return m_subSprite[list].MulColor;
		}
	}
	/// <summary>
	/// �A���t�@�̐ݒ�
	/// </summary>
	void SetAlpha(const float& Alpha, const int& list = -1) {

		if (list == -1) {
			m_mainSprite.MulColor.w = Alpha;
			m_sprite.SetMulColor(m_mainSprite.MulColor);
		}
		else {
			m_subSprite[list].MulColor.w = Alpha;
			m_maskSprite->GetSubList_Sprite(list)->SetMulColor(m_subSprite[list].MulColor);
		}
	}
	/// <summary>
	/// �A���t�@�̎擾
	/// </summary>
	float GetAlpha(const int& list = -1) {
		if (list == -1) {
			return m_mainSprite.MulColor.w;
		}
		else {
			return m_subSprite[list].MulColor.w;
		}
	}

	//�p�^�[���擾�֘A
	int GetMaxPattern() {
		return m_pattern;		//�ő�p�^�[��
	}
	int GetNowPattern() {
		return m_nowPattern;	//���݃p�^�[��
	}

	/// <summary>
	/// �}�X�N�X�v���C�g�̎g�p�t���O
	/// </summary>
	/// <returns>
	/// false�Ȃ�}�X�N�X�v���C�g�ł͂Ȃ�
	/// true�Ȃ炱���̓}�X�N�X�v���C�g
	/// </returns>
	bool GetMaskSpriteFlag() {
		if (m_maskSprite == nullptr) {
			return false;
		}
		else {
			return true;
		}
	}
	/// <summary>
	/// �T�u�X�v���C�g�̐���Ԃ�
	/// </summary>
	int GetSubSpriteNum() {
		return static_cast<int>(m_subSprite.size());
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
	void SetCutLine(const float& cut) {
		m_pos_Cut = cut;
		m_sprite.m_cut_UV = m_pos_Cut;
	}
	float GetCutLine() {
		return m_pos_Cut;
	}

	/// <summary>
	/// SliceSprite�Ȃ�3Slice�ɕύX����
	/// </summary>
	void Set3Slice(const float& size) {
		if (m_sliceSprite != nullptr) {
			m_sliceSprite->Change3Slice(size);
		}
	}

	/// <summary>
	/// �c�p�^�[���̐ݒ�
	/// </summary>
	/// <param name="pt">�p�^�[����</param>
	void SetHighPattern(const int& pattern,const int& nowPt = 0) {
		m_sprite.m_renderMode = Sprite_RenderMode::Pattern;
		m_sprite.m_slicePattern = pattern;
		m_pattern = pattern;
		m_defPosition = m_mainSprite.Position;
		m_nowPattern = nowPt;
		ChangePattern(m_nowPattern);
	}

	void ChangePattern(int pattern);

	/// <summary>
	/// �}�X�N�̃T�u�X�v���C�g�̃����_�[���[�h��ς��܂�
	/// </summary>
	void ChangeRenderMode_Mask(const Sprite_RenderMode srm, const int& list) {
		if (m_subSpriteFlag == true) {
			m_maskSprite->ChangeRenderMode(srm, list);
	}
	}

	/// <summary>
	/// �}�E�X�������ɏd�Ȃ��Ă���True��Ԃ�
	/// </summary>
	/// <returns>�d�Ȃ��Ă�H</returns>
	bool MouseOverMouse();

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
	//�T�u�T�|�[�^�[�̎擾
	SpriteSupporter* GetSubSpriteSupporter(const int& No) {
		return m_subSpriteSupporter[No];
	}

private:
	//�}�X�N�X�v���C�g�Ȃ���s�����
	void MaskSpriteDataSet();
	//�X�v���C�g�T�|�[�^�[�̍X�V
	void SpriteSp_Update() {
		//���C��
		m_spriteSupporter.SpriteSupporter_Update();
		//�T�u
		for (int i = 0; i < m_subSpriteSupporter.size(); i++) {
			m_subSpriteSupporter[i]->SpriteSupporter_Update();
		}
	}

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

	Sprite m_sprite;		//!<�X�v���C�g�B
	MaskSprite* m_maskSprite = nullptr;
	SliceSprite* m_sliceSprite = nullptr;

	SpriteData m_mainSprite;								//���C���X�v���C�g
	std::vector<SpriteData> m_subSprite;					//�T�u�X�v���C�g
	std::vector<SpriteSupporter*> m_subSpriteSupporter;		//�T�u�X�v���C�g�E�T�|�[�^�[

	bool m_subSpriteFlag = false;	//�T�u�X�v���C�g�g�p���H�H�H
	bool m_sliceSpriteFlag = false;	//slice9�X�v���C�g�g�p���H�H�H

	Sprite_RenderMode m_sprite_RenderMode = Sprite_RenderMode::Normal;	//�����_�[���[�h
	float m_pos_Cut = 0.0f;				//CutMode���A�ǂ�����؂�H�H�H�H

	int m_pattern = -1;					//�c�p�^�[����
	int m_nowPattern = 0;				//���݃p�^�[��
	CVector3 m_defPosition = CVector3::Zero();	//Pos�ꎞ�ۑ�
};

