#include "stdafx.h"
#include "SystemBox.h"

GhostBox::GhostBox()
{
	//ボックス形状のゴーストを作成する。
	m_ghostObject.CreateBox(
		m_position,		//第一引数は座標。
		m_rotation,		//第二引数は回転クォータニオン。
		m_scale			//第三引数はボックスのサイズ。
	);

	//プレイヤーの検索
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);

}


GhostBox::~GhostBox()
{
}

void GhostBox::Update() {

	CharacterController* charaCon = m_player->GetCharaCon();
	g_physics->ContactTest(*charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった

		}
		});

}

void GhostBox::Render() {

}

/// <summary>
/// ここからスタティックボックス
/// </summary>

StaticBox::StaticBox()
{
	//箱を作成
	m_physicsStaticObject.CreateBox(m_position, m_rotation, m_scale);
}


StaticBox::~StaticBox()
{
}

void StaticBox::Update() {

	//箱を更新
	m_physicsStaticObject.SetPositionAndRotation(m_position, m_rotation);

}

void StaticBox::Render() {

}
