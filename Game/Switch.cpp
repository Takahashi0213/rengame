#include "stdafx.h"
#include "Switch.h"

#include "Game.h"
#include "BoxMaker.h"


Switch::Switch()
{
	//はじまるよ
	m_model.Init(L"Assets/modelData/Switch_Base.cmo");
	//m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation, m_scale);

}

Switch::~Switch()
{
}

void Switch::Update() {

	//更新
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

	m_switchObj.SwitchUpdate();

}

void Switch::Render() {
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

/// <summary>
/// SwitchObj
/// </summary>

SwitchObj::SwitchObj()
{
}

SwitchObj::~SwitchObj()
{
}

void SwitchObj::SwitchObj_Init(CVector3 Pos) {

	//おじゅんび
	m_skinModel.Model_Init(L"Assets/modelData/Switch.cmo");

	//座標計算
	m_position = Pos + Local;
	//設定
	m_skinModel.SetUp(m_position, m_rotation, m_scale);

	//ボックス形状のゴーストを作成する。
	m_ghostObject.CreateBox(
		m_position,		//第一引数は座標。
		m_rotation,		//第二引数は回転クォータニオン。
		GhostScale		//第三引数はボックスのサイズ。
	);

	//プレイヤー検索
	m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	m_physicsStaticObject.CreateMeshObject(m_skinModel.GetModel_(), m_position, m_rotation, m_scale);

}

void SwitchObj::SwitchUpdate() {

	//更新
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

	//アクションモードだけ実行
	if (Game::GetInstance()->GetGameMode() == Game::ActionMode ) {
		GhostCheck();
	}
}

void SwitchObj::GhostCheck() {
	
	//プレイヤーと箱チェック
	bool OnFlag = false;

	//プレイヤー
	CharacterController* charaCon = m_pl->GetCharaCon();
	g_physics.ContactTest(*charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった
			OnFlag = true;
		}
		});

	//箱
	std::list<GameBox*>boxList = BoxMaker::GetInstance()->GetBoxList();
	for (auto go : boxList) {

		if (go->GetColli_InitFlag() == true) {

			RigidBody* rigidBody = go->GetRigidBody();
			g_physics.ContactTest(*rigidBody, [&](const btCollisionObject& contactObject) {
				if (m_ghostObject.IsSelf(contactObject) == true) {
					//m_ghostObjectとぶつかった
					OnFlag = true;
				}
				});
		}
	}

	//オンフラグチェック！
	if (OnFlag == false && m_switchState == On) {	//現在オンだけど、今何も乗ってないよ

		m_switchState = Off;
	}
	else if (OnFlag == true && m_switchState == Off){	//現在オフだけど、なんか乗ってた！！

		m_switchState = On;
	}

}