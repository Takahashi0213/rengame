#pragma once

/// <summary>
/// �����G�֘A
/// </summary>
class GameEffect_Stand {

public:
	//�����G�Ăяo���p
	enum Stand_Name {
		Stand_Null,		//��
		Stand_Normal,	//�ʏ�
		Stand_Happy,	//�ɂ�����
		Stand_Sad,		//�߂���
		Stand_Ang,		//����
		Stand_Wow,		//�т����肵��
	};
	//�����G����R�}���h
	enum Stand_Command {
		New_Stand,		//�\��
		Delete_Stand,	//�폜
		Jump_Stand,		//�W�����v����
	};

	/// <summary>
	/// ����
	/// </summary>
	void StandInit();

	/// <summary>
	/// �����G����
	/// </summary>
	/// <param name="stand">�\�����闧���G</param>
	/// <param name="command">�R�}���h
	/// 
	/// New_Stand->�������ɐݒ肵�������G��\��
	/// Delete_Stand->�ⓚ���p�ŗ����G������
	/// Jump_Stand->�����G���W�����v������i�X�e�[�^�X�͒萔�j
	/// </param>
	void StandControl(Stand_Name stand, Stand_Command command);

private:

	struct Stand_Data {		//�����G�f�[�^�\����
		wchar_t* SpriteName;	//�X�v���C�g�t�@�C����
		float High;				//����
		float Wide;				//��
	};

	const Stand_Data Game_Stand_Data[6]{	//�����G�z��
		{ L"test",100.0f,100.0f },		//�\���f�[�^
		{ L"Assets/sprite/keis.dds",588.0f,1240.0f },
		{ L"Assets/sprite/keis_happy.dds",588.0f,1240.0f },
		{ L"Assets/sprite/keis_sad.dds",588.0f,1240.0f },
		{ L"Assets/sprite/keis_ang.dds",588.0f,1240.0f },
		{ L"Assets/sprite/keis_wow.dds",588.0f,1240.0f },
	};

	//�����G�\���p
	SpriteRender* m_standSprite;				//�����G�̃X�v���C�g�ł��I
	const int StandSpritePriority = 5;			//�����G�̗D��x

	const CVector3 StandDefPos_Move = { 700.0f,-250.0f,0.0f };	//�ړ��O
	const CVector2 StandDefPos = { 280.0f,-250.0f };			//�ړ���
	const CVector2 StandDefPos2 = { 250.0f,-250.0f };			//�ړ���2
	const float StandDefScale = 0.9f;

	bool m_standFlag = false;				//�����G�\�����H

};

/// <summary>
/// ���b�Z�[�W�֘A
/// </summary>
class GameEffect_Message {

public:

	/// <summary>
	/// ����
	/// </summary>
	void MessageInit();

private:

	//��b�g�\���p
	SpriteRender* m_windowSprite;			//��b�E�B���h�E�̃X�v���C�g
	const int WindowSpritePriority = 6;		//��b�E�B���h�E�̗D��x

	FontRender* m_messageFont;				//���b�Z�[�W
	const int MessageFontPriority = 7;		//���b�Z�[�W�̗D��x

};

/// <summary>
/// �Q�[���̉��o�T�|�[�g
/// ���V���O���g��
/// </summary>
class GameEffect
{
	static GameEffect* m_instance;
public:

	GameEffect();
	~GameEffect();

	/// <summary>
	/// �C���X�^���X���擾�V���[�Y
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static GameEffect* GameEffect::GetInstance() {
		return m_instance;
	}
	GameEffect_Stand* GetInstance_Stand() {
		return &m_stand;
	}
	GameEffect_Message* GetInstance_Message() {
		return &m_message;
	}

private:
	GameEffect_Stand m_stand;
	GameEffect_Message m_message;

};
