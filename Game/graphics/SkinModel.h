#pragma once

#include "Skeleton.h"
#include "DirectionLight.h"

/*!
*@brief	FBX�̏�����B
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
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
	void Draw( CMatrix viewMatrix, CMatrix projMatrix );
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
	void SetEmissionColor(CVector3 color)
	{
		//m_emissionColor = color;
	}
	/*!
	*@brief	SRV�̃��W�X�^�ԍ��B
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<�f�B�t���[�Y�e�N�X�`���B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
	};
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

private:
	//�萔�o�b�t�@�B
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		//CVector3 emissionColor;
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
		CVector3			eyePos;				//���_�̍��W�B
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
	ID3D11Buffer*		m_lightCb2 = nullptr;			//!<���C�g�p�̒萔�o�b�t�@2�B
	ID3D11Buffer*		m_ambientlightCb = nullptr;		//!<���C�g�p�̒萔�o�b�t�@�B
	AmbientLight		m_AmbientLight;					//!<���C�g�\���́B
	SLight				m_light;						//!<���C�g�\���́B
	Skeleton			m_skeleton;						//!<�X�P���g���B
	CMatrix				m_worldMatrix;					//!<���[���h�s��B
	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B
	ID3D11SamplerState* m_samplerState = nullptr;		//!<�T���v���X�e�[�g�B
	CVector3 m_emissionColor = CVector3().Zero();		//!<���Ȕ����J���[�B
	ID3D11ShaderResourceView* m_albedoTextureSRV = nullptr;	//!<�A���x�h�e�N�X�`����SRV
};
