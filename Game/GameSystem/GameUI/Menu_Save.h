#pragma once

/// <summary>
/// �Z�[�u���
/// </summary>
class Menu_Save
{
public:
	Menu_Save();
	~Menu_Save();

	//�A�b�v�f�[�g�iGameMenu�ɌĂ�ł��炤�j
	void SaveUpdate();
	//�R�}���h�̃t�F�[�h�A�E�g
	void CommandEnd();

	bool GetDeleteFlag() {
		return m_deleteFlag;
	}

private:

	//�Z�[�u���o
	void SaveEffect();

	//���݂̑I����
	enum NowCommand {
		NullSelect_Command,		//�ǂ����I��ł��Ȃ�
		Yes_Command,			//�͂���I��
		No_Command,				//��������I��
	};
	NowCommand m_nowCommand = NullSelect_Command;		//���݂̑I���R�}���h

	//�m�F���b�Z�[�W
	const wchar_t* HeaderText = L"�Z�[�u";
	const wchar_t* SaveCheckText = L"���݂̏󋵂��Z�[�u���܂����H";
	const wchar_t* SaveNowText = L"�Z�[�u���܂����I";
	const wchar_t* YesText = L"�Z�[�u";
	const wchar_t* NoText = L"��߂�";
	const wchar_t* NewText = L"�V";
	const wchar_t* OldText = L"��";

	//�X�v���C�g�����_�[
	SpriteRender* MenuWindow = nullptr;							//�E�B���h�E
	const CVector3 MenuDefPos = { -200.0f,-100.0f,0.0f };		//���W
	const CVector2 DefMenuWindowSize = { 700.0f,500.0f };		//�T�C�Y

	SpriteRender* ButtonWindow_Left = nullptr;					//���E�B���h�E
	SpriteRender* ButtonWindow_Right = nullptr;					//�E�E�B���h�E
	const CVector3 MenuButtonDefSize = { 200.0f,60.0f,0.0f };	//�傫��
	const CVector2 MenuButtonPosHosei = { 150.0f,-200.0f };		//���W�␳�i�E�B���h�E��j

	SpriteRender* NewSaveWindow = nullptr;						//�V�����Z�[�u�̃E�B���h�E
	const CVector3 NewSaveDefPos = { -200.0f,0.0f,0.0f };		//���W
	SpriteRender* OldSaveWindow = nullptr;						//���Z�[�u�̃E�B���h�E
	const CVector3 OldSaveDefPos = { -200.0f,-150.0f,0.0f };	//���W
	const CVector2 SaveWindowSize = { 500.0f,100.0f };			//�T�C�Y

	SpriteRender* NewMapIC = nullptr;							//�}�b�v�A�C�R���V
	SpriteRender* OldMapIC = nullptr;							//�}�b�v�A�C�R����
	const CVector3 MapIC_PosHosei = { -180.0f, 0.0f,0.0f };		//���W�␳�i�Z�[�u�E�B���h�E��j
	const CVector2 MapIC_Size = { 80.0f,80.0f };				//�T�C�Y

	SpriteRender* SaveCursor = nullptr;							//�㉺����Z�[�u�J�[�\��
	const CVector3 SaveCursorPos = { -200.0f,-73.0f,0.0f };		//���W
	const CVector2 DefSaveCursorSize = { 60.0f,40.0f };			//�T�C�Y
	const float SaveCursorMove = 5.0f;							//�ړ���
	const int SaveCursorMoveTime = 6;							//�ړ�����

	//�t�H���g
	FontRender* Header_Font = nullptr;							//�E�B���h�E�̃w�b�_�[
	const float Header_FontSize = 0.6f;							//�w�b�_�[�e�L�X�g�̑傫��
	const CVector2 Header_Font_Hosei = { -60.0f,235.0f };		//�w�b�_�[�e�L�X�g�̍��W�␳

	FontRender* Check_Font = nullptr;							//�Z�[�u���܂����H�̃e�L�X�g
	const float Check_FontSize = 0.5f;							//�Z�[�u���܂����H�̑傫��
	const CVector2 Check_Font_Hosei = { -190.0f,-120.0f };		//�Z�[�u���܂����H�̍��W�␳
	const CVector2 Check_Font_Hosei2 = { -115.0f,-120.0f };		//�Z�[�u���܂����H�̍��W�␳2

