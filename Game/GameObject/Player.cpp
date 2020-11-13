#include "stdafx.h"
#include "Player.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"

#include "GameSystem/GameUI/GameUI.h"
#include "GameSystem/Box/BoxMaker.h"
#include "GameCamera.h"

Player::Player()
{
	//スキンモデルレンダーの生成
	m_playerModel = new SkinModelRender;
	m_playerModel_Sl = new SkinModelRender;

	//アニメーション
	m_playerAnimationClips[enAnimationClip_Idle].Load(L"Assets/animData/idle.tka");
	m_playerAnimationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_playerAnimationClips[enAnimationClip_Run].Load(L"Assets/animData/run.tka");
	m_playerAnimationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_playerAnimationClips[enAnimationClip_Jump].Load(L"Assets/animData/jump.tka");
	m_playerAnimationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_playerAnimationClips[enAnimationClip_Damage].Load(L"Assets/animData/damage.tka");
	m_playerAnimationClips[enAnimationClip_Damage].SetLoopFlag(false);
	m_playerAnimationClips[enAnimationClip_GameOver].Load(L"Assets/animData/KneelDown.tka");
	m_playerAnimationClips[enAnimationClip_GameOver].SetLoopFlag(false);
	m_playerAnimationClips[enAnimationClip_Clear].Load(L"Assets/animData/clear.tka");
	m_playerAnimationClips[enAnimationClip_Clear].SetLoopFlag(false);

	//cmoファイルの読み込み。
	m_playerModel->Model_Init_Anim(L"Assets/modelData/unityChan.cmo",
		m_playerAnimationClips, enAnimationClip_Num, enFbxUpAxisY);
	m_playerModel_Sl->Model_Init_Anim(L"Assets/modelData/unityChan.cmo",
		m_playerAnimationClips, enAnimationClip_Num, enFbxUpAxisY);
	m_playerModel_Sl->SetRenderMode(RenderMode::Silhouette);
	m_playerModel->PlayAnimation(enAnimationClip_Idle);
	m_playerModel_Sl->PlayAnimation(enAnimationClip_Idle);

	//ワールド行列の更新。
	m_playerModel->SetUp(m_position, m_rotation, m_scale);
	m_playerModel_Sl->SetUp(m_position, m_rotation, m_scale);
	m_nextPos = m_position;		//移動先を初期化

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(Radius, Height, m_position);

	//ライトメーカーの取得
	m_lightMaker = LightMaker::GetInstance();

	//シャドウレシーバーにする。
	m_playerModel->SetShadowReciever(true);

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
	if (Game::GetInstance() != nullptr) {
		if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode && m_monochromeFlag == false) {
			m_playerModel->SetRenderMode(RenderMode::Monochrome);
			m_monochromeFlag = true;
		}
		else if (SceneManager::GetInstance()->GetGameMode() != SceneManager::CreateMode && m_monochromeFlag == true) {
			m_playerModel->SetRenderMode(RenderMode::Default);
			m_monochromeFlag = false;
		}
	}

	//処理

	//持ち上げ中の箱の座標をプレイヤーに合わせる
	BoxUp();
	//移動
	MoveClick();
	Move();
	//地上にいたらジャンプ
	Jump();
	//持ち上げる箱を探す
	BoxSearch();
	//キーが押されたら持ち上げたり下ろしたりする
	BoxCatch();
	BoxPut();
	//キーが押されたら持ち上げている箱を削除する
	BoxDelete();
	//上げ下げ中の補完移動をする
	BoxMove();

	//アニメーション
	PlayerAnimation();

	//ゲームオーバー演出
	if (m_gameOverFlag == true) {
		m_gameOvetTimer++;
		if (m_gameOvetTimer == GameOverLimit) {
			m_playerModel->SetDrawFlag(false);
		}
	}

	//モデルの更新。
	m_playerModel->SetUp(m_position, m_rotation, m_scale);
	m_playerModel_Sl->SetUp(m_position, m_rotation, m_scale);
	m_playerModel->Update();
	m_playerModel_Sl->Update();

	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::ActionMode){ //アクションモードでなければ更新しない！

		if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true &&
			SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag == false) {
			//何もしない
		}
		else {
			//重力
			m_moveSpeed.y -= m_gravity;
			//キャラコン移動
			m_position = m_charaCon.Execute(1.0f, m_moveSpeed);
		}
	}

	//シャドウキャスターを登録。
	ShadowMap::GetInstance()->RegistShadowCaster(m_playerModel->GetModel());
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
	//グラフィック座標を更新（ディザリング用）
	SceneManager::GetInstance()->GetGameGraphicInstance()->m_playerPos = m_position;
}

