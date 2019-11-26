#include "stdafx.h"
#include "BoxMaker.h"

BoxMaker* BoxMaker::m_instance = nullptr;

BoxMaker::BoxMaker()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

BoxMaker::~BoxMaker()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
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
	if (key == MouseSupporter::New_Push && NowGameMode == Game::CreateMode 
		&& m_boxMakerMode == NomalMode) {	//左クリックされた瞬間かつクリエイトモードかつ箱拡大中でない

		//選択中の箱だけ実行する
		if (m_nowBox != nullptr) {

			//リセット
			m_surfaceFlag = false;
			for (int i = 0; i < 4; i++) { //箱の座標もリセット
				m_boxPoint[i] = CVector3::Zero();
				m_boxPoint_Stock[i] = CVector3::Zero();
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

				go->CheckHitRayToPlane(g_camera3D.GetPosition(), m_boxPos, m_boxPoint_Stock, m_boxN);

				if (m_surfaceFlag == false) {	//まだ未設定

					//問答無用で設定
					m_surfaceFlag = true;
					for (int i = 0; i < 4; i++) {
						m_boxPoint[i] = m_boxPoint_Stock[i];
					}

				}
				else {	//設定済み

					//既に保存している面と比較して新しい面がカメラに近いなら上書きする
					CVector3 AveragePoint_Old = m_boxPoint[0] + m_boxPoint[1] + m_boxPoint[2] + m_boxPoint[3];
					AveragePoint_Old /= 4.0f;
					CVector3 AveragePoint_New = m_boxPoint_Stock[0] + m_boxPoint_Stock[1] + m_boxPoint_Stock[2] + m_boxPoint_Stock[3];
					AveragePoint_New /= 4.0f;
					CVector3 CameraPos = g_camera3D.GetPosition();

					//距離を計算
					CVector3 Lange_Old_V = AveragePoint_Old - CameraPos;
					CVector3 Lange_New_V = AveragePoint_New - CameraPos;
					float Lange_Old = Lange_Old_V.Length();
					float Lange_New = Lange_New_V.Length();

					if (Lange_Old > Lange_New) {
						for (int i = 0; i < 4; i++) {
							m_boxPoint[i] = m_boxPoint_Stock[i];
						}
					}

				}

			}

		}

		//マウスカーソルが箱のいずれかのポリゴンに衝突しているなら…
		if (m_boxPoint[0].x != m_boxPoint[1].x || 
			m_boxPoint[0].y != m_boxPoint[1].y || 
			m_boxPoint[0].z != m_boxPoint[1].z) {
			//各m_boxPointの平均を計算
			CVector3 AveragePoint = m_boxPoint[0] + m_boxPoint[1] + m_boxPoint[2] + m_boxPoint[3];
			AveragePoint /= 4.0f;

			//箱を生成
			GameBox* m_box = new GameBox;
			m_box->GameBox_Set(AveragePoint);

			//回転設定
			CVector3 boxUp = { 0.0f,1.0f,0.0f };
			m_boxN.Cross(boxUp);
			m_box_N = m_boxN;		//わかりにくいけど箱の向きを保存する
			CQuaternion rot = m_box->GetRotation();

			CQuaternion addRot;

			if (m_boxN.y < 0.098f) {
				//ものすご～い計算
				addRot.SetRotationDeg(m_boxN, 90.0f);
				rot *= addRot;
			}
			m_box->SetRotation(rot);

			//リストの処理
			m_boxList.push_back(m_box);
			m_nowBoxList.push_back(m_box);

			//現在見ているボックスを変更する
			m_nowBox->SetBox(m_box);

			//ポインタを変更
			m_nowBox_Stock = m_nowBox;
			m_nowBox = m_box;

			//マウス移動量を初期化
			m_mouseMove.x = 0.0f;
			m_mouseMove.y = 0.0f;
			//箱のデフォルトサイズも保存
			m_boxScaleDef = m_nowBox->GetScale();

			//モードを拡大モードに変更
			m_boxMakerMode = FocusMode;
		}
	}

	//フォーカスモード用の処理～～～～～～～
	if (NowGameMode == Game::CreateMode && m_boxMakerMode == FocusMode) {
		
		key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		
		if (key == MouseSupporter::Now_Pushing) {	//押されてるやん

			CVector2 mouseMove = MouseSupporter::GetInstance()->GetMouseMove();
			m_boxScale = m_nowBox->GetScale();

			mouseMove.x /= 2.0f;
			mouseMove.y /= 2.0f;

			m_boxScale.x += mouseMove.x;
			m_boxScale.y += mouseMove.y;

			//小さくなりすぎるとバグるので
			if (m_boxScale.x < m_boxScaleDef.x) {
				m_boxScale.x = m_boxScaleDef.x;
			}
			if (m_boxScale.y < m_boxScaleDef.y) {
				m_boxScale.y = m_boxScaleDef.y;
			}

			m_nowBox->SetScale(m_boxScale);


		}else if (key == MouseSupporter::Release_Push) {	//離された！！！

			//ポインタを変更
			m_nowBox = m_nowBox_Stock;

			//モードを通常モードに変更
			m_boxMakerMode = NomalMode;

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