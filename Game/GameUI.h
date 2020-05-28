#pragma once
#include "system/CGameObjectManager.h"
#include "GameMenu.h"

/// <summary>
/// �Q�[����UI���܂Ƃ߂�����
/// �E�V���O���g��
/// </summary>
class GameUI : public IGameObject
{
	static GameUI* m_instance;
public:
	GameUI();
	~GameUI();
	void Update()override;
	void Render()override;

	//�Ăяo�����o

	/// <summary>
	/// �Ăяo�������ŁI�}�i�o�[���V�F�C�N������
	/// </summary>
	void ManaShake() {
		GageUnder->m_spriteSupporter.SpriteShake({ m_manaGageShakeData.MoveX,0.0f },
			m_manaGageShakeData.MoveTime, m_manaGageShakeData.MoveCount);
		RedGage->m_spriteSupporter.SpriteShake({ m_manaGageShakeData.MoveX,0.0f },
			m_manaGageShakeData.MoveTime, m_manaGageShakeData.MoveCount);
		Gage->m_spriteSupporter.SpriteShake({ m_manaGageShakeData.MoveX,0.0f },
			m_manaGageShakeData.MoveTime, m_manaGageShakeData.MoveCount);
		MagicWindow->m_spriteSupporter.SpriteShake({ m_manaGageShakeData.MoveX,0.0f },
			m_manaGageShakeData.MoveTime, m_manaGageShakeData.MoveCount);
	}
	/// <summary>
	/// UI�̊J��
	/// </summary>
	void CloseUI() {
		m_uiDrawNow = false;
		for (int i = 0; i < m_spriteList.size(); i++) {
			m_spriteList[i]->m_spriteSupporter.SpriteMove({ OpenAndCloseMoveBound,0.0f },
				OpenAndCloseTimeBound, 0, true);
			m_spriteList[i]->m_spriteSupporter.SpriteMove({ -OpenAndCloseMove,0.0f }, 
				OpenAndCloseTime, OpenAndCloseTimeBound, true);
		}
	}
	void OpenUI() {
		m_uiDrawNow = true;
		for (int i = 0; i < m_spriteList.size(); i++) {
			m_spriteList[i]->m_spriteSupporter.SpriteMove({ OpenAndCloseMove,0.0f }, 
				OpenAndCloseTime, 0, true);
			m_spriteList[i]->m_spriteSupporter.SpriteMove({ -OpenAndCloseMoveBound,0.0f },
				OpenAndCloseTimeBound, OpenAndCloseTime, true);
		}
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static GameUI* GameUI::GetInstance() {
		return m_instance;
	}
	GameMenu* GameUI::GetGemeMenu() {
		return &m_gameMenu;
	}

private:
	
	//���j���[
	GameMenu m_gameMenu;

	//�X�V�F�X
	void GameUI::ManaUpdate();
	void GameUI::LifeUpdate();

	//�����o�ϐ�

	bool m_uiDrawNow = true;	//UI�\�����H

	//�ړ��p
	const float OpenAndCloseMove = 1000.0f;
	const float OpenAndCloseMoveBound = 20.0f;	//����
	const int OpenAndCloseTime = 16;
	const int OpenAndCloseTimeBound = 4;	//����

	//����
	const CVector3 AccScale = { 0.5f,0.5f,1.0f };
	const CVector3 AccDefPos = { -500.0f,250.0f,1.0f };
	const CVector3 Acc2DefPos = { -350.0f,280.0f,1.0f };

	//�Q�[�W
	const CVector4 RedGageColor = { 5.0f,0.2f,0.2f,1.0f };	//�Ԃ��Q�[�W�i�}�i�Q�[�W�j�̐F
	const CVector3 GagePos = { -350.0f,280.0f,1.0f };
	const float RedGageDownSpeed = 0.8f;
	struct ManaGageShakeData	//ManaShake���Ă΂ꂽ�Ƃ��̃X�e�[�^�X
	{
		float MoveX = 20.0f;
		int MoveTime = 2;
		int MoveCount = 3;
	};
	const ManaGageShakeData m_manaGageShakeData;		//ManaShake�Ăяo���p

	//���C�t
	const CVector3 LifeScale = { 0.15f,0.15f,1.0f };
	const CVector3 LifeDefPos = { -520.0f,220.0f,1.0f };	//�i�X�E�Ɋ���Ă���
	const float LifeX_Hosei = 40.0f;

	//�X�v���C�g���낢��
	std::vector<SpriteRender*>m_spriteList;

	//����
	SpriteRender* Accessory1;
	SpriteRender* Accessory2;

	//�Q�[�W
	SpriteRender* GageUnder;
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
	SpriteRender* Life1_Window;
	SpriteRender* Life2_Window;
	SpriteRender* Life3_Window;
	SpriteRender* Life4_Window;
	SpriteRender* Life5_Window;
	SpriteRender* Life6_Window;
	SpriteRender* Life7_Window;
	SpriteRender* Life8_Window;
	SpriteRender* Life9_Window;
	SpriteRender* Life10_Window;

};

