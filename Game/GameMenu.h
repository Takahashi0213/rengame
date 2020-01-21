#pragma once

/// <summary>
/// ���j���[�̃A���R���𑍊�����c�Ȃ���Ȃ�
/// </summary>
class GameMenu
{
public:
	enum MenuCommand {	//���j���[�̍���
		Item,			//�����Ă�A�C�e�����m�F
		Create,			//�}�i�A�A�C�e���A�X�^�[�}�l�[���g�p���ĐF�X�n��
		Box_Release,	//�S������i����S�ď������ă}�i���񕜁j
		Library,		//�}�ӂ₠�炷��
		Save,			//�Z�[�u
		GameEnd,		//�I���I
	};

	GameMenu();
	~GameMenu();

	//GameUI���Ă�ł����
	void GameMenuUpdate();

private:

	//�����o�ϐ�
	const int SpriteNo = 7;		//�X�v���C�g�̊�ƂȂ�D��x
	const float MenuMove = 370.0f;	//���j���[���J���鎞�̈ړ���
	MenuCommand m_nowMenuCommand = MenuCommand::Item;	//���݂̃R�}���h�H�I

	//���j���[�g�֘A
	const CVector2 DefMenuWindowSize = { 500.0f,742.0f };
	const CVector2 DefMenuWindow_2Size = { 350.0f,200.0f };

	const CVector3 DefMenuWindowPosition = { 480.0f + MenuMove,0.0f,1.0f };
	const CVector3 DefMenuWindow_2Position = { 450.0f + MenuMove,-220.0f,1.0f };
	const CVector3 DefMenuButtonPosition = { 220.0f + MenuMove,300.0f,1.0f };

	const float MenuButtonSize = 150.0f;
	const float MenuButtonSize_Hosei = 150.0f;

	//���������火�X�v���C�g��

	//�S��
	SpriteRender* MenuWindow;
	SpriteRender* MenuWindow2;		//������
	SpriteRender* MenuButton;
	//�R�}���h�ł�


};

