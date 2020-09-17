#pragma once

/// <summary>
/// �����폜����R�}���h�I�I
/// </summary>
class Menu_BoxAllDelete
{
public:
	Menu_BoxAllDelete();
	~Menu_BoxAllDelete();

	//�����ՂŁ[�[�[�[�[�[��
	void DeleteCheckUpdate();

private:

	//������
	std::vector<SpriteRender*> m_spriteRenderList;
	std::vector<FontRender*> m_fontRenderList;

	//���������Ƃ��̊m�F���b�Z
	const wchar_t* CheckText = L"�S�Ă̔���j�󂵂�\n�}�i��S�񕜂��܂����H";
	const wchar_t* YesText = L"�j��";
	const wchar_t* NoText = L"��߂�";

	//��񂾁`�`
	SpriteRender* MenuWindow;		//�E�B���h�E
	SpriteRender* ButtonWindow_Left;	//���E�B���h�E
	SpriteRender* ButtonWindow_Right;	//�E�E�B���h�E
	//
	FontRender* Check_Font;	//�����܂����H�̃e�L�X�g
	FontRender* Yes_Font;	//�͂��̃e�L�X�g
	FontRender* No_Font;	//�������̃e�L�X�g

};

