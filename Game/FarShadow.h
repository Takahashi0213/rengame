#pragma once
class PostEffect;

/// <summary>
/// 
/// </summary>
class FarShadow
{
public:
	~FarShadow();
	/// <summary>
	/// �������B
	/// </summary>
	void Init();
	/// <summary>
	/// �`��B
	/// </summary>
	/// <param name="postEffect"></param>
	void Draw(PostEffect& postEffect);
private:
	ID3D11BlendState * m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B

	Shader m_vs;				//���_�V�F�[�_�[�B
	Shader m_ps;				//�s�N�Z���V�F�[�_�[�B

};

