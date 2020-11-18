#pragma once

/// <summary>
/// ������@���펞�\������
/// �ꕔ�̑���͂����ōs����悤�ɂ�����
/// ���j���[���͔�\���ɂ���
/// </summary>
class UI_Supporter
{
public:
	UI_Supporter();
	~UI_Supporter();

	/// <summary>
	/// UI�T�|�[�^�[�̍X�V�i�Q�[���ɌĂ�ł��炤�j
	/// </summary>
	void UI_Suppoter_Update();

	/// <summary>
	/// �v���C���[��ݒ�
	/// </summary>
	void SetPlayer(Player* pl) {
		m_player = pl;
	}

	/// <summary>
	/// ��������UI�Ƀ}�E�X�I�[�o�[���Ă���H
	/// </summary>
	bool GetUI_MouseOver() {
		return m_mouseOver_Flag;
	}

private:
	/// <summary>
	/// �S���܂Ƃ߂�Alpha��ݒ�
	/// </summary>
	void SetAllAlpha(const float& alpha);
	/// <summary>
	/// �`���Ԃ��ς�邽�тɌĂ�
	/// </summary>
	void UI_Suppoter_DrawUpdate();

	//��r�i�Վ��j
	bool Vector4Hikaku(const CVector4& hoge, const CVector4& hoge2) {
		if (hoge.x != hoge2.x) {
			return false;
		}
		if (hoge.y != hoge2.y) {
			return false;
		}
		if (hoge.z != hoge2.z) {
			return false;
		}
		if (hoge.w != hoge2.w) {
			return false;
		}
		return true;
	}

	Player * m_player = nullptr;

	bool m_mouseOver_Flag = false;						//��������}�E�X�I�[�o�[���Ă���H

	//�X�v���C�g
	const CVector2 UI_UnderSize = { 120.0f,120.0f };	//UI�A���_�[�̃T�C�Y
	const CVector2 UI_IconSize = { 80.0f,80.0f };		//UI�A�C�R���̃T�C�Y
	const CVector2 UI_MouseSize = { 25.0f,35.0f };		//�}�E�X�A�C�R���̃T�C�Y

	const float UI_MouseOverScale = 1.05f;				//�}�E�X�I�[�o�[���̑傫��

	const CVector4 UI_NullColor = { 0.1f,0.1f,0.1f,1.0f };	//�󔒂̎��̐F

	SpriteRender* m_UI_Under1 = nullptr;				//����A�C�R���̉��i���j
	const CVector3 UI_Under1_Hosei = { 0.0f,80.0f,0.0f };	//���W�␳

	SpriteRender* m_UI_Under2 = nullptr;				//����A�C�R���̉��i���j
	const CVector3 UI_Under2_Hosei = { -80.0f,0.0f,0.0f };	//���W�␳

	SpriteRender* m_UI_Under3 = nullptr;				//����A�C�R���̉��i���j
	const CVector3 UI_Under3_Hosei = { 80.0f,0.0f,0.0f };	//���W�␳

	SpriteRender* m_UI_Under4 = nullptr;				//����A�C�R���̉��i���j
	const CVector3 UI_Under4_Hosei = { 0.0f,-80.0f,0.0f };	//���W�␳

	SpriteRender* m_UI_Icon1 = nullptr;					//����A�C�R���i���j
	SpriteRender* m_UI_Icon2 = nullptr;					//����A�C�R���i���j
	SpriteRender* m_UI_Icon3 = nullptr;					//����A�C�R���i���j
	SpriteRender* m_UI_Icon4 = nullptr;					//����A�C�R���i���j

	SpriteRender* m_UI_MouseCenter = nullptr;			//�}�E�X�A�C�R���i���N���b�N�j
	const CVector3 UI_Mouse_Hosei = { 100.0f,-80.0f,0.0f };	//���W�␳

	//�e�L�X�g
	const float UI_Font_Scale = 0.4f;					//�t�H���g�T�C�Y
	const float UI_Font_MouseScale = 0.3f;				//�}�E�X�����t�H���g�T�C�Y

	const CVector4 UI_Futi_Color = CVector4::White();	//�t�`�̐F
	const float FutiOffset = 2.0f;						//�t�`�̃I�t�Z�b�g

	FontRender* m_UI_Text1 = nullptr;					//���얼�i���j
	const CVector3 UI_Text1_Hosei = { -40.0f,90.0f,0.0f };	//���W�␳
	const CVector4 UI_Text1_Color = { 0.8f,0.7f,0.2f,1.0f };	//�t�H���g�J���[

	FontRender* m_UI_Text2 = nullptr;					//���얼�i���j
	const CVector3 UI_Text2_Hosei = { -10.0f,90.0f,0.0f };	//���W�␳
	const CVector4 UI_Text2_Color = { 0.7f,0.1f,0.8f,1.0f };	//�t�H���g�J���[

	FontRender* m_UI_Text3 = nullptr;					//���얼�i���j
	const CVector3 UI_Text3_Hosei = { -10.0f,90.0f,0.0f };	//���W�␳
	const CVector4 UI_Text3_Color = { 0.1f,0.1f,0.8f,1.0f };	//�t�H���g�J���[

	FontRender* m_UI_Text4 = nullptr;					//���얼�i���j
	const CVector3 UI_Text4_Hosei = { -10.0f,90.0f,0.0f };	//���W�␳
	const CVector4 UI_Text4_Color = { 0.8f,0.1f,0.1f,1.0f };	//�t�H���g�J���[

	FontRender* m_UI_Text_Center = nullptr;				//���얼�i���N���b�N�j
	const CVector3 UI_TextCenter_Hosei = { 70.0f,-110.0f,0.0f };	//���W�␳
	const CVector4 UI_TextCenter_Color = { 1.0f,0.5f,0.2f,1.0f };	//�t�H���g�J���[
	const float UI_TextCenter_X_Hosei = -20.0f;						//�␳

	//�萔
	const CVector3 UI_Position = { 420.0f,-190.0f,0.0f };	//��b���W
	const int SpritePriority = 8;							//�D��x

	//�}�E�X����̃e�L�X�g
	//�����E�̓I�~�b�g�i�N�ł��킩��Ǝv���̂Łc�j
	enum MouseUI_Text {
		MouseUI_Center_Action,	//���N���b�N�A�A�N�V�������[�h		
		MouseUI_Center_Create,	//���N���b�N�A�N���G�C�g���[�h		
		MouseUI_Num,			//�v�f��
	};
	//���e
	const wchar_t* Mouse_Text[MouseUI_Num]{
		L"�������",
		L"��������������",
	};

	//�`��֘A
	bool m_noDrawFlag = false;		//���͕`�悵�܂���
	enum UI_DrawState {
		NULL_Mode,				//��
		ActionMode_Normal,		//�A�N�V�������[�h�A�ʏ�
		ActionMode_BoxCatch,	//�������グ�̐�
		ActionMode_BoxUp,		//�������グ��
		CreateMode_Normal,		//�N���G�C�g���[�h
	};
	UI_DrawState m_ui_DrawMode = NULL_Mode;		//�`����

	//�N�C�b�N�A�N�V����
	enum QuickAction {
		NULL_Action,		//��
		Up_Action,			//��{�^��
		Left_Action,		//���{�^��
		Right_Action,		//�E�{�^��
		Down_Action,		//���{�^��
	};

};

