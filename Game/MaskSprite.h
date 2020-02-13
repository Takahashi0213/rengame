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
	void SetPosition(const CVector3 pos, int list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Position = pos;
		}
		else {
			m_subSpriteList[list].subData.Position = pos;
		}
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	const CVector3 GetPosition(int list = -1) const
	{
		if (list == -1) {
			return m_mainSpriteData.Position;
		}
		else {
			return m_subSpriteList[list].subData.Position;		//�T�u
		}
	}
	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot,int list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Rotation = rot;
		}
		else {
			m_subSpriteList[list].subData.Rotation = rot;		//�T�u
		}
	}
	/// <summary>
	/// ��]���擾
	/// </summary>
	/// <returns>��]</returns>
	const CQuaternion GetRotation(int list = -1) const
	{
		if (list == -1) {
			return m_mainSpriteData.Rotation;
		}
		else {
			return m_subSpriteList[list].subData.Rotation;		//�T�u
		}
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scr">�g�嗦</param>
	void SetScale(const CVector3 scl,int list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Scale = scl;
		}
		else {
			m_subSpriteList[list].subData.Scale = scl;		//�T�u
		}
	}
	void SetScale(const float scl, int list = -1) { //�֗�Ver
		if (list == -1) {
			m_mainSpriteData.Scale.x = scl;
			m_mainSpriteData.Scale.y = scl;
		}
		else {
			m_subSpriteList[list].subData.Scale.x = scl;
			m_subSpriteList[list].subData.Scale.y = scl;
		}
	}
	/// <summary>
	/// �g�嗦���擾
	/// </summary>
	/// <returns>�g�嗦</returns>
	const CVector3 GetScale(int list = -1) const
	{
		if (list == -1) {
			return m_mainSpriteData.Scale;
		}
		else {
			return m_subSpriteList[list].subData.Scale;
		}
	}
	/// <summary>
	/// �s�{�b�g��ݒ�
	/// </summary>
	/// <param name="pivot">�s�{�b�g</param>
	void SetPivot(const CVector2 pivot, int list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Pivot = pivot;
		}
		else {
			m_subSpriteList[list].subData.Pivot = pivot;
		}
	}
	/// <summary>
	/// �s�{�b�g���擾
	/// </summary>
	/// <returns>�s�{�b�g</returns>
	CVector2 GetPivot(int list = -1)
	{
		if (list == -1) {
			return m_mainSpriteData.Pivot;
		}
		else {
			return m_subSpriteList[list].subData.Pivot;
		}
	}

	/// <summary>
	/// �T�C�Y��ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	void SetSize(CVector2 size, int list = -1) {
		
		if (list == -1) {
			m_mainSpriteData.Wide = size.x;
			m_mainSpriteData.High = size.y;
		}
		else {
			m_subSpriteList[list].subData.Wide = size.x;
			m_subSpriteList[list].subData.High = size.y;
		}
	}

	/// <summary>
	/// ��Z�J���[��ݒ�
	/// </summary>
	/// <param name="mulColor">��Z�J���[</param>
	void SetMulColor(const CVector4& mulColor, int list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.MulColor = mulColor;
			m_mainSprite.SetMulColor(m_mainSpriteData.MulColor);
		}
		else {
			m_subSpriteList[list].subData.MulColor = mulColor;
			m_subSpriteList[list].sprite->SetMulColor(m_subSpriteList[list].subData.MulColor);
		}
	}
	/// <summary>
	/// ��Z�J���[���擾
	/// </summary>
	/// <returns>��Z�J���[</returns>
	CVector4 GetMulColor(int list = -1)
	{
		if (list == -1) {
			return m_mainSpriteData.MulColor;
		}
		else {
			return m_subSpriteList[list].subData.MulColor;
		}
	}
	
	/// <summary>
	/// �T�u�X�v���C�g�̒ǉ�
	/// </summary>
	Sprite* AddSubSprite(const wchar_t* texFilePath, float w, float h);

	//�擾
	Sprite* GetMainSprite() {
		return &m_mainSprite;
	}
	Sprite* GetSubList_Sprite(int i) {
		return m_subSpriteList[i].sprite;
	}


private:
	//�X�e�[�g���쐬
	void MaskSprite::CreateDepthStencilState();

	//�[�x�X�e���V��
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11DepthStencilState* m_depthStencilState_Def = nullptr;
	ID3D11DepthStencilState* m_depthStencilState_Z = nullptr;

	//�X�v���C�g�̃f�[�^
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

	//���C���X�v���C�g
	SpriteData m_mainSpriteData;
	Sprite m_mainSprite;

	//�T�u�X�v���C�g�I�I
	struct SubSpriteData {
		Sprite* sprite;
		SpriteData subData;
	};
	std::vector<SubSpriteData> m_subSpriteList;		//�ǉ���

};

