#pragma once

/// <summary>
/// �u�S������v
/// ����S�č폜����R�}���h
/// BAD(BoxAllDelete)
/// </summary>
class Menu_BoxAllDelete
{
public:
	Menu_BoxAllDelete();
	~Menu_BoxAllDelete();

	//�A�b�v�f�[�g�iGameMenu�ɌĂ�ł��炤�j
	void DeleteCheckUpdate();
	//�R�}���h�̃t�F�[�h�A�E�g
	void CommandEnd();

	bool GetDeleteFlag() {
		return m_deleteFlag;
	}

private:


	//���݂̑I����
	enum NowCommand {
		NullSelect_Command,		//�ǂ����I��ł��Ȃ�
		Yes_Command,			//�͂���I��
		No_Command,				//��������I��
	};
	NowCommand m_nowCommand = NullSelect_Command;		//���݂̑I���R�}���h

	//���������Ƃ��̊m�F���b�Z�[�W
	const wchar_t* HeaderText = L"�S�����";
	const wchar_t* CheckText = L"�S�Ă̔����폜����\n�}�i��S�񕜂��܂����H";
	const wchar_t* YesText = L"�n�j�I";
	const wchar_t* NoText = L"��߂�";

	//�X�v���C�g�����_�[
	SpriteRender* MenuWindow;									//�E�B���h�E
	const CVector3 MenuDefPos = { -200.0f,-50.0f,0.0f };		//���W
	const CVector2 DefMenuWindowSize = { 600.0f,400.0f };		//�T�C�Y

	SpriteRender* ButtonWindow_Left;							//���E�B���h�E
	SpriteRender* ButtonWindow_Right;							//�E�E�B���h�E
	const CVector3 MenuButtonDefSize = { 200.0f,60.0f,0.0f };	//�傫��
	const CVector2 MenuButtonPosHosei = { 150.0f,-200.0f };		//���W�␳�i�E�B���h�E��j

	//�t�H���g
	FontRender* Header_Font;									//�E�B���h�E�̃w�b�_�[
	const float Header_FontSize = 0.6f;							//�w�b�_�[�e�L�X�g�̑傫��
	const CVector2 Header_Font_Hosei = { -80.0f,190.0f };		//�w�b�_�[�e�L�X�g�̍��W�␳

	FontRender* Check_Font;										//�����܂����H�̃e�L�X�g
	const CVector2 Check_Font_Hosei = { -180.0f,20.0f };		//�����܂����H�̍��W�␳

	FontRender* Yes_Font;										//�͂��̃e�L�X�g
	const float YesFont_XHosei = 5.0f;							//�͂��̃e�L�X�gX�␳
	FontRender* No_Font;										//�������̃e�L�X�g
	const float NoFont_XHosei = -5.0f;							//�������̃e�L�X�gX�␳
	const CVector2 YesNo_Font_Hosei = { -40.0f,23.0f };			//���e�L�X�g�̍��W�␳

	//�폜�t���O
	bool m_deleteFlag = false;									//true��GameMenu�ɕԂ��ƍ폜���Ă��炦��

	//�萔
	const int SpriteNo = 8;										//�X�v���C�g�̊�ƂȂ�D��x
	const float NoActiveAlpha = 0.5f;							//��I���̎��̔������A���t�@�l
	const int DeleteTime = 6;									//�폜����

};

