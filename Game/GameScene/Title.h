#pragma once
#include "system/CGameObjectManager.h"

/// <summary>
/// ���S�ɓ�����X�v���C�g����������̂ł܂Ƃ߂邱�Ƃɂ��܂���
/// </summary>
class TitleRogo {
public:

	//���S�i�p�[�c�����j
	std::map<std::string, SpriteRender*> TitleRogo_Circle;
	std::map<std::string, SpriteRender*> TitleRogo_Mozi;

	SpriteRender* m_titleRogo_Mozi_Hakobun;					//�E��~�j�����uHAKOBUN�v

	//���S�֘A�̒萔 �`���
	const CVector2 RogoSpriteSize = { 1000.0f,400.0f };		//���S�摜�̑傫��
	const CVector3 RogoDefPos = { 0.0f,0.0f,0.0f };			//���S�̊
	const int RogoCirclePriority = 9;						//�T�C�N���̗D��x
	const int RogoMoziPriority = 4;							//�����̗D��x�i�~�j�����܂ށj
	//���o�� �T�C�N��
	const int RogoCircleDelay = 2;							//�T�C�N�����Ƃ̃f�B���C
	const float RogoCircleMaxScale = 1.2f;					//�T�C�N���̍ő�T�C�Y
	const int RogoCircleScaleTime = 12;						//�T�C�N���̊g�厞��
	//���o�� ����
	const int RogoMoziDelay = 6;							//�������Ƃ̃f�B���C
	const int RogoMoziTime = 12;							//�����̉��o����
	const float RogoMoziStartHosei = 200.0f;				//�����̏���Y�ʒu�␳�i�������j
	const float RogoMoziMove = -250.0f;						//�����̈ړ��ʁi�������j
	//���o�� �~�j����
	const int RogoMiniMoziFadeTime = 12;					//�����̕\������
	const int RogoMiniMoziFadeDelay = 30;					//�����̃f�B���C

};

/// <summary>
/// �����Ƃ�I
/// �E�V���O���g��
/// </summary>
class Title final : public IGameObject
{
	static Title* m_instance;
public:
	Title();
	~Title();
	void Update()override;
	void Render()override;

	//�R�}���h�̑I�����
	enum TitleCommand {
		No_Select,		//���I��
		Game_Start,		//�͂��߂���
		Game_Continue,	//�Â�����
		Game_End,		//�I��
	};

