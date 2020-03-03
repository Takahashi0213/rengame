#pragma once
#include "character/CharacterController.h"
#include "EnemySystem.h"

class TestEnemy : public IGameObject, public EnemySystem
{
public:
	enum State {
		Move,
		Follow,
		Death,
	};

	TestEnemy();
	~TestEnemy();
	void Update()override;
	void Render()override;

private:

	SkinModelRender* m_modelRender;	//スキンモデル。
	CharacterController m_charaCon; //キャラコン

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率
	CVector3 m_moveSpeed = CVector3().Zero();

	State m_state = Move;	//ステート
};

