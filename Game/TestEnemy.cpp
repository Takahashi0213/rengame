#include "stdafx.h"
#include "TestEnemy.h"

TestEnemy::TestEnemy()
{
	//調整
	m_position.Set(0.0f, 100.0f, 200.0f);
	m_scale.Set(10.0f, 10.0f, 10.0f);

	//モデル準備
	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("TestEnemy", 1);
	m_modelRender->Model_Init(L"Assets/modelData/Test_Enemy.cmo",
		m_position, m_rotation, m_scale);

	//シャドウレシーバーにする。
	m_modelRender->SetShadowReciever(true);

	//シャドウキャスターにも登録
	m_modelRender->SetShadowCasterFlag(true);

	//キャラコン！！
	m_charaCon.Init(
		60.0f,  //キャラクターの半径。
		60.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

}

TestEnemy::~TestEnemy()
{
	//片付ける
	CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
	m_charaCon.RemoveRigidBoby();
}

void TestEnemy::Update() {

	//箱との衝突判定
	bool DeathFlag = BoxAttackSearch(m_position);
	if (DeathFlag == true) {
		//死んじゃっﾀ。。。。
		m_state = State::Death;
	}

	//ステートで分岐
	switch (m_state)
	{
	case TestEnemy::Move:
		//移動
		m_moveSpeed.z = 1.0f;
		break;
	case TestEnemy::Follow:
		//追尾
		break;
	case TestEnemy::Death:
		//死亡
		CGameObjectManager::GetInstance()->DeleteGO(this);
		break;
	}

	//移動
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	//ModelRender更新
	m_modelRender->SetPosition(m_position);

}

void TestEnemy::Render() {

}