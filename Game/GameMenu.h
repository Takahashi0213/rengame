#pragma once

/// <summary>
/// ���j���[�̃A���R���𑍊�����c�Ȃ���Ȃ�
/// �E�V���O���g��
/// </summary>
class GameMenu
{
	static GameMenu* m_instance;
public:
	enum MenuCommand {	//���j���[�̍���
		Create,			//�}�i�A�A�C�e���A�X�^�[�}�l�[���g�p���ĐF�X�n��
		Box_Release,	//�S������i����S�ď������ă}�i���񕜁j
		Library,		//�}�ӂ₠�炷��
		Save,			//�Z�[�u
	};

	GameMenu();
	~GameMenu();

	//GameUI���Ă�ł����
	void GameMenuUpdate();

	/// <summary>
	/// �}�E�X�J�[�\�������j���[�{�^���ɔ���Ă���true
	/// </summary>
	bool GetSelectFlag() {
		return m_selectFlag;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static GameMenu* GameMenu::GetInstance() {
		return m_instance;
	}

private:

	//�̪�ĩ
	void Update_Effect(int mode);
	//���܂��
	void Update_Command();
	void Update_CommandDelta(const int delta, bool& flag);
	void Update_CommandDraw(bool drawStile);

	//�����o�ϐ�
	const int SpriteNo = 7;		//�X�v���C�g�̊�ƂȂ�D��x
	const float MenuMove = 370.0f;	//���j���[���J���鎞�̈ړ���
	const float MenuMove_Over = 30.0f;	//���j���[���J���鎞�̈ړ��ʁi�I�[�o�[�����p�j
	const int MenuMoveTime = 4;	//���j���[���J���鎞��
	int m_menuMoveTimer = 0;
	MenuCommand m_nowMenuCommand = MenuCommand::Create;	//���݂̃R�}���h�H�I
	bool m_selectFlag = false;		//�I��

	//���j���[�֘A�̉摜���������߂�ǂ�
	std::vector<SpriteRender*> m_spriteRenderList;
	std::vector<FontRender*> m_fontRenderList;

	//���j���[�g�֘A
	const CVector2 DefMenuWindowSize = { 600.0f,742.0f };
	const CVector2 DefMenuWindow_2Size = { 350.0f,150.0f };		//Window2�͐�����

	const CVector3 DefMenuWindowPosition = { 530.0f,0.0f,1.0f };
	const CVector3 DefMenuWindow_2Position = { 450.0f,-250.0f,1.0f };
	const CVector3 DefMenuButtonPosition = { 220.0f,300.0f,1.0f };

	const float MenuButtonSize = 150.0f;
	const float MenuButtonSize_Hosei = 150.0f;

	//���@�w
	const float MenuMahojinSize = 1000.0f;
	const CVector3 MenuMahojinDefPosition = { 1000.0f,-60.0f,1.0f };
	const float MezuMahojinScale = 0.6f;
	const float MenuMahojinAlpha = 0.2f;
	const float MenuMahojinRotSpeed = -0.2f;

	//���j���[���S
	const CVector2 MenuLogoSize = { 450.0f,200.0f };
	const CVector2 MenuLogoAccSize = { 70.0f,70.0f };	//���̕���
	const CVector2 MenuLogoNami = { 450.0f,338.0f };
	const float MenuLogoScale = 0.8f;
	const CVector3 DefMenuLogoPosition = { 830.0f,280.0f,1.0f };
	const CVector3 DefMenuLogo_AccPosition = { 980.0f,300.0f,1.0f };
	const int MenuLogoMoveSpeed = 300;	//�g�̈ړ�
	const int MenuLogo_AccRotSpeed = 30;	//���̉�]
	int MenuLogoTimer = 0;
	int MenuLogoRotTimer = 0;
	const float MenuAccRot = 2.0f;		//1�t���[�����Ƃ̉�]��

	//�R�}���h
	const CVector2 MenuCommandWindowDefSize = { 430.0f,75.0f };	//�摜���̂̑傫��
	const CVector2 MenuCommandWindowSize = { 350.0f,75.0f };	//�ŏI�̑傫��
	const float MenuCommand_SideScale = 350.0f;	//���[�̑傫��
	const CVector3 DefMenuCommandPosition = { 450.0f,160.0f,1.0f };
	const float MenuCommand_YHosei = 90.0f;	//�R�}���h���Ƃ�Y�␳
	const CVector3 TextColor = { 0.1f,0.1f,0.5f };		//�e�L�X�g�̐F
	const float TextFontSize = 0.6f;						//�e�L�X�g�̑傫��
	const CVector2 DefMenuCommand_TextPosition = { 375.0f,182.0f };
	const float SaveX_Hosei = 30.0f;
	//���ړ��e
	const wchar_t* Koumoku[4]{
		L"�N���G�C�g",
		L"�S�����",
		L"���C�u����",
		L"�Z�[�u",
	};
	//�A�N�Z�T���[

	//������
	const CVector3 SetumeiTextColor = { 0.9f,0.9f,0.9f };		//�������̐F
	const float TextFontSize_Setumei = 0.5f;					//�e�L�X�g�̑傫��
	const CVector2 DefSetumei_TextPosition = { -140.0f,60.0f };	//�������E�B���h�E����ɂ������W
	//���e
	const wchar_t* SetumeiBun[4]{
		L"�N���G�C�g��\n����������",
		L"�S�������\n�������ł�",
		L"���C�u������\n���������]",
		L"�Z�[�u��\n����������I�I",
	};

	//�I���J�[�\��
	const CVector3 DefCursorPosition = { 280.0f,160.0f,1.0f };	//��ԏ�̃|�W�V�����I�I
	int m_cursorMoveTimer = 0;			//�J�[�\���̍��E�ړ��^�C�}�[
	const int CursorMoveLimit = 20;		//�J�[�\�������E1��������܂ł̎���
	const float Cursor_YMove = 10.0f;	//�J�[�\����Y�ړ���

	//���j���[���̃u���[�֘A
	const float BlurSpeed = 1.0f;	//1�t���[�����Ƃ̏d�ݑ�����
	const float MaxBlur = 5.0f;		//�u���[�̍ő�d��

	//���j���[����֘A

	//���Z���N�g���[�h�̎d�l����
	//
	//false�Ȃ�J�[�\���͏d�Ȃ��Ă��Ȃ��̂Ńz�C�[���ő���A�}�E�X�J�[�\���̈ʒu�͌��Ȃ�
	//true�Ȃ�J�[�\�����ǂꂩ�̃{�^���ɏd�Ȃ��Ă���̂ŁA�ʒu������
	//true�̎��Ƀz�C�[���𑀍삳�ꂽ�烂�[�h��false�ɕύX���A
	//�ēx�}�E�X�J�[�\�������킹��܂Ń��[�h�͂�����false
	bool m_selectMode = false;
	bool m_selectOverFlag = false;	//����true�̎��Ƀz�C�[���𑀍삳�ꂽ��t���O
	bool m_selectOverFlag_ = false;	//�\��

	//���������火�X�v���C�g��

	//�S��
	SpriteRender* MenuWindow;
	SpriteRender* MenuWindow2;		//������
	SpriteRender* MenuButton;
	//���������股
	SpriteRender* MenuLogo_Under;
	SpriteRender* MenuLogo;
	SpriteRender* MenuLogo_Up;
	SpriteRender* Menu_Mahojin;		//���@�w
	//�R�}���h�ł�
	SpriteRender* MenuCommand_Sprite1;		//���肦����
	FontRender* MenuCommand_Font1;
	SpriteRender* MenuCommand_Sprite2;		//�S�����
	FontRender* MenuCommand_Font2;
	SpriteRender* MenuCommand_Sprite3;		//���C�u�����[
	FontRender* MenuCommand_Font3;
	SpriteRender* MenuCommand_Sprite4;		//�Z�[�u
	FontRender* MenuCommand_Font4;
	//�R�}���h�A�N�Z�T���[

	//������
	FontRender* MenuSetumeiFont;
	//�J�[�\��
	SpriteRender* MenuCommand_Cursor;		//�I���J�[�\��

};