	//�R�}���h�̑I����Ԃ�Ԃ�
	//�I�񂾃R�}���h�̓���������SceneManager���s��
	const TitleCommand& GetCommand()const {
		return m_nowCommand;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static Title* Title::GetInstance() {
		return m_instance;
	}

private:
	//�֐�
	void SetUp();
	void CommandSelect();
	//�G�t�F�N�g�A�b�v�f�[�g
	void EffectUpdate_RogoEffect();
	void EffectUpdate_TitleEffect();
	void EffectUpdate_CommandWait();
	void EffectUpdate_CommandEffect();
	//���[�v�w�i
	void BG_Update();

	//�R�}���h�����
	TitleCommand m_nowCommand = No_Select;		//�ŏ��͖��I��
	TitleCommand m_memberCommand = No_Select;	//�����p

	//���C�g���[�J�[
	//LightMaker* lm = nullptr;

	//�\�����
	enum TitleEffect {	//�G�t�F�N�g�̏�
		Rogo_Effect,	//���S�o����
		Title_Effect,	//���S�o���I����ă^�C�g���Ɉڍs��
		Command_Wait,	//�v���C���[�̑I��҂�
		Command_Effect,	//�R�}���h�I�����o��
	};
	TitleEffect m_titleEffect = Rogo_Effect;	//�G�t�F�N�g���

	//���f��
	SkinModelRender* m_ball;									//�܂��{�[���i�n���H�j
	const CVector3 Ball_DefPos = { 150.0f,-150.0f,-200.0f };	//�������W
	const CVector3 Ball_RotAxis = CVector3::AxisY();			//������]��
	const float Ball_RotAngle = 35.0f;							//������]��
	const float Ball_AutoRotAngle = 1.0f;						//������]���x
	const CVector3 Ball_AutoRotAxis = CVector3::AxisX();		//������]��

	SkinModel m_player;											//�v���C���[
	const CVector3 Player_DefPos = { -70.0f,146.0f,-100.0f };	//�������W�i�{�[������ɂ���j
	const float Player_Scale = 0.5f;							//�g�嗦
	const float Plyer_RotAngleX = 20.0f;						//X��]��
	Animation m_playerAnimation;								//�A�j���[�V�����B
	AnimationClip m_playerAnimationClips[1];					//�A�j���[�V�����N���b�v�B
	CVector3 m_p_pos;
	CQuaternion m_p_rot;
	CVector3 m_p_scl;

	SkinModelRender* m_dummyBox;								//�_�~�[�{�b�N�X
	const CVector3 DummyBoxHosei = { -25.0f ,55.0f ,-40.0f };	//���̍��W�␳
	const float DummyBoxScale = 40.0f;							//���̑傫��
	const float UpDownY = 2.0f;									//���̏㉺�X�s�[�h
	const int UpDownTime = 10;									//���̏㉺����

	//�X�v���C�g
	SpriteRender* m_black;					//�y��
	const int Black_Priority = 3;			//�D��x

	SpriteRender* m_bg1;					//���[�v�w�i1�i���f������ɕ`���j
	const int BG1_Priority = 0;				//�D��x

	SpriteRender* m_bg2;					//���[�v�w�i2�i���f������ɕ`���j
	const int BG2_Priority = 0;				//�D��x
	int m_bgMoveTimer = 0;					//�w�i�p�^�C�}�[
	const int BG_MoveTime = 600;			//�w�i�ړ�����
	bool m_BG_MoveMode = false;				//�ړ����

	//�^�C�g�����S
	TitleRogo Rogo;												//���S
	//�^�C�g���R�}���h
	SpriteRender* m_command_Start;								//�J�n�R�}���h
	SpriteRender* m_command_Continue;							//�Â�����I
	SpriteRender* m_command_End;								//�Q�[���I��
	const CVector3 Command_DefPos = { -400.0f,0.0f,0.0f };		//�������W
	const float Command_Y_Hosei = 120.0f;						//�R�}���h���m�̊Ԋu
	const CVector2 CommandSpriteSize = { 350.0f,120.0f };		//�R�}���h�摜�̑傫��
	const int Command_Priority = 1;								//�D��x
	const float Command_Y_Up = 800.0f;							//�R�}���h�̏����ʒuY�␳�i���Ƃ��p�j

	//���S�G�t�F�N�g
	float m_rogoEffectTimer = 0.0f;								//���S�G�t�F�N�g�p�^�C�}�[
	const float RogoEffectRimit = 1.5f;							//���̃G�t�F�N�g���I����Ď��ɐ؂�ւ��܂ł̎���
	//���S���^�C�g��
	float m_titleEffectTimer = 0.0f;							//�^�C�g���G�t�F�N�g�p�^�C�}�[
	const int TitleMoveTime = 60;								//�^�C�g���G�t�F�N�g���̕����̈ړ�����
	const int TitleFadeTime = 80;								//�^�C�g���G�t�F�N�g���̃t�F�[�h����
	const CVector2 TitleRogoPos = { -380.0f,230.0f };			//���S�̍ŏI�ړ���
	const float TitleRogoScale = 0.5f;							//���S�̍ŏI�g�嗦
	const float TitleCommandEffectRimit = 1.0f;					//�R�}���h����������^�C�~���O
	bool m_commandMoveFlag = false;								//�R�}���h�����t���O
	const float TitleCommandDrop_YHosei = 15.0f;				//�R�}���h���I�[�o�[�ɗ�������ړ���
	const int TitleCommandDrop_Time = 20;						//�R�}���h���Ƃ̈ړ�����
	const int TitleCommandDrop_Delay = 10;						//�R�}���h���Ƃ̃f�B���C
	const float TitleEffectRimit = 2.0f;						//���̃G�t�F�N�g���I����Ď��ɐ؂�ւ��܂ł̎���
	//�R�}���h�I���G�t�F�N�g
	const CVector4 CommandMulColor = { 1.0f,0.4f,0.4f,1.0f };	//�R�}���h�I�����̐F
	const float CommandSelectMove = 10.0f;						//�R�}���h�I�����̈ړ���
	const int CommandSelectMoveTime = 3;						//�R�}���h�I�����̈ړ�����
	//�R�}���h�J�n�G�t�F�N�g
	float m_commandStartEffectTimer = 0.0f;						//�R�}���h�G�t�F�N�g�p�^�C�}�[
	const int CommandAlphaTime = 12;							//�I���O�̃R�}���h����������鎞��
	const float CommandStartEffectRimit = 1.0f;					//�R�}���h�����肳��ăQ�[���}�l�[�W���[�֕ԋp�����܂ł̎���
	//���S�G�t�F�N�g
	const int LogoEffectInterval = 10;							//���S�������Ƃ̊g��k���C���^�[�o��
	const int LogoEffectIntervalHosei = 60;						//���S�������Ƃ̊g��k���C���^�[�o��+�A���t�@
	const float LogoEffectScale = 0.55f;						//���S�̉��o�X�P�[��
	const int LogoEffectTime = 3;								//���S�̊g��k�����ԁi�Г��j

};

