#pragma once
#include "system/CGameObjectManager.h"
#include "TransitionSprite.h"

/// <summary>
/// �g�����W�V���������s
/// �E�V���O���g��
/// </summary>
class TransitionGenerator : public IGameObject
{
	static TransitionGenerator* m_instance;
public:
	//�g�����W�V�������Ăяo���Ƃ��̂����O
	enum TransitionName {
		UnderSlide,	//������t�F�[�h
		NanameBox,	//�i�i���{�b�N�X
	};

	TransitionGenerator();
	~TransitionGenerator();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �C���X�^���X���擾�V���[�Y
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static TransitionGenerator* TransitionGenerator::GetInstance() {
		return m_instance;
	}

	//�g�����W�V�����̎��s
	void TransitionInit(
		const TransitionName& name,
		const int& MoveTime,
		const bool& mode
	);

private:
	TransitionSprite m_transitionSprite;

	struct Transition_Data {		//�X�v���C�g�p�^�[���f�[�^�\����
		wchar_t* SpriteName;	//�X�v���C�g�t�@�C����
	};

	Transition_Data Transition_DataList[3]{
		{ L"Assets/sprite/under.dds" },
		{ L"Assets/sprite/naname_box.dds" },
		{ L"Assets/sprite/levelUp_8F.dds" },
	};

	//�g�����W�V�����p
	int m_transitionLimit = 0;			//�g�����W�V�������s����
	float m_borderLine = 0.0f;			//�`�悳��郉�C��
	bool m_transitionMode = false;		//false�Ȃ�\���Atrue�Ȃ����
	bool m_nowTransitionFlag = false;	//�g�����W�V��������
	const float MoveSpeed = 10.0f;		//�v�Z�p

};

