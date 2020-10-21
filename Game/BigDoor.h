#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

class BigDoor : public ObjectClass
{
public:
	BigDoor();
	~BigDoor();
	void Update()override;
	void Render()override;

	//���f���̎��
	enum BoxModel {
		Model_BigDoor,
		Model_BigDoor2,
		Model_BigDoorNum,
	};

	/// <summary>
	/// ���f���̎�ނ�ݒ�
	/// ���e�͓��������ǌ����ڂ��Ⴄ�h�A���������񂠂�̂�
	/// </summary>
	/// <param name="model">���f���̎��</param>
	void ModelChange(const BoxModel model);

private:
	SkinModelRender * m_model = nullptr;			//�y����Ł`�`��

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g

	//�萔
	const CVector3 StaticSize = { 250.0f,300.0f,20.0f };	//���̓����蔻��T�C�Y
	const float StaticY_Hosei = 100.0f;						//�����蔻�肪���܂�̂ŏ�ɕ␳����s

};