void Player::Render()
{
	m_playerModel_Sl->Render();
	m_playerModel->Render();
}

void Player::PlayerAnimation() {

	//クリエイトモードかメニューモードの時中断
	if (SceneManager::GetInstance()->GetGameMode() == SceneManager::CreateMode ||
		SceneManager::GetInstance()->GetGameMode() == SceneManager::MenuMode) {
		return;
	}

	//アニメーション再生
	bool RunFlag = false;
	bool OnG_Flag = m_charaCon.IsOnGround();
	float MovePower = m_moveSpeed.Length();
	if (OnG_Flag == false) {
		if (m_damage_JumpFlag == false) {
			m_playerModel->PlayAnimation(enAnimationClip_Jump);
			m_playerModel_Sl->PlayAnimation(enAnimationClip_Jump);
		}
		else {
			m_playerModel->PlayAnimation(enAnimationClip_Damage);
			m_playerModel_Sl->PlayAnimation(enAnimationClip_Damage);
		}
	}
	else {
		if (MovePower > 1.0f) {
			m_playerModel->PlayAnimation(enAnimationClip_Run);
			m_playerModel_Sl->PlayAnimation(enAnimationClip_Run);
			RunFlag = true;
		}
		else {
			m_playerModel->PlayAnimation(enAnimationClip_Idle);
			m_playerModel_Sl->PlayAnimation(enAnimationClip_Idle);
		}
	}
	//アニメーションアップデート
	if (RunFlag == false) {
		m_playerModel->SetAnimationSpeed();
		m_playerModel_Sl->SetAnimationSpeed();
	}
	else {
		MovePower = min(MovePower, 35.0f);
		m_playerModel->SetAnimationSpeed(40.0f - MovePower);
		m_playerModel_Sl->SetAnimationSpeed(40.0f - MovePower);
	}

}

void Player::MoveClick() {

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
	if (m_ui == nullptr) {
		m_ui = CGameObjectManager::GetInstance()->FindGO<GameUI>(Hash::MakeHash("GameUI"));
	}

	//左キーが離された＆現在アクションモード＆メニューボタンに被っていない＆ノックバック中でない
	if (key == MouseSupporter::Release_Push &&
		SceneManager::GetInstance()->GetGameMode() == SceneManager::ActionMode &&
		m_ui->GetGemeMenu()->GetSelectFlag() == false &&
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
			//エフェクト
			EffekseerSupporter::GetInstance()->EffectDelete(m_moveEffect);
			m_moveEffect = EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::PlayerMove,
				false, m_nextPos.x, m_nextPos.y, m_nextPos.z);
			//現在位置のバックアップ
			if (m_jumpNow == false) {
				m_posBackup = m_position;
			}
		}
	}

}

