#pragma once
#include "character/CharacterController.h"
#include "GameObject/EnemySystem.h"

/// <summary>
/// マネキン（敵です）
/// チュートリアル用
/// 動かない 倒せるだけの敵
/// </summary>
class Mannequin : public EnemySystem
{
public:
	enum EnAnimationClip {
		enAnimationClip_wait, //待機
		enAnimationClip_Num,  //アニメーションクリップ
	};

	Mannequin();
	~Mannequin();
	void Update()override;
	void Render()override;

private:

	CharacterController m_charaCon; //キャラコン
	AnimationClip m_animClips[enAnimationClip_Num];

	//定数
	const float Scale = 4.0f;	//大きさ

	const int EXP = 10;

};

