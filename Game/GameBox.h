#pragma once
#include "character/CharacterController.h"
#include "Physics/MeshCollider.h"
#include "physics/PhysicsStaticObject.h"

class GameBox
{
public:
	enum BoxTag {
		Origin,			//�ŏ��ɍ������
		Another,		//���̑��̔�
	};

	typedef std::vector<CVector3>					VertexBuffer;		//���_�o�b�t�@�B
	typedef std::vector<unsigned int>				IndexBuffer;		//�C���f�b�N�X�o�b�t�@�B
	GameBox();
	~GameBox();
	void GameBox_Update();
	void GameBox_Render();

	/// <summary>
	/// ������Ԃ��Z�b�g
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void GameBox_Set(CVector3 pos, CQuaternion rot = CQuaternion::Identity()) {
		m_position = pos;
		m_rotation = rot;
	}

	bool CheckHitRayToPlane(CVector3 startPos, CVector3 endPos,CVector3* boxPos,CVector3& box_N, CVector3& plane_scale);
	
	CVector3 GetPosition() {
		return m_position;
	}

	/// <summary>
	/// �F�ݒ�
	/// </summary>
	void SetColor(CVector3 color) {
		m_model.SetEmissionColor(color);
	}
	CVector3 GetColor() {
		return m_model.GetEmissionColor();
	}
	void SetAllColor(CVector3 color);

	//�ړ��ʊ֘A
	CVector3 GetMoveSpeed() {
		return m_moveSpeed;
	}
	void SetMoveSpeed(CVector3 speed) {
		m_moveSpeed = speed;
	}

	/// <summary>
	/// �q�̃{�b�N�X���X�g��ǉ�����
	/// </summary>
	/// <param name="box">�ǉ����锠�̃A�h���X</param>
	void SetBox(GameBox* box) {
		m_boxList.push_back(box);
	}

	/// <summary>
	/// �q�̃{�b�N�X���X�g���폜����
	/// </summary>
	void SetBox_Delete() {
		m_boxList.pop_back();
	}

	/// <summary>
	/// ���̃^�O��ύX����
	/// </summary>
	/// <param name="box_tag">����</param>
	void SetBoxTag(BoxTag box_tag) {
		m_boxTag = box_tag;
	}

	/// <summary>
	/// ���̃^�O���擾����
	/// </summary>
	/// <returns>�^�O�ł�</returns>
	BoxTag GetBoxTag() {
		return m_boxTag;
	}

	/// <summary>
	/// ���̊g�嗦��ύX����
	/// </summary>
	/// <param name="scl">�g�嗦�I</param>
	void SetScale(CVector3 scl) {
		m_scale = scl;
	}

	/// <summary>
	/// ���̊g�嗦��Ԃ�
	/// </summary>
	/// <returns>�g�嗦�I�I�I�I�I�I</returns>
	CVector3 GetScale() {
		return m_scale;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(CQuaternion rot) {
		m_rotation = rot;
	}
	/// <summary>
	/// ��]���擾
	/// </summary>
	/// <returns>��]</returns>
	CQuaternion GetRotation() {
		return m_rotation;
	}

	void GameBoxUpdate_Colli();

	/// <summary>
	/// ���̃��[�J�����W�I
	/// </summary>
	void SetLocalPos(CVector3 pos) {
		m_localPosition = pos;
	}
	CVector3 GetLocalPos() {
		return m_localPosition;
	}

	/// <summary>
	/// ���㔠��ݒ�
	/// </summary>
	void SetOriginBox(GameBox* box) {
		m_originBox = box;
	}
	GameBox* GetOriginBox() {
		return m_originBox;
	}

	/// <summary>
	/// �R���C�_�[�̐ݒ�t���O��Ԃ�
	/// </summary>
	bool GetColli_InitFlag() {
		return m_colli_InitFlag;
	}

	/// <summary>
	/// ���̂�Ԃ�
	/// </summary>
	RigidBody* GetRigidBody() {
		return m_physicsStaticObject.GetRigidBody();
	}

	/// <summary>
	/// �������Ƃ��̍��W�␳�ʂ��v�Z����ZO
	/// </summary>
	CVector3 GetAnotherHosei();
	/// <summary>
	/// �������Ƃ��͈͕̔␳�ʂ��v�Z����ZE 
	/// </summary>
	float GetAnotherRangeHosei();

private:
	void GetTrianglePositionAndNormal(
		int polyNo,
		IndexBuffer& indexBuffer,
		VertexBuffer& vertexBuffer,
		CMatrix& mWorld,
		CMatrix& mRot,
		CVector3& vPos_0,
		CVector3& vPos_1,
		CVector3& vPos_2,
		CVector3& N);
	/// <summary>
	/// �x�N�g���̔�r�p
	/// </summary>
	/// <param name="a">��r�������x�N�g���P</param>
	/// <param name="b">��r�������x�N�g���Q</param>
	/// <returns>false�Ȃ犮�S��v�Atrue�Ȃ�ǂ���1�v�f�Ⴄ</returns>
	bool VectorHikaku(CVector3 a, CVector3 b) {
		bool Flag = false;
		if (fabsf(a.x - b.x) > 0.02f) {
			Flag = true;
		}
		if (fabsf(a.y - b.y) > 0.02f) {
			Flag = true;
		}	
		if (fabsf(a.z - b.z) > 0.02f) {
			Flag = true; 
		}
		return Flag;
	}

	void MeshStandBy();
	SkinModel m_model;	//�X�L�����f���B

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
	CMatrix  m_World;
	
	LightMaker* m_lightMaker;

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦
	CVector3 m_moveSpeed = CVector3().Zero();

	//�e�̔��Ƃ̃��[�J�����W
	GameBox* m_originBox = nullptr;		//���㔠�l�I�I�I�I
	CVector3 m_localPosition = CVector3().Zero();	//�e�Ƃ̑��΍��W
	BoxTag m_boxTag = Another;

	//Vector
	std::vector<VertexBuffer>						m_vertexBufferArray;		//���_�o�b�t�@�̔z��B
	std::vector<IndexBuffer>						m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��B

	//�����Ȍv�Z
	CVector3 m_N;
	CVector3 m_vPos_0;
	CVector3 m_vPos_1;
	CVector3 m_vPos_2;

	bool m_colli_InitFlag = false;

	//�q�ɂȂ�{�b�N�X�ǂ��iOrizinBox�����ύX�����j
	std::vector<GameBox*> m_boxList;

	//�萔
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };
	const float m_gravity = 0.6f;		//�d���ߩܧ
	const float Scale = 50.0f;		//�␳�v�Z�p
	const float Y_Hosei = 60.0f;	//�����␳

};

