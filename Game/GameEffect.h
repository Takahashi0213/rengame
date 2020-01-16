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
		Shake_Stand,	//�k����
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
	///			   �����ɗ����G�\���ς݂̏ꍇ�A�E����X���C�h�C�����鉉�o���X�L�b�v����
	/// Delete_Stand->�ⓚ���p�ŗ����G������
	/// Jump_Stand->�����G���W�����v������i�X�e�[�^�X�͒萔�j
	/// Shake_Stand->�����G���k����i�X�e�[�^�X�͒萔�j
	/// 
	/// </param>
	/// <remarks>
	/// 
	/// �����G���󔒂̏ꍇ�A������Null������܂�
	/// Null�̏ꍇ�����G�͍X�V���ꂸ���݂̕����g���܂�
	/// 
	/// �R�}���h���󔒂̏ꍇ�A������New_Stand������܂�
	/// 
	/// </remarks>
	void StandControl(Stand_Name stand = Stand_Null, Stand_Command command = Stand_Command::New_Stand);

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

	Stand_Name m_nowStand = Stand_Name::Stand_Null;		//���݂̗����G

	const CVector3 StandDefPos_Move = { 700.0f,-250.0f,0.0f };	//�ړ��O
	const CVector2 StandDefPos = { 280.0f,-250.0f };			//�ړ���
	const CVector2 StandDefPos2 = { 250.0f,-250.0f };			//�ړ���2
	const float StandDefScale = 0.9f;

	bool m_standFlag = false;				//�����G�\�����H

	//�W�����v���o�p�萔
	const float JumpMove_A = 80.0f;		//�ŏ��̃W�����vY����
	const int JumpWait_A = 4;			//�ŏ��̃W�����v����
	const float JumpMove_B = 20.0f;		//2��ڂ̃W�����vY����
	const int JumpWait_B = 2;			//2��ڂ̃W�����v����

	//�k�����o�p�萔
	const float ShakeMove_X = 50.0f;	//�V�F�C�N��X�ړ���
	const int ShakeCount = 6;			//�V�F�C�N��
	

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

	/// <summary>
	/// �����R�}���h�ŉ�b���܂�
	/// </summary>
	/// <param name="Message">��b���e</param>
	void MessageEffect(wchar_t* Message);

	/// <summary>
	/// ���b�Z�[�W���蒆�͌Ă�łˁ`
	/// </summary>
	void MessageUpdate();

	/// <summary>
	/// ���b�Z�[�W���肳�ꂽ�u�Ԃ���true��Ԃ�
	/// </summary>
	/// <returns>�����</returns>
	bool GetMessageOkuriFlag() {
		return m_messageClickFlag;
	}

private:

	//��b�g�\���p
	SpriteRender* m_windowSprite;			//��b�E�B���h�E�̃X�v���C�g
	const int WindowSpritePriority = 6;		//��b�E�B���h�E�̗D��x

	SpriteRender* m_windowOkuriSprite;				//��b����A�C�R���̃X�v���C�g
	const int WindowOkuriSpritePriority = 6;		//��b����A�C�R���̗D��x

	SpriteRender* m_messageSkipSprite;				//�X�L�b�v���̃X�v���C�g
	const int MessageSkipSpritePriority = 6;		//�X�L�b�v���̗D��x

	FontRender* m_messageFont;				//���b�Z�[�W
	const int MessageFontPriority = 7;		//���b�Z�[�W�̗D��x

	FontRender* m_messageSkipOshiraseFont;				//�X�L�b�v�̂��m�点
	const int MessageSkipOshiraseFontPriority = 7;		//�X�L�b�v���m�点�̗D��x

	//���W�w��
	const CVector3 WindowDefPos = { -200.0f,50.0f,0.0f };
	const CVector3 WindowOkuriDefPos = { -50.0f,-50.0f,0.0f };
	const CVector2 TextDefPos = { -350.0f,125.0f };
	const CVector2 TextSkipDefPos = { -600.0f,-300.0f };

	//���b�Z�[�W����A�C�R��
	const float MessageOkuriMove = 50.0f;	//���b�Z�[�W����A�C�R���̈ړ���
	const int MessageOkuriMoveTime = 30;	//���b�Z�[�W����A�C�R���̈ړ���1���[�v����t���[����

	//�F�w��
	const CVector3 TextColor = { 1.0f,0.1f,0.3f };		//�e�L�X�g�̐F

	//���b�Z�[�W�t���O
	bool m_nowMessage = false;			//���b�Z�[�W�\������
	bool m_messageOkuriWait = false;	//�N���b�N�҂��I
	bool m_messageClickFlag = false;	//���b�Z�[�W���肳�ꂽ�u�Ԃ���true�ɂȂ� ������擾�����烁�b�Z�[�W���肪�X���[�Y

	//���b�Z�[�W����
	const int MessageDelateWait = 4;	//���b�Z�[�W��������܂ł̑҂�����
	int m_messageTimer = 0;

	//�X�L�b�v
	bool m_skipFlag = false;			//�X�L�b�v���H
	int m_skipTimer = 0;				//�X�L�b�v�^�C�}�[
	const int SkipLimit = 30;			//�X�L�b�v�̐�������

	//�X�L�b�v���m�点�e�L�X�g
	const wchar_t* SkipText = L"�r�o�`�b�d�������F�X�L�b�v";

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

	/// <summary>
	/// �X�V����
	/// </summary>
	void GameEffectUpdate() {
		m_message.MessageUpdate();
	}

	/// <summary>
	/// 2�̉�b�������Z�b�g�ɂ�������
	/// </summary>
	/// <param name="Message">���b�Z�[�W</param>
	/// <param name="stand">�����G</param>
	/// <param name="command">���o</param>
	void EasyEffect(wchar_t* Message,
		GameEffect_Stand::Stand_Name stand = GameEffect_Stand::Stand_Name::Stand_Null,
		GameEffect_Stand::Stand_Command command = GameEffect_Stand::Stand_Command::New_Stand){

		m_message.MessageEffect(Message);
		m_stand.StandControl(stand, command);

	}

private:
	GameEffect_Stand m_stand;
	GameEffect_Message m_message;

};
