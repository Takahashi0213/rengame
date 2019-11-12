#include "stdafx.h"
#include "BoxMaker.h"

BoxMaker::BoxMaker()
{
}

BoxMaker::~BoxMaker()
{
}	

void BoxMaker::Update() {

	//中クリックの状態を判定
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Center_Key);
	Game::GameMode NowGameMode = m_game->GetGameMode();		//現在のゲームモードを呼び出す

	if (key == MouseSupporter::New_Push && NowGameMode == Game::ActionMode) {	//中クリックされた瞬間かつアクションモード

		//クリエイトモードへ変更
		m_game->SetGameMode(Game::CreateMode);

		m_boxPos = MouseSupporter::GetInstance()->GetMousePos_3D();

		btDiscreteDynamicsWorld* dw = g_physics.GetDynamicWorld();
		btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_boxPos);
		dw->rayTest((btVector3)g_camera3D.GetPosition(), m_boxPos, CRR_Callback);
		if (CRR_Callback.hasHit()) {
			m_boxPos = CRR_Callback.m_hitPointWorld;
		}
		else {
			//プレイヤーのちょい上
			m_boxPos = m_player->Getm_Position();
			m_boxPos.y += PosHoseiY;
			//CVector3 m_bp = MouseSupporter::GetInstance()->GetMousePos_3D();
			//m_bp.Normalize();
			//m_boxPos.x += m_bp.x;
			//m_boxPos.y += m_bp.y;
			//m_boxPos.z += m_bp.z;
		}

		GameBox* m_box = new GameBox;
		m_box->GameBox_Set(m_boxPos);
		m_boxList.push_back(m_box);
		m_nowBoxList.push_back(m_box);
		m_nowBox = m_box;

		//ゲームカメラに渡す
		int a = Hash::MakeHash("GameCamera");
		GameCamera* GC = CGameObjectManager::GetInstance()->FindGO<GameCamera>(a);
		GC->SetGameBox(m_box);

	}

	//箱の追加処理
	key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	if (key == MouseSupporter::New_Push && NowGameMode == Game::CreateMode) {	//左クリックされた瞬間かつクリエイトモード

		//選択中の箱だけ実行する
		if (m_nowBox != nullptr) {

			for (int i = 0; i < 4; i++) { //リセット
				m_boxPoint[i] = CVector3::Zero();
			}

			for (auto go : m_nowBoxList) {

				//準備
				m_boxPos = MouseSupporter::GetInstance()->GetMousePos_3D();

				btDiscreteDynamicsWorld* dw = g_physics.GetDynamicWorld();
				btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_boxPos);
				dw->rayTest((btVector3)g_camera3D.GetPosition(), m_boxPos, CRR_Callback);

				//線分チェック
				//CVector3 ray = g_camera3D.GetTarget() - g_camera3D.GetPosition();
				//ray.Normalize();
				//ray *= 10000.0f;

				go->CheckHitRayToPlane(g_camera3D.GetPosition(), m_boxPos, m_boxPoint);

			}

		}

		//マウスカーソルが箱のいずれかのポリゴンに衝突しているなら…
		if (m_boxPoint[0].x != 0.0f && m_boxPoint[0].y != 0.0f && m_boxPoint[0].z != 0.0f) {
			//各m_boxPointの平均を計算
			CVector3 AveragePoint = m_boxPoint[0] + m_boxPoint[1] + m_boxPoint[2] + m_boxPoint[3];
			AveragePoint /= 4.0f;

			GameBox* m_box = new GameBox;
			m_box->GameBox_Set(AveragePoint);
			m_boxList.push_back(m_box);
			m_nowBoxList.push_back(m_box);
			m_nowBox->SetBox(m_box);
		}
	}

	BoxUpdate();

}

/// <summary>
/// ボックスを全部アップデートする
/// </summary>
void BoxMaker::BoxUpdate() {

	for (auto go : m_boxList) {
	
		go->GameBox_Update();
	}
	
}

/// <summary>
/// ボックスを全部描画する
/// </summary>
void BoxMaker::Render() {

	for (auto go : m_boxList) {

		go->GameBox_Render();

	}
}