#pragma once

class ObjectClass : public IGameObject
{
public:
	//�I�u�W�F�N�g�̎��
	enum ObjectClass_Tag {
		NullObj,		//�_�~�[
		ItemObj,		//�A�C�e��
		GimmickObj,		//�M�~�b�N�n
		EnemyObj,		//�G�i���̂܂�܁j
		SystemObj,		//�Q�[���V�X�e���n�i�S�[�X�g�Ȃǁj
	};

	ObjectClass();
	~ObjectClass();

	//�C���X�^���X�擾
	ObjectClass* GetInstance() {
		return this;
	}

	//���W
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
	CVector3 GetPosition() {
		return m_position;
	}

	//��]
	void SetRotation(const CQuaternion& rot) {
		m_rotation = rot;
	}
	CQuaternion GetRotation() {
		return m_rotation;
	}

	//�g�嗦
	void SetScale(const CVector3& scl) {
		m_scale = scl;
	}
	CVector3 GetScale() {
		return m_scale;
	}

	//�ꉞ�p�u���b�N�̂܂܂Łc

	ObjectClass_Tag m_object = NullObj;			//���������҂�������

	SkinModelRender * m_modelRender = nullptr;	//�X�L�����f���B

	//�悭�����Q
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦

	bool m_monochromeFlag = false;		//�N���G�C�g���[�h���Ƀ��m�N���ɂ���t���O

	//�����t���O
	//�Ȃ񂩃A�N�V�������������Ƃ��p
	bool m_actionFlag = false;

};