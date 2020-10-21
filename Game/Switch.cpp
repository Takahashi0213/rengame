#include "stdafx.h"
#include "Switch.h"

#include "Game.h"
#include "BoxMaker.h"

Switch::Switch()
{
	//テスト用
	m_scale = CVector3{ 5.0f,5.0f,5.0f };

	//はじまるよ
	m_model.Init(L"Assets/modelData/Switch_Base.cmo");
	//m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation, m_scale);
	//シャドウレシーバーにする。
	m_model.SetShadowReciever(true);

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

}

Switch::~Switch()
{
}

void Switch::Update() {

	//更新
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

	//スイッチ状態の更新
	m_actionFlag = GetSwitchState();

	//拡大率の再設定
	m_switchObj.SetScale(m_scale);
	//赤い部分の更新
	m_switchObj.SwitchUpdate();

}

void Switch::Render() {

	//描画
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

	m_switchObj.SwitchDraw();
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

void SwitchObj::SwitchObj_Init(const CVector3& Pos) {

	//おじゅんび
	m_model.Init(L"Assets/modelData/Switch.cmo");
	//SkinModel Coli_Model;
	//Coli_Model.Init(L"Assets/modelData/Switch_Coli.cmo", EnFbxUpAxis::enFbxUpAxisZ);

	//座標計算
	m_position = Pos + Local;
	//設定
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//ゴーストの座標を作成
	CVector3 ghostPos = m_position;
	ghostPos.y += GhostY_Up;

	//ボックス形状のゴーストを作成する。
	m_ghostObject.CreateBox(
		ghostPos,		//第一引数は座標。
		m_rotation,		//第二引数は回転クォータニオン。
		GhostScale		//第三引数はボックスのサイズ。
	);

	//プレイヤー検索
	m_pl = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"));

	m_physicsStaticObject.CreateMeshObject(m_model, m_position, m_rotation, m_scale);
	//m_physicsStaticObject.CreateBox(m_position, m_rotation, m_scale);

	//シャドウレシーバーにする。
	m_model.SetShadowReciever(true);

}

void SwitchObj::SwitchUpdate() {

	//更新
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

	//アクションモードだけ実行
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::ActionMode ) {
		GhostCheck();
	}
}

void SwitchObj::SwitchDraw() {

	//描画
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void SwitchObj::GhostCheck() {
	
	//プレイヤーと箱チェック
	bool OnFlag = false;

	//プレイヤー
	CharacterController* charaCon = m_pl->GetCharaCon();
	g_physics->ContactTest(*charaCon, [&](const btCollisionObject& contactObject) {
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
			g_physics->ContactTest(*rigidBody, [&](const btCollisionObject& contactObject) {
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

		//スイッチの赤い部分を動かす
		m_position.y = m_position.y + SwitchMove;

	}
	else if (OnFlag == true && m_switchState == Off){	//現在オフだけど、なんか乗ってた！！

		m_switchState = On;

		//スイッチの赤い部分を動かす
		m_position.y = m_position.y - SwitchMove;

	}

}