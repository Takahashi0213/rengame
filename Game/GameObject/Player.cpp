#include "stdafx.h"
#include "Player.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "GameSystem/GameUI/GameUI.h"
#include "BoxMaker.h"

int Game_UI = Hash::MakeHash("GameUI");

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	m_model_Sl.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	//m_model.SetEmissionColor({ 100.0f,1.0f,1.0f });
	m_model_Sl.SetRenderMode(RenderMode::Silhouette);

	//アニメーション
	m_playerAnimationClips[enAnimationClip_Idle].Load(L"Assets/animData/idle.tka");
	m_playerAnimationClips[enAnimationClip_Idle].SetLoopFlag(true);

	m_playerAnimationClips[enAnimationClip_Run].Load(L"Assets/animData/run.tka");
	m_playerAnimationClips[enAnimationClip_Run].SetLoopFlag(true);
	//アニメーションの初期化。
	m_playerAnimation.Init(
		m_model,					//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		m_playerAnimationClips,		//アニメーションクリップの配列。
		enAnimationClip_Num			//アニメーションクリップの数。
	);
	m_playerAnimationSL.Init(
		m_model_Sl,					//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		m_playerAnimationClips,		//アニメーションクリップの配列。
		enAnimationClip_Num			//アニメーションクリップの数。
	);

	//ワールド行列の更新。
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_nextPos = m_position;		//移動先を初期化

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(Radius, Height, m_position);

	//ライトメーカーの取得
	m_lightMaker = LightMaker::GetInstance();

	//シャドウレシーバーにする。
	m_model.SetShadowReciever(true);

	//ゲームのポインタ
	m_gameObj = Game::GetInstance();

	//スプライトマスクのテスト

	//SpriteRender* MainSprite = NewGO<SpriteRender>("TEST", 0);
	//MainSprite->ChangeMaskSprite();
	//MainSprite->Init(L"Assets/sprite/keis.dds", 588.0f, 1240.0f, 0);
	//MainSprite->SetPosition({ 250.0f,-250.0f ,0.0f });
	//MainSprite->InitSub(L"Assets/sprite/fukidasi.dds", 600.0f, 400.0f, 0);
	//MainSprite->SetPosition({ 250.0f,-50.0f ,0.0f }, 0);
	//MainSprite->GetSubSpriteSupporter(0)->SpriteRotation(10.0f, 600, 0, true);

}

Player::~Player()
{

}

void Player::Update()
{
	//モノクロになる
	if (m_gameObj != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
			m_model.SetRenderMode(RenderMode::Monochrome);
			m_monochromeFlag = true;
		}
		else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
			m_model.SetRenderMode(RenderMode::Default);
			m_monochromeFlag = false;
		}
	}
	//アニメーション
	if (m_gameObj != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode) {
			//アニメーション再生
			float MovePower = m_moveSpeed.Length();
			if (MovePower > 10.0f) {
				m_playerAnimation.Play(enAnimationClip_Run);
				m_playerAnimationSL.Play(enAnimationClip_Run);
			}
			else {
				m_playerAnimation.Play(enAnimationClip_Idle);
				m_playerAnimationSL.Play(enAnimationClip_Idle);
			}
			m_playerAnimation.Update(1.0f / 20.0f);
			m_playerAnimationSL.Update(1.0f / 20.0f);
		}
	}

	//処理

	//持ち上げ中の箱の座標をプレイヤーに合わせる
	BoxUp();
	//移動
	Move();
	//地上にいたらジャンプ
	Jump();
	//持ち上げる箱を探す
	BoxSearch();
	//キーが押されたら持ち上げたり下ろしたりする
	BoxCatch();
	//キーが押されたら持ち上げている箱を削除する
	BoxDelete();
	//上げ下げ中の補完移動をする
	BoxMove();

	//ワールド行列の更新。
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::ActionMode){ //アクションモードでなければ更新しない！

		//重力
		m_moveSpeed.y -= m_gravity;
		//キャラコン移動
		m_position = m_charaCon.Execute(1.0f, m_moveSpeed);

	}

	//シャドウキャスターを登録。
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
	ShadowMap::GetInstance()->Update(m_lightMaker->GetLightCameraPosition(), m_lightMaker->GetLightCameraTarget());

	//ライトカメラを更新
	CVector3 LC_Pos = LightMaker::GetInstance()->GetLightCameraPosition();
	LC_Pos = m_position;
	LC_Pos.y += 1000.0f;
	LightMaker::GetInstance()->SetLightCameraPosition(LC_Pos);
	//ターゲットも
	LC_Pos = LightMaker::GetInstance()->GetLightCameraTarget();
	LC_Pos = m_position;
	LightMaker::GetInstance()->SetLightCameraTarget(LC_Pos);
}

