#include "stdafx.h"
#include "GameEffect.h"

GameEffect* GameEffect::m_instance = nullptr;

GameEffect::GameEffect()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�������珀��(/�E�ցE)/
	m_stand.StandInit();
	m_message.MessageInit();
}


GameEffect::~GameEffect()
{	
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

//��������`�`�`GameEffect_Stand

void GameEffect_Stand::StandInit() {

	//�ݒ�
	m_standSprite = NewGO<SpriteRender>("StandSprite", StandSpritePriority);
}

void GameEffect_Stand::StandControl(Stand_Name stand, Stand_Command command) {

	//�R�}���h���e�ŕ���
	switch (command)
	{
	case GameEffect_Stand::New_Stand:
		m_standSprite->Init(Game_Stand_Data[stand].SpriteName,
			Game_Stand_Data[stand].High,
			Game_Stand_Data[stand].Wide,
			StandSpritePriority);
		m_standSprite->SetScale(StandDefScale);
		if (m_standFlag == false) {
			m_standSprite->SetPosition(StandDefPos_Move);
			m_standSprite->m_spriteSupporter.SpriteMove(StandDefPos, 6, 0);
			m_standSprite->m_spriteSupporter.SpriteMove(StandDefPos2, 4, 6);
			m_standFlag = true;
		}
		else {
			m_standSprite->SetPosition({ StandDefPos2.x,StandDefPos2.y,0.0f });
		}
		break;
	case GameEffect_Stand::Delete_Stand:
		break;
	case GameEffect_Stand::Jump_Stand:
		if (m_standFlag == true) {
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,80.0f }, 4, 0, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,-80.0f }, 4, 4, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,20.0f }, 2, 8, true);
			m_standSprite->m_spriteSupporter.SpriteMove({ 0.0f,-20.0f }, 2, 10, true);
		}
		break;
	}

}

//��������`�`�`GameEffect_Message

void GameEffect_Message::MessageInit() {

	//�D��x��ݒ�
	m_windowSprite = NewGO<SpriteRender>("WindowSprite", WindowSpritePriority);
	m_messageFont = NewGO<FontRender>("MessageFont", MessageFontPriority);

	//�摜��ݒ�

}