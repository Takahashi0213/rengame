#pragma once
#include "character/CharacterController.h"
#include "GameObject/EnemySystem.h"

/// <summary>
/// �}�l�L���i�G�ł��j
/// �`���[�g���A���p
/// �����Ȃ� �|���邾���̓G
/// </summary>
class Mannequin : public EnemySystem
{
public:
	enum EnAnimationClip {
		enAnimationClip_wait, //�ҋ@
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	Mannequin();
	~Mannequin();
	void Update()override;
	void Render()override;

private:

	CharacterController m_charaCon; //�L�����R��
	AnimationClip m_animClips[enAnimationClip_Num];

	//�萔
	const float Scale = 4.0f;	//�傫��

	const int EXP = 10;

};

