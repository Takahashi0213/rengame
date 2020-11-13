#pragma once
#include "physics/PhysicsStaticObject.h"
#include "system/CGameObjectManager.h"

/// <summary>
/// �w�i�i�X�e�[�W�j
/// ��̃X�v���C�g���ۗL
/// </summary>
class BackGround : public ObjectClass
{
public:
	BackGround();
	~BackGround();
	void Update()override;
	void Render()override;

	//�X�e�[�W�̐ݒ�
	void Init(const wchar_t* filePath);
	//�V���h�E�L���X�^�[�t���O�̐ݒ�
	void SetShadowCasterFlag(const bool& flag) {
		m_shadowCasterFlag = flag;
	}

private:
	bool m_initFlag = false;

	SkinModel m_model;	//�X�L�����f���B
	SpriteRender* m_sprite = nullptr;
	bool m_monochromeFlag = false;
	LightMaker* m_lightMaker;

	PhysicsStaticObject m_physicsStaticObject;				//�ÓI�����I�u�W�F�N�g�B

	CVector3 m_position = { 0.0f,0.0f,0.0f };
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 10.0f,10.0f,10.0f };				//�g�嗦

	bool m_shadowCasterFlag = false;						//�V���h�E�L���X�^�[�ɂ���
};

