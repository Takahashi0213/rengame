#include "stdafx.h"
#include "GameMenu.h"
#include "GameScene/Game.h"

GameMenu* GameMenu::m_instance = nullptr;

GameMenu::GameMenu()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//���j���[�̃��C������
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

	//���@�w
	Menu_Mahojin = NewGO<SpriteRender>("MenuMahojin", SpriteNo);
	Menu_Mahojin->Init(L"Assets/sprite/mahojin.dds", MenuMahojinSize, MenuMahojinSize, SpriteNo);
	Menu_Mahojin->SetPosition(MenuMahojinDefPosition);
	Menu_Mahojin->SetScale(MezuMahojinScale);
	Menu_Mahojin->SetAlpha(MenuMahojinAlpha);
	Menu_Mahojin->m_spriteSupporter.SpriteRotation(MenuMahojinRotSpeed, 1, 0, true);

	//������
	MenuWindow2 = NewGO<SpriteRender>("MenuWindow2", SpriteNo);
	MenuWindow2->ChangeSliceSprite({ 150.0f,150.0f });
	MenuWindow2->Init(L"Assets/sprite/window1.dds",
		DefMenuWindow_2Size.x,
		DefMenuWindow_2Size.y,
		SpriteNo);
	MenuWindow2->SetPosition({ DefMenuWindow_2Position.x + MenuMove ,
		DefMenuWindow_2Position.y,DefMenuWindow_2Position.z });

	//�{�^���Ƒ���

	//�낲
	MenuLogo_Under = NewGO<SpriteRender>("MenuLogo_Under", SpriteNo);
	MenuLogo_Under->Init(L"Assets/sprite/MenuLogo_Under.dds", MenuLogoSize.x, MenuLogoSize.y, SpriteNo);
	MenuLogo_Under->SetPosition(DefMenuLogoPosition);
	MenuLogo_Under->SetScale(MenuLogoScale);
	MenuLogo = NewGO<SpriteRender>("MenuLogo", SpriteNo);
	MenuLogo->ChangeMaskSprite();
	MenuLogo->Init(L"Assets/sprite/MenuLogo.dds", MenuLogoSize.x, MenuLogoSize.y, SpriteNo);
	MenuLogo->SetPosition(DefMenuLogoPosition);
	MenuLogo->SetScale(MenuLogoScale);
	//���S���g
	MenuLogo->InitSub(L"Assets/sprite/MenuLogo_Nami.dds", MenuLogoNami.x, MenuLogoNami.y, 
		DefMenuLogoPosition, { 1.0f,1.0f,1.0f,1.0f }, SpriteNo);
	MenuLogo->InitSub(L"Assets/sprite/MenuLogo_Nami.dds", MenuLogoNami.x, MenuLogoNami.y,
		{ DefMenuLogoPosition.x + MenuLogoNami.x ,DefMenuLogoPosition.y ,DefMenuLogoPosition.z }, { 1.0f,1.0f,1.0f,1.0f }, SpriteNo);
	MenuLogo->InitSub(L"Assets/sprite/MenuLogoLight.dds", MenuLogoSize.x, MenuLogoSize.y,
		{ DefMenuLogoPosition.x - MenuMove ,DefMenuLogoPosition.y,DefMenuLogoPosition.z }, { 1.0f,1.0f,1.0f,1.0f }, SpriteNo);
	//���S����
	MenuLogo_Up = NewGO<SpriteRender>("MenuLogo_Up", SpriteNo);
	MenuLogo_Up->Init(L"Assets/sprite/MenuLogo_Up.dds", MenuLogoAccSize.x, MenuLogoAccSize.y, SpriteNo);
	MenuLogo_Up->SetPosition(DefMenuLogo_AccPosition);
	MenuLogo_Up->SetScale(MenuLogoScale);
	//���S�̃����_�[���[�h�ύX
	MenuLogo->ChangeRenderMode_Mask(Sprite_RenderMode::Overlay, 0);
	MenuLogo->ChangeRenderMode_Mask(Sprite_RenderMode::Overlay, 1);
	MenuLogo->ChangeRenderMode_Mask(Sprite_RenderMode::Add, 2);

	//���j���[
	float Y_Hosei = 0.0f;
	MenuCommand_Sprite1 = NewGO<SpriteRender>("MenuCommand_Sprite1", SpriteNo);
	MenuCommand_Sprite1->ChangeSliceSprite(MenuCommandWindowDefSize);
	MenuCommand_Sprite1->Set3Slice(MenuCommand_SideScale);
	MenuCommand_Sprite1->Init(L"Assets/sprite/window5.dds",
		MenuCommandWindowSize.x,
		MenuCommandWindowSize.y,
		SpriteNo);
	MenuCommand_Sprite1->SetPosition({ DefMenuCommandPosition.x + MenuMove ,
		DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
	MenuCommand_Font1 = NewGO<FontRender>("MenuCommand_Font1", SpriteNo);
	MenuCommand_Font1->SetText(Koumoku[Create]);
	MenuCommand_Font1->SetColor(TextColor);
	MenuCommand_Font1->SetScale(TextFontSize);
	MenuCommand_Font1->SetPosition({ DefMenuCommand_TextPosition.x + MenuMove ,
		DefMenuCommand_TextPosition.y + Y_Hosei });
	//
	Y_Hosei -= MenuCommand_YHosei;
	MenuCommand_Sprite2 = NewGO<SpriteRender>("MenuCommand_Sprite2", SpriteNo);
	MenuCommand_Sprite2->ChangeSliceSprite(MenuCommandWindowDefSize);
	MenuCommand_Sprite2->Set3Slice(MenuCommand_SideScale);
	MenuCommand_Sprite2->Init(L"Assets/sprite/window5.dds",
		MenuCommandWindowSize.x,
		MenuCommandWindowSize.y,
		SpriteNo);
	MenuCommand_Sprite2->SetPosition({ DefMenuCommandPosition.x + MenuMove ,
		DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
	MenuCommand_Font2 = NewGO<FontRender>("MenuCommand_Font2", SpriteNo);
	MenuCommand_Font2->SetText(Koumoku[Box_Release]);
	MenuCommand_Font2->SetColor(TextColor);
	MenuCommand_Font2->SetScale(TextFontSize);
	MenuCommand_Font2->SetPosition({ DefMenuCommand_TextPosition.x + MenuMove , 
		DefMenuCommand_TextPosition.y + Y_Hosei });
	//
	Y_Hosei -= MenuCommand_YHosei;
	MenuCommand_Sprite3 = NewGO<SpriteRender>("MenuCommand_Sprite3", SpriteNo);
	MenuCommand_Sprite3->ChangeSliceSprite(MenuCommandWindowDefSize);
	MenuCommand_Sprite3->Set3Slice(MenuCommand_SideScale);
	MenuCommand_Sprite3->Init(L"Assets/sprite/window5.dds",
		MenuCommandWindowSize.x,
		MenuCommandWindowSize.y,
		SpriteNo);
	MenuCommand_Sprite3->SetPosition({ DefMenuCommandPosition.x + MenuMove ,
		DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
	MenuCommand_Font3 = NewGO<FontRender>("MenuCommand_Font3", SpriteNo);
	MenuCommand_Font3->SetText(Koumoku[Library]);
	MenuCommand_Font3->SetColor(TextColor);
	MenuCommand_Font3->SetScale(TextFontSize);
	MenuCommand_Font3->SetPosition({ DefMenuCommand_TextPosition.x + MenuMove ,
		DefMenuCommand_TextPosition.y + Y_Hosei });
	//
	Y_Hosei -= MenuCommand_YHosei;
	MenuCommand_Sprite4 = NewGO<SpriteRender>("MenuCommand_Sprite4", SpriteNo);
	MenuCommand_Sprite4->ChangeSliceSprite(MenuCommandWindowDefSize);
	MenuCommand_Sprite4->Set3Slice(MenuCommand_SideScale);
	MenuCommand_Sprite4->Init(L"Assets/sprite/window5.dds",
		MenuCommandWindowSize.x,
		MenuCommandWindowSize.y,
		SpriteNo);
	MenuCommand_Sprite4->SetPosition({ DefMenuCommandPosition.x + MenuMove ,
		DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
	MenuCommand_Font4 = NewGO<FontRender>("MenuCommand_Font4", SpriteNo);
	MenuCommand_Font4->SetText(Koumoku[Save]);
	MenuCommand_Font4->SetColor(TextColor);
	MenuCommand_Font4->SetScale(TextFontSize);
	MenuCommand_Font4->SetPosition({ DefMenuCommand_TextPosition.x + MenuMove + SaveX_Hosei,
		DefMenuCommand_TextPosition.y + Y_Hosei });

	//�R�}���h�A�N�Z�T���[


	//������
	MenuSetumeiFont = NewGO<FontRender>("MenuSetumeiFont", SpriteNo);
	MenuSetumeiFont->SetText(L"");
	MenuSetumeiFont->SetColor(SetumeiTextColor);
	MenuSetumeiFont->SetScale(TextFontSize_Setumei);
	MenuSetumeiFont->SetPosition({ DefMenuWindow_2Position.x + DefSetumei_TextPosition.x + MenuMove ,
		DefMenuWindow_2Position.y + DefSetumei_TextPosition.y });

	//�J�[�\��
	MenuCommand_Cursor = NewGO<SpriteRender>("MenuCommand_Cursor", SpriteNo);
	MenuCommand_Cursor->Init(L"Assets/sprite/MenuCursor.dds", 60.0f, 50.0f, SpriteNo);
	MenuCommand_Cursor->SetPosition({ DefCursorPosition.x + MenuMove,DefCursorPosition.y,DefCursorPosition.z });
	MenuCommand_Cursor->SetAlpha(0.0f);

	//�o�^���Ă���
	m_spriteRenderList.push_back(MenuWindow);
	m_spriteRenderList.push_back(MenuWindow2);
	m_spriteRenderList.push_back(MenuButton);
	m_spriteRenderList.push_back(Menu_Mahojin);
	m_spriteRenderList.push_back(MenuLogo_Under);
	m_spriteRenderList.push_back(MenuLogo);
	m_spriteRenderList.push_back(MenuLogo_Up);
	m_spriteRenderList.push_back(MenuCommand_Sprite1);
	m_spriteRenderList.push_back(MenuCommand_Sprite2);
	m_spriteRenderList.push_back(MenuCommand_Sprite3);
	m_spriteRenderList.push_back(MenuCommand_Sprite4);
	m_spriteRenderList.push_back(MenuCommand_Cursor);
	//
	m_fontRenderList.push_back(MenuCommand_Font1);
	m_fontRenderList.push_back(MenuCommand_Font2);
	m_fontRenderList.push_back(MenuCommand_Font3);
	m_fontRenderList.push_back(MenuCommand_Font4);
	m_fontRenderList.push_back(MenuSetumeiFont);

}

GameMenu::~GameMenu()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
	//�R�}���h���폜
	DeleteMenuCommand();
}

void GameMenu::GameMenuUpdate() {

	//�擾
	SceneManager::GameMode GameMode = SceneManager::GetInstance()->GetGameMode();
	CVector2 MousePos = MouseSupporter::GetInstance()->GetMousePos_Sprite();
	int Left_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	int Right_Key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Right_Key);

	//���̍X�V
	GameMenu::Update_Effect(GameMode);
	GameMenu::Update_Command();
	if (GameMode == SceneManager::MenuMode) {
		GameMenu::Update_MenuEnter(Left_Key);
		GameMenu::Update_CommandNow();
	}

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
	case SceneManager::ActionMode:

		//���W�␳
		PosX += MenuMove;
		PosX2 += MenuMove;
		//�{�^���ƍ��W��v ���� �A�N�V�������[�h�Ȃ�{�^���̃X�v���C�g��傫������
		if (MenuButton->MouseOverMouse() == true &&
			GameMode == SceneManager::GameMode::ActionMode) {

			//����
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });
			//�t���O�ύX
			m_selectFlag = true;
			if (m_selectSE_Flag == false) {
				//SE
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");
				m_selectSE_Flag = true;
			}

			//���N���b�N���ꂽ�烁�j���[���J���A���[�h�����j���[���[�h�ɕύX����
			if (Left_Key == MouseSupporter::Release_Push) {

				SceneManager::GetInstance()->SetGameMode(SceneManager::GameMode::MenuMode);
				MenuLogoTimer = -1;
				//NoActive�̉摜���o�����Z�b�g
				MenuWindow2->SetAlpha(1.0f);
				MenuSetumeiFont->SetAlpha(1.0f);
				MenuCommand_Cursor->SetAlpha(1.0f);
				m_nowMenuCommand = MenuCommand::Create;	//�J�[�\���ʒu���Z�b�g
				m_menuMoveTimer = 0;
				EffekseerSupporter::GetInstance()->NoPostStop(true);
				m_commandNow = false;
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Menu_Open.wav");
				SceneManager::GetInstance()->GetSoundManagerInstance()->BGM_VolumeFade(MenuBGM_Volume, MenuBGM_FadeTime);

				//�R�}���h�̕`������Z�b�g
				Update_CommandDraw(true);

				//�ړ�
				MenuButton->Init(L"Assets/sprite/MenuButton_Back.dds", MenuButtonSize, MenuButtonSize, SpriteNo);

				for (int i = 0 ; i < m_spriteRenderList.size() ; i++) {

					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ + MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -(MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

				for (int i = 0; i < m_fontRenderList.size(); i++) {

					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ +MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ -(MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

			}

		}
		else {		//�����łȂ���Ζ߂�

			MenuButton->SetScale(1.0f);
			MenuButton->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			m_selectSE_Flag = false;
		}

		break;
	case SceneManager::MenuMode:
		//�{�^���ƍ��W��v ���� ���j���[���[�h�Ȃ�{�^���̃X�v���C�g��傫������
		if ((MenuButton->MouseOverMouse() == true &&
			GameMode == SceneManager::GameMode::MenuMode) ||
			Right_Key == MouseSupporter::New_Push) {

			//����
			MenuButton->SetScale(1.1f);
			MenuButton->SetMulColor({ 1.5f,1.5f,1.5f,1.0f });
			//�t���O�ύX
			m_selectFlag = true;
			if (m_selectSE_Flag == false) {
				//SE
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");
				m_selectSE_Flag = true;
			}

			//���N���b�N���ꂽ�烁�j���[����A���[�h���A�N�V�������[�h�ɕύX����
			if (Left_Key == MouseSupporter::Release_Push ||
				Right_Key == MouseSupporter::New_Push) {

				SceneManager::GetInstance()->SetGameMode(SceneManager::GameMode::ActionMode);
				MenuCommand_Cursor->SetAlpha(0.0f);
				EffekseerSupporter::GetInstance()->NoPostStop(false);
				m_commandEndFlag = true;
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Menu_Close.wav");
				SceneManager::GetInstance()->GetSoundManagerInstance()->BGM_VolumeFade(1.0f, MenuBGM_FadeTime);

				//�R�}���h�̃t�F�[�h�A�E�g
				if (m_menu_BoxAllDelete != nullptr) {
					m_menu_BoxAllDelete->CommandEnd();
				}

				//�ړ�
				MenuButton->Init(L"Assets/sprite/MenuButton.dds", MenuButtonSize, MenuButtonSize, SpriteNo);
				MenuLogo_Up->m_spriteSupporter.SpriteDelayReset();

				for (int i = 0; i < m_spriteRenderList.size(); i++) {

					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ (MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_spriteRenderList[i]->m_spriteSupporter.SpriteMove({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

				for (int i = 0; i < m_fontRenderList.size(); i++) {

					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, 0, true);
					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ (MenuMove + (MenuMove_Over * 2)),0.0f },
						MenuMoveTime, MenuMoveTime / 2, true);
					m_fontRenderList[i]->m_fontSupporter.FontMoveSet({ -MenuMove_Over,0.0f },
						MenuMoveTime / 2, MenuMoveTime + (MenuMoveTime / 2), true);

				}

			}

		}
		else {		//�����łȂ���Ζ߂�

			MenuButton->SetScale(1.0f);
			MenuButton->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			m_selectSE_Flag = false;
		}


		break;
	}

	//�^�C�}�[�X�V
	if (GameMode == SceneManager::MenuMode) {
		m_menuMoveTimer++;
	}

	//�R�}���h�I���`�F�b�N
	if (m_commandEndFlag == true) {
		m_commandEndTimer++;
		if (m_commandEndTimer == CommandEndLimit) {
			m_commandEndTimer = 0;
			m_commandEndFlag = false;
			m_commandNow = false;
			if (GameMode == SceneManager::MenuMode) {
				Update_CommandDraw(false);
				//NoActive�̉摜���o�����Z�b�g
				MenuWindow2->SetAlpha(1.0f);
				MenuSetumeiFont->SetAlpha(1.0f);
				MenuCommand_Cursor->SetAlpha(1.0f);
			}
		}
	}

}

void GameMenu::Update_Effect(const int& mode) {

	//���j���[���[�h�Ȃ��ʂɃu���[��������
	if (mode == SceneManager::GameMode::MenuMode) {

		float blur = SceneManager::GetInstance()->GetGameGraphicInstance()->m_blurIntensity;
		blur += BlurSpeed;
		if (blur > MaxBlur) {
			blur = MaxBlur;
		}
		SceneManager::GetInstance()->GetGameGraphicInstance()->m_blurIntensity = blur;

	}
	//�Ⴄ�Ȃ�߂�
	if (mode != SceneManager::GameMode::MenuMode) {

		float blur = SceneManager::GetInstance()->GetGameGraphicInstance()->m_blurIntensity;
		blur -= BlurSpeed;
		if (blur < 0.0f) {
			blur = 0.0f;
		}
		SceneManager::GetInstance()->GetGameGraphicInstance()->m_blurIntensity = blur;
	}

	//���j���[�̔g�ł�

	//���j���[���[�h�Ȃ�g���V�[�����X�ړ�
	if (mode == SceneManager::GameMode::MenuMode) {

		if (MenuLogoTimer == -1) {
			//����ړ��I

			//�}�X�N�X�v���C�g�̈ړ������Z�b�g
			MenuLogo->GetSubSpriteSupporter(0)->SpriteDelayReset();
			MenuLogo->GetSubSpriteSupporter(1)->SpriteDelayReset();
			
			MenuLogo_Up->SetRotation(CQuaternion::Identity());

			//�����ʒu�փ��[�v
			MenuLogo->SetPosition({ DefMenuLogoPosition.x - MenuMove ,
				DefMenuLogoPosition.y,DefMenuLogoPosition.z}, 0);
			MenuLogo->SetPosition({ DefMenuLogoPosition.x + MenuLogoNami.x - MenuMove ,
				DefMenuLogoPosition.y ,DefMenuLogoPosition.z }, 1);

			MenuLogo->GetSubSpriteSupporter(0)->SpriteMove({ -MenuLogoNami.x,0.0f }, MenuLogoMoveSpeed, 0, true);
			MenuLogo->GetSubSpriteSupporter(1)->SpriteMove({ -MenuLogoNami.x,0.0f }, MenuLogoMoveSpeed, 0, true);

			MenuLogo_Up->m_spriteSupporter.SpriteRotation(MenuAccRot, MenuLogo_AccRotSpeed, 0, false);

			MenuLogoRotTimer = 0;
			MenuLogoTimer++;
		}

		MenuLogoTimer++;
		MenuLogoRotTimer++;

		if (MenuLogoMoveSpeed -1 == MenuLogoTimer) {		//������ƕ␳
			//�ړ��X�V���ă^�C�}�[���Z�b�g

			//�Q���ׂč��ɂ�������E�Ɏ����Ă���
			CVector3 Pos1 = MenuLogo->GetPosition(0);
			CVector3 Pos2 = MenuLogo->GetPosition(1);

			if (Pos1.x < Pos2.x) {
				//0�Ԃ����ɂ���
				MenuLogo->SetPosition({ DefMenuLogoPosition.x + MenuLogoNami.x - MenuMove ,
					DefMenuLogoPosition.y ,DefMenuLogoPosition.z }, 0);				
			}
			else {
				//1�Ԃ����ɂ���
				MenuLogo->SetPosition({ DefMenuLogoPosition.x + MenuLogoNami.x - MenuMove ,
					DefMenuLogoPosition.y ,DefMenuLogoPosition.z }, 1);
			}

			//�ړ�
			MenuLogo->GetSubSpriteSupporter(0)->SpriteMove({ -MenuLogoNami.x,0.0f }, MenuLogoMoveSpeed, 0, true);
			MenuLogo->GetSubSpriteSupporter(1)->SpriteMove({ -MenuLogoNami.x,0.0f }, MenuLogoMoveSpeed, 0, true);

			MenuLogoTimer = 0;
		}

		//��]�p
		if (MenuLogoRotTimer == MenuLogo_AccRotSpeed) {
			MenuLogo_Up->m_spriteSupporter.SpriteRotation(-MenuAccRot, MenuLogoMoveSpeed, 0, false);
		}
		if (MenuLogoRotTimer == MenuLogo_AccRotSpeed * 2) {
			MenuLogo_Up->m_spriteSupporter.SpriteRotation(MenuAccRot, MenuLogoMoveSpeed, 0, false);
			MenuLogoRotTimer = 0;
		}

	}

}

/// <summary>
/// �R�}���h�̍X�V
/// </summary>
void GameMenu::Update_Command() {

	//�����������j���[�J���Ă܂��H
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::MenuMode) {
		return;
	}
	//�ړ��������ĂȂ��Ȃ���s�����܂���
	if (m_menuMoveTimer < MenuMoveTime) {
		return;
	}

	//�ⓚ���p�ō��E�ړ�����
	if (m_cursorMoveTimer == 0) {
		//�ړ���\��
		MenuCommand_Cursor->m_spriteSupporter.SpriteMove({ Cursor_YMove ,0.0f }, CursorMoveLimit / 2, 0, true);
		MenuCommand_Cursor->m_spriteSupporter.SpriteMove({ -Cursor_YMove ,0.0f }, CursorMoveLimit / 2, CursorMoveLimit / 2, true);
	}
	else if (m_cursorMoveTimer == CursorMoveLimit) {
		m_cursorMoveTimer = -1;	//ؾ��
	}
	m_cursorMoveTimer++;

	//�J�[�\���ړ��͏�ɂ��邪�A�R�}���h�X�V��t�̓R�}���h���s��Ȃ�
	if (m_commandNow == true) {
		return;
	}

	//�}�E�X�̓��͂őI�𒆂̃R�}���h���J�G�[��
	int now_delta = MouseSupporter::GetInstance()->GetWheelMove();		//�ړ���
	bool ChangeFlag = false;

	//�����J�[�\�����ǂꂩ�̃R�}���h�ɏd�Ȃ��Ă����烂�[�h�ύX�I
	if (((MenuCommand_Sprite1->MouseOverMouse() == true) ||
		(MenuCommand_Sprite2->MouseOverMouse() == true)  ||
		(MenuCommand_Sprite3->MouseOverMouse() == true)  ||
		(MenuCommand_Sprite4->MouseOverMouse() == true)) && m_selectOverFlag == false) {

		m_selectMode = true;		//�J�[�\���ʒu���Q�Ƃ��郂�[�h�ɕύX

	}

	if (m_selectMode == false) {
		//�ʒu�͊֌W�Ȃ��z�C�[�������擾����
		Update_CommandDelta(now_delta, ChangeFlag);
	}
	else if(m_selectMode == true && m_selectOverFlag == false){
		//�ʒu�����A�z�C�[�����삪�������ꍇ�̓��[�h�ύX����
		if (MenuCommand_Sprite1->MouseOverMouse() == true && 
			m_nowMenuCommand != GameMenu::Create) {
			ChangeFlag = true;
			m_nowMenuCommand = GameMenu::Create;
		}
		if (MenuCommand_Sprite2->MouseOverMouse() == true &&
			m_nowMenuCommand != GameMenu::Box_Release) {
			ChangeFlag = true;
			m_nowMenuCommand = GameMenu::Box_Release;
		}
		if (MenuCommand_Sprite3->MouseOverMouse() == true &&
			m_nowMenuCommand != GameMenu::Library) {
			ChangeFlag = true;
			m_nowMenuCommand = GameMenu::Library;
		}
		if (MenuCommand_Sprite4->MouseOverMouse() == true &&
			m_nowMenuCommand != GameMenu::Save) {
			ChangeFlag = true;
			m_nowMenuCommand = GameMenu::Save;
		}

		//�z�C�[���������I
		if (now_delta != 0) {
			Update_CommandDelta(now_delta, ChangeFlag);
			m_selectMode = false;
			m_selectOverFlag = true;
		}
	}
	
	//���[�h����
	if ((MenuCommand_Sprite1->MouseOverMouse() == false) &&
		(MenuCommand_Sprite2->MouseOverMouse() == false) &&
		(MenuCommand_Sprite3->MouseOverMouse() == false) &&
		(MenuCommand_Sprite4->MouseOverMouse() == false) &&
		m_selectOverFlag == true) {

		m_selectOverFlag_ = true;
	}
	if (((MenuCommand_Sprite1->MouseOverMouse() == true) ||
		(MenuCommand_Sprite2->MouseOverMouse() == true) ||
		(MenuCommand_Sprite3->MouseOverMouse() == true) ||
		(MenuCommand_Sprite4->MouseOverMouse() == true)) && m_selectOverFlag_ == true) {

		m_selectOverFlag_ = false;
		m_selectOverFlag = false;

	}

	//�X�V���ꂽ��G���X�V����
	if (ChangeFlag == true) {
		Update_CommandDraw(false);
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");	//SE
	}

}

/// <summary>
/// �R�}���h�̏㉺�ړ�
/// </summary>
void GameMenu::Update_CommandDelta(const int delta, bool& flag) {
	
	//�R�}���h���s���͓������Ȃ�
	if (m_commandNow == true) {
		return;
	}

	if (delta < 0) {	//�z�C�[����
		flag = true;
		switch (m_nowMenuCommand)
		{
		case GameMenu::Create:
			m_nowMenuCommand = GameMenu::Box_Release;
			break;
		case GameMenu::Box_Release:
			m_nowMenuCommand = GameMenu::Library;
			break;
		case GameMenu::Library:
			m_nowMenuCommand = GameMenu::Save;
			break;
		case GameMenu::Save:
			m_nowMenuCommand = GameMenu::Create;
			break;
		}
	}
	else if (delta > 0) {	//�z�C�[����
		flag = true;
		switch (m_nowMenuCommand)
		{
		case GameMenu::Create:
			m_nowMenuCommand = GameMenu::Save;
			break;
		case GameMenu::Box_Release:
			m_nowMenuCommand = GameMenu::Create;
			break;
		case GameMenu::Library:
			m_nowMenuCommand = GameMenu::Box_Release;
			break;
		case GameMenu::Save:
			m_nowMenuCommand = GameMenu::Library;
			break;
		}
	}

}

/// <summary>
/// �R�}���h�Ɛ������̕`��
/// </summary>
void GameMenu::Update_CommandDraw(bool drawStile) {

	//�������s���Ă���Ȃ璆�f
	if (m_commandNow == true) {
		return;
	}
	//�I�����Ȃ璆�f
	if (m_commandEndFlag == true) {
		return;
	}

	//�R�}���h�ʒu�̈ړ�
	m_cursorMoveTimer = 0;
	//���Z�b�g���Ȃ��ƃo�O��܂�
	MenuCommand_Cursor->m_spriteSupporter.SpriteDelayReset();
	{
		MenuCommand_Sprite1->m_spriteSupporter.SpriteDelayReset();
		MenuCommand_Font1->m_fontSupporter.FontDelayReset();
		MenuCommand_Sprite2->m_spriteSupporter.SpriteDelayReset();
		MenuCommand_Font2->m_fontSupporter.FontDelayReset();
		MenuCommand_Sprite3->m_spriteSupporter.SpriteDelayReset();
		MenuCommand_Font3->m_fontSupporter.FontDelayReset();
		MenuCommand_Sprite4->m_spriteSupporter.SpriteDelayReset();
		MenuCommand_Font4->m_fontSupporter.FontDelayReset();
	}

	if (drawStile == false) {
		MenuCommand_Cursor->SetPosition({ DefCursorPosition.x ,
			DefCursorPosition.y - (MenuCommand_YHosei * m_nowMenuCommand),DefCursorPosition.z });	//�R�}���hY�ʒu�͕␳����

		float Y_Hosei = 0.0f;
		MenuCommand_Sprite1->SetPosition({ DefMenuCommandPosition.x,
			DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
		MenuCommand_Font1->SetPosition({ DefMenuCommand_TextPosition.x,
			DefMenuCommand_TextPosition.y + Y_Hosei });
		Y_Hosei -= MenuCommand_YHosei;
		MenuCommand_Sprite2->SetPosition({ DefMenuCommandPosition.x,
			DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
		MenuCommand_Font2->SetPosition({ DefMenuCommand_TextPosition.x,
			DefMenuCommand_TextPosition.y + Y_Hosei });
		Y_Hosei -= MenuCommand_YHosei;
		MenuCommand_Sprite3->SetPosition({ DefMenuCommandPosition.x,
			DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
		MenuCommand_Font3->SetPosition({ DefMenuCommand_TextPosition.x,
			DefMenuCommand_TextPosition.y + Y_Hosei });
		Y_Hosei -= MenuCommand_YHosei;
		MenuCommand_Sprite4->SetPosition({ DefMenuCommandPosition.x,
			DefMenuCommandPosition.y + Y_Hosei,DefMenuCommandPosition.z });
		MenuCommand_Font4->SetPosition({ DefMenuCommand_TextPosition.x + SaveX_Hosei,
			DefMenuCommand_TextPosition.y + Y_Hosei });
	}
	else {
		MenuCommand_Cursor->SetPosition({ DefCursorPosition.x + MenuMove,
			DefCursorPosition.y - (MenuCommand_YHosei * m_nowMenuCommand),DefCursorPosition.z });	//�R�}���hY�ʒu�͕␳����
	}

	//�ʂ̍X�V
	switch (m_nowMenuCommand)
	{
	case GameMenu::Create:
		MenuCommand_Sprite1->SetAlpha(1.0f);
		MenuCommand_Font1->SetAlpha(1.0f);
		MenuCommand_Sprite2->SetAlpha(NoActiveAlpha);
		MenuCommand_Font2->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite3->SetAlpha(NoActiveAlpha);
		MenuCommand_Font3->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite4->SetAlpha(NoActiveAlpha);
		MenuCommand_Font4->SetAlpha(NoActiveAlpha);
		//
		MenuCommand_Sprite1->m_spriteSupporter.SpriteMove({ 0.0f,MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, 0, true);
		MenuCommand_Sprite1->m_spriteSupporter.SpriteMove({ 0.0f,-MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, MenuCommandSelectJumpTime, true);
		MenuCommand_Font1->m_fontSupporter.FontMoveSet({ 0.0f,MenuCommandSelectJumpY },
			MenuCommandSelectJumpTime, 0, true);
		MenuCommand_Font1->m_fontSupporter.FontMoveSet({ 0.0f,-MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, MenuCommandSelectJumpTime, true);
		break;
	case GameMenu::Box_Release:
		MenuCommand_Sprite1->SetAlpha(NoActiveAlpha);
		MenuCommand_Font1->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite2->SetAlpha(1.0f);
		MenuCommand_Font2->SetAlpha(1.0f);
		MenuCommand_Sprite3->SetAlpha(NoActiveAlpha);
		MenuCommand_Font3->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite4->SetAlpha(NoActiveAlpha);
		MenuCommand_Font4->SetAlpha(NoActiveAlpha);
		//
		MenuCommand_Sprite2->m_spriteSupporter.SpriteMove({ 0.0f,MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, 0, true);
		MenuCommand_Sprite2->m_spriteSupporter.SpriteMove({ 0.0f,-MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, MenuCommandSelectJumpTime, true);
		MenuCommand_Font2->m_fontSupporter.FontMoveSet({ 0.0f,MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, 0, true);
		MenuCommand_Font2->m_fontSupporter.FontMoveSet({ 0.0f,-MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, MenuCommandSelectJumpTime, true);
		break;
	case GameMenu::Library:
		MenuCommand_Sprite1->SetAlpha(NoActiveAlpha);
		MenuCommand_Font1->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite2->SetAlpha(NoActiveAlpha);
		MenuCommand_Font2->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite3->SetAlpha(1.0f);
		MenuCommand_Font3->SetAlpha(1.0f);
		MenuCommand_Sprite4->SetAlpha(NoActiveAlpha);
		MenuCommand_Font4->SetAlpha(NoActiveAlpha);
		//
		MenuCommand_Sprite3->m_spriteSupporter.SpriteMove({ 0.0f,MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, 0, true);
		MenuCommand_Sprite3->m_spriteSupporter.SpriteMove({ 0.0f,-MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, MenuCommandSelectJumpTime, true);
		MenuCommand_Font3->m_fontSupporter.FontMoveSet({ 0.0f,MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, 0, true);
		MenuCommand_Font3->m_fontSupporter.FontMoveSet({ 0.0f,-MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, MenuCommandSelectJumpTime, true);
		break;
	case GameMenu::Save:
		MenuCommand_Sprite1->SetAlpha(NoActiveAlpha);
		MenuCommand_Font1->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite2->SetAlpha(NoActiveAlpha);
		MenuCommand_Font2->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite3->SetAlpha(NoActiveAlpha);
		MenuCommand_Font3->SetAlpha(NoActiveAlpha);
		MenuCommand_Sprite4->SetAlpha(1.0f);
		MenuCommand_Font4->SetAlpha(1.0f);
		//
		MenuCommand_Sprite4->m_spriteSupporter.SpriteMove({ 0.0f,MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, 0, true);
		MenuCommand_Sprite4->m_spriteSupporter.SpriteMove({ 0.0f,-MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, MenuCommandSelectJumpTime, true);
		MenuCommand_Font4->m_fontSupporter.FontMoveSet({ 0.0f,MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, 0, true);
		MenuCommand_Font4->m_fontSupporter.FontMoveSet({ 0.0f,-MenuCommandSelectJumpY }, 
			MenuCommandSelectJumpTime, MenuCommandSelectJumpTime, true);
		break;
	}

	//�������̐ݒ�
	MenuSetumeiFont->SetText(SetumeiBun[m_nowMenuCommand]);

}

/// <summary>
/// �R�}���h�̌����t
/// </summary>
void GameMenu::Update_MenuEnter(const int& leftKey) {

	//�������s���Ă���Ȃ璆�f
	if (m_commandNow == true) {
		return;
	}
	//�I�����Ȃ璆�f
	if (m_commandEndFlag == true) {
		return;
	}
	//�߂�{�^���Ƀ}�E�X�I�[�o�[�Ȃ璆�f
	if (MenuButton->MouseOverMouse() == true) {
		return;
	}

	//�������肳�ꂽ��R�}���h������i���{�ꂪ���������j
	if (leftKey == MouseSupporter::Release_Push) {

		//����
		switch (m_nowMenuCommand)
		{
		case GameMenu::Create:
			m_menu_Create = new Menu_Create;
			break;
		case GameMenu::Box_Release:
			m_menu_BoxAllDelete = new Menu_BoxAllDelete;
			break;
		case GameMenu::Library:

			break;
		case GameMenu::Save:

			break;
		}

		//SE
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/OK.wav");
		//�R�}���h�𔼓�����
		GameMenu_NoActiveEffect();
		//�t���OTrue
		m_commandNow = true;
	}

}

/// <summary>
/// �R�}���h���e�̃A�b�v�f�[�g
/// </summary>
void GameMenu::Update_CommandNow() {

	//�����������j���[�J���Ă܂��H
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::MenuMode) {
		return;
	}
	//�������s���ĂȂ��Ȃ璆�f
	if (m_commandNow == false) {
		return;
	}
	//�I�����Ȃ璆�f
	if (m_commandEndFlag == true) {
		return;
	}

	//�R�}���h�ɉ����čX�V���I���`�F�b�N
	switch (m_nowMenuCommand)
	{
	case GameMenu::Create:

		break;
	case GameMenu::Box_Release:
		m_menu_BoxAllDelete->DeleteCheckUpdate();
		if (m_menu_BoxAllDelete->GetDeleteFlag() == true) {
			//�R�}���h�I��
			DeleteMenuCommand();
			m_commandEndFlag = true;
		}
		break;
	case GameMenu::Library:

		break;
	case GameMenu::Save:

		break;
	}

}

void GameMenu::GameMenu_NoActiveEffect() {

	//�S���������I
	MenuWindow2->SetAlpha(NoActiveAlpha);
	MenuCommand_Sprite1->SetAlpha(NoActiveAlpha);
	MenuCommand_Sprite2->SetAlpha(NoActiveAlpha);
	MenuCommand_Sprite3->SetAlpha(NoActiveAlpha);
	MenuCommand_Sprite4->SetAlpha(NoActiveAlpha);
	MenuCommand_Cursor->SetAlpha(NoActiveAlpha);
	MenuCommand_Font1->SetAlpha(NoActiveAlpha);
	MenuCommand_Font2->SetAlpha(NoActiveAlpha);
	MenuCommand_Font3->SetAlpha(NoActiveAlpha);
	MenuCommand_Font4->SetAlpha(NoActiveAlpha);
	MenuSetumeiFont->SetAlpha(NoActiveAlpha);
}

void GameMenu::DeleteMenuCommand() {

	if (m_menu_Create != nullptr) {
		delete m_menu_Create;
		m_menu_Create = nullptr;
	}
	if (m_menu_BoxAllDelete != nullptr) {
		delete m_menu_BoxAllDelete;
		m_menu_BoxAllDelete = nullptr;
	}

}