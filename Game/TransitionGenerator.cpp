#include "stdafx.h"
#include "TransitionGenerator.h"

TransitionGenerator* TransitionGenerator::m_instance = nullptr;

TransitionGenerator::TransitionGenerator()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}
	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


TransitionGenerator::~TransitionGenerator()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void TransitionGenerator::Update() {

	if (m_borderLine < 0.0f) {
		m_nowTransitionFlag = false;
	}
	if (m_borderLine > MoveSpeed) {
		m_nowTransitionFlag = false;
	}

	if (m_nowTransitionFlag == true) {
		if (m_transitionMode == false) {
			m_borderLine += (1.0f / m_transitionLimit)*MoveSpeed;
		}
		else {
			m_borderLine -= (1.0f / m_transitionLimit)*MoveSpeed;
		}
		m_transitionSprite.m_alpha = m_borderLine;
	}

	m_transitionSprite.Sprite_Update();

	if (m_loadingSprite != nullptr) {
		m_loadingSprite->Update();
	}

}
void TransitionGenerator::Render() {

	m_transitionSprite.Sprite_Draw();
	if (m_loadingSprite != nullptr) {
		m_loadingSprite->Render();
	}
}

/// <summary>
/// �g�����W�V�����̊J�n
/// false�Ȃ�\���Atrue�Ȃ����
/// </summary>
/// <remarks>
/// 
/// ���T���v���R�[�h
/// 
/// //�΂߃{�b�N�X�A60�t���[�������ĕ\��
/// TransitionInit(TransitionName::NanameBox, 60, false);
/// 
/// </remarks>
void TransitionGenerator::TransitionInit(
	const TransitionName& name, 
	const int& MoveTime,
	const bool& mode,
	const bool& loadingFlag
) {

	//�����Ă���
	m_nowTransitionFlag = true;
	m_transitionLimit = MoveTime;
	m_transitionMode = mode;
	if (mode == false) {
		m_borderLine = 0.0f;
	}
	else {
		m_borderLine = MoveSpeed / 2.0f;
	}
	//�Ԃ����݂܂�
	m_transitionSprite.Sprite_Init(Transition_DataList[name].SpriteName, FRAME_BUFFER_W, FRAME_BUFFER_H);

	//���[�f�B���O�A�j���[�V����
	if (loadingFlag == true && m_loadingSprite == nullptr && mode == false) {
		//�\��
		m_loadingSprite = new SpriteRender;
		m_loadingSprite->SetPosition(SceneManager::GetInstance()->GetGameGraphicInstance()->LoadingAnimePos);
		m_loadingSprite->Init(L"Assets/sprite/Loading_6F.dds",
			130.0f, 480.0f, 10);
		m_loadingSprite->SetHighPattern(6, 0);
		m_loadingSprite->m_spriteSupporter.SpritePattern(1, true, 0);
	}
	if (loadingFlag == true && m_loadingSprite != nullptr && mode == true) {
		//�폜
		delete m_loadingSprite;
		m_loadingSprite = nullptr;
	}

}