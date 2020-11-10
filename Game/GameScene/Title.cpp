#include "stdafx.h"
#include "Title.h"
#include "GameCamera.h"

Title* Title::m_instance = nullptr;

Title::Title()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//現在をタイトルにする
	SceneManager::GetInstance()->SetGameMode(SceneManager::TitleMode);
	//Dofを無効にする
	SceneManager::GetInstance()->GetGameGraphicInstance()->m_dofFlag = false;
	//明るくする
	LightMaker::GetInstance()->SetAmbientColor({ 1.0f, 1.0f, 1.0f });

	//初期設定
	Title::SetUp();

	//タイトルBGMの再生
	SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(L"Assets/sound/BGM/Title.wav");
}


Title::~Title()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

	//全て片付ける！！！
	DeleteGO(m_black);
	DeleteGO(m_bg1);
	DeleteGO(m_bg2);
	DeleteGO(m_ball);
	DeleteGO(m_dummyBox);
	for (auto iter = Rogo.TitleRogo_Circle.begin(); iter != Rogo.TitleRogo_Circle.end(); iter++) {
		DeleteGO(iter->second);
	}
	for (auto iter = Rogo.TitleRogo_Mozi.begin(); iter != Rogo.TitleRogo_Mozi.end(); iter++) {
		DeleteGO(iter->second);
	}
	DeleteGO(Rogo.m_titleRogo_Mozi_Hakobun);
	DeleteGO(m_command_Start);
	DeleteGO(m_command_Continue);
	DeleteGO(m_command_End);

	//BGMのフェードアウト
	SceneManager::GetInstance()->GetSoundManagerInstance()->BGM_VolumeFade(0.0f, 60);

}

void Title::Update() {

	switch (m_titleEffect)
	{
	case Title::Rogo_Effect:
		EffectUpdate_RogoEffect();
		break;
	case Title::Title_Effect:
		EffectUpdate_TitleEffect();
		break;
	case Title::Command_Wait:
		EffectUpdate_CommandWait();
		CommandSelect();	//コマンド選択待ち
		break;
	case Title::Command_Effect:
		EffectUpdate_CommandEffect();
		break;
	}

	//背景更新
	BG_Update();
	//アニメーション
	m_player.UpdateWorldMatrix(m_p_pos, m_p_rot, m_p_scl);
	m_playerAnimation.Play(0);
	m_playerAnimation.Update(1.0f / 20.0f);
	//箱の上下
	if (m_dummyBox->m_skinModelSupporter.GetSkinModelMoveListLen() == 0) {
		m_dummyBox->m_skinModelSupporter.SkinModelMove({ 0.0f,UpDownY,0.0f }, UpDownTime, 0, true);
		m_dummyBox->m_skinModelSupporter.SkinModelMove({ 0.0f,-UpDownY,0.0f }, UpDownTime, UpDownTime, true);
	}

	//カメラ
	g_camera3D.Update();
	//シャドウマップ
	//ShadowMap::GetInstance()->RegistShadowCaster(&m_player->GetModel_());
	//ShadowMap::GetInstance()->RegistShadowCaster(&m_dummyBox->GetModel_());
	//ShadowMap::GetInstance()->Update(lm->GetLightCameraPosition(), lm->GetLightCameraTarget());
}

