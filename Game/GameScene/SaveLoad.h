#pragma once

/// <summary>
/// ���[�h���
/// �E�V���O���g��
/// </summary>
class SaveLoad : public IGameObject
{
	static SaveLoad* m_instance;
public:
	SaveLoad();
	~SaveLoad();
	void Update()override;
	void Render()override;

	//���[�h����
	enum SaveLoadEnd {
		NULL_LoadEnd,	//��
		LoadSuccess,	//���[�h����
		NoLoad,			//���[�h���Ȃ�����
	};

	/// <summary>
	/// ���[�h���ʂ�Ԃ�
	/// </summary>
	const SaveLoadEnd& Get_SaveLoadEnd()const {
		return m_saveLoadEnd;
	}
	/// <summary>
	/// �I���t���O��Ԃ�
	/// </summary>
	bool GetEndFlag() {
		return m_endFlag;
	}

private:

	void LoadData();

	SaveLoadEnd m_saveLoadEnd = NULL_LoadEnd;					//���[�h�I��

	//���݂̑I����
	enum NowCommand {
		NullSelect_Command,		//�ǂ����I��ł��Ȃ�
		Yes_Command,			//�͂���I��
		No_Command,				//��������I��
	};
	NowCommand m_nowCommand = NullSelect_Command;		//���݂̑I���R�}���h

	//�m�F���b�Z�[�W
	const wchar_t* LoadCheckText = L"���̃f�[�^�����[�h���܂����H";
	const wchar_t* LoadCheckText_No = L"�Z�[�u�f�[�^��������܂���";
	const wchar_t* LoadNowText = L"���[�h����";
	const wchar_t* YesText = L"���[�h";
	const wchar_t* NoText = L"���ǂ�";

	//�X�v���C�g�����_�[
	SpriteRender* m_BG = nullptr;								//�w�i
	const CVector2 BG_Size = { 1920.0f,1358.0f };				//�T�C�Y

	SpriteRender* ButtonWindow_Left = nullptr;					//���E�B���h�E
	SpriteRender* ButtonWindow_Right = nullptr;					//�E�E�B���h�E
	const CVector3 MenuButtonDefSize = { 200.0f,60.0f,0.0f };	//�傫��
	const CVector2 MenuButtonPosHosei = { 150.0f,-170.0f };		//���W�␳�i�E�B���h�E��j

	SpriteRender* m_saveWindow = nullptr;						//���Z�[�u�̃E�B���h�E
	const CVector3 SaveDefPos = { -300.0f,0.0f,0.0f };			//���W
	const CVector2 SaveWindowSize = { 500.0f,100.0f };			//�T�C�Y

	SpriteRender* m_mapIC = nullptr;							//�}�b�v�A�C�R��
	const CVector3 MapIC_PosHosei = { -180.0f, 0.0f,0.0f };		//���W�␳�i�Z�[�u�E�B���h�E��j
	const CVector2 MapIC_Size = { 80.0f,80.0f };				//�T�C�Y
	
	//�t�H���g�����_�[
	FontRender* m_loadChackText = nullptr;						//���[�h���܂����Hor�Z�[�u�f�[�^������܂���or���[�h���܂���
	const CVector2 LoadChackTextPos = { -480.0f,-75.0f };		//�e�L�X�g�̍��W
	const float Check_FontSize = 0.5f;							//�Z�[�u���܂����H�̑傫��
	const CVector4 Check_FontColor = { 1.0f,0.5f,0.0f,1.0f };	//�`�F�b�N�t�H���g�̐F
	const float LoadX_Hosei = 100.0f;							//���[�h���܂�����X�␳

	FontRender* Yes_Font = nullptr;								//�͂��̃e�L�X�g
	const float YesFont_XHosei = -5.0f;							//�͂��̃e�L�X�gX�␳
	FontRender* No_Font = nullptr;								//�������̃e�L�X�g
	const float NoFont_XHosei = -5.0f;							//�������̃e�L�X�gX�␳
	const CVector2 YesNo_Font_Hosei = { -40.0f,23.0f };			//���e�L�X�g�̍��W�␳
	const float YesNo_FontSize = 0.6f;							//�傫��

	FontRender* m_load_PlayerLevel = nullptr;					//�f�[�^�̃v���C���[���x��
	const CVector2 PlayerLevel_Hosei = { -130.0f,35.0f };		//���e�L�X�g�̍��W�␳

	FontRender* m_load_PlayerHP = nullptr;						//�f�[�^�̃v���C���[HP
	const CVector2 PlayerHP_Hosei = { 10.0f,35.0f };			//���e�L�X�g�̍��W�␳

	FontRender* m_load_PlayerPlace = nullptr;					//�f�[�^�̃v���C���[�ʒu
	const CVector2 PlayerPlace_Hosei = { -130.0f,-5.0f };		//���e�L�X�g�̍��W�␳

	const float SaveDataFontSize = 0.4f;						//�Z�[�u�f�[�^���̑傫��

	//���[�h�����֘A
	FILE * fp = nullptr;										//���[�h�t�@�C��
	bool m_fifeFlag = false;									//�t�@�C�����݂���H
	GameData* m_gameData_Load = nullptr;						//���f�[�^�p�Վ�

	//��ʃt�F�[�h�A�E�g
	int m_fadeoutTimer = 0;										//�t�F�[�h�A�E�g�^�C�}�[
	const int FadeOutLimit = 60;								//�t�F�[�h�A�E�g��������
	int m_fadeinTimer = 0;										//�t�F�[�h�C���^�C�}�[
	const int FadeInLimit = 60;									//�t�F�[�h�C����������
	const int FadeInEndLimit = 120;								//�t�F�[�h�C����������+�I������

	bool m_loadFlag = false;									//���[�h�t���O
	bool m_noLoadFlag = false;									//���[�h���Ȃ��t���O
	bool m_endFlag = false;										//�����true�ɂ�����I��
	bool m_loadDataFlag = false;								//�Q�[���f�[�^��1�񂾂����[�h����

	//���ʉ�
	bool m_seFlag = false;										//���ʉ��t���O

	//�萔
	const int SpriteNo = 8;										//�X�v���C�g�̊�ƂȂ�D��x
	const float NoActiveAlpha = 0.5f;							//��I���̎��̔������A���t�@�l
	const CVector4 CanNotSelect = { 0.2f,0.2f,0.2f,0.5f };		//�I���ł��܂���
	const int DeleteTime = 6;									//�폜����

};

