#pragma once
#include "RenderTarget.h"
#include "graphics/skinModel/SkinModel.h"

//�E�V���O���g��
class ShadowMap
{
	static ShadowMap* m_instance;
public:
	ShadowMap();
	~ShadowMap();
	void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	void RenderToShadowMap();
	void RegistShadowCaster(SkinModel* AddModel);

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static ShadowMap* ShadowMap::GetInstance() {

		if (m_instance == nullptr) { //�I�u�W�F�N�g������Ă��Ȃ���΍��
			m_instance = new ShadowMap;
		}
		return m_instance;
	}

	/// <summary>
	/// ���C�g�r���[�s����擾�B
	/// </summary>
	/// <returns></returns>
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}

	/// <summary>
	/// ���C�g�v���W�F�N�V�����s����擾�B
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}

	/// <summary>
	/// �V���h�E�}�b�v��SRV���擾�B
	/// </summary>
	/// <returns>�V���h�E�}�b�v��SRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}

private:
	CMatrix m_lightViewMatrix;					//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix;					//���C�g�v���W�F�N�V�����s��B
	RenderTarget m_shadowMapRT;					//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B

	std::vector<SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B

};

