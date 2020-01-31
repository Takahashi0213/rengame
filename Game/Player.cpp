#include "stdafx.h"
#include "Player.h"
#include "BulletCollision/CollisionDispatch/btCollisionWorld.h"
#include "GameUI.h"

int Game_UI = Hash::MakeHash("GameUI");

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_model_Sl.Init(L"Assets/modelData/unityChan.cmo");
	//m_model.SetEmissionColor({ 100.0f,1.0f,1.0f });
	m_model_Sl.SetRenderMode(RenderMode::Silhouette);

	//ワールド行列の更新。
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_nextPos = m_position;		//移動先を初期化

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(25, 30, m_position);

	//ライトメーカーの取得
	int a = Hash::MakeHash("LightMaker");
	m_lightMaker = CGameObjectManager::GetInstance()->FindGO<LightMaker>(a);

	//シャドウレシーバーにする。
	m_model.SetShadowReciever(true);

	//ニセプレイヤーの作成
	//SkinModelRender* smr = NewGO<SkinModelRender>("Player2", 0);
	//smr->Model_Init(L"Assets/modelData/unityChan.cmo");
	//smr->SetPosition({ 100.0f,50.0f,100.0f });

	//スプライトマスクのテスト

	//SpriteRender* MainSprite = NewGO<SpriteRender>("TEST", 0);
	//MainSprite->ChangeMaskSprite();
	//MainSprite->Init(L"Assets/sprite/fukidasi.dds", 600.0f, 400.0f, 0);
	//MainSprite->SetPosition({ 250.0f,-50.0f ,0.0f });
	//MainSprite->InitSub(L"Assets/sprite/keis.dds", 588.0f, 1240.0f, 0);
	//MainSprite->SetPosition({ 250.0f,-250.0f ,0.0f }, true);
	//MainSprite->m_spriteSupporter.SpriteRotation(10.0f, 600, 0, true);

	//if (g_pad[0].IsTrigger(enButtonA)) {
	//	CGameObjectManager::GetInstance()->DeleteGO(this);
	//}
	//if (g_pad[0].IsTrigger(enButtonB)) {
	//	int s = CGameObjectManager::GetInstance()->ObjCount<Player>(a);
	//	Player* p = CGameObjectManager::GetInstance()->FindGO<Player>(a,false);
	//}

	m_titan.Init(L"Assets/modelData/Titan.cmo");
	m_titan.UpdateWorldMatrix({ 0.0f,30.0f,0.0f }, CQuaternion::Identity(), { 5.0f,5.0f,5.0f });

	//法線マップをロード。
	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Titan_normals.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_normalMapSRV);

	//モデルに法線マップを設定する。
	m_titan.SetNormalMap(m_normalMapSRV);

	//スペキュラマップをロード。
	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Titan_Metallic.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_specMapSRV);

	//モデルにスペキュラマップを設定する。
	m_titan.SetSpecMap(m_specMapSRV);


}

Player::~Player()
{

}

void Player::Update()
{
	hoge = 10;
	if (hoge == 0) {
		//GameEffect::GetInstance()->EasyEffect(L"ああ感\Rいい\Dうう\n\Rええ\Dおお",
		GameEffect::GetInstance()->EasyEffect(L"ああ感いいうう\nええおお",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
		hoge++;
	}
	if (hoge == 2) {
		GameEffect::GetInstance()->EasyEffect(L"今日もいい天気", GameEffect_Stand::Stand_Happy);
		hoge++;
	}
	if (hoge == 4) {
		GameEffect::GetInstance()->EasyEffect(L"ご飯食ってて\n喋れません",
			GameEffect_Stand::Stand_Sad,
			GameEffect_Stand::Shake_Stand);
		hoge++;
	}	
	if (hoge == 6) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::Jump_Stand);
		GameEffect::GetInstance()->GetInstance_Message()->MessageEffect(L"笑いやがった");
		hoge++;
	}
	if (hoge == 8) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		hoge++;
	}
	if (GameEffect::GetInstance()->GetInstance_Message()->GetMessageOkuriFlag() == true) {
		hoge++;
	}

	//モノクロになーる
	if (m_gameObj != nullptr) {
		if (m_gameObj->GetGameMode() == Game::CreateMode && m_monochromeFlag == false) {
			m_model.SetRenderMode(RenderMode::Monochrome);
			m_monochromeFlag = true;
		}
		else if (m_gameObj->GetGameMode() != Game::CreateMode && m_monochromeFlag == true) {
			m_model.SetRenderMode(RenderMode::Default);
			m_monochromeFlag = false;
		}
	}

	Move();

	bool OnG_Flag = m_charaCon.IsOnGround();

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		if (m_jumpNow == false && OnG_Flag == true) {
			Jump();
		}
		m_jumpNow = true;
	}
	else {
		m_jumpNow = false;
	}

	//ワールド行列の更新。
	m_model_Sl.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	if (m_gameObj->GetGameMode() == Game::ActionMode){ //アクションモードでなければ更新しない！

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
	//ターゲットも！
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
	m_titan.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}

void Player::Move() {

	//左クリックの状態を判定
	int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
	bool OnG_Flag = m_charaCon.IsOnGround();
	GameUI* ui = CGameObjectManager::GetInstance()->FindGO<GameUI>(Game_UI);

	if (key == MouseSupporter::Release_Push && m_gameObj->GetGameMode() == Game::ActionMode
		&& ui->GetGemeMenu()->GetSelectFlag() == false) {
		if (MouseSupporter::GetInstance()->GetMouseTimer(MouseSupporter::Left_Key) < 12) {

			m_nextPos = MouseSupporter::GetInstance()->GetMousePos_3D();

			//btCollisionWorld::ClosestRayResultCallback ResultCallback();
			btDiscreteDynamicsWorld* dw = g_physics.GetDynamicWorld();
			btCollisionWorld::ClosestRayResultCallback CRR_Callback(g_camera3D.GetPosition(), m_nextPos);
			dw->rayTest((btVector3)g_camera3D.GetPosition(), m_nextPos, CRR_Callback);
			if (CRR_Callback.hasHit()) {
				m_nextPos = CRR_Callback.m_hitPointWorld;
			}
			else {
				m_nextPos = m_position;
			}

		}
	}

	m_nextPos.y = m_position.y;

	m_moveSpeed.x = m_nextPos.x - m_position.x;
	m_moveSpeed.z = m_nextPos.z - m_position.z;
	m_moveSpeed.x /= 20.0f;
	m_moveSpeed.z /= 20.0f;

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

	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3().AxisY(), angle);

}

void Player::Jump() {
	
	m_moveSpeed.y = m_jumpPower;

}