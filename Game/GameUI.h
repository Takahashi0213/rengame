#pragma once
#include "system/CGameObjectManager.h"

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();
	void Update()override;
	void Render()override;


private:

	//�X�V�F�X
	void ManaUpdate();
	void LifeUpdate();

	//�����o�ϐ�

	//����
	const CVector3 AccScale = { 0.5f,0.5f,1.0f };
	const CVector3 AccDefPos = { -500.0f,250.0f,1.0f };

	//�Q�[�W
	const CVector4 RedGageColor = { 5.0f,0.2f,0.2f,1.0f };	//�Ԃ��Q�[�W�i�}�i�Q�[�W�j�̐F
	const CVector3 GagePos = { -350.0f,280.0f,1.0f };
	const float RedGageDownSpeed = 0.8f;

	//���C�t
	const CVector3 LifeScale = { 0.15f,0.15f,1.0f };
	const CVector3 LifeDefPos = { -520.0f,220.0f,1.0f };	//�i�X�E�Ɋ���Ă���
	const float LifeX_Hosei = 40.0f;

	//�X�v���C�g���낢��i��ނɂ����Render�̎g�p�L����ς���j�i������y�����邽�߁j

	//����
	Sprite* Accessory1;

	//�Q�[�W
	Sprite* GageUnder;
	SpriteRender* RedGage;
	SpriteRender* Gage;
	SpriteRender* MagicWindow;
	//�̗�
	//�n�[�g1��100���� Y_Slice�I
	SpriteRender* Life1;
	SpriteRender* Life2;
	SpriteRender* Life3;
	SpriteRender* Life4;
	SpriteRender* Life5;
	SpriteRender* Life6;
	SpriteRender* Life7;
	SpriteRender* Life8;
	SpriteRender* Life9;
	SpriteRender* Life10;
	Sprite* Life1_Window;
	Sprite* Life2_Window;
	Sprite* Life3_Window;
	Sprite* Life4_Window;
	Sprite* Life5_Window;
	Sprite* Life6_Window;
	Sprite* Life7_Window;
	Sprite* Life8_Window;
	Sprite* Life9_Window;
	Sprite* Life10_Window;

};

