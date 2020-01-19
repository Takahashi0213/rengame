#pragma once
class MaskSprite
{
public:
	MaskSprite();
	~MaskSprite();

	void Draw();

	//�ݒ�F�X
	//�S�Ă�subFlag��false�Ȃ烁�C���X�v���C�g�Atrue�Ȃ�T�u�X�v���C�g��ύX���܂�

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3 pos, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.Position = pos;
		}
		else {
			m_subSpriteData.Position = pos;
		}
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3 GetPosition(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSpriteData.Position;
		}
		else {
			return m_subSpriteData.Position;
		}
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.Rotation = rot;
		}
		else {
			m_subSpriteData.Rotation = rot;
		}
	}
	/// <summary>
	/// ��]���擾
	/// </summary>
	/// <returns>��]</returns>
	const CQuaternion GetRotation(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSpriteData.Rotation;
		}
		else {
			return m_subSpriteData.Rotation;
		}
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scr">�g�嗦</param>
	void SetScale(const CVector3 scl, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.Scale = scl;
		}
		else {
			m_subSpriteData.Scale = scl;
		}
	}
	void SetScale(const float scl, bool subFlag = false) { //�֗�Ver
		if (subFlag == false) {
			m_mainSpriteData.Scale.x = scl;
			m_mainSpriteData.Scale.y = scl;
		}
		else {
			m_subSpriteData.Scale.x = scl;
			m_subSpriteData.Scale.y = scl;
		}
	}
	/// <summary>
	/// �g�嗦���擾
	/// </summary>
	/// <returns>�g�嗦</returns>
	const CVector3 GetScale(bool subFlag = false) const
	{
		if (subFlag == false) {
			return m_mainSpriteData.Scale;
		}
		else {
			return m_subSpriteData.Scale;
		}
	}
	/// <summary>
	/// �s�{�b�g��ݒ�
	/// </summary>
	/// <param name="pivot">�s�{�b�g</param>
	void SetPivot(const CVector2 pivot, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.Pivot.x = pivot.x;
			m_mainSpriteData.Pivot.y = pivot.y;
		}
		else {
			m_subSpriteData.Pivot.x = pivot.x;
			m_subSpriteData.Pivot.y = pivot.y;
		}
	}
	/// <summary>
	/// �s�{�b�g���擾
	/// </summary>
	/// <returns>�s�{�b�g</returns>
	CVector2 GetPivot(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSpriteData.Pivot;
		}
		else {
			return m_subSpriteData.Pivot;
		}
	}

	/// <summary>
	/// �T�C�Y��ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	void SetSize(CVector2 size, bool subFlag = false) {
		if (subFlag == false) {
			m_mainSpriteData.Wide = size.x;
			m_mainSpriteData.High = size.y;
		}
		else {
			m_subSpriteData.Wide = size.x;
			m_subSpriteData.High = size.y;
		}

	}

	/// <summary>
	/// ��Z�J���[��ݒ�
	/// </summary>
	/// <param name="mulColor">��Z�J���[</param>
	void SetMulColor(const CVector4& mulColor, bool subFlag = false)
	{
		if (subFlag == false) {
			m_mainSpriteData.MulColor = mulColor;
			m_mainSprite.SetMulColor(m_mainSpriteData.MulColor);
		}
		else {
			m_subSpriteData.MulColor = mulColor;
			m_subSprite.SetMulColor(m_subSpriteData.MulColor);
		}
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	/// <returns>��Z�J���[</returns>
	CVector4 GetMulColor(bool subFlag = false)
	{
		if (subFlag == false) {
			return m_mainSpriteData.MulColor;
		}
		else {
			return m_subSpriteData.MulColor;
		}
	}
	
	Sprite* GetMainSprite() {
		return &m_mainSprite;
	}
	Sprite* GetSubSprite() {
		return &m_subSprite;
	}

private:
	void MaskSprite::CreateDepthStencilState();

	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11DepthStencilState* m_depthStencilState2 = nullptr;

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

	SpriteData m_mainSpriteData;	//���C���X�v���C�g
	SpriteData m_subSpriteData;		//�T�u�X�v���C�g�i�}�X�N�����Ƃ��Ɏg���܂��I�j

	Sprite m_mainSprite;
	Sprite m_subSprite;

};