	FontRender* Yes_Font = nullptr;								//�͂��̃e�L�X�g
	const float YesFont_XHosei = -5.0f;							//�͂��̃e�L�X�gX�␳
	FontRender* No_Font = nullptr;								//�������̃e�L�X�g
	const float NoFont_XHosei = -5.0f;							//�������̃e�L�X�gX�␳
	const CVector2 YesNo_Font_Hosei = { -40.0f,23.0f };			//���e�L�X�g�̍��W�␳

	FontRender* NewSave_Text = nullptr;							//�u�V�v�̃e�L�X�g
	FontRender* OldSave_Text = nullptr;							//�u���v�̃e�L�X�g
	const float NewOld_FontSize = 0.6f;							//�V���e�L�X�g�̑傫��
	const CVector2 NewOld_Font_Hosei = { -310.0f,25.0f };		//���e�L�X�g�̍��W�␳

	FontRender* NewSave_PlayerLevel = nullptr;					//�V�f�[�^�̃v���C���[���x��
	FontRender* OldSave_PlayerLevel = nullptr;					//���f�[�^�̃v���C���[���x��
	const CVector2 NewOld_PlayerLevel_Hosei = { -130.0f,35.0f };//���e�L�X�g�̍��W�␳

	FontRender* NewSave_PlayerHP = nullptr;						//�V�f�[�^�̃v���C���[HP
	FontRender* OldSave_PlayerHP = nullptr;						//���f�[�^�̃v���C���[HP
	const CVector2 NewOld_PlayerHP_Hosei = { 10.0f,35.0f };		//���e�L�X�g�̍��W�␳

	FontRender* NewSave_PlayerPlace = nullptr;					//�V�f�[�^�̃v���C���[�ʒu
	FontRender* OldSave_PlayerPlace = nullptr;					//���f�[�^�̃v���C���[�ʒu
	const CVector2 NewOld_PlayerPlace_Hosei = { -130.0f,-5.0f };//���e�L�X�g�̍��W�␳

	const float NewOld_SaveDataFontSize = 0.4f;					//�Z�[�u�f�[�^���̑傫��

	//�܂Ƃ߂ē����������I
	std::vector<SpriteRender*> m_newSave_SpriteRenderList;
	std::vector<FontRender*> m_newSave_FontRenderList;
	std::vector<SpriteRender*> m_oldSave_SpriteRenderList;
	std::vector<FontRender*> m_oldSave_FontRenderList;

	//�Z�[�u���o�֘A
	bool m_saveFlag = false;									//�Z�[�u�t���O�i�Z�[�u���j
	int m_saveTimer = 0;										//�Z�[�u�^�C�}�[
	const int SaveTimeLimit = 40;								//�Z�[�u�I������
	const CVector3 EffectPos = { -200.0f,0.0f,0.0f };			//�G�t�F�N�g���W

	const float SaveMove_1 = 10.0f;								//����
	const float SaveMove_2 = -170.0f;							//������
	const float SaveMove_3 = 60.0f;								//�オ��
	const int MoveTime_1 = 3;									//�ړ�����
	const int MoveTime_2 = 6;									//�ړ�����
	const int MoveTime_3 = 10;									//�ړ�����

	//�Z�[�u�����֘A
	FILE* fp = nullptr;											//�Z�[�u�t�@�C��
	bool m_fifeFlag = false;									//�t�@�C�����݂���H
	GameData* m_gameData_Load = nullptr;						//���f�[�^�p�Վ�

	//�폜�t���O
	bool m_deleteFlag = false;									//true��GameMenu�ɕԂ��ƍ폜���Ă��炦��

	//�萔
	const int SpriteNo = 8;										//�X�v���C�g�̊�ƂȂ�D��x
	const float NoActiveAlpha = 0.5f;							//��I���̎��̔������A���t�@�l
	const int DeleteTime = 6;									//�폜����


};

