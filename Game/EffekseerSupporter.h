#pragma once
//Effekseer�̃w�b�_�[�t�@�C��
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

/// <summary>
/// �G�t�F�N�g�ȒP�\��
/// �E�V���O���g��
/// </summary>
class EffekseerSupporter
{
	static EffekseerSupporter* m_instance;
public:
	//�G�t�F�N�g�̎��
	enum EffectData {
		TestData,
		Null,
	};

	//

	struct Effect {	//�G�t�F�N�g�f�[�^
		int Handle;
		bool PostFlag;
	};
	std::list<Effect>* g_effectList_P = &m_effectList;

	//

	EffekseerSupporter();
	~EffekseerSupporter();
	
	/// <summary>
	/// �G�t�F�N�g�̐���
	/// </summary>
	Effekseer::Handle NewEffect(const wchar_t* EffectFileName, 
		bool PostFlag = false,
		Effekseer::Vector3D DefPos = { 0.0f,0.0f,0.0f });
	Effekseer::Handle NewEffect(const EffectData EffectFileName,
		bool PostFlag = false,
		Effekseer::Vector3D DefPos = { 0.0f,0.0f,0.0f });
	Effekseer::Handle NewEffect_Vector(const EffectData EffectFileName,
		bool PostFlag = false,float X = 0.0f, float Y = 0.0f, float Z = 0.0f);

	/// <summary>
	/// ��������G�t�F�N�g����
	/// </summary>
	
	/// <summary>
	/// ��ɕ`�悳���G�t�F�N�g�̃X�g�b�v���ĊJ
	/// </summary>
	void NoPostStop();
	void NoPostMove();

	/// <summary>
	/// �G�t�F�N�g�f�[�^�̍폜�i���t���[���Ă�łˁj
	/// </summary>
	void EffectClear();

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static EffekseerSupporter* EffekseerSupporter::GetInstance() {
		return m_instance;
	}

private:

	//�G�t�F�N�g�t�@�C����
	const wchar_t EffectDetaBase[2][30]{
	{ L"Assets/effect/test.efk" },
	{ L"Assets/effect/test.efk" },
	};

	std::list<Effect> m_effectList;		//�G�t�F�N�g���X�g

};