void Title::Render() {
	m_player.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

/// <summary>
/// 最初に呼ぶ
/// レンダーの生成と画像設定
/// </summary>
void Title::SetUp() {

	//背景
	m_bg1 = NewGO<SpriteRender>("TitleSprite_BG1", 0);
	m_bg1->SetObjectTag(objectTag::t_BackSprite);
	m_bg1->Init(L"Assets/sprite/Title_BG.dds", FRAME_BUFFER_W, FRAME_BUFFER_H, BG1_Priority);
	m_bg1->SetPosition(CVector3::Zero());

	m_bg2 = NewGO<SpriteRender>("TitleSprite_BG2", 0);
	m_bg2->SetObjectTag(objectTag::t_BackSprite);
	m_bg2->Init(L"Assets/sprite/Title_BG.dds", FRAME_BUFFER_W, FRAME_BUFFER_H, BG2_Priority);
	m_bg2->SetPosition(CVector3::Zero());

	//ボール
	m_ball = NewGO<SkinModelRender>("TitleModel_Ball", 0);
	m_ball->Model_Init(L"Assets/modelData/Title_Ball.cmo");
	m_ball->SetPosition(Ball_DefPos);
	CQuaternion rot;
	rot.SetRotationDeg(Ball_RotAxis, Ball_RotAngle);
	m_ball->SetRotation(rot);
	m_ball->m_skinModelSupporter.SkinModelRotation(Ball_AutoRotAngle, Ball_AutoRotAxis, 1, 0, true);
	m_ball->SetShadowReciever(true);

	//プレイヤー	
	m_player.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	m_p_pos.Set(Ball_DefPos.x + Player_DefPos.x,
		Ball_DefPos.y + Player_DefPos.y,
		Ball_DefPos.z + Player_DefPos.z);
	m_p_scl.Set(Player_Scale, Player_Scale, Player_Scale);
	//プレイヤーの回転
	CQuaternion p_rot, p_rot2;
	p_rot.SetRotationDeg(CVector3::AxisX(), Plyer_RotAngleX);
	p_rot2.SetRotationDeg(CVector3::AxisY(), 180.0f + Ball_RotAngle);	//モデルが後ろを向いているので正面+ボールの回転
	p_rot *= p_rot2;
	m_p_rot = p_rot;
	m_player.SetShadowReciever(true);
	m_player.UpdateWorldMatrix(m_p_pos, m_p_rot, m_p_scl);
	//プレイヤーのアニメーション
	m_playerAnimationClips[0].Load(L"Assets/animData/run.tka");
	m_playerAnimationClips[0].SetLoopFlag(true);
	//アニメーションの初期化。
	m_playerAnimation.Init(
		m_player,					//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		m_playerAnimationClips,		//アニメーションクリップの配列。
		1							//アニメーションクリップの数。
	);

	//ボックス
	m_dummyBox = NewGO<SkinModelRender>("TitleModel_Box", 0);
	m_dummyBox->Model_Init(L"Assets/modelData/box.cmo");
	CVector3 Pl_Pos = m_p_pos;
	m_dummyBox->SetPosition({ Pl_Pos.x + DummyBoxHosei.x,
		Pl_Pos.y + DummyBoxHosei.y,
		Pl_Pos.z + DummyBoxHosei.z });
	m_dummyBox->SetRotation(p_rot);
	m_dummyBox->SetScale(DummyBoxScale);

	//コマンド
	m_command_Start = NewGO<SpriteRender>("TitleSprite_Command1", 0);
	m_command_Start->Init(L"Assets/sprite/Hazimekara.dds", CommandSpriteSize.x, CommandSpriteSize.y, Command_Priority);
	m_command_Start->SetPosition({ Command_DefPos.x, Command_DefPos.y + Command_Y_Up, Command_DefPos.z });

	m_command_Continue = NewGO<SpriteRender>("TitleSprite_Command2", 0);
	m_command_Continue->Init(L"Assets/sprite/Tudukikara.dds", CommandSpriteSize.x, CommandSpriteSize.y, Command_Priority);
	m_command_Continue->SetPosition({ Command_DefPos.x,
		Command_DefPos.y - Command_Y_Hosei + Command_Y_Up,
		Command_DefPos.z });

	m_command_End = NewGO<SpriteRender>("TitleSprite_Command3", 0);
	m_command_End->Init(L"Assets/sprite/End.dds", CommandSpriteSize.x, CommandSpriteSize.y, Command_Priority);
	m_command_End->SetPosition({ Command_DefPos.x,
		Command_DefPos.y - (Command_Y_Hosei*2.0f) + Command_Y_Up,
		Command_DefPos.z });

	//ロゴ土台
	m_black = NewGO<SpriteRender>("TitleSprite_Black", 0);
	m_black->Init(L"Assets/sprite/black.dds", FRAME_BUFFER_W, FRAME_BUFFER_H, Black_Priority);
	m_black->SetPosition(CVector3::Zero());

	//ロゴサイクル
	Rogo.TitleRogo_Circle["Circle1"] = NewGO<SpriteRender>("TitleSprite_RogoCircle1", 0);
	Rogo.TitleRogo_Circle["Circle2"] = NewGO<SpriteRender>("TitleSprite_RogoCircle2", 0);
	Rogo.TitleRogo_Circle["Circle3"] = NewGO<SpriteRender>("TitleSprite_RogoCircle3", 0);
	Rogo.TitleRogo_Circle["Circle4"] = NewGO<SpriteRender>("TitleSprite_RogoCircle4", 0);
	Rogo.TitleRogo_Circle["Circle5"] = NewGO<SpriteRender>("TitleSprite_RogoCircle5", 0);
	Rogo.TitleRogo_Circle["Circle6"] = NewGO<SpriteRender>("TitleSprite_RogoCircle6", 0);
	Rogo.TitleRogo_Circle["Circle7"] = NewGO<SpriteRender>("TitleSprite_RogoCircle7", 0);
	Rogo.TitleRogo_Circle["Circle8"] = NewGO<SpriteRender>("TitleSprite_RogoCircle8", 0);

	Rogo.TitleRogo_Circle["Circle1"]->Init(L"Assets/sprite/Logo_Circle1.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Circle["Circle2"]->Init(L"Assets/sprite/Logo_Circle2.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Circle["Circle3"]->Init(L"Assets/sprite/Logo_Circle3.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Circle["Circle4"]->Init(L"Assets/sprite/Logo_Circle4.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Circle["Circle5"]->Init(L"Assets/sprite/Logo_Circle5.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Circle["Circle6"]->Init(L"Assets/sprite/Logo_Circle6.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Circle["Circle7"]->Init(L"Assets/sprite/Logo_Circle7.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Circle["Circle8"]->Init(L"Assets/sprite/Logo_Circle8.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);

	//共通設定
	for (auto iter = Rogo.TitleRogo_Circle.begin(); iter != Rogo.TitleRogo_Circle.end(); iter++) {
		iter->second->SetPosition({ Rogo.RogoDefPos.x,Rogo.RogoDefPos.y,Rogo.RogoDefPos.z });
		iter->second->SetAlpha(0.0f);
		iter->second->SetScale(0.0f);
	}

	//ここから文字
	Rogo.TitleRogo_Mozi["Mozi1"] = NewGO<SpriteRender>("TitleSprite_RogoMozi1", 0);
	Rogo.TitleRogo_Mozi["Mozi2"] = NewGO<SpriteRender>("TitleSprite_RogoMozi2", 0);
	Rogo.TitleRogo_Mozi["Mozi3"] = NewGO<SpriteRender>("TitleSprite_RogoMozi3", 0);
	Rogo.TitleRogo_Mozi["Mozi4"] = NewGO<SpriteRender>("TitleSprite_RogoMozi4", 0);
	Rogo.TitleRogo_Mozi["Mozi5"] = NewGO<SpriteRender>("TitleSprite_RogoMozi5", 0);

	Rogo.TitleRogo_Mozi["Mozi1"]->Init(L"Assets/sprite/Logo_Ha.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Mozi["Mozi2"]->Init(L"Assets/sprite/Logo_Ko.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Mozi["Mozi3"]->Init(L"Assets/sprite/Logo_Bu.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Mozi["Mozi4"]->Init(L"Assets/sprite/Logo_N.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.TitleRogo_Mozi["Mozi5"]->Init(L"Assets/sprite/Logo_Bikkuri.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);

	for (auto iter = Rogo.TitleRogo_Mozi.begin(); iter != Rogo.TitleRogo_Mozi.end(); iter++) {
		iter->second->SetPosition({ Rogo.RogoDefPos.x,Rogo.RogoDefPos.y,Rogo.RogoDefPos.z });
		iter->second->SetAlpha(0.0f);
		iter->second->SetScale(0.0f);
	}

	//ミニ文字
	Rogo.m_titleRogo_Mozi_Hakobun = NewGO<SpriteRender>("TitleSprite_HakobunMini", 0);
	Rogo.m_titleRogo_Mozi_Hakobun->Init(L"Assets/sprite/Logo_hakobun.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.m_titleRogo_Mozi_Hakobun->SetPosition({ Rogo.RogoDefPos.x,Rogo.RogoDefPos.y,Rogo.RogoDefPos.z });
	Rogo.m_titleRogo_Mozi_Hakobun->SetAlpha(0.0f);

}

/// <summary>
/// エフェクト
/// </summary>
void Title::EffectUpdate_RogoEffect() {

	//初期設定
	if (m_rogoEffectTimer == 0.0f) {
		//サイクル
		int Delay = 0;
		for (auto iter = Rogo.TitleRogo_Circle.begin(); iter != Rogo.TitleRogo_Circle.end(); iter++) {
			//まとめて演出
			iter->second->m_spriteSupporter.SpriteScale(Rogo.RogoCircleMaxScale, 
				Rogo.RogoCircleScaleTime, 
				Delay);
			iter->second->m_spriteSupporter.SpriteScale(1.0f,
				Rogo.RogoCircleScaleTime / 2,
				Delay + Rogo.RogoCircleScaleTime);
			iter->second->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, 
				Rogo.RogoCircleScaleTime,
				Delay);
			Delay += Rogo.RogoCircleDelay;		//ディレイをかける
		}
		//文字
		Delay = 0;
		bool UpDounFlag = false;
		for (auto iter = Rogo.TitleRogo_Mozi.begin(); iter != Rogo.TitleRogo_Mozi.end(); iter++) {
			//まとめて演出
			iter->second->SetScale({ 1.0f,0.0f,1.0f });
			//Y補正
			float Y_Hosei = Rogo.RogoMoziStartHosei;
			if (UpDounFlag == true) {
				Y_Hosei *= -1.0f;
			}
			iter->second->SetPosition({ 0.0f,Y_Hosei,1.0f });
			//移動処理
			float Y_Move = Rogo.RogoMoziMove;
			if (UpDounFlag == true) {
				Y_Move *= -1.0f;
			}
			iter->second->m_spriteSupporter.SpriteMove({ 0.0f,Y_Move },
				Rogo.RogoMoziTime,
				Delay + Rogo.RogoMoziDelay, true);
			//バウンド
			Y_Move = (Y_Hosei + Y_Move)* -1.0f;
			iter->second->m_spriteSupporter.SpriteMove({ 0.0f, Y_Move },
				Rogo.RogoMoziTime / 2, 
				Delay + Rogo.RogoMoziTime + Rogo.RogoMoziDelay, true);
			//拡大率
			iter->second->m_spriteSupporter.SpriteScale({ 1.0f,0.5f,1.0f }, 
				Rogo.RogoMoziTime,
				Delay + Rogo.RogoMoziDelay);
			iter->second->m_spriteSupporter.SpriteScale({ 1.0f,1.0f,1.0f },
				Rogo.RogoMoziTime / 2,
				Delay + Rogo.RogoMoziTime + Rogo.RogoMoziDelay);
			//アルファ
			iter->second->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f },
				Rogo.RogoMoziTime,
				Delay + Rogo.RogoMoziDelay);
			//終了
			if (UpDounFlag == false) {
				UpDounFlag = true;
			}
			else {
				UpDounFlag = false;
			}
			Delay += Rogo.RogoMoziDelay;		//ディレイをかける
		}
		//ミニ文字
		Rogo.m_titleRogo_Mozi_Hakobun->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f },
			Rogo.RogoMiniMoziFadeTime,
			Delay + Rogo.RogoMiniMoziFadeDelay);
	}

	//終了
	m_rogoEffectTimer += CGameTime::GetFrameDeltaTime();

	if (m_rogoEffectTimer >= RogoEffectRimit) {
		//このエフェクトは終了
		m_titleEffect = Title_Effect;
	}
}

void Title::EffectUpdate_TitleEffect() {

	//初期設定
	if (m_titleEffectTimer == 0.0f) {
		//ロゴを左上へ移動
		{
			for (auto iter = Rogo.TitleRogo_Circle.begin(); iter != Rogo.TitleRogo_Circle.end(); iter++) {
				iter->second->m_spriteSupporter.SpriteMove(TitleRogoPos, TitleMoveTime, 0, false);
				iter->second->m_spriteSupporter.SpriteScale(TitleRogoScale, TitleMoveTime, 0);
			}
			for (auto iter = Rogo.TitleRogo_Mozi.begin(); iter != Rogo.TitleRogo_Mozi.end(); iter++) {
				iter->second->m_spriteSupporter.SpriteMove(TitleRogoPos, TitleMoveTime, 0, false);
				iter->second->m_spriteSupporter.SpriteScale(TitleRogoScale, TitleMoveTime, 0);
			}
			Rogo.m_titleRogo_Mozi_Hakobun->m_spriteSupporter.SpriteMove(TitleRogoPos, TitleMoveTime, 0, false);
			Rogo.m_titleRogo_Mozi_Hakobun->m_spriteSupporter.SpriteScale(TitleRogoScale, TitleMoveTime, 0);
		}
		//黒いカバーをフェードアウトさせてタイトル画面を見せる
		m_black->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, TitleFadeTime, 0);
	}

	//コマンド落下
	if (m_titleEffectTimer >= TitleCommandEffectRimit && m_commandMoveFlag == false) {

		//コマンド落下演出
		{
			m_command_End->m_spriteSupporter.SpriteMove({ 0.0f,-(Command_Y_Up + TitleCommandDrop_YHosei) },
				TitleCommandDrop_Time, 0, true);
			m_command_End->m_spriteSupporter.SpriteMove({ 0.0f,TitleCommandDrop_YHosei },
				TitleCommandDrop_Time / 2, TitleCommandDrop_Time, true);
			//
			m_command_Continue->m_spriteSupporter.SpriteMove({ 0.0f,-(Command_Y_Up + TitleCommandDrop_YHosei) },
				TitleCommandDrop_Time, TitleCommandDrop_Delay, true);
			m_command_Continue->m_spriteSupporter.SpriteMove({ 0.0f,TitleCommandDrop_YHosei },
				TitleCommandDrop_Time / 2, TitleCommandDrop_Time + TitleCommandDrop_Delay, true);
			//
			m_command_Start->m_spriteSupporter.SpriteMove({ 0.0f,-(Command_Y_Up + TitleCommandDrop_YHosei) },
				TitleCommandDrop_Time, TitleCommandDrop_Delay * 2, true);
			m_command_Start->m_spriteSupporter.SpriteMove({ 0.0f,TitleCommandDrop_YHosei },
				TitleCommandDrop_Time / 2, TitleCommandDrop_Time + (TitleCommandDrop_Delay * 2), true);
		}
		m_commandMoveFlag = true;
	}

	//終了
	m_titleEffectTimer += CGameTime::GetFrameDeltaTime();

	if (m_titleEffectTimer >= TitleEffectRimit) {
		//このエフェクトは終了
		m_titleEffect = Command_Wait;
	}
}

void Title::EffectUpdate_CommandWait() {

	//選択待ち

	//ロゴエフェクト
	if (Rogo.TitleRogo_Mozi["Mozi5"]->m_spriteSupporter.GetSpriteScaleListLen() == 0) {
		int Delay = 0;
		for (auto iter = Rogo.TitleRogo_Mozi.begin(); iter != Rogo.TitleRogo_Mozi.end(); iter++) {
			iter->second->m_spriteSupporter.SpriteScale(LogoEffectScale, LogoEffectTime, Delay);
			Delay += LogoEffectTime;
			iter->second->m_spriteSupporter.SpriteScale(TitleRogoScale, LogoEffectTime, Delay);
			Delay += LogoEffectTime + LogoEffectInterval;
		}
		Delay += LogoEffectIntervalHosei;
		Rogo.TitleRogo_Mozi["Mozi5"]->m_spriteSupporter.SpriteScale(TitleRogoScale, 1, Delay);
	}

}

void Title::EffectUpdate_CommandEffect() {

	//演出
	if (m_commandStartEffectTimer == 0.0f) {

		//トランジション
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox, 
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, false);

		switch (m_memberCommand)
		{
		case Title::No_Select:
			std::abort();	//ありえないこと
			break;
		case Title::Game_Start:
			m_command_Continue->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, CommandAlphaTime, 0);
			m_command_End->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, CommandAlphaTime, 0);
			break;
		case Title::Game_Continue:
			m_command_Start->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, CommandAlphaTime, 0);
			m_command_End->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, CommandAlphaTime, 0);
			break;
		case Title::Game_End:
			m_command_Start->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, CommandAlphaTime, 0);
			m_command_Continue->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, CommandAlphaTime, 0);
			break;
		}
	}

	//終了
	m_commandStartEffectTimer += CGameTime::GetFrameDeltaTime();

	if (m_commandStartEffectTimer >= CommandStartEffectRimit) {
		//ゲームマネージャーに処理をしてもらう
		m_nowCommand = m_memberCommand;
	}

}

