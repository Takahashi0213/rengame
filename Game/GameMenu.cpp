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
	MenuWindow->SetPosition({ DefMenuWindowPosition.x + MenuMove ,
		DefMenuWindowPosition.y,DefMenuWindowPosition.z });

	MenuButton = NewGO<SpriteRender>("MenuButton", SpriteNo);
	MenuButton->Init(L"Assets/sprite/MenuButton.dds", MenuButtonSize, MenuButtonSize, SpriteNo);
	MenuButton->SetPosition({ DefMenuButtonPosition.x + MenuMove ,
		DefMenuButtonPosition.y,DefMenuButtonPosition.z });

	MenuWindow2 = NewGO<SpriteRender>("MenuWindow2", SpriteNo);
	MenuWindow2->ChangeSliceSprite({ 150.0f,150.0f });
	MenuWindow2->Init(L"Assets/sprite/window1.dds",
		DefMenuWindow_2Size.x,
		DefMenuWindow_2Size.y,
		SpriteNo);
	MenuWindow2->SetPosition({ DefMenuWindow_2Position.x + MenuMove ,
		DefMenuWindow_2Position.y,DefMenuWindow_2Position.z });

	//�o�^���Ƃ�
	m_spriteRenderList.push_back(MenuWindow);
	m_spriteRenderList.push_back(MenuWindow2);
	m_spriteRenderList.push_back(MenuButton);

}

GameMenu::~GameMenu()
{
}

void GameMenu::GameMenuUpdate() {

	//�擾
	Game::GameMode GameMode = Game::GetInstance()->GetGameMode();
	CVector2 MousePos = MouseSupporter::GetInstance()->GetMousePos_Sprite();
	int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);

	//���̍X�V
	Update_Effect(GameMode);

	//�t���O���Z�b�g
	m_selectFlag = false;

	//���W�v�Z
	float PosX = DefMenuButtonPosition.x + (MenuButtonSize / 2.0f);
	float PosX2 = DefMenuButtonPosition.x - (MenuButtonSize / 2.0f);
	float PosY = DefMenuButtonPosition.y + (MenuButtonSize / 2.0f);
	float PosY2 = DefMenuButtonPosition.y - (MenuButtonSize / 2.0f);

	//�܂��̓��j���[�t���O�̍X�V
	switch (GameMode)
	{
	case Game::ActionMode:

		//���W�␳
		PosX += MenuMove;
		PosX2 += MenuMove;
		//�{�^���ƍ��W��v ���� �A�N�V�������[�h�Ȃ�{�^���̃X�v���C�g��傫������
		if (MousePos.x <= PosX && MousePos.x >= PosX2 && MousePos.y <= PosY && MousePos.y >= PosY2 &&
			GameMode == Game::GameMode::ActionMode) {

			//����
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });
			//�t���O�ύX
			m_selectFlag = true;

			//���N���b�N���ꂽ�烁�j���[���J���A���[�h�����j���[���[�h�ɕύX����
			if (Left_Key == MouseSupporter::Release_Push) {

				Game::GetInstance()->SetGameMode(Game::GameMode::MenuMode);
				//�ړ�
				MenuButton->Init(L"Assets/sprite/MenuButton_Back.dds", MenuButtonSize, MenuButtonSize, SpriteNo);

				for (int i = 0 ; i < m_spriteRenderList.size() ; i++) {

					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ +MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -(MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

			}

		}
		else {		//�����łȂ���Ζ߂�

			MenuButton->SetScale(1.0f);
			MenuButton->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}

		break;
	case Game::MenuMode:
		//�{�^���ƍ��W��v ���� ���j���[���[�h�Ȃ�{�^���̃X�v���C�g��傫������
		if (MousePos.x <= PosX && MousePos.x >= PosX2 && MousePos.y <= PosY && MousePos.y >= PosY2 &&
			GameMode == Game::GameMode::MenuMode) {

			//����
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });
			//�t���O�ύX
			m_selectFlag = true;

			//���N���b�N���ꂽ�烁�j���[����A���[�h���A�N�V�������[�h�ɕύX����
			if (Left_Key == MouseSupporter::Release_Push) {

				Game::GetInstance()->SetGameMode(Game::GameMode::ActionMode);
				//�ړ�
				MenuButton->Init(L"Assets/sprite/MenuButton.dds", MenuButtonSize, MenuButtonSize, SpriteNo);

				for (int i = 0; i < m_spriteRenderList.size(); i++) {

					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ (MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

			}

		}
		else {		//�����łȂ���Ζ߂�

			MenuButton->SetScale(1.0f);
			MenuButton->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}


		break;
	}


}

void GameMenu::Update_Effect(int mode) {

	//���j���[���[�h�Ȃ�I��ʂɃu���[��������D�I
	if (mode == Game::GameMode::MenuMode) {

		float blur = Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity;
		blur += BlurSpeed;
		if (blur > MaxBlur) {
			blur = MaxBlur;
		}
		Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity = blur;

	}
	//�Ⴄ�Ȃ�߂���I�I�I�I
	if (mode != Game::GameMode::MenuMode) {

		float blur = Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity;
		blur -= BlurSpeed;
		if (blur < 0.0f) {
			blur = 0.0f;
		}
		Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity = blur;
	}
}