void Player::Render()
{
	m_model_Sl.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::Move() {

	//イベント中なら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//箱の上げ下ろし中は強制終了
	if (m_boxMoveFlag == true) {
		return;
	}

	//左クリックの状態を判定
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	bool OnG_Flag = m_charaCon.IsOnGround();
	GameUI* ui = CGameObjectManager::GetInstance()->FindGO<GameUI>(Game_UI);

	//左キーが離された＆現在アクションモード＆メニューボタンに被っていない＆ノックバック中でない
	if (key == MouseSupporter::Release_Push &&
		SceneManager::GetInstance()->GetGameMode() == SceneManager::ActionMode &&
		ui->GetGemeMenu()->GetSelectFlag() == false &&
		m_damage_Flag == false)
	{
		if (MouseSupporter::GetInstance()->GetMouseTimer(MouseSupporter::Left_Key) < 12) {

			m_nextPos = MouseSupporter::GetInstance()->GetMousePos_3D();

			//btCollisionWorld::ClosestRayResultCallback ResultCallback();
			btDiscreteDynamicsWorld* dw = g_physics->GetDynamicWorld();
			btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_nextPos);
			dw->rayTest((btVector3)g_camera3D.GetPosition(), m_nextPos, CRR_Callback);
			if (CRR_Callback.hasHit()) {
				m_nextPos = CRR_Callback.m_hitPointWorld;
			}
			else {
				m_nextPos = m_position + (m_moveSpeed / 1000.0f);
			}

		}
	}

	//移動
	m_nextPos.y = m_position.y;

	m_moveSpeed.x = m_nextPos.x - m_position.x;
	m_moveSpeed.z = m_nextPos.z - m_position.z;
	m_moveSpeed.x /= 20.0f;
	m_moveSpeed.z /= 20.0f;

	//上限
	if (m_moveSpeed.x > m_moveMax) {
		m_moveSpeed.x = m_moveMax;
	}
	if (m_moveSpeed.x < -m_moveMax) {
		m_moveSpeed.x = -m_moveMax;
	}
	if (m_moveSpeed.z > m_moveMax) {
		m_moveSpeed.z = m_moveMax;
	}
	if (m_moveSpeed.z < -m_moveMax) {
		m_moveSpeed.z = -m_moveMax;
	}

	//移動方向に回転させる（ノックバック中は回転しない）
	if (m_damage_Flag == false) {
		float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(CVector3().AxisY(), angle);
	}

	//現在位置のバックアップ
	if (m_jumpNow == false) {
		m_posBackup = m_position;
	}

}

void Player::Jump() {
	
	//イベント中なら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//箱の上げ下ろし中は強制終了
	if (m_boxMoveFlag == true) {
		return;
	}

	bool OnG_Flag = m_charaCon.IsOnGround();

	//ジャンプ処理
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (m_jumpNow == false && OnG_Flag == true) {
			m_moveSpeed.y = m_jumpPower;

			//EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::TestData, false, 100.0f, 100.0f, 0.0f);
			//EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::TestData, true,
			//	300.0f, 100.0f, 0.0f,
			//	180.0f, 180.0f, 180.0f);
		}
		m_jumpNow = true;

	}
	else {
		m_jumpNow = false;
	}

	//空中フラグリセット
	if (OnG_Flag == false) {
		if (m_damage_JumpFlag == false && m_damage_Flag == true) {
			m_damage_JumpFlag = true;
		}
	}
	else {
		if (m_damage_JumpFlag == true && m_damage_Flag == true) {
			//ノックバック終了
			m_damage_Flag = false;
			m_damage_JumpFlag = false;
			m_nextPos = m_position;
		}
	}

}

