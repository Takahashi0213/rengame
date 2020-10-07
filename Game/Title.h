#pragma once

#include "system/CGameObjectManager.h"

/// <summary>
/// �����Ƃ�I
/// �E�V���O���g��
/// </summary>
class Title : public IGameObject
{
	static Title* m_instance;
public:
	Title();
	~Title();
	void Update()override;
	void Render()override;

	//�R�}���h�̑I�����
	enum TitleCommand {
		No_Select,		//���I��
		Game_Start,		//�͂��߂���
		Game_Continue,	//�Â�����
		Game_End,		//�I��
	};

	//�R�}���h�̑I����Ԃ�Ԃ�
	//�I�񂾃R�}���h�̓���������SceneManager���s��
	const TitleCommand& GetCommand()const {
		return m_nowCommand;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static Title* Title::GetInstance() {
		return m_instance;
	}

private:

	//�R�}���h�����
	TitleCommand m_nowCommand = No_Select;	//�ŏ��͖��I��

};

