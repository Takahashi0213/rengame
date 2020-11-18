#include "stdafx.h"
#include "UI_Supporter.h"
#include "GameSystem/Box/BoxMaker.h"

//SceneManager::GameMode m_backupMode = SceneManager::GameMode::Null_Mode;	//�Ō�̃��[�h

UI_Supporter::UI_Supporter()
{
	//UI�A���_�[
	m_UI_Under1 = NewGO<SpriteRender>("UI_Under1", SpritePriority);
	m_UI_Under1->Init(L"Assets/sprite/UI_Under1.dds",
		UI_UnderSize.x,
		UI_UnderSize.y,
		SpritePriority);
	m_UI_Under1->SetPosition(UI_Position + UI_Under1_Hosei);

	m_UI_Under2 = NewGO<SpriteRender>("UI_Under2", SpritePriority);
	m_UI_Under2->Init(L"Assets/sprite/UI_Under2.dds",
		UI_UnderSize.x,
		UI_UnderSize.y,
		SpritePriority);
	m_UI_Under2->SetPosition(UI_Position + UI_Under2_Hosei);

	m_UI_Under3 = NewGO<SpriteRender>("UI_Under3", SpritePriority);
	m_UI_Under3->Init(L"Assets/sprite/UI_Under3.dds",
		UI_UnderSize.x,
		UI_UnderSize.y,
		SpritePriority);
	m_UI_Under3->SetPosition(UI_Position + UI_Under3_Hosei);

	m_UI_Under4 = NewGO<SpriteRender>("UI_Under4", SpritePriority);
	m_UI_Under4->Init(L"Assets/sprite/UI_Under4.dds",
		UI_UnderSize.x,
		UI_UnderSize.y,
		SpritePriority);
	m_UI_Under4->SetPosition(UI_Position + UI_Under4_Hosei);

	//�A�C�R��
	m_UI_Icon1 = NewGO<SpriteRender>("UI_Icon1", SpritePriority);
	m_UI_Icon1->Init(L"Assets/sprite/Supporter_Jump.dds",	//�_�~�[
		UI_IconSize.x,
		UI_IconSize.y,
		SpritePriority);
	m_UI_Icon1->SetPosition(UI_Position + UI_Under1_Hosei);

	m_UI_Icon2 = NewGO<SpriteRender>("UI_Icon2", SpritePriority);
	m_UI_Icon2->Init(L"Assets/sprite/Supporter_Jump.dds",	//�_�~�[
		UI_IconSize.x,
		UI_IconSize.y,
		SpritePriority);
	m_UI_Icon2->SetPosition(UI_Position + UI_Under2_Hosei);

	m_UI_Icon3 = NewGO<SpriteRender>("UI_Icon3", SpritePriority);
	m_UI_Icon3->Init(L"Assets/sprite/Supporter_Jump.dds",	//�_�~�[
		UI_IconSize.x,
		UI_IconSize.y,
		SpritePriority);
	m_UI_Icon3->SetPosition(UI_Position + UI_Under3_Hosei);

	m_UI_Icon4 = NewGO<SpriteRender>("UI_Icon4", SpritePriority);
	m_UI_Icon4->Init(L"Assets/sprite/Supporter_Jump.dds",	//�_�~�[
		UI_IconSize.x,
		UI_IconSize.y,
		SpritePriority);
	m_UI_Icon4->SetPosition(UI_Position + UI_Under4_Hosei);

	//�}�E�X�A�C�R��
	m_UI_MouseCenter = NewGO<SpriteRender>("UI_MouseCenter", SpritePriority);
	m_UI_MouseCenter->Init(L"Assets/sprite/Mouse_Center.dds",
		UI_MouseSize.x,
		UI_MouseSize.y,
		SpritePriority);
	m_UI_MouseCenter->SetPosition(UI_Position + UI_Mouse_Hosei);

	//UI�e�L�X�g
	CVector3 font_pos;
	m_UI_Text1 = NewGO<FontRender>("UI_Font1", SpritePriority);
	m_UI_Text1->SetText(L"A");	//�_�~�[
	m_UI_Text1->SetColor(UI_Text1_Color);
	m_UI_Text1->SetScale(UI_Font_Scale);
	font_pos = UI_Position + UI_Under1_Hosei + UI_Text1_Hosei;
	m_UI_Text1->SetPosition({ font_pos.x,font_pos.y });
	m_UI_Text1->SetShadowParam(true, FutiOffset, UI_Futi_Color);

	m_UI_Text2 = NewGO<FontRender>("UI_Font2", SpritePriority);
	m_UI_Text2->SetText(L"B");	//�_�~�[
	m_UI_Text2->SetColor(UI_Text2_Color);
	m_UI_Text2->SetScale(UI_Font_Scale);
	font_pos = UI_Position + UI_Under2_Hosei + UI_Text2_Hosei;
	m_UI_Text2->SetPosition({ font_pos.x,font_pos.y });
	m_UI_Text2->SetShadowParam(true, FutiOffset, UI_Futi_Color);

	m_UI_Text3 = NewGO<FontRender>("UI_Font3", SpritePriority);
	m_UI_Text3->SetText(L"C");	//�_�~�[
	m_UI_Text3->SetColor(UI_Text3_Color);
	m_UI_Text3->SetScale(UI_Font_Scale);
	font_pos = UI_Position + UI_Under3_Hosei + UI_Text3_Hosei;
	m_UI_Text3->SetPosition({ font_pos.x,font_pos.y });
	m_UI_Text3->SetShadowParam(true, FutiOffset, UI_Futi_Color);

	m_UI_Text4 = NewGO<FontRender>("UI_Font4", SpritePriority);
	m_UI_Text4->SetText(L"D");	//�_�~�[
	m_UI_Text4->SetColor(UI_Text4_Color);
	m_UI_Text4->SetScale(UI_Font_Scale);
	font_pos = UI_Position + UI_Under4_Hosei + UI_Text4_Hosei;
	m_UI_Text4->SetPosition({ font_pos.x,font_pos.y });
	m_UI_Text4->SetShadowParam(true, FutiOffset, UI_Futi_Color);

	//�}�E�X�e�L�X�g
	m_UI_Text_Center = NewGO<FontRender>("UI_FontCenter", SpritePriority);
	m_UI_Text_Center->SetText(L"�}�E�X�̑������");	//�_�~�[
	m_UI_Text_Center->SetColor(UI_TextCenter_Color);
	m_UI_Text_Center->SetScale(UI_Font_MouseScale);
	font_pos = UI_Position + UI_TextCenter_Hosei;
	m_UI_Text_Center->SetPosition({ font_pos.x,font_pos.y });
	m_UI_Text_Center->SetShadowParam(true, FutiOffset, UI_Futi_Color);

}


