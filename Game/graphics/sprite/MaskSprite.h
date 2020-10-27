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
	void SetPosition(const CVector3& pos, const int& list = -1)
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
	const CVector3 GetPosition(const int& list = -1) const
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
	void SetRotation(const CQuaternion& rot, const int& list = -1)
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
	const CQuaternion GetRotation(const int& list = -1) const
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
	void SetScale(const CVector3& scl, const int& list = -1)
	{
		if (list == -1) {
			m_mainSpriteData.Scale = scl;
		}
		else {
			m_subSpriteList[list].subData.Scale = scl;		//�T�u
		}
	}
	void SetScale(const float& scl, const int& list = -1) { //�֗�Ver
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
	const CVector3 GetScale(const int& list = -1) const
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
	void SetPivot(const CVector2& pivot, const int& list = -1)
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
	CVector2 GetPivot(const int& list = -1)
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
	void SetSize(const CVector2& size, const int& list = -1) {
		
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
	void SetMulColor(const CVector4& mulColor, const int& list = -1)
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
	CVector4 GetMulColor(const int& list = -1)
	{
		if (list == -1) {
			return m_mainSpriteData.MulColor;
		}
		else {
			return m_subSpriteList[list].subData.MulColor;
		}
	}
	
	/// <summary>
	/// �����_�[���[�h�̕ύX
	/// </summary>
	void ChangeRenderMode(const Sprite_RenderMode srm, const int& list) {
		if (list >= 0) {
			m_subSpriteList[list].sprite->m_renderMode = srm;
		}
		else {
			std::abort(); //�ُ�Ȓl�ł��I�I�I
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
