#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "GameSystem/Mouse/MouseOver.h"
#include "GameBox.h"

class Player final: public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	void Render()override;

	enum EnAnimationClip {
		enAnimationClip_Idle,		//�ҋ@
		enAnimationClip_Run,		//����
		enAnimationClip_Num,		//�A�j���[�V�����N���b�v
	};

	/// <summary>
	/// �v���C���[���G����_���[�W���󂯂���Ăт܂��傤�I
	/// </summary>
	void PlayerMiss(const CVector3& pos);

	/// <summary>
	/// �v���C���[�̃|�W�V������Ԃ�
	/// </summary>
	CVector3 GetPosition() {
		return m_position;
	}
	const CVector3& GetPositionBackup() {
		return m_posBackup;
	}
	//�v���C���[�̍��W��ݒ�
	void SetPosition(const CVector3& pos) {
		m_moveSpeed = CVector3::Zero();
		m_nextPos = CVector3::Zero();
		m_position = pos;
		m_charaCon.SetPosition(pos);
	}

	/// <summary>
	/// �v���C���[�̉�]��Ԃ�
	/// </summary>
	CQuaternion GetRotation() {
		return m_rotation;
	}

	/// <summary>
	/// �L�����R�����擾
	/// </summary>
	CharacterController* GetCharaCon() {
		return &m_charaCon;
	}

private:

	//�펞�Ă΂��
	void BoxUp();

	SkinModel m_model;					//�X�L�����f���B
	SkinModel m_model_Sl;				//�X�L�����f���i�V���G�b�g�j
	CharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	Game* m_gameObj;
	LightMaker* m_lightMaker;
	//MouseOver ms;

	//�A�j���[�V����
	Animation m_playerAnimation;								//�A�j���[�V�����B
	Animation m_playerAnimationSL;								//�A�j���[�V�����B
	AnimationClip m_playerAnimationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�B

	//���m�N���t���O
	bool m_monochromeFlag = false;

	//�s��
	void Move();
	void Jump();
	//�s�� ���֘A
	void BoxCatch();
	void BoxSearch();
	void BoxMove();
	void BoxDelete();
	CVector3 BoxThrowSearch();

	//�v���C���[
	CVector3 m_position = { 0.0f,50.0f,-800.0f };
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_nextPos = CVector3::Zero();
	CVector3 m_posBackup = CVector3::Zero();

	//�ړ�
	const float m_moveMax = 30.0f;

	//�L�����R��
	const float Radius = 25.0f;		//���a
	const float Height = 30.0f;		//����

	//�W�����v
	bool m_jumpNow = false;
	const float m_jumpPower = 26.0f;		//�W�����v�ߩܧ
	const float m_gravity = 2.0f;			//�d���ߩܧ

	//�������グ
	GameBox* m_upBox = nullptr;				//�����グ�Ă��锠
	GameBox* m_upKouho_Box = nullptr;		//�����グ���̔�
	bool m_boxUpFlag = false;				//�������グ���H
	bool m_boxMoveFlag = false;				//���グ���낵���쒆�H�i���쒆�͓����܂���j
	bool m_upOrDown = false;				//�����グ�Ă���Ȃ�false�A�����Ă���Ȃ�true
	bool m_boxButtonFlag = false;			//���̃{�^��
	bool m_boxDeleteButtonFlag = false;		//���̃{�^��
	const float m_boxPutHosei = 4.0f;		//����u���������邩�̊�␳�i�傫������ƒu���₷���Ȃ�j
	const float m_boxUpRange = 200.0f;		//���������グ����͈�
	const float m_boxUp_Y_Max = 50.0f;		//���������グ���鍂���͈̔�
	const float m_boxUp_Angle = 90.0f;		//���������グ�鎋��p�͈�
	//�グ�����ړ��icatmull�j�i���������ǃx�W�F�Ȑ��ɕύX�j
	CVector3 m_point_1 = CVector3::Zero();	//�I�_���
	CVector3 m_point_2 = CVector3::Zero();	//�n�_
	CVector3 m_point_3 = CVector3::Zero();	//�I�_
	CVector3 m_point_4 = CVector3::Zero();	//�n�_���
	float m_catmull_U = 0.0f;
	const float m_boxMove_Y_Hosei = 150.0f;		//�����グ��ۂ̍ō����B�_Y�␳
	const float m_boxMove_Y_Hosei_Put = 50.0f;	//�������낷�ۂ̍ō����B�_Y�␳
	const float m_boxPos_Y_Hosei = 150.0f;		//���������グ�Ă���Ƃ��̃v���C���[Y�␳
	const float m_boxPut_Hosei = 150.0f;		//����u���Ƃ��̈ړ���
	//������
	const float BoxThrowMaxLength = 500.0f;		//�������̃^�[�Q�b�g�ɂȂ�͈�
	//�_���[�W
	const float m_damage_YHosei = 20.0f;		//�_���[�W���󂯂����ɔ�т������
	const float m_damage_knockback = -200.0f;	//�_���[�W���󂯂����̃m�b�N�o�b�N����
	bool m_damage_Flag = false;					//�_���[�W�Ŕ�яオ���Ă���Ԃ͕������Œ肷��
	bool m_damage_JumpFlag = false;				//�_���[�W�Ŕ�яオ���Ă���Ԃ͕������Œ肷��i�󒆗p�j

};
