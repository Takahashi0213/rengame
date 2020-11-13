#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// �����i�|�C���g���C�g�����[�v�G�t�F�N�g�j
/// �A�N�V�����t���O�ɉ����ď����̃I���I�t�ύX
/// </summary>
class Torch : public ObjectClass
{
public:
	Torch();
	~Torch();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �g�[�`��Ԃ̕ύX
	/// false�Ȃ�I�t�Atrue�Ȃ�I��
	/// </summary>
	/// <param name="flag"></param>
	void SetTorch(const bool& flag) {
		m_actionFlag = flag;
	}

	/// <summary>
	/// �G�t�F�N�g�␳��ݒ�
	/// </summary>
	void SetHosei(const CVector3& hosei) {
		m_hosei.Set(hosei);
	}

private:
	SkinModel m_model;										//���f��

	bool m_fireFlag = false;								//�g�[�`�ύX�p

	const float Y_Hosei = 50.0f;							//Y�␳
	CVector3 m_hosei = CVector3::Zero();					//�␳

	int m_pointLightNo = -1;								//�|�C���g���C�g�ԍ�
	Effekseer::Handle m_Effect = -1;						//���G�t�F�N�g

	const CVector3 PointLightColor = { 0.8f,0.2f,0.2f };	//�|�C���g���C�g�̐F
	const float PointLightRange = 400.0f;					//�|�C���g���C�g�̗L���͈�
	
};