void Player::BoxCatch() {

	//イベント中なら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}

	//アクションモードでないなら強制終了
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}

	//箱の上げ下ろし中は強制終了
	if (m_boxMoveFlag == true) {
		return;
	}

	//対応するボタンが押されてないなら強制終了
	if (HIWORD(GetAsyncKeyState(GameData::GetInstance()->GetBoxCatchKey()))) {
		if (m_boxButtonFlag == false) {
			m_boxButtonFlag = true;
		}
		else {
			return;
		}
	}
	else {
		m_boxButtonFlag = false;
		return;
	}

	//箱を持ち上げているかどうかで分岐
	if (m_boxUpFlag == false) {

		//箱を持ちあげる

		if (m_upKouho_Box != nullptr) { //持ち上げられる箱がある？
			m_upBox = m_upKouho_Box;
			m_boxUpFlag = true;
			m_boxMoveFlag = true;
			m_upOrDown = false;	//箱を上げてるフラグ
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
			
			//箱の方を向く
			{
				CVector3 playerForward = { 0.0f, 0.0f, 1.0f };
				//　向かせたい方向のベクトルを計算する。
				CVector3 targetVector = m_upBox->GetPosition() - m_position;
				//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
				targetVector.y = 0.0f;
				targetVector.Normalize();
				CQuaternion qRot;
				qRot.SetRotation(playerForward, targetVector);
				m_rotation = qRot;
			}
			//座標計算
			{
				m_point_2 = m_upBox->GetPosition();	//始点
				CVector3 Pos = m_position;
				Pos.y += m_boxPos_Y_Hosei;
				m_point_3 = Pos;	//終点
				CVector3 Vec = Pos - m_upBox->GetPosition();	//始点から終点に伸びるベクトル
				Vec /= 4.0f;
				CVector3 Pos2 = m_upBox->GetPosition() + Vec;
				Pos2.y += m_boxMove_Y_Hosei;
				m_point_4 = Pos2;	//始点寄り
				Pos2 = Pos - Vec;
				Pos2.y = m_point_4.y;
				m_point_1 = Pos2;	//終点寄り
			}

		}

	}
	else {

		//移動量に応じて箱を置くか投げるか変更
		CVector3 Move = m_moveSpeed / m_boxPutHosei;
		Move.y = 0.0f;
		float MovePower = Move.Length();
		if (MovePower >= 0.0f) {

			//投げる
			CVector3 MoveSpeed = BoxThrowSearch();
			m_upBox->SetMoveSpeed(MoveSpeed);

			//リセット
			m_boxUpFlag = false;
			m_upBox = nullptr;

		}
		else {
			//箱をおろす

			//座標は前方床
			{
				//座標計算
				m_point_2 = m_upBox->GetPosition();	//始点
				CVector3 Pos = m_position;
				CVector3 Move_ = m_moveSpeed;
				Move_.Normalize();
				Pos += Move_ * m_boxPut_Hosei;
				m_point_3 = Pos;	//終点
				CVector3 Vec = Pos - m_upBox->GetPosition();	//始点から終点に伸びるベクトル
				Vec /= 4.0f;
				CVector3 Pos2 = m_upBox->GetPosition() + Vec;
				Pos2.y += m_boxMove_Y_Hosei_Put;
				m_point_4 = Pos2;	//始点寄り
				Pos2 = Pos - Vec;
				Pos2.y = m_point_4.y;
				m_point_1 = Pos2;	//終点寄り
			}

			//リセット
			m_boxUpFlag = false;
			m_boxMoveFlag = true;
			m_upOrDown = true;	//箱を下ろしてるフラグ
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;

		}

	}

}

