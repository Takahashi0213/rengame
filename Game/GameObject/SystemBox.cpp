#include "stdafx.h"
#include "SystemBox.h"

#include "GameSystem/StageSet/StageSet.h"

GhostBox::GhostBox()
{
	//プレイヤーの検索
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}


GhostBox::~GhostBox()
{
	//矢印の削除
	if (m_Yazirushi != nullptr) {
		DeleteGO(m_Yazirushi);
	}

	if (m_boxSystem == MapMove && m_mapMoveFlag == true) {
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
			GhostAction();
		}
		});

	//矢印
	if (m_boxSystem == MapMove) {

		if (m_Yazirushi == nullptr) {
			//生成
			m_Yazirushi = CGameObjectManager::GetInstance()->NewGO<SkinModelRender>(L"Yazirushi", 0);

			//座標補正
			CVector3 pos = m_position;
			pos.y += m_yazirushiYHosei;
			CQuaternion RotationY;
			RotationY.SetRotationDeg(CVector3().AxisY(), m_yazirushiRotAngle);
			CQuaternion rot = m_rotation * RotationY;
			//どっちが上？
			EnFbxUpAxis axis;
			if (YazirushiRotFlag == false) {
				axis = EnFbxUpAxis::enFbxUpAxisY;
			}
			else {
				axis = EnFbxUpAxis::enFbxUpAxisZ;
			}

			m_Yazirushi->Model_Init(
				L"Assets/modelData/Yazirushi.cmo",
				pos,
				rot,
				{5.0f,5.0f,5.0f},
				axis
			);
		}
		else {
			//モノクロ化
			if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
				m_Yazirushi->GetModel()->SetRenderMode(RenderMode::Monochrome);
				m_Yazirushi->SetIsUpdateSkinModelSupporter(false);	//矢印の移動を一時停止
				m_monochromeFlag = true;
			}
			else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
				m_Yazirushi->GetModel()->SetRenderMode(RenderMode::Default);
				m_Yazirushi->SetIsUpdateSkinModelSupporter(true);	//矢印の移動を再開
				m_monochromeFlag = false;
			}

			//移動
			if (m_Yazirushi->m_skinModelSupporter.GetSkinModelMoveListLen() == 0) {
				CVector3 front;
				if (YazirushiRotFlag == false) {
					front.Set(0.0f, 1.0f, 0.0f);
				}
				else {
					front.Set(0.0f, 0.0f, 1.0f);
				}

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
			//現在の場所と移動先の場所が違うならBGMを再生する
			GameData::Place_Data NextPlace = StageSet::GetInstance()->GetStagePlace(m_LoadName);
			GameData::Place_Data NowPlace = GameData::GetInstance()->GetPlace();
			if (NowPlace != NextPlace) {
				wchar_t* bgmName = StageSet::GetInstance()->GetStageBGM_Name(NextPlace);
				SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(bgmName);
			}
			m_player->SetPosition(m_playerMoveTarget);				//プレイヤー移動
			StageSet::GetInstance()->InitStage(m_LoadName);			//ステージ読み込み
			m_player->MapMove();									//持ち上げ状態のリセット
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
		m_scale			//第三引数はボックスのサイズ。
	);

}

void GhostBox::GhostAction() {

	//イベント中なら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//アクションモードでないなら強制終了
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}

	//マップ移動
	if (m_boxSystem == MapMove && m_mapMoveFlag == false) {
		//トランジション
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::Circle,
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, false, true);
		//マップ移動SE
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/MapMove.wav");
		//現在の場所と移動先の場所が違うならBGMをフェードアウトさせる
		GameData::Place_Data NowPlace = GameData::GetInstance()->GetPlace();
		GameData::Place_Data NextPlace = StageSet::GetInstance()->GetStagePlace(m_LoadName);
		if (NowPlace != NextPlace) {
			//BGMのフェードアウト
			SceneManager::GetInstance()->GetSoundManagerInstance()->BGM_VolumeFade(0.0f,
				SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime);
		}
		//マップ移動フラグをtrueにする
		m_mapMoveFlag = true;
	}
	//イベント
	if (m_boxSystem == MapEvent) {
	
		//イベントの実行
		SceneManager::GetInstance()->GetGameEvent()->EvemtStart(m_LoadName);

		//この箱は削除される
		DeleteGO(this);
	}
	//落下ダメージ
	if (m_boxSystem == DamageZone) {
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/PlayerDamage.wav");
		Game::GetInstance()->GetDamageSystem()->Damage(-FallDamage);	//ダメージを受ける
		CVector3 pos = m_player->GetPositionBackup();
		pos.y += PlayerMiss_Y_Hosei;
		m_player->SetPosition(pos);			//座標を戻す
	}
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