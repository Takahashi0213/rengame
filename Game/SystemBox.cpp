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
	if (m_Yazirushi != nullptr) {
		DeleteGO(m_Yazirushi);
	}

	if (m_LoadStageName != nullptr && m_mapMoveFlag == true) {
		//トランジション閉じる
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::Circle,
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, true , true);
	}
}

void GhostBox::Update() {

	//プレイヤーとの衝突判定
	CharacterController* charaCon = m_player->GetCharaCon();
	g_physics->ContactTest(*charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject) == true) {
			//m_ghostObjectとぶつかった
			if (m_LoadStageName != nullptr && m_mapMoveFlag == false) {
				//マップ移動
				//トランジション
				TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::Circle,
					SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, false, true);
				//マップ移動フラグをtrueにする
				m_mapMoveFlag = true;
			}
			else {
				//落下ダメージ

			}
		}
		});

	//矢印
	if (m_LoadStageName != nullptr) {
		if (m_Yazirushi == nullptr) {
			//生成
			m_Yazirushi = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>(L"Yazirushi", 0);

			//座標補正
			CVector3 pos = m_position;
			pos.y += m_yazirushiYHosei;
			CQuaternion RotationY;
			RotationY.SetRotationDeg(CVector3().AxisY(), m_yazirushiRotAngle);
			CQuaternion rot = m_rotation * RotationY;

			m_Yazirushi->Model_Init(
				L"Assets/modelData/Yazirushi.cmo",
				pos,
				rot,
				{5.0f,5.0f,5.0f},
				EnFbxUpAxis::enFbxUpAxisY
			);
		}
		else {
			//移動
			if (m_Yazirushi->m_skinModelSupporter.GetSkinModelMoveListLen() == 0) {
				CVector3 front = { 0.0f, 1.0f,0.0f };
				CQuaternion y_rot = m_Yazirushi->GetRotation();
				y_rot.Multiply(front);
				CVector3 moveVec = front * YazirushiMoveHosei;
				m_Yazirushi->m_skinModelSupporter.SkinModelMove(moveVec, YazirushiMoveTime, 0, true);
				m_Yazirushi->m_skinModelSupporter.SkinModelMove(-moveVec, YazirushiMoveTime, YazirushiMoveTime, true);
			}
		}
	}

	//マップ移動待ち
	if (m_mapMoveFlag == true) {
		m_mapMoveTimer++;
		if (m_mapMoveTimer == SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime) {
			m_player->SetPosition(m_playerMoveTarget);				//プレイヤー移動
			StageSet::GetInstance()->InitStage(m_LoadStageName);	//ステージ読み込み
		}
	}

}

void GhostBox::Render() {

}

void GhostBox::CreateGhost() {

	//ボックス形状のゴーストを作成する。
	m_ghostObject.CreateBox(
		m_position,		//第一引数は座標。
		m_rotation,		//第二引数は回転クォータニオン。
		m_scale				//第三引数はボックスのサイズ。
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