void Player::BoxSearch() {

	//イベント中なら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//アクションモードでないなら強制終了
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}
	//箱を持ち上げているなら強制終了
	if (m_boxUpFlag == true) {
		return;
	}

	//ボックスメーカー
	BoxMaker* BoxMaker_p = BoxMaker::GetInstance();

	//近くに箱があるか検索
	const std::list<GameBox*>& boxList = BoxMaker_p->GetBoxList();
	float FinalRange = 0.0f;		//距離保存用
	GameBox* UpBox = nullptr;		//持ち上げる箱のポインタ
	CVector3 P_B_Range;				//高さ計算用
	float P_B_Range_Final;			//距離
	GameBox* UpBox_Origin= nullptr;	//持ち上げる箱の親（nullならオリジン）
	CVector3 Hosei;					//Another用座標補正
	float Range_Hosei;				//距離補正

	for (auto go : boxList) {

		//Originかな？
		if (go->GetBoxTag() == GameBox::Origin) {

			UpBox_Origin = nullptr;	//こいつがオリジンなので初期化しておく
			Hosei = CVector3::Zero();
			Range_Hosei = 0.0f;

			go->SetAllColor({ 0.0f,0.0f,0.0f });	//色も初期化しておく

		}
		else if (go->GetBoxTag() == GameBox::Another) {
			//アナザー箱
			UpBox_Origin = go->GetOriginBox();
			Hosei = go->GetAnotherHosei();
			Range_Hosei = go->GetAnotherRangeHosei();
		}

		//移動量計算
		P_B_Range = m_position - (go->GetPosition() + Hosei);
		P_B_Range_Final = P_B_Range.Length();

		//判別タイム
		bool Flag = false;

		//近くにあるか？
		if (P_B_Range_Final > m_boxUpRange + Range_Hosei) {
			Flag = true;	//遠すぎ！アウト！
		}
		//高さが合うか？
		if (fabsf(P_B_Range.y) > m_boxUp_Y_Max) {
			Flag = true;	//高さ違いすぎ！アウト！
		}
		//角度が合うか？
		CVector3 playerForward = CVector3::AxisZ();
		m_rotation.Multiply(playerForward);
		//箱からプレイヤーに伸びるベクトルを求める。
		CVector3 toPlayerDir = m_position - (go->GetPosition() + Hosei);
		toPlayerDir.Normalize();
		//内積を計算する。
		float d = playerForward.Dot(toPlayerDir);
		//なす角を求める。
		float angle = acos(d);
		//視野角判定
		if (fabsf(angle) < CMath::DegToRad(m_boxUp_Angle)) {
			Flag = true;	//角度違いすぎ！アウト！
		}

		if (Flag == false) {	//審査に通った箱のみがここまで来れる

			if (UpBox == nullptr) {
				if (UpBox_Origin == nullptr) {
					UpBox = go;
				}
				else {
					UpBox = UpBox_Origin;
				}
				FinalRange = P_B_Range_Final;
			}
			else {
				//距離が近いかな？
				if (FinalRange > P_B_Range_Final) {
					if (UpBox_Origin == nullptr) {
						UpBox = go;
					}
					else {
						UpBox = UpBox_Origin;
					}
					FinalRange = P_B_Range_Final;
				}
			}

		}

	}

	//決定！
	m_upKouho_Box = UpBox;

	//色変更
	if (m_upKouho_Box != nullptr) {
		m_upKouho_Box->SetAllColor({ 1.0f,0.0f,0.0f });
	}

}

void Player::BoxUp() {

	//何も持ち上げてないなら終了
	if (m_upBox == nullptr) {
		return;
	}
	//箱の上げ下ろし中なら強制終了
	if (m_boxMoveFlag == true) {
		return;
	}

	//箱移動
	CVector3 BoxPos = m_upBox->GetPosition();
	BoxPos = m_position;
	BoxPos.y += m_boxPos_Y_Hosei;	//箱をあるべき場所に動かす
	m_upBox->GameBox_Set(BoxPos, m_rotation);
	
}

void Player::BoxMove() {

	//イベント中なら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//アクションモードでないなら強制終了
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}
	//箱の上げ下ろし中でないなら強制終了
	if (m_boxMoveFlag == false) {
		return;
	}

	//ベジェ曲線を使った計算
	m_catmull_U += 0.1f;
	CVector3 output_point = m_point_2 * (1 - m_catmull_U)*(1 - m_catmull_U)*(1 - m_catmull_U) + 3 * 
							m_point_4 * m_catmull_U*(1 - m_catmull_U)*(1 - m_catmull_U) + 3 * 
							m_point_1 * m_catmull_U*m_catmull_U*(1 - m_catmull_U) + 
							m_point_3 * m_catmull_U*m_catmull_U*m_catmull_U;
	m_upBox->GameBox_Set(output_point, m_upBox->GetRotation());

	//移動終了
	if (m_catmull_U >= 1.0f) {
		m_boxMoveFlag = false;
		m_catmull_U = 0.0f;
		if (m_upOrDown == true) {
			m_upBox = nullptr;
		}
	}

}

void Player::BoxDelete() {

	//イベント中なら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//アクションモードでないなら強制終了
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}
	//何も持ち上げてないなら終了
	if (m_upBox == nullptr) {
		return;
	}
	//箱の上げ下ろし中なら強制終了
	if (m_boxMoveFlag == true) {
		return;
	}

	//対応するボタンが押されてないなら強制終了
	if (HIWORD(GetAsyncKeyState(GameData::GetInstance()->GetBoxDeleteKey()))) {
		if (m_boxDeleteButtonFlag == false) {
			m_boxDeleteButtonFlag = true;
		}
		else {
			return;
		}
	}
	else {
		m_boxDeleteButtonFlag = false;
		return;
	}

	//箱削除
	BoxMaker::GetInstance()->BoxDelete(m_upBox);
	m_upBox = nullptr;
	m_boxUpFlag = false;

}

CVector3 Player::BoxThrowSearch() {

	CVector3 MousePos = MouseSupporter::GetInstance()->GetMousePos_3D();

	btDiscreteDynamicsWorld* dw = g_physics->GetDynamicWorld();
	btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), MousePos);
	dw->rayTest((btVector3)g_camera3D.GetPosition(), MousePos, CRR_Callback);
	if (CRR_Callback.hasHit()) {

		//検索
		CVector3 ThrowTarget = CVector3::Zero();
		float TargetLength = BoxThrowMaxLength;
		bool TargetSetFlag = false;
		LevelSet::Obj_Data* obj_data = StageSet::GetInstance()->GetObjData();

		for (int i = 0; i < MAX_LEVEL_OBJ; i++) {
			if (wcscmp(obj_data->ObjName, L"") == 0) {
				//名前がない！強制終了
				break;
			}
			else {
				//検索して敵なら計算する
				ObjectClass* go = CGameObjectManager::GetInstance()->FindGO<ObjectClass>(obj_data->nameKey);
				if (go != nullptr) {
					if (go->m_object == ObjectClass::ObjectClass_Tag::EnemyObj) {
						//敵なので座標を取得して距離が近いなら上書き
						CVector3 diff = go->GetPosition() - CRR_Callback.m_hitPointWorld;
						float Len = diff.Length();
						if (Len <= TargetLength) {
							//上書き
							ThrowTarget = go->GetPosition();
							TargetLength = Len;
							TargetSetFlag = true;	//1度でも引っかかったらtrueになる
						}
					}
				}
			}
			obj_data++;
		}

		//最終結果
		if (TargetSetFlag == true) {
			//移動速度を計算して返す
			CVector3 diff = ThrowTarget - m_position;
			diff.Normalize();
			diff *= 100.0f;		//移動パワー
			diff.y = -3.0f;		//高さ
			return diff;
		}
		else {
			//どこにも引っかからなかった			
			CVector3 MoveSpeed = CRR_Callback.m_hitPointWorld - m_upBox->GetPosition();
			MoveSpeed.Normalize();
			MoveSpeed *= 100.0f;	//移動パワー
			MoveSpeed.y = 1.0f;		//高さ
			return MoveSpeed;
		}

	}
	else {
		CVector3 MoveSpeed = m_moveSpeed;
		MoveSpeed.Normalize();
		MoveSpeed *= 100.0f;	//移動パワー
		MoveSpeed.y = 1.0f;		//高さ
		return MoveSpeed;
	}

}

void Player::PlayerMiss(const CVector3& pos) {

	//ノックバックの計算
	CVector3 Pos = m_position;
	CVector3 Move = m_moveSpeed;
	Move.Normalize();
	Pos += (Move * m_damage_knockback);
	m_nextPos = Pos;

	m_moveSpeed = CVector3::Zero();
	m_moveSpeed.y = m_damage_YHosei;
	m_damage_Flag = true;
	m_damage_JumpFlag = false;
}