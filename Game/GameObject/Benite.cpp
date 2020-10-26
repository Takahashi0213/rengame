#include "stdafx.h"
#include "Benite.h"

Benite::Benite()
{

	//モデル準備
	m_modelRender = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>("Benite", 1);
	m_modelRender->Model_Init(L"Assets/modelData/Mannequin.cmo",
		m_position, m_rotation, m_scale);

	m_modelRender->SetScale(Scale);

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

Benite::~Benite()
{
	//片付ける
	CGameObjectManager::GetInstance()->DeleteGO(m_modelRender);
	m_charaCon.RemoveRigidBoby();
}

void Benite::Update() {

	//モノクロ化
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
		m_modelRender->GetModel()->SetRenderMode(RenderMode::Monochrome);
		m_monochromeFlag = true;
	}
	else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
		m_modelRender->GetModel()->SetRenderMode(RenderMode::Default);
		m_monochromeFlag = false;
	}

	//クリエイトモード中は一切の更新をしない
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode) {
		return;
	}

	//箱との衝突判定
	bool DeathFlag = BoxAttackSearch(m_position);
	if (DeathFlag == true) {
		//死んじゃった
		m_state = State::Death;
	}

	//プレイヤーとのダメージ判定
	CVector3 toPlayerDir = m_player->GetPosition() - m_position;
	float toPlayerLen = toPlayerDir.Length();
	if (toPlayerLen < DamageLength) {
		Game::GetInstance()->GetDamageSystem()->Damage(-ATK);
	}

	//ステートで分岐
	switch (m_state)
	{
	case Benite::Move:
		//移動
		MoveAction();
		break;
	case Benite::AttackWait:
		//予備動作
		Attack_Wait();
		break;
	case Benite::Attack:
		//攻撃
		AttackAction();
		break;
	case Benite::Death:
		//死亡
		m_actionFlag = true;
		GameStatus_UISystem::GetInstance()->AddEXP(EXP);		//経験値を獲得
		CGameObjectManager::GetInstance()->DeleteGO(this);
		break;
	}

	//キャラコン移動
	m_charaCon.SetPosition(m_position);
	//キャラコン実行
	m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
	//ModelRender更新
	m_modelRender->SetPosition(m_position);
	m_modelRender->SetRotation(m_rotation);

}
void Benite::Render() {

}

void Benite::MoveAction() {

	if (m_moveTimer == 0.0f) {
		//ランダム移動
		int random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY(), static_cast<float>(random));
		CVector3 front = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(front);
		m_moveSpeed = front * RandomSpeed;
	}

	if (m_moveTimer >= MoveWaitLimit && m_moveFlag == false) {
		//停止する
		m_moveSpeed = CVector3::Zero();
		m_moveFlag = true;
	}
	
	//タイマー加算
	m_moveTimer += CGameTime::GetFrameDeltaTime();

	if (m_moveTimer >= MoveWaitEndLimit) {
		//停止を終了する（移動を再開する）
		m_moveTimer = 0.0f;
		m_moveFlag = false;
	}

	//プレイヤーの探索
	CVector3 enemyForward = CVector3::AxisZ();
	m_rotation.Multiply(enemyForward);
	CVector3 toPlayerDir = m_player->GetPosition() - m_position;
	//正規化を行う前に、プレイヤーまでの距離を求めておく。
	float toPlayerLen = toPlayerDir.Length();
	//正規化！
	toPlayerDir.Normalize();
	//enemyForwardとtoPlayerDirとの内積を計算する。
	float d = enemyForward.Dot(toPlayerDir);
	//内積の結果をacos関数に渡して、enemyForwardとtoPlayerDirのなす角を求める。
	float angle = acos(d);
	//角度はマイナスが存在するから、絶対値にする。
	if (fabsf(angle) < CMath::DegToRad(EnemyAngle) && toPlayerLen < FollowLength) {
		//攻撃準備へ移行
		m_moveSpeed = CVector3::Zero();
		m_moveTimer = 0.0f;
		m_moveFlag = false;
		m_state = AttackWait;
	}
}

void Benite::Attack_Wait() {

	if (m_moveTimer == 0.0f) {
		CVector3 P_Position = m_player->GetPosition();
		CVector3 diff = P_Position - m_position;
		m_moveSpeed = diff;
		m_moveSpeed.Normalize();
		m_moveSpeed *= BackSpeed;
	}

	//タイマー加算
	m_moveTimer += CGameTime::GetFrameDeltaTime();

	if (m_moveTimer >= AttackWaitLimit) {
		//攻撃へ移行
		m_moveSpeed = CVector3::Zero();
		m_moveTimer = 0.0f;
		m_state = Attack;
	}

	CVector3 front = { 0.0f, 0.0f,1.0f };
	//プレイヤーの向きに回転
	m_moveSpeed.y = 0.0f;
	CVector3 diff = m_moveSpeed;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(front, diff);
	m_rotation = qRot;
}

void Benite::AttackAction() {

	if (m_moveTimer == 0.0f) {
		CVector3 P_Position = m_player->GetPosition();
		CVector3 diff = P_Position - m_position;
		m_moveSpeed = diff;
		m_moveSpeed.Normalize();
		m_moveSpeed *= AttackSpeed;

		CVector3 front = { 0.0f, 0.0f,1.0f };
		//プレイヤーの向きに回転
		m_moveSpeed.y = 0.0f;
		diff = m_moveSpeed;
		diff.Normalize();
		CQuaternion qRot;
		qRot.SetRotation(front, diff);
		m_rotation = qRot;
	}

	//タイマー加算
	m_moveTimer += CGameTime::GetFrameDeltaTime();

	//移動後のスタン
	if (m_moveTimer >= AttackLimit && m_moveFlag == false) {
		m_moveSpeed = CVector3::Zero();
		m_moveFlag = true;
	}

	if (m_moveTimer >= AttackEndLimit) {
		//移動へ移行
		m_moveSpeed = CVector3::Zero();
		m_moveTimer = 0.0f;
		m_moveFlag = false;
		m_state = Move;
	}


}