void Title::BG_Update() {

	if (m_bgMoveTimer == 0.0f) {

		m_bg1->m_spriteSupporter.SpriteDelayReset();
		m_bg2->m_spriteSupporter.SpriteDelayReset();

		if (m_BG_MoveMode == false) {
			m_bg1->SetPosition(CVector3::Zero());
			m_bg2->SetPosition({ -FRAME_BUFFER_W,0.0f,0.0f });
			m_BG_MoveMode = true;
		}
		else {
			m_bg2->SetPosition(CVector3::Zero());
			m_bg1->SetPosition({ -FRAME_BUFFER_W,0.0f,0.0f });
			m_BG_MoveMode = false;
		}

		//移動の指示を出す
		m_bg1->m_spriteSupporter.SpriteMove({ FRAME_BUFFER_W,0.0f }, BG_MoveTime, 0, true);
		m_bg2->m_spriteSupporter.SpriteMove({ FRAME_BUFFER_W,0.0f }, BG_MoveTime, 0, true);
	}

	//時間経過
	m_bgMoveTimer++;

	//リセット
	if (m_bgMoveTimer >= BG_MoveTime) {
		m_bgMoveTimer = 0;
	}

}

void Title::CommandSelect() {

	//どのコマンドにもマウスカーソルが重なってない場合用
	bool HitFlag = false;

	//各コマンド受付
	//スタート
	if (m_command_Start->MouseOverMouse() == true) {

		HitFlag = true;

		if (m_memberCommand != Game_Start) {
			//初回演出
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");	//SE
			m_command_Start->SetMulColor(CommandMulColor);
			m_command_Start->m_spriteSupporter.SpriteMove({ 0.0f,CommandSelectMove }, CommandSelectMoveTime, 0, true);
			m_command_Start->m_spriteSupporter.SpriteMove({ 0.0f,-CommandSelectMove }, CommandSelectMoveTime, CommandSelectMoveTime, true);
			m_memberCommand = Game_Start;
		}

	}
	else {
		//戻す
		m_command_Start->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

	}
	//コンティニュー
	if (m_command_Continue->MouseOverMouse() == true) {
		HitFlag = true;

		if (m_memberCommand != Game_Continue) {
			//初回演出
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");	//SE
			m_command_Continue->SetMulColor(CommandMulColor);
			m_command_Continue->m_spriteSupporter.SpriteMove({ 0.0f,CommandSelectMove }, CommandSelectMoveTime, 0, true);
			m_command_Continue->m_spriteSupporter.SpriteMove({ 0.0f,-CommandSelectMove }, CommandSelectMoveTime, CommandSelectMoveTime, true);
			m_memberCommand = Game_Continue;
		}

	}
	else {
		m_command_Continue->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	}
	//エンド
	if (m_command_End->MouseOverMouse() == true) {
		HitFlag = true;

		if (m_memberCommand != Game_End) {
			//初回演出
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");	//SE
			m_command_End->SetMulColor(CommandMulColor);
			m_command_End->m_spriteSupporter.SpriteMove({ 0.0f,CommandSelectMove }, CommandSelectMoveTime, 0, true);
			m_command_End->m_spriteSupporter.SpriteMove({ 0.0f,-CommandSelectMove }, CommandSelectMoveTime, CommandSelectMoveTime, true);
			m_memberCommand = Game_End;
		}

	}
	else {
		m_command_End->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	}

	//共通処理
	if (HitFlag == false) {
		//どこにも重なってないので初期化する
		m_memberCommand = No_Select;
	}
	else {
		//左クリックされたら確定させる
		if (MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key) == MouseSupporter::Release_Push) {
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/GameStart.wav", 2.0f);
			m_titleEffect = Command_Effect;
		}
	}

}