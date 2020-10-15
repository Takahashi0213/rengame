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

	SpriteRender* m_titleRogo_Mozi_Hakobun;	//�E��~�j�����uHAKOBUN�v

	//���S�֘A�̒萔 �`���
	const CVector2 RogoSpriteSize = { 1000.0f,400.0f };		//���S�摜�̑傫��
	const CVector3 RogoDefPos = { 0.0f,0.0f,0.0f };			//���S�̊
	const int RogoCirclePriority = 9;						//�T�C�N���̗D��x
	const int RogoMoziPriority = 10;						//�����̗D��x�i�~�j�����܂ށj
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
	//�G�t�F�N�g�A�b�v�f�[�g
	void EffectUpdate_RogoEffect();
	void EffectUpdate_TitleEffect();
	void EffectUpdate_CommandWait();
	void EffectUpdate_CommandEffect();

	//�R�}���h�����
	TitleCommand m_nowCommand = No_Select;	//�ŏ��͖��I��
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
	const float Ball_RotSpeed = 10.0f;							//��]���x

	SkinModelRender* m_player;				//�v���C���[


	SkinModelRender* m_dummyBox;			//�_�~�[�{�b�N�X


	//�X�v���C�g
	SpriteRender* m_black;					//�y��
	const int Black_Priority = 8;			//�D��x

	SpriteRender* m_bg1;					//���[�v�w�i1�i���f������ɕ`���j
	const int BG1_Priority = 0;				//�D��x

	SpriteRender* m_bg2;					//���[�v�w�i2�i���f������ɕ`���j
	const int BG2_Priority = 0;				//�D��x

	//�^�C�g�����S
	TitleRogo Rogo;												//���S
	//�^�C�g���R�}���h
	SpriteRender* m_command_Start;								//�J�n�R�}���h
	SpriteRender* m_command_Continue;							//�Â�����I
	SpriteRender* m_command_End;								//�Q�[���I��
	const CVector3 Command_DefPos = { -400.0f,0.0f,0.0f };		//�������W
	const float Command_Y_Hosei = 120.0f;						//�R�}���h���m�̊Ԋu
	const CVector2 CommandSpriteSize = { 350.0f,120.0f };		//�R�}���h�摜�̑傫��
	const int Command_Priority = 5;								//�D��x

	//���S�G�t�F�N�g
	float m_rogoEffectTimer = 0.0f;								//���S�G�t�F�N�g�p�^�C�}�[
	const float RogoEffectRimit = 1.5f;							//���̃G�t�F�N�g���I����Ď��ɐ؂�ւ��܂ł̎���
	//���S���^�C�g��
	float m_titleEffectTimer = 0.0f;							//�^�C�g���G�t�F�N�g�p�^�C�}�[
	const int TitleMoveTime = 60;								//�^�C�g���G�t�F�N�g���̕����̈ړ�����
	const int TitleFadeTime = 80;								//�^�C�g���G�t�F�N�g���̃t�F�[�h����
	const CVector2 TitleRogoPos = { -380.0f,250.0f };			//���S�̍ŏI�ړ���
	const float TitleRogoScale = 0.5f;							//���S�̍ŏI�g�嗦
	const float TitleEffectRimit = 2.0f;						//���̃G�t�F�N�g���I����Ď��ɐ؂�ւ��܂ł̎���


	//�萔


};