UI_Supporter::~UI_Supporter()
{
	DeleteGO(m_UI_Under1);
	DeleteGO(m_UI_Under2);
	DeleteGO(m_UI_Under3);
	DeleteGO(m_UI_Under4);
	DeleteGO(m_UI_Icon1);
	DeleteGO(m_UI_Icon2);
	DeleteGO(m_UI_Icon3);
	DeleteGO(m_UI_Icon4);
	DeleteGO(m_UI_MouseCenter);
	DeleteGO(m_UI_Text1);
	DeleteGO(m_UI_Text2);
	DeleteGO(m_UI_Text3);
	DeleteGO(m_UI_Text4);
	DeleteGO(m_UI_Text_Center);
}

void UI_Supporter::UI_Suppoter_Update() {

	SceneManager::GameMode now_gameMode = SceneManager::GetInstance()->GetGameMode();

	//�A�N�V�������[�h�ł��N���G�C�g���[�h�łȂ� �܂��� �C�x���g�� �ł���Δ�\���ɂ���
	if ((now_gameMode != SceneManager::ActionMode && now_gameMode != SceneManager::CreateMode) ||
		SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true)
	{
		if (m_noDrawFlag == false) {
			SetAllAlpha(0.0f);
			m_noDrawFlag = true;
		}
		return;		//�����I��
	}
	//�߂�
	if (m_noDrawFlag == true) {
		SetAllAlpha(1.0f);
		m_noDrawFlag = false;
	}

	//�X�V����
	UI_DrawState nowState = NULL_Mode;
	if (now_gameMode == SceneManager::ActionMode) {
		if (m_player->GetBoxUpFlag() == true && m_player->GetBoxUpDownFlag() == false) {
			nowState = ActionMode_BoxUp;		//�������グ��
		}
		else {
			if (m_player->GetBoxSearchFlag() == true && m_player->GetBoxUpDownFlag() == false) {
				nowState = ActionMode_BoxCatch;	//�������グ�̐�
			}
			else {
				nowState = ActionMode_Normal;	//�A�N�V�������[�h�i�����Ȃ��j
			}
		}
	}
	if (now_gameMode == SceneManager::CreateMode) {
		nowState = CreateMode_Normal;		//�N���G�C�g���[�h
	}
	//�X�V���ꂽ�Ȃ�`����e���ύX����
	if (nowState != m_ui_DrawMode) {
		m_ui_DrawMode = nowState;
		UI_Suppoter_DrawUpdate();
	}

	//�N�C�b�N�A�N�V����
	QuickAction quickAction = NULL_Action;
	if (m_UI_Under1->MouseOverMouse() == true && Vector4Hikaku(m_UI_Under1->GetMulColor(), UI_NullColor) == false) {
		quickAction = Up_Action;
	}
	if (m_UI_Under2->MouseOverMouse() == true && Vector4Hikaku(m_UI_Under2->GetMulColor(), UI_NullColor) == false) {
		quickAction = Left_Action;
	}
	if (m_UI_Under3->MouseOverMouse() == true && Vector4Hikaku(m_UI_Under3->GetMulColor(), UI_NullColor) == false) {
		quickAction = Right_Action;
	}
	if (m_UI_Under4->MouseOverMouse() == true && Vector4Hikaku(m_UI_Under4->GetMulColor(), UI_NullColor) == false) {
		quickAction = Down_Action;
	}
	//�}�E�X�I�[�o�[�t���O�̍X�V
	if (quickAction == NULL_Action) {
		m_mouseOver_Flag = false;
	}
	else {
		m_mouseOver_Flag = true;
	}

	//�J�[�\���g�嗦�ύX
	if (quickAction == Up_Action) {
		m_UI_Under1->SetScale(UI_MouseOverScale);
	}
	else {
		m_UI_Under1->SetScale(1.0f);
	}
	if (quickAction == Left_Action) {
		m_UI_Under2->SetScale(UI_MouseOverScale);
	}
	else {
		m_UI_Under2->SetScale(1.0f);
	}
	if (quickAction == Right_Action) {
		m_UI_Under3->SetScale(UI_MouseOverScale);
	}
	else {
		m_UI_Under3->SetScale(1.0f);
	}
	if (quickAction == Down_Action) {
		m_UI_Under4->SetScale(UI_MouseOverScale);
	}
	else {
		m_UI_Under4->SetScale(1.0f);
	}

	//�N���b�N�󂯕t��
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	if (quickAction != NULL_Action && key == MouseSupporter::Release_Push) {
		//���삷��
		switch (m_ui_DrawMode)
		{
		case UI_Supporter::ActionMode_Normal:
			if (quickAction == Up_Action) {
				//�W�����v
				m_player->PlayerJump();
			}
			break;
		case UI_Supporter::ActionMode_BoxCatch:
			if (quickAction == Up_Action) {
				//�W�����v
				m_player->PlayerJump();
			}
			if (quickAction == Left_Action) {
				//�������グ
				m_player->PublicBoxCatchAndThrow();
			}
			break;
		case UI_Supporter::ActionMode_BoxUp:
			if (quickAction == Up_Action) {
				//�W�����v
				m_player->PlayerJump();
			}
			if (quickAction == Left_Action) {
				//������
				m_player->PublicBoxCatchAndThrow();
			}
			if (quickAction == Right_Action) {
				//���u��
				m_player->PublicBoxPut();
			}
			if (quickAction == Down_Action) {
				//���폜
				m_player->PublicBoxDelete();
			}
			break;
		case UI_Supporter::CreateMode_Normal:
			if (quickAction == Up_Action) {
				//�A���h�D
				BoxMaker::GetInstance()->BoxUndo();
			}
			break;
		}
	}

}

