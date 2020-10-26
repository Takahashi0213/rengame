#pragma once

#include "graphics/Skeleton.h"

#include "graphics/light/DirectionLight.h"
#include "graphics/light/PointLight.h"

/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
enum RenderMode {
	Default = 0,		//����
	Silhouette = 1,		//�V���G�b�g
	Monochrome = 2,		//���m�N��
	Box = 3,			//���ł��B	
	Kirameki = 4,		//��΂̋P��
};
/*!
*@brief	�X�L�����f���N���X�B
*/
class SkinModel
{
public:
	//���b�V�������������Ƃ��̃R�[���o�b�N�֐��B
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~SkinModel();
	
	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	position	���f���̍��W�B
	*@param[in]	rotation	���f���̉�]�B
	*@param[in]	scale		���f���̊g�嗦�B
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	�{�[���������B
	*@param[in]		boneName	�{�[���̖��O�B
	*@return	���������{�[���B������Ȃ������ꍇ��nullptr��Ԃ��܂��B
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	���f����`��B
	*@param[in]	viewMatrix		�J�����s��B
	*  ���[���h���W�n��3D���f�����J�������W�n�ɕϊ�����s��ł��B
	*@param[in]	projMatrix		�v���W�F�N�V�����s��B
	*  �J�������W�n��3D���f�����X�N���[�����W�n�ɕϊ�����s��ł��B
	*/
	void Draw(CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode renderMode = enRenderMode_Normal);
	/*!
	*@brief	�X�P���g���̎擾�B
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	���b�V������������B
	*@param[in] onFindMesh		���b�V�������������Ƃ��̃R�[���o�b�N�֐�
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/// <summary>
	/// ���Ȕ����F��ݒ�
	/// </summary>
	/// <param name="color">���Ȕ����F</param>
	void SetEmissionColor(const CVector3& color)
	{
		m_emissionColor = color;
	}
	/// <summary>
	/// ���Ȕ����F���擾
	/// </summary>
	/// <returns>���Ȕ����F</returns>
	CVector3 GetEmissionColor() {
		return m_emissionColor;
	}
	/*!
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};

	/// <summary>
	/// �����_�[���[�h��ύX
	/// </summary>
	/// <param name="mode">���[�h</param>
	void SetRenderMode(const int& mode) {
		m_renderMode = mode;
	}

	/// <summary>
	/// �V���h�E���V�[�o�[�̃t���O��ݒ肷��B
	/// </summary>
	/// <param name="flag">true��n���ƃV���h�E���V�[�o�[�ɂȂ�</param>
	/// <remarks>
	/// �V���h�E���V�[�o�[�Ƃ͉e�𗎂Ƃ����I�u�W�F�N�g�̂��Ƃł��B
	/// �V���h�E�L���X�^�[�ɂ���Đ������ꂽ�A�V���h�E�}�b�v�𗘗p����
	/// ���g�ɉe�𗎂Ƃ��܂��B
	/// �I�u�W�F�N�g���V���h�E���V�[�o�[���V���h�E�L���X�^�[�ɂȂ��Ă���ꍇ��
	/// �Z���t�V���h�E(�����̉e�������ɗ�����)���s�����Ƃ��ł��܂��B
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}
	/// <summary>
	/// World�s����擾�B
	/// </summary>
	/// <returns></returns>
	CMatrix GetWorldMatrix() const
	{
		return m_worldMatrix;
	}

	/// <summary>
	/// �@���}�b�v�̐ݒ�B
	/// </summary>
	void SetNormalMap(ID3D11ShaderResourceView* srv)
	{
		m_normalMapSRV = srv;
	}
	/// <summary>
	/// �X�y�L�����}�b�v�̐ݒ�B
	/// </summary>
	void SetSpecMap(ID3D11ShaderResourceView* srv)
	{
		m_specMapSRV = srv;
	}
	/// <summary>
	/// �A���r�G���g�I�N�����[�W�����}�b�v�̐ݒ�B
	/// </summary>
	void SetAOMap(ID3D11ShaderResourceView* srv)
	{
		m_aoMapSRV = srv;
	}
	/// <summary>
	/// ����߂��e�N�X�`���̐ݒ�
	/// </summary>
	void SetKirameki(ID3D11ShaderResourceView* srv) {
		m_kiramekiTextureSRV = srv;
	}

private:
	/*!
	*@brief	�T���v���X�e�[�g�̏������B
	*/
	void InitSamplerState();
	/*!
	*@brief	�萔�o�b�t�@�̍쐬�B
	*/
	void InitConstantBuffer();
	/*!
	*@brief	�X�P���g���̏������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*/
	void InitSkeleton(const wchar_t* filePath);
	
	//�f�B���N�V�������C�g���Z�b�g
	void D_LightUpdate();
	//�f�B���N�V�������C�g���Z�b�g
	void P_LightUpdate();

private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		//todo ���C�g�r���[�s��B
		CMatrix mLightProj;		//todo ���C�g�v���W�F�N�V�����s��B
		int isShadowReciever;	//todo �V���h�E���V�[�o�[�̃t���O�B
		int isHasNormalMap;		//�@���}�b�v��ێ����Ă���H
		int isHasSpecMap;		//�X�y�L�����}�b�v��ێ����Ă���H
		int isHasAOMap;			//AO�}�b�v��ێ����Ă���H
		int isHasKirameki;		//����߂���ێ����Ă���H
		float mHigh;
		float mWide;			//��ʂ̏c��
		float emissionColor_R;
		float emissionColor_G;
		float emissionColor_B;
	};

	//�����̒萔�o�b�t�@
	struct AmbientLight {
		float Ambient_R;
		float Ambient_G;
		float Ambient_B;
	};

	/*!
	*@brief	���C�g�\���́B
	*/
	struct SLight {
		SDirectionLight		directionLight;		//�f�B���N�V�������C�g
		SPointLight			pointLight;			//�|�C���g���C�g
		CVector4			eyePos;				//���_�̍��W�B
		float				specPow;			//���ʔ��˂̍i��B
	};

	/// <summary>
	/// �����̏�����
	/// </summary>
	void LoadAmbientLight();

	/// <summary>
	/// 16�̔{���ɐ؂�グ�鏈��
	/// </summary>
	/// <param name="n">�؂�グ��������</param>
	/// <returns>16�̔{���ɐ؂�グ���l</returns>
	int Raundup16(int n)
	{
		return (((n - 1) / 16) + 1) * 16;
	}

	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBX�̏�����B
	ID3D11Buffer*		m_cb = nullptr;					//!<�萔�o�b�t�@�B
	ID3D11Buffer*		m_lightCb = nullptr;			//!<���C�g�p�̒萔�o�b�t�@�B
	ID3D11Buffer*		m_ambientlightCb = nullptr;		//!<���C�g�p�̒萔�o�b�t�@�B
	AmbientLight		m_AmbientLight;					//!<���C�g�\���́B
	SLight				m_light;						//!<���C�g�\���́B
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
	CVector3 m_emissionColor = CVector3().Zero();		//!<���Ȕ����J���[�B
	ID3D11ShaderResourceView* m_albedoTextureSRV = nullptr;	//!<�A���x�h�e�N�X�`����SRV
	int					m_renderMode = 0;				//!<�����_�[���[�h
	bool m_isShadowReciever = false;						//�V���h�E���V�[�o�[�̃t���O�B

	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;		//�@���}�b�v��SRV
	ID3D11ShaderResourceView* m_specMapSRV = nullptr;		//�X�y�L�����}�b�v��SRV
	ID3D11ShaderResourceView* m_aoMapSRV = nullptr;			//AO�}�b�v��SRV
	ID3D11ShaderResourceView* m_kiramekiTextureSRV = nullptr;//����߂��e�N�X�`����SRV

};

