#pragma once
#include "character/CharacterController.h"
#include "Physics/MeshCollider.h"
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// �v���C���[���������锠
/// </summary>
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
	bool DeathBox();					//���x�����ȉ��ɂȂ����玩��

	/// <summary>
	/// ������Ԃ��Z�b�g
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void GameBox_Set(const CVector3& pos, const CQuaternion& rot = CQuaternion::Identity()) {
		m_position = pos;
		m_rotation = rot;
	}

	//���C���������Ă邩���`�F�b�N
	bool CheckHitRayToPlane(const CVector3& startPos, const CVector3& endPos,
		CVector3* boxPos,CVector3& box_N, CVector3& plane_scale);
	
	//���W��Ԃ�
	const CVector3& GetPosition() const {
		return m_position;
	}

	/// <summary>
	/// �F�擾���폜
	/// </summary>
	void SetColor(const CVector3& color) {
		m_model.SetEmissionColor(color);
	}
	CVector3 GetColor() {
		return m_model.GetEmissionColor();
	}
	//�i�q���܂߁j�܂Ƃ߂Ē��F
	void SetAllColor(const CVector3& color);

	//�ړ��ʎ擾���폜
	CVector3 GetMoveSpeed() {
		return m_moveSpeed;
	}
	void SetMoveSpeed(const CVector3& speed) {
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
	/// �q�̃{�b�N�X���X�g��Ԃ�
	/// </summary>
	/// <returns></returns>
	std::vector<GameBox*> GetBoxList() {
		return m_boxList;
	}

	/// <summary>
	/// ���̃^�O��ύX���擾
	/// </summary>
	void SetBoxTag(const BoxTag box_tag) {
		m_boxTag = box_tag;
	}
	BoxTag GetBoxTag() {
		return m_boxTag;
	}

	/// <summary>
	/// ���̊g�嗦 �ݒ聕�擾
	/// </summary>
	void SetScale(const CVector3& scl) {
		m_scale = scl;
	}
	CVector3 GetScale() {
		return m_scale;
	}

	/// <summary>
	/// ��]��ݒ聕�擾
	/// </summary>
	void SetRotation(const CQuaternion& rot) {
		m_rotation = rot;
	}
	CQuaternion GetRotation() {
		return m_rotation;
	}

	/// <summary>
	/// �}�i�p���[�̐ݒ�Ǝ擾�i���̍폜�Ɏg���܂��j
	/// </summary>
	void SetManaPower(const int& mana) {
		m_manaPower = mana;
	}
	int GetManaPower() {
		return m_manaPower;
	}

	/// <summary>
	/// ��������������R���C�_�[��ݒ肵��
	/// ����ȍ~���W�ɉ����ăR���C�_�[���ړ�������
	/// �R���C�_�[��p�A�b�v�f�[�g
	/// </summary>
	void GameBoxUpdate_Colli();

	/// <summary>
	/// ���̃��[�J�����W�I
	/// </summary>
	void SetLocalPos(const CVector3& pos) {
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
	/// �Ă΂ꂽ��q������S�č폜
	/// </summary>
	void DeleteBox();

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
	const float DeathHeight = -200.0f;	//���ł���Œፂ�x

	SkinModel m_model;	//�X�L�����f���B

	PhysicsStaticObject m_physicsStaticObject;		//�ÓI�����I�u�W�F�N�g
	CMatrix  m_World;
	
	LightMaker* m_lightMaker;		//���C�g���[�J�[�i�e�𗎂Ƃ��Ȃ�K�v�j

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One();				//�g�嗦
	CVector3 m_moveSpeed = CVector3().Zero();

	//�e�̔��Ƃ̃��[�J�����W
	GameBox* m_originBox = nullptr;					//���㔠�l�I�I�I�I�i��ɂȂ�j
	CVector3 m_localPosition = CVector3().Zero();	//�e�Ƃ̑��΍��W
	BoxTag m_boxTag = Another;						//���̃^�O

	//Vector
	std::vector<VertexBuffer>						m_vertexBufferArray;	//���_�o�b�t�@�̔z��B
	std::vector<IndexBuffer>						m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��B

	//�����Ȍv�Z�p
	CVector3 m_N;
	CVector3 m_vPos_0;
	CVector3 m_vPos_1;
	CVector3 m_vPos_2;

	bool m_colli_InitFlag = false;		//�R���C�_�[�ݒ肵���H�H

	//�q�ɂȂ�{�b�N�X�ǂ��iOrizinBox�����ύX�����AAnother�͕s�v�j
	std::vector<GameBox*> m_boxList;
	//�}�i�p���[�����i�������Orizin��p�j
	int m_manaPower = 0;

	//�萔
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };		//���̏����X�P�[��
	const float m_gravity = 0.6f;		//�d���ߩܧ
	const float Scale = 50.0f;			//�␳�v�Z�p
	const float Y_Hosei = 60.0f;		//�����␳

};