void Player::Move() {

	//イベント中かつEventMoveしないなら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true &&
		SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag == false) {
		return;
	}
	//箱の上げ下ろし中は強制終了
	if (m_boxMoveFlag == true) {
		return;
	}

	//移動
	m_nextPos.y = m_position.y;

	m_moveSpeed.x = m_nextPos.x - m_position.x;
	m_moveSpeed.z = m_nextPos.z - m_position.z;
	m_moveSpeed.x /= MoveHosei;
	m_moveSpeed.z /= MoveHosei;

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

	//移動している時はSEを再生する
	MoveSE();

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
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Jump.wav", 1.5f);
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
			m_upOrDown = false;			//箱を上げてるフラグ
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/BoxCatch.wav", 2.0f);

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

		//投げる
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/BoxThrow.wav");
		CVector3 MoveSpeed = BoxThrowSearch();
		m_upBox->SetMoveSpeed(MoveSpeed);

		//リセット
		m_boxUpFlag = false;
		m_upBox = nullptr;

	}

}

void Player::BoxPut() {

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

	//箱を持ち上げていないなら強制終了
	if (m_boxUpFlag == false) {
		return;
	}

	//対応するボタンが押されてないなら強制終了
	if (HIWORD(GetAsyncKeyState(GameData::GetInstance()->GetBoxPutKey()))) {
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

	//効果音
	SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/BoxCatch.wav");
	//リセット
	m_boxUpFlag = false;
	m_boxMoveFlag = true;
	m_upOrDown = true;	//箱を下ろしてるフラグ
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

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

	//イベント中かつEventMoveしないなら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true &&
		SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag == false) {
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
			CVector3 diff = ThrowTarget - m_upBox->GetPosition();
			diff.Normalize();
			diff *= 100.0f;		//移動パワー
			diff.y = -3.0f;		//高さ
			//エフェクト
			m_moveEffect = EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::EnemyScope,
				false, ThrowTarget.x, ThrowTarget.y + BoxThrowEffect_Y_Hosei, ThrowTarget.z);
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

void Player::MoveSE() {

	//アクションモードでないなら強制終了
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}

	float MovePower = m_moveSpeed.Length();
	bool OnG_Flag = m_charaCon.IsOnGround();

	//移動力が足りないので強制終了
	if (MovePower < 1.0f) {
		return;
	}
	//空中にいるので強制終了
	if (OnG_Flag == false) {
		return;
	}

	//タイマー加算
	m_stepSE_Timer += CGameTime::GetFrameDeltaTime() * MovePower;

	//SE再生
	if (m_stepSE_Timer >= StepSE_Limit) {
		m_stepSE_Timer = 0.0f;
		if (m_stepSE_LeftRight == false) {
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/PlayerStep_Left.wav", StepVolume);
			m_stepSE_LeftRight = true;
		}
		else {
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/PlayerStep_Right.wav", StepVolume);
			m_stepSE_LeftRight = false;
		}
	}
}

void Player::PlayerMiss(const CVector3& pos) {

	//ノックバックの計算
	CVector3 Pos = m_position;
	CVector3 Move = m_moveSpeed;
	Move.Normalize();
	Pos += (Move * m_damage_knockback);
	m_nextPos = Pos;
	//ノックバック設定
	m_moveSpeed = CVector3::Zero();
	m_moveSpeed.y = m_damage_YHosei;
	m_damage_Flag = true;
	m_damage_JumpFlag = false;
	SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/PlayerDamage.wav");

}

void Player::SetPosition(const CVector3& pos) {

	//座標の設定
	m_moveSpeed = CVector3::Zero();
	m_nextPos = pos;
	m_position = pos;
	m_charaCon.SetPosition(pos);
	GameCamera::GetInstance()->ActionModeCameraMove();	//カメラも動かす

}

void Player::GemaOverFlag() {
	m_gameOverFlag = true;
	SetMoveTarget(m_position);
	//エフェクト
	CVector3 pos = m_position;
	CVector3 hosei = g_camera3D.GetPosition() - m_position;
	hosei.Normalize();
	hosei *= 50.0f;
	pos += hosei;

	EffekseerSupporter::GetInstance()->NewEffect_Vector(EffekseerSupporter::EffectData::PlayerDeath,
		false, pos.x, pos.y, pos.z);
}
