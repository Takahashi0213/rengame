#include "stdafx.h"
#include "GameMenu.h"
#include "Game.h"

GameMenu::GameMenu()
{
	MenuWindow = NewGO<SpriteRender>("MenuWindow", SpriteNo);
	MenuWindow->ChangeSliceSprite({ 150.0f,150.0f });
	MenuWindow->Init(L"Assets/sprite/window3.dds", 
		DefMenuWindowSize.x,
		DefMenuWindowSize.y,
		SpriteNo);
	MenuWindow->SetPosition(DefMenuWindowPosition);

	MenuButton = NewGO<SpriteRender>("MenuButton", SpriteNo);
	MenuButton->Init(L"Assets/sprite/MenuButton.dds", MenuButtonSize, MenuButtonSize, SpriteNo);
	MenuButton->SetPosition(DefMenuButtonPosition);

	MenuWindow2 = NewGO<SpriteRender>("MenuWindow2", SpriteNo);
	MenuWindow2->ChangeSliceSprite({ 150.0f,150.0f });
	MenuWindow2->Init(L"Assets/sprite/window1.dds",
		DefMenuWindow_2Size.x,
		DefMenuWindow_2Size.y,
		SpriteNo);
	MenuWindow2->SetPosition(DefMenuWindow_2Position);

}

GameMenu::~GameMenu()
{
}

void GameMenu::GameMenuUpdate() {

	//�擾
	Game::GameMode GameMode = Game::GetInstance()->GetGameMode();
	CVector2 MousePos = MouseSupporter::GetInstance()->GetMousePos_Sprite();
	int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);

	float PosX = DefMenuButtonPosition.x + (MenuButtonSize / 2.0f);
	float PosX2 = DefMenuButtonPosition.x - (MenuButtonSize / 2.0f);
	float PosY = DefMenuButtonPosition.y + (MenuButtonSize / 2.0f);
	float PosY2 = DefMenuButtonPosition.y - (MenuButtonSize / 2.0f);

	//�܂��̓��j���[�t���O�̍X�V
	switch (GameMode)
	{
	case Game::ActionMode:
		//�{�^���ƍ��W��v ���� �A�N�V�������[�h�Ȃ�{�^���̃X�v���C�g��傫������
		if (MousePos.x <= PosX && MousePos.x >= PosX2 && MousePos.y <= PosY && MousePos.y >= PosY2 &&
			GameMode == Game::GameMode::ActionMode) {

			//����
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });

		}
		else {		//�����łȂ���Ζ߂�

			MenuButton->SetScale(1.0f);
			MenuButton->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}

		//�{�^���ƍ��W��v ���� �A�N�V�������[�h ���� ���N���b�N���ꂽ��
		//���j���[���J���A���[�h�����j���[���[�h�ɕύX����

		break;
	case Game::MenuMode:
		//�{�^���ƍ��W��v ���� ���j���[���[�h�Ȃ�{�^���̃X�v���C�g��傫������

		//�����łȂ���Ζ߂�

		//�{�^���ƍ��W��v ���� ���j���[���[�h ���� ���N���b�N���ꂽ��
		//���j���[����A���[�h���A�N�V�������[�h�ɕύX����

		break;
	}


}