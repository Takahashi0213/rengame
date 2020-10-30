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
		TestData,			//�e�X�g�f�[�^
		EnemyDeath,			//�G���|���
		PlayerMove,			//�v���C���[�̈ړ���
		EnemyScope,			//�����΂���i�G�j
		EffectNum,
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
	/// PostFlag��true�ɂ����2D��Ԃɕ`�悳���
	/// </summary>
	Effekseer::Handle NewEffect(const wchar_t* EffectFileName, 
		const bool& PostFlag = false,
		const Effekseer::Vector3D& DefPos = { 0.0f,0.0f,0.0f });
	Effekseer::Handle NewEffect(const EffectData EffectFileName,
		const bool& PostFlag = false,
		const Effekseer::Vector3D& DefPos = { 0.0f,0.0f,0.0f });
	Effekseer::Handle NewEffect_Vector(const EffectData EffectFileName,
		const bool& PostFlag = false, const float& X = 0.0f, const float& Y = 0.0f, const float& Z = 0.0f,
		const float& rotX=0.0f, const float& rotY = 0.0f, const float& rotZ = 0.0f);

	/// <summary>
	/// ��������G�t�F�N�g����
	/// </summary>
	
	/// <summary>
	/// ��ɕ`�悳���G�t�F�N�g�̃X�g�b�v���ĊJ
	/// </summary>
	void NoPostStop(const bool& flag);

	/// <summary>
	/// �G�t�F�N�g�̋����폜
	/// </summary>
	/// <param name="effect">�폜����G�t�F�N�g�̃n���h��</param>
	void EffectDelete(const Effekseer::Handle& effect);

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
	const wchar_t EffectDetaBase[EffectNum][MAX_PATH]{
	{ L"Assets/effect/test.efk" },
	{ L"Assets/effect/EnemyDeath.efk" },
	{ L"Assets/effect/PlayerMove.efk" },
	{ L"Assets/effect/EnemyScope.efk" },
	};

	std::list<Effect> m_effectList;		//�G�t�F�N�g���X�g

};

