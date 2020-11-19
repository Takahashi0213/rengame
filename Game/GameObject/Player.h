#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "GameSystem/Mouse/MouseOver.h"
#include "GameSystem/Box/GameBox.h"

/// <summary>
/// �v���C���[
/// ��{�I�ɏ��ł��Ȃ�
/// </summary>
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
		enAnimationClip_Jump,		//�W�����v
		enAnimationClip_Damage,		//�_���[�W
		enAnimationClip_GameOver,	//�Q�[���I�[�o�[
		enAnimationClip_Clear,		//�N���A
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
	void SetPosition(const CVector3& pos);
	//�ړ����ݒ�
	void SetMoveTarget(const CVector3& pos) {
		m_nextPos = pos;
	}
	/// <summary>
	/// �ړ����x��Ԃ�
	/// </summary>
	CVector3 GetMoveSpeed() {
		return m_moveSpeed;
	}

	/// <summary>
	/// �v���C���[�̉�]��Ԃ�
	/// </summary>
	CQuaternion GetRotation() {
		return m_rotation;
	}
	void SetRotation(const CQuaternion& rot) {
		m_rotation = rot;
	}

	/// <summary>
	/// ��]�t���O��ݒ�
	/// </summary>
	void SetRotFlag(const bool& flag) {
		m_rotFlag = flag;
	}
	/// <summary>
	/// Clear�A�j���[�V�����̍Đ��E��~
	/// </summary>
	void SetClearAnimationFlag(const bool& flag) {
		m_clearAnimationFlag = flag;
	}
	/// <summary>
	/// �Q�[���I�[�o�[�ɂȂ�����Ă�
	/// </summary>
	void GemaOverFlag();

	/// <summary>
	/// �}�b�v�ړ����ɌĂ�
	/// </summary>
	void MapMove();

	/// <summary>
	/// �v���C���[���W�����v������
	/// </summary>
	void PlayerJump();
	/// <summary>
	/// �O������ł������グ�������Ă��锠�𓊂�����悤�ɂ���
	/// </summary>
	void PublicBoxCatchAndThrow();
	/// <summary>
	/// �O������ł������Ă��锠��u����悤�ɂ���
	/// </summary>
	void PublicBoxPut();
	/// <summary>
	/// �O������ł������Ă��锠��������悤�ɂ���
	/// </summary>
	void PublicBoxDelete();

	/// <summary>
	/// �������グ�̐��Ȃ�true��Ԃ�
	/// </summary>
	bool GetBoxSearchFlag() {
		if (m_upKouho_Box != nullptr) {
			return true;
		}
		return false;
	}
	/// <summary>
	/// �������グ�t���O��Ԃ�
	/// </summary>
	bool GetBoxUpFlag() {
		return m_boxUpFlag;
	}
	/// <summary>
	/// ���グ���낵�t���O��Ԃ�
	/// </summary>
	bool GetBoxUpDownFlag() {
		return m_boxMoveFlag;
	}

	/// <summary>
	/// �X�L�����f�������_�[��Ԃ�
	/// </summary>
	SkinModelRender* GetSkinModelRender() {
		return m_playerModel;
	}
	SkinModelRender* GetSkinModelRender_SL() {
		return m_playerModel_Sl;
	}

	/// <summary>
	/// �L�����R�����擾
	/// </summary>
	CharacterController* GetCharaCon() {
		return &m_charaCon;
	}

private:

	SkinModelRender* m_playerModel;						//�v���C���[�̃��f��
	SkinModelRender* m_playerModel_Sl;					//�v���C���[�̃��f���i�V���G�b�g�j
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[�B
	LightMaker* m_lightMaker;
	GameUI* m_ui = nullptr;
	ID3D11ShaderResourceView* m_specMapSRV = nullptr;	//�X�y�L�����}�b�v

	//�A�j���[�V����
	AnimationClip m_playerAnimationClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�B

	//���m�N���t���O
	bool m_monochromeFlag = false;

	//�A�j���[�V����
	void PlayerAnimation();
	//�s�� �ړ�
	void MoveClick();
	void Move();
	void MoveSE();		//�����Đ�
	void Jump();
	//�s�� ���֘A
	void BoxUp();
	void BoxCatch();
	void BoxPut();
	void BoxSearch();
	void BoxMove();
	void BoxDelete();
	CVector3 BoxThrowSearch();

	//�v���C���[
	CVector3 m_position = { 0.0f,50.0f,-1900.0f };		//�������W
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_nextPos = CVector3::Zero();				//�ړ���
	CVector3 m_posBackup = CVector3::Zero();			//���݈ʒu�o�b�N�A�b�v

	//�ړ�
	const float m_moveMax = 30.0f;			//�ő�ړ����x
	const float MoveHosei = 20.0f;			//�ړ��͂ւ̕␳�i�傫���قǒx���Ȃ�j
	Effekseer::Handle m_moveEffect = -1;	//�ړ��G�t�F�N�g
	bool m_rotFlag = true;					//��]����t���O

	//�L�����R��
	const float Radius = 25.0f;				//���a
	const float Height = 30.0f;				//����

	//�W�����v
	bool m_jumpNow = false;					//�W�����v�t���O
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
	float m_catmull_U = 0.0f;				//�x�W�F�Ȑ��p
	const float m_boxMove_Y_Hosei = 150.0f;		//�����グ��ۂ̍ō����B�_Y�␳
	const float m_boxMove_Y_Hosei_Put = 50.0f;	//�������낷�ۂ̍ō����B�_Y�␳
	const float m_boxPos_Y_Hosei = 150.0f;		//���������グ�Ă���Ƃ��̃v���C���[Y�␳
	const float m_boxPut_Hosei = 150.0f;		//����u���Ƃ��̈ړ���
	//������
	const float BoxThrowMaxLength = 500.0f;		//�������̃^�[�Q�b�g�ɂȂ�͈�
	const float BoxThrowEffect_Y_Hosei = 50.0f;	//�������G�t�F�N�g��Y�␳
	//�_���[�W
	const float m_damage_YHosei = 20.0f;		//�_���[�W���󂯂����ɔ�т������
	const float m_damage_knockback = -200.0f;	//�_���[�W���󂯂����̃m�b�N�o�b�N����
	bool m_damage_Flag = false;					//�_���[�W�Ŕ�яオ���Ă���Ԃ͕������Œ肷��
	bool m_damage_JumpFlag = false;				//�_���[�W�Ŕ�яオ���Ă���Ԃ͕������Œ肷��i�󒆗p�j
	//����
	const float StepVolume = 0.5f;				//�����̑傫��
	float m_stepSE_Timer = 0.0f;				//�����p�^�C�}�[
	const float StepSE_Limit = 1.0f;			//������������
	bool m_stepSE_LeftRight = false;			//�����ƉE��
	//�Q�[���I�[�o�[
	bool m_gameOverFlag = false;				//�Q�[���I�[�o�[�ɂȂ��Ă���I
	int m_gameOvetTimer = 0;					//�Q�[���I�[�o�[�^�C�}�[
	const int GameOverLimit = 20;				//�Q�[���I�[�o�[���~�b�g
	//�������A�j���[�V����
	bool m_clearAnimationFlag = false;			//�N���A�A�j���[�V�����t���O

};