void UI_Supporter::SetAllAlpha(const float& alpha) {
	//�X�v���C�g
	m_UI_Under1->SetAlpha(alpha);
	m_UI_Under2->SetAlpha(alpha);
	m_UI_Under3->SetAlpha(alpha);
	m_UI_Under4->SetAlpha(alpha);
	m_UI_Icon1->SetAlpha(alpha);
	m_UI_Icon2->SetAlpha(alpha);
	m_UI_Icon3->SetAlpha(alpha);
	m_UI_Icon4->SetAlpha(alpha);
	m_UI_MouseCenter->SetAlpha(alpha);
	//�e�L�X�g
	m_UI_Text1->SetAlpha(alpha);
	m_UI_Text2->SetAlpha(alpha);
	m_UI_Text3->SetAlpha(alpha);
	m_UI_Text4->SetAlpha(alpha);
	m_UI_Text1->SetShadowParam(true, FutiOffset, { UI_Futi_Color.x,UI_Futi_Color.y,UI_Futi_Color.z,alpha });
	m_UI_Text2->SetShadowParam(true, FutiOffset, { UI_Futi_Color.x,UI_Futi_Color.y,UI_Futi_Color.z,alpha });
	m_UI_Text3->SetShadowParam(true, FutiOffset, { UI_Futi_Color.x,UI_Futi_Color.y,UI_Futi_Color.z,alpha });
	m_UI_Text4->SetShadowParam(true, FutiOffset, { UI_Futi_Color.x,UI_Futi_Color.y,UI_Futi_Color.z,alpha });
	m_UI_Text_Center->SetAlpha(alpha);
	m_UI_Text_Center->SetShadowParam(true, FutiOffset, { UI_Futi_Color.x,UI_Futi_Color.y,UI_Futi_Color.z,alpha });
}

