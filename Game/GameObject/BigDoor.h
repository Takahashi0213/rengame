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
	enum DoorModel {
		Model_BigDoor,
		Model_BigDoor2,
		Model_BigDoorNum,
	};

	/// <summary>
	/// ���f���̎�ނ�ݒ�
	/// ���e�͓��������ǌ����ڂ��Ⴄ�h�A���������񂠂�̂�
	/// </summary>
	/// <param name="model">���f���̎��</param>
	void ModelChange(const DoorModel model);

	/// <summary>
	/// ���̃A�C�e���ԍ���ݒ�
	/// </summary>
	void SetItemNo(const int& no) {
		m_itemNo = no;
	}

private:
	void DoorOpen();

	SkinModelRender * m_model = nullptr;			//�y�䃂�f��

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
	DoorModel m_thisModel;							//���f���̎��
	Player* m_pl = nullptr;							//�v���C���[

	int m_itemNo = -1;								//�Ή��A�C�e���ԍ�
	bool m_doorOpenFlag = false;					//�h�A�J���t���O

	//DoorModel�ɑΉ��������f���̎��
	const wchar_t* ModelNames[Model_BigDoorNum] = {
		L"Assets/modelData/BigDoor.cmo",
		L"Assets/modelData/BigDoor_.cmo"
	};

	//�萔
	const CVector3 StaticSize = { 250.0f,300.0f,20.0f };	//���̓����蔻��T�C�Y
	const float StaticY_Hosei = 100.0f;						//�����蔻�肪���܂�̂ŏ�ɕ␳����
	const float OpenRange = 700.0f;							//�擾�ł���͈�

};

