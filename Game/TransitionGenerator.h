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
		Mesh,		//���b�V��
		Circle,		//�~
		TransitionName_Nom	//�f�[�^��
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
		const bool& mode,
		const bool& loadingFlag = false		//true�ɂ���ƃ��[�f�B���O�A�j���[�V�����������ɕ\�������
	);

private:
	TransitionSprite m_transitionSprite;
	SpriteRender* m_loadingSprite = nullptr;	//���[�f�B���O�A�j���[�V����

	struct Transition_Data {		//�X�v���C�g�p�^�[���f�[�^�\����
		wchar_t* SpriteName;		//�X�v���C�g�t�@�C����
	};

	//�g�����W�V�����̑f�ރX�v���C�g�ꗗ
	Transition_Data Transition_DataList[TransitionName_Nom]{
		{ L"Assets/sprite/under.dds" },
		{ L"Assets/sprite/naname_box.dds" },
		{ L"Assets/sprite/mesh.dds" },
		{ L"Assets/sprite/circle_b.dds" },
	};

	//�g�����W�V�����p
	int m_transitionLimit = 0;			//�g�����W�V�������s����
	float m_borderLine = 0.0f;			//�`�悳���{�[�_�[���C��
	bool m_transitionMode = false;		//false�Ȃ�\���Atrue�Ȃ����
	bool m_nowTransitionFlag = false;	//�g�����W�V������
	const float MoveSpeed = 10.0f;		//�v�Z�p

};