void UI_Supporter::UI_Suppoter_DrawUpdate() {

	wchar_t text[MAX_PATH];
	CVector3 font_pos = CVector3::Zero();

	switch (m_ui_DrawMode)
	{
	case UI_Supporter::ActionMode_Normal:
		//�A�N�V�������[�h�ύX���̕`��
		m_UI_Icon1->Init(L"Assets/sprite/Supporter_Jump.dds",
			UI_IconSize.x,
			UI_IconSize.y,
			SpritePriority);
		m_UI_Text1->SetText(L"�r�o�`�b�d");
		//���͋󔒂ɂ���
		m_UI_Under2->SetMulColor(UI_NullColor);
		m_UI_Under3->SetMulColor(UI_NullColor);
		m_UI_Under4->SetMulColor(UI_NullColor);
		m_UI_Icon2->Init(L"", 0.0f, 0.0f, SpritePriority);
		m_UI_Icon3->Init(L"", 0.0f, 0.0f, SpritePriority);
		m_UI_Icon4->Init(L"", 0.0f, 0.0f, SpritePriority);
		m_UI_Text2->SetText(L"");
		m_UI_Text3->SetText(L"");
		m_UI_Text4->SetText(L"");
		//�}�E�X�e�L�X�g
		m_UI_Text_Center->SetText(Mouse_Text[MouseUI_Center_Action]);
		font_pos = UI_Position + UI_TextCenter_Hosei;
		m_UI_Text_Center->SetPosition({ font_pos.x,font_pos.y });
		break;
	case UI_Supporter::ActionMode_BoxCatch:
		//�������グ��Ԃ̕`��
		m_UI_Icon1->Init(L"Assets/sprite/Supporter_Jump.dds",
			UI_IconSize.x,
			UI_IconSize.y,
			SpritePriority);
		m_UI_Text1->SetText(L"�r�o�`�b�d");
		//�����グ��
		m_UI_Under2->SetMulColor(CVector4::White());
		m_UI_Icon2->Init(L"Assets/sprite/Supporter_BoxUp.dds",
			UI_IconSize.x,
			UI_IconSize.y,
			SpritePriority);
		mbstowcs_s(0, text, GameData::GetInstance()->GetBoxCatchKey_(), sizeof(char));
		//mbstowcs(text, GameData::GetInstance()->GetBoxCatchKey_(), sizeof(char));
		m_UI_Text2->SetText(text);
		//���͋󔒂ɂ���
		m_UI_Under3->SetMulColor(UI_NullColor);
		m_UI_Under4->SetMulColor(UI_NullColor);
		m_UI_Icon3->Init(L"", 0.0f, 0.0f, SpritePriority);
		m_UI_Icon4->Init(L"", 0.0f, 0.0f, SpritePriority);
		m_UI_Text3->SetText(L"");
		m_UI_Text4->SetText(L"");
		//�}�E�X�e�L�X�g
		m_UI_Text_Center->SetText(Mouse_Text[MouseUI_Center_Action]);
		font_pos = UI_Position + UI_TextCenter_Hosei;
		m_UI_Text_Center->SetPosition({ font_pos.x,font_pos.y });
		break;
	case UI_Supporter::ActionMode_BoxUp:
		//�������グ��Ԃ̕`��
		m_UI_Icon1->Init(L"Assets/sprite/Supporter_Jump.dds",
			UI_IconSize.x,
			UI_IconSize.y,
			SpritePriority);
		m_UI_Text1->SetText(L"�r�o�`�b�d");
		//������
		m_UI_Under2->SetMulColor(CVector4::White());
		m_UI_Icon2->Init(L"Assets/sprite/Supporter_BoxThrow.dds",
			UI_IconSize.x,
			UI_IconSize.y,
			SpritePriority);
		mbstowcs_s(0, text, GameData::GetInstance()->GetBoxCatchKey_(), sizeof(char));
		m_UI_Text2->SetText(text);
		//�u��
		m_UI_Under3->SetMulColor(CVector4::White());
		m_UI_Icon3->Init(L"Assets/sprite/Supporter_BoxPut.dds",
			UI_IconSize.x,
			UI_IconSize.y,
			SpritePriority);
		mbstowcs_s(0, text, GameData::GetInstance()->GetBoxPutKey_(), sizeof(char));
		m_UI_Text3->SetText(text);
		//�폜
		m_UI_Under4->SetMulColor(CVector4::White());
		m_UI_Icon4->Init(L"Assets/sprite/Supporter_Delete.dds",
			UI_IconSize.x,
			UI_IconSize.y,
			SpritePriority);
		mbstowcs_s(0, text, GameData::GetInstance()->GetBoxDeleteKey_(), sizeof(char));
		m_UI_Text4->SetText(text);
		//�}�E�X�e�L�X�g
		m_UI_Text_Center->SetText(Mouse_Text[MouseUI_Center_Action]);
		font_pos = UI_Position + UI_TextCenter_Hosei;
		m_UI_Text_Center->SetPosition({ font_pos.x,font_pos.y });
		break;
	case UI_Supporter::CreateMode_Normal:
		//�N���G�C�g���[�h�ύX���̕`��
		m_UI_Icon1->Init(L"Assets/sprite/Supporter_Undo.dds",
			UI_IconSize.x,
			UI_IconSize.y,
			SpritePriority);
		m_UI_Text1->SetText(L"�b�s�q�k�{�y");
		//���͋󔒂ɂ���
		m_UI_Under2->SetMulColor(UI_NullColor);
		m_UI_Under3->SetMulColor(UI_NullColor);
		m_UI_Under4->SetMulColor(UI_NullColor);
		m_UI_Icon2->Init(L"", 0.0f, 0.0f, SpritePriority);
		m_UI_Icon3->Init(L"", 0.0f, 0.0f, SpritePriority);
		m_UI_Icon4->Init(L"", 0.0f, 0.0f, SpritePriority);
		m_UI_Text2->SetText(L"");
		m_UI_Text3->SetText(L"");
		m_UI_Text4->SetText(L"");
		//�}�E�X�e�L�X�g
		m_UI_Text_Center->SetText(Mouse_Text[MouseUI_Center_Create]);
		font_pos = UI_Position + UI_TextCenter_Hosei;
		m_UI_Text_Center->SetPosition({ font_pos.x + UI_TextCenter_X_Hosei,font_pos.y });
		break;
	}

}