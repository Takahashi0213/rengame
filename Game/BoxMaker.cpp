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

	ModeChange();
	bool result = false;

	CVector3 boxPoint[4] = { CVector3::Zero() };
	CVector3 boxPoint_Stock[4] = { CVector3::Zero() };
	m_box_N_Now = CVector3::Zero();
	m_planeScaleNow = CVector3::Zero();

	//箱の追加処理
	key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	if (key == MouseSupporter::New_Push && NowGameMode == Game::CreateMode 
		&& m_boxMakerMode == NomalMode) {	//左クリックされた瞬間かつクリエイトモードかつ箱拡大中でない

		//選択中の箱だけ実行する
		if (m_nowBox != nullptr) {

			//リセット
			bool surfaceFlag = false;
	
			for (auto go : m_nowBoxList) {

				//準備
				m_boxPos = MouseSupporter::GetInstance()->GetMousePos_3D();
				
				//線分チェック
				//CVector3 ray = g_camera3D.GetTarget() - g_camera3D.GetPosition();
				//ray.Normalize();
				//ray *= 10000.0f;
			
				result |= go->CheckHitRayToPlane(g_camera3D.GetPosition(), m_boxPos, boxPoint_Stock, m_boxN, m_planeScale);
				
				if (result == true) {
					if (surfaceFlag == false) {	//まだ未設定

						//問答無用で設定
						m_box_N_Now = m_boxN;
						m_planeScaleNow = m_planeScale;
						surfaceFlag = true;
						for (int i = 0; i < 4; i++) {
							boxPoint[i] = boxPoint_Stock[i];
						}

					}
					else {	//設定済み

						//既に保存している面と比較して新しい面がカメラに近いなら上書きする
						CVector3 AveragePoint_Old = boxPoint[0] + boxPoint[1] + boxPoint[2] + boxPoint[3];
						AveragePoint_Old /= 4.0f;
						CVector3 AveragePoint_New = boxPoint_Stock[0] + boxPoint_Stock[1] + boxPoint_Stock[2] + boxPoint_Stock[3];
						AveragePoint_New /= 4.0f;
						CVector3 CameraPos = g_camera3D.GetPosition();

						//距離を計算
						CVector3 Lange_Old_V = AveragePoint_Old - CameraPos;
						CVector3 Lange_New_V = AveragePoint_New - CameraPos;
						float Lange_Old = Lange_Old_V.Length();
						float Lange_New = Lange_New_V.Length();

						if (Lange_Old > Lange_New) {
							m_box_N_Now = m_boxN;
							m_planeScaleNow = m_planeScale;
							for (int i = 0; i < 4; i++) {
								boxPoint[i] = boxPoint_Stock[i];
							}
						}

					}
				}

			}

		}
		
		
		//マウスカーソルが箱のいずれかのポリゴンに衝突しているなら…
		if (result) {
			//各m_boxPointの平均を計算
			CVector3 AveragePoint = boxPoint[0] + boxPoint[1] + boxPoint[2] + boxPoint[3];
			AveragePoint /= 4.0f;

			//箱を生成
			GameBox* m_box = new GameBox;
			m_box->GameBox_Set(AveragePoint);

			//回転設定
			CVector3 boxUp = { 0.0f,1.0f,0.0f };
			m_box_N_Now.Cross(boxUp, m_box_N_Now);
			m_box_N = m_box_N_Now;		//わかりにくいけど箱の向きを保存する
			CQuaternion rot = m_box->GetRotation();

			CQuaternion addRot;

			if (m_box_N_Now.y < 0.098f) {
				//ものすご～い計算
				addRot.SetRotationDeg(m_box_N_Now, 90.0f);
				rot *= addRot;
			}
			m_box->SetRotation(rot);

			//拡大率設定
			CVector3 scl= m_box->GetScale();
			scl.y = 0.1f;
			//潰す方向を確認する
			if (m_planeScaleNow.x <= 0.01f) {
				m_boxDirection = X_Direction;
				scl.x = m_planeScaleNow.y;
				scl.z = m_planeScaleNow.z;
			}
			else if (m_planeScaleNow.y <= 0.01f) {
				m_boxDirection = Y_Direction;
				scl.x = m_planeScaleNow.x;
				scl.z = m_planeScaleNow.z;				
			}
			else if (m_planeScaleNow.z <= 0.01f) {
				m_boxDirection = Z_Direction;
				scl.x = m_planeScaleNow.x;				
				scl.z = m_planeScaleNow.y;
			}
			else {
				m_boxDirection = Z_Direction;
			}
			m_box->SetScale(scl);

			//リストの処理
			m_boxList.push_back(m_box);
			m_nowBoxList.push_back(m_box);

			//現在見ているボックスを変更する
			m_originBox->SetBox(m_box);

			//ポインタを変更
			m_nowBox_Stock = m_nowBox;
			m_nowBox = m_box;

			//マウス移動量を初期化
			m_mouseMove.x = 0.0f;
			m_mouseMove.y = 0.0f;
			//箱のデフォルトサイズも保存
			m_boxScaleDef = m_nowBox->GetScale();
			//箱の数を追加
			m_box_Nom++;

			//モードを拡大モードに変更
			m_boxMakerMode = FocusMode;
		}
	}

	//フォーカスモード用の処理～～～～～～～
	if (NowGameMode == Game::CreateMode && m_boxMakerMode == FocusMode) {
		
		key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		
		if (key == MouseSupporter::Now_Pushing) {	//押されてるやん

			//箱の拡大縮小～～～～～
			CVector2 mouseMove = MouseSupporter::GetInstance()->GetMouseMove();
			m_boxScale = m_nowBox->GetScale();

			//移動量に補正をかける
			mouseMove.x *= m_mouseMoveHosei;
			mouseMove.y *= m_mouseMoveHosei;

			//箱の向きに合わせて拡大率を色々する
			switch (m_boxDirection)
			{
			case BoxMaker::X_Direction:
				//m_boxScale.x += mouseMove.x;
				m_boxScale.y += mouseMove.y;
				break;
			case BoxMaker::Y_Direction:
				//m_boxScale.x += mouseMove.x;
				m_boxScale.y += -mouseMove.y;
				break;
			case BoxMaker::Z_Direction:
				//m_boxScale.x += mouseMove.x;
				m_boxScale.y += mouseMove.y;
				break;
			}

			//小さくなりすぎるとバグるので
			if (m_boxScale.x < m_boxScaleDef.x) {
				m_boxScale.x = m_boxScaleDef.x;
			}
			if (m_boxScale.y < m_boxScaleDef.y) {
				m_boxScale.y = m_boxScaleDef.y;
			}
			if (m_boxScale.z < m_boxScaleDef.z) {
				m_boxScale.z = m_boxScaleDef.z;
			}

			m_nowBox->SetScale(m_boxScale);


		}else if (key == MouseSupporter::Release_Push) {	//離された！！！

			//ポインタを変更
			m_nowBox = m_nowBox_Stock;

			//モードを通常モードに変更
			m_boxMakerMode = NomalMode;

		}

	}

	//アンドゥ処理！！！！
	if (NowGameMode == Game::CreateMode && m_box_Nom > 1) {
		//CTRL+Z
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && GetAsyncKeyState('Z') & 0x8000) {

			if (m_undoFlag == false) {
				//直前の箱を消す
				auto p = m_boxList.back();
				delete(p);
				
				m_boxList.pop_back();
				m_nowBoxList.pop_back();
				m_originBox->SetBox_Delete();

				m_undoFlag = true;
				m_box_Nom--;
			}
		}
		else {
			m_undoFlag = false;
		}
	}

	BoxUpdate();

}

/// <summary>
/// ボックスを全部アップデートする
/// </summary>
void BoxMaker::BoxUpdate() {
	Game::GameMode NowGameMode = m_game->GetGameMode();		//現在のゲームモードを呼び出す

	for (auto go : m_boxList) {
	
		go->GameBox_Update();

		if (NowGameMode == Game::ActionMode) {
			go->GameBoxUpdate_Colli();
		}
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

void BoxMaker::ModeChange() {

	//中クリックの状態を判定
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Center_Key);
	Game::GameMode NowGameMode = m_game->GetGameMode();		//現在のゲームモードを呼び出す
	
	//中クリックされた瞬間かつアクションモード
	if (key == MouseSupporter::New_Push && NowGameMode == Game::ActionMode) {

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
		m_box->SetBoxTag(GameBox::Origin);	//箱のタグを「最初の箱」に変更する
		m_boxList.push_back(m_box);
		m_nowBoxList.push_back(m_box);
		m_nowBox = m_box;
		m_originBox = m_box;

		m_box_Nom = 1;				//箱の数をリセット

		//ゲームカメラに渡す
		int a = Hash::MakeHash("GameCamera");
		GameCamera* GC = CGameObjectManager::GetInstance()->FindGO<GameCamera>(a);
		GC->SetGameBox(m_box);

	}
	//クリエイトモードからアクションモードへ戻りマス
	else if (key == MouseSupporter::New_Push && NowGameMode == Game::CreateMode) {	//中クリックされた瞬間かつアクションモード

		//アクションモードへ変更
		m_game->SetGameMode(Game::ActionMode);

		//カメラ移動を制御する
		int a = Hash::MakeHash("GameCamera");
		GameCamera* GC = CGameObjectManager::GetInstance()->FindGO<GameCamera>(a);
		GC->PlayerCameraMove();

	}

}