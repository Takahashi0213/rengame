#pragma once

/// <summary>
/// �`���[�g���A���p������@�e�L�X�g
/// </summary>
class TutorialSupporter
{
public:
	TutorialSupporter();
	~TutorialSupporter();

	//�i�s�x
	enum Tutorial_Progress {
		Progress_Move,		//�ړ����悤
		Progress_Switch,	//�W�����v���ăX�C�b�`�𓥂���
		Progress_Box,		//���𐶐����ăX�C�b�`�ɏ悹�悤
		Progress_Enemy,		//���𐶐����ēG�ɂԂ��悤�i�����グ�j
		Progress_Enemy2,	//���𐶐����ēG�ɂԂ��悤�i������j
		Progress_Exit,		//���A�̏o����ڎw����
		ProgressNum,		//�v�f��
	};

	/// <summary>
	/// �`���[�g���A���̕\����ύX����
	/// </summary>
	/// <param name="Progress">�\�����e</param>
	void TutorialChange(const Tutorial_Progress Progress);

private:

	Tutorial_Progress m_tutorialProgress = Progress_Move;	//���݂̕\��

	FontRender* m_tutorialText = nullptr;					//�`���[�g���A���̕���

	//���e
	const wchar_t* Tutorial[ProgressNum]{
		L"���N���b�N�ňړ����Đ�֐i��",
		L"�r�o�`�b�d�L�[�ŃW�����v����\n�X�C�b�`�ɏ��",
		L"�E�N���b�N�Ŕ��������\n�X�C�b�`�ɏ悹��",
		L"���̋߂��łb�L�[�������Ĕ��������グ��",
		L"������x�b�L�[�������Ɣ��𓊂���",
		L"���A��E�o����",
	};

	//�萔
	const CVector2 TutorialTextPos = { 0.0f,-300.0f };		//�`���[�g���A�������̍��W
	
};

