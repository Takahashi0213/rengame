#include "stdafx.h"
#include "SystemBox.h"

#include "StageSet.h"

GhostBox::GhostBox()
{
	//プレイヤーの検索
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}


GhostBox::~GhostBox()
{
}

void GhostBox::Update() {

	//プレイヤーとの衝突判定
	CharacterController* charaCon = m_player->GetCharaCon();
	g_physics->ContactTest(*charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった
			if (m_LoadStageName != nullptr) {
				//マップ移動
				StageSet::GetInstance()->InitStage(m_LoadStageName);	//ステージ読み込み
				m_player->SetPosition(m_playerMoveTarget);				//プレイヤー移動
			}
			else {
				//ゲームオーバー

			}
		}
		});

}

void GhostBox::Render() {

}

void GhostBox::CreateGhost() {

	//ボックス形状のゴーストを作成する。
	m_ghostObject.CreateBox(
		m_position,		//第一引数は座標。
		m_rotation,		//第二引数は回転クォータニオン。
		m_scale			//第三引数はボックスのサイズ。
	);

}

/// <summary>
/// ここからスタティックボックス
/// </summary>

StaticBox::StaticBox()
{

}

StaticBox::~StaticBox()
{
}

void StaticBox::Update() {
	//箱を更新
	//m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);
}

void StaticBox::Render() {

}

void StaticBox::CreateStaticBox() {
	//箱を作成
	m_physicsStaticObject.CreateBox(m_position, m_rotation, m_scale);
}