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

	/// <summary>
	/// �}�E�X�J�[�\�������j���[�{�^���ɔ���Ă���true
	/// </summary>
	bool GetSelectFlag() {
		return m_selectFlag;
	}

private:

	void Update_Effect(int mode);


	//�����o�ϐ�
	const int SpriteNo = 7;		//�X�v���C�g�̊�ƂȂ�D��x
	const float MenuMove = 370.0f;	//���j���[���J���鎞�̈ړ���
	const float MenuMove_Over = 30.0f;	//���j���[���J���鎞�̈ړ��ʁi�I�[�o�[�����p�j
	const int MenuMoveTime = 4;	//���j���[���J���鎞��
	MenuCommand m_nowMenuCommand = MenuCommand::Item;	//���݂̃R�}���h�H�I
	bool m_selectFlag = false;		//�I��

	//���j���[�֘A�̉摜���������߂�ǂ�
	std::vector<SpriteRender*> m_spriteRenderList;

	//���j���[�g�֘A
	const CVector2 DefMenuWindowSize = { 600.0f,742.0f };
	const CVector2 DefMenuWindow_2Size = { 350.0f,150.0f };

	const CVector3 DefMenuWindowPosition = { 530.0f,0.0f,1.0f };
	const CVector3 DefMenuWindow_2Position = { 450.0f,-250.0f,1.0f };
	const CVector3 DefMenuButtonPosition = { 220.0f,300.0f,1.0f };

	const float MenuButtonSize = 150.0f;
	const float MenuButtonSize_Hosei = 150.0f;

	//���j���[���̃u���[�֘A
	const float BlurSpeed = 1.0f;	//1�t���[�����Ƃ̏d�ݑ�����
	const float MaxBlur = 5.0f;		//�u���[�̍ő�d��

	//���������火�X�v���C�g��

	//�S��
	SpriteRender* MenuWindow;
	SpriteRender* MenuWindow2;		//������
	SpriteRender* MenuButton;
	//�R�}���h�ł�


};

