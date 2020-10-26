#pragma once
#include "system/CGameObjectManager.h"
#include "GameMenu.h"

/// <summary>
/// ゲームのUIをまとめたもの
/// ・シングルトン
/// </summary>
class GameUI : public IGameObject
{
	static GameUI* m_instance;
public:
	GameUI();
	~GameUI();
	void Update()override;
	void Render()override;

	//呼び出し演出

	/// <summary>
	/// 呼び出すだけで！マナバーをシェイクさせる
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
	/// UIの開閉
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
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static GameUI* GameUI::GetInstance() {
		return m_instance;
	}
	GameMenu* GameUI::GetGemeMenu() {
		return &m_gameMenu;
	}

private:
	
	//メニュー
	GameMenu m_gameMenu;

	//更新色々
	void GameUI::ManaUpdate();
	void GameUI::LifeUpdate();

	//メンバ変数

	bool m_uiDrawNow = true;	//UI表示中？

	//移動用
	const float OpenAndCloseMove = 1000.0f;
	const float OpenAndCloseMoveBound = 20.0f;	//反動
	const int OpenAndCloseTime = 16;
	const int OpenAndCloseTimeBound = 4;	//反動

	//装飾
	const CVector3 AccScale = { 0.5f,0.5f,1.0f };
	const CVector3 AccDefPos = { -500.0f,250.0f,1.0f };
	const CVector3 Acc2DefPos = { -350.0f,280.0f,1.0f };

	//ゲージ
	const CVector4 RedGageColor = { 5.0f,0.2f,0.2f,1.0f };	//赤いゲージ（マナゲージ）の色
	const CVector3 GagePos = { -350.0f,280.0f,1.0f };
	const float RedGageDownSpeed = 0.8f;
	struct ManaGageShakeData	//ManaShakeが呼ばれたときのステータス
	{
		float MoveX = 20.0f;
		int MoveTime = 2;
		int MoveCount = 3;
	};
	const ManaGageShakeData m_manaGageShakeData;		//ManaShake呼び出し用

	//ライフ
	const CVector3 LifeScale = { 0.15f,0.15f,1.0f };
	const CVector3 LifeDefPos = { -520.0f,220.0f,1.0f };	//段々右に寄っていく
	const float LifeX_Hosei = 40.0f;

	//スプライトいろいろ
	std::vector<SpriteRender*>m_spriteList;

	//装飾
	SpriteRender* Accessory1;
	SpriteRender* Accessory2;

	//ゲージ
	SpriteRender* GageUnder;
	SpriteRender* RedGage;
	SpriteRender* Gage;
	SpriteRender* MagicWindow;

	//体力
	//ハート1つで100扱い Y_Slice！
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

