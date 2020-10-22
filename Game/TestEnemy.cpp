#include "stdafx.h"
#include "TestEnemy.h"

TestEnemy::TestEnemy()
{
	//デバッグ用調整
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

	//プレイヤーの検索
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::EnemyObj;

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
		//死んじゃった
		m_state = State::Death;
	}

	//ステートで分岐
	switch (m_state)
	{
	case TestEnemy::Move:
		//移動
		MoveAction();
		break;
	case TestEnemy::Follow:
		//追尾
		FollowAction();
		break;
	case TestEnemy::AttackWait:
		//予備動作



		break;
	case TestEnemy::Attack:
		//攻撃



		break;
	case TestEnemy::Death:
		//死亡
		m_actionFlag = true;
		GameStatus_UISystem::GetInstance()->AddEXP(EXP);		//経験値を獲得
		CGameObjectManager::GetInstance()->DeleteGO(this);
		break;
	}

	//キャラコン移動
	m_charaCon.SetPosition(m_position);
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	//ModelRender更新
	m_modelRender->SetPosition(m_position);

}

void TestEnemy::Render() {

}

void TestEnemy::MoveAction() {

	CVector3 P_Position = m_player->GetPosition();
	CVector3 diff = P_Position - m_position;

	if (diff.Length() < FollowLength) {
		//距離が近いので追尾する。
		m_state = Follow;
	}


}

void TestEnemy::FollowAction() {

	CVector3 P_Position = m_player->GetPosition();
	CVector3 diff = P_Position - m_position;

	if (diff.Length() > FollowLength) {
		//追尾終了
		m_state = Move;
	}

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

	//　向かせたい方向のベクトルを計算する。
	CVector3 enemyVec = diff;
	enemyVec.Normalize();
	enemyVec *= FollowSpeed;
	CVector3 targetVector = P_Position - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;
	m_moveSpeed = enemyVec;
}