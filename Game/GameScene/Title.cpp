#include "stdafx.h"
#include "Title.h"
#include "GameCamera.h"

Title* Title::m_instance = nullptr;

Title::Title()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//���݂��^�C�g���ɂ���
	SceneManager::GetInstance()->SetGameMode(SceneManager::TitleMode);
	//Dof�𖳌��ɂ���
	SceneManager::GetInstance()->GetGameGraphicInstance()->m_dofFlag = false;
	//���邭����
	LightMaker::GetInstance()->SetAmbientColor({ 1.0f, 1.0f, 1.0f });

	//�����ݒ�
	Title::SetUp();

	//�^�C�g��BGM�̍Đ�
	SceneManager::GetInstance()->GetSoundManagerInstance()->InitBGM(L"Assets/sound/BGM/Title.wav");
}


Title::~Title()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

	//�S�ĕЕt����I�I�I
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

	//BGM�̃t�F�[�h�A�E�g
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
		CommandSelect();	//�R�}���h�I��҂�
		break;
	case Title::Command_Effect:
		EffectUpdate_CommandEffect();
		break;
	}

	//�w�i�X�V
	BG_Update();
	//�A�j���[�V����
	m_player.UpdateWorldMatrix(m_p_pos, m_p_rot, m_p_scl);
	m_playerAnimation.Play(0);
	m_playerAnimation.Update(1.0f / 20.0f);
	//���̏㉺
	if (m_dummyBox->m_skinModelSupporter.GetSkinModelMoveListLen() == 0) {
		m_dummyBox->m_skinModelSupporter.SkinModelMove({ 0.0f,UpDownY,0.0f }, UpDownTime, 0, true);
		m_dummyBox->m_skinModelSupporter.SkinModelMove({ 0.0f,-UpDownY,0.0f }, UpDownTime, UpDownTime, true);
	}

	//�J����
	g_camera3D.Update();
	//�V���h�E�}�b�v
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
/// �ŏ��ɌĂ�
/// �����_�[�̐����Ɖ摜�ݒ�
/// </summary>
void Title::SetUp() {

	//�w�i
	m_bg1 = NewGO<SpriteRender>("TitleSprite_BG1", 0);
	m_bg1->SetObjectTag(objectTag::t_BackSprite);
	m_bg1->Init(L"Assets/sprite/Title_BG.dds", FRAME_BUFFER_W, FRAME_BUFFER_H, BG1_Priority);
	m_bg1->SetPosition(CVector3::Zero());

	m_bg2 = NewGO<SpriteRender>("TitleSprite_BG2", 0);
	m_bg2->SetObjectTag(objectTag::t_BackSprite);
	m_bg2->Init(L"Assets/sprite/Title_BG.dds", FRAME_BUFFER_W, FRAME_BUFFER_H, BG2_Priority);
	m_bg2->SetPosition(CVector3::Zero());

	//�{�[��
	m_ball = NewGO<SkinModelRender>("TitleModel_Ball", 0);
	m_ball->Model_Init(L"Assets/modelData/Title_Ball.cmo");
	m_ball->SetPosition(Ball_DefPos);
	CQuaternion rot;
	rot.SetRotationDeg(Ball_RotAxis, Ball_RotAngle);
	m_ball->SetRotation(rot);
	m_ball->m_skinModelSupporter.SkinModelRotation(Ball_AutoRotAngle, Ball_AutoRotAxis, 1, 0, true);
	m_ball->SetShadowReciever(true);

	//�v���C���[	
	m_player.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);
	m_p_pos.Set(Ball_DefPos.x + Player_DefPos.x,
		Ball_DefPos.y + Player_DefPos.y,
		Ball_DefPos.z + Player_DefPos.z);
	m_p_scl.Set(Player_Scale, Player_Scale, Player_Scale);
	//�v���C���[�̉�]
	CQuaternion p_rot, p_rot2;
	p_rot.SetRotationDeg(CVector3::AxisX(), Plyer_RotAngleX);
	p_rot2.SetRotationDeg(CVector3::AxisY(), 180.0f + Ball_RotAngle);	//���f�������������Ă���̂Ő���+�{�[���̉�]
	p_rot *= p_rot2;
	m_p_rot = p_rot;
	m_player.SetShadowReciever(true);
	m_player.UpdateWorldMatrix(m_p_pos, m_p_rot, m_p_scl);
	//�v���C���[�̃A�j���[�V����
	m_playerAnimationClips[0].Load(L"Assets/animData/run.tka");
	m_playerAnimationClips[0].SetLoopFlag(true);
	//�A�j���[�V�����̏������B
	m_playerAnimation.Init(
		m_player,					//�A�j���[�V�����𗬂��X�L�����f���B
									//����ŃA�j���[�V�����ƃX�L�����f�����֘A�t�������B
		m_playerAnimationClips,		//�A�j���[�V�����N���b�v�̔z��B
		1							//�A�j���[�V�����N���b�v�̐��B
	);

	//�{�b�N�X
	m_dummyBox = NewGO<SkinModelRender>("TitleModel_Box", 0);
	m_dummyBox->Model_Init(L"Assets/modelData/box.cmo");
	CVector3 Pl_Pos = m_p_pos;
	m_dummyBox->SetPosition({ Pl_Pos.x + DummyBoxHosei.x,
		Pl_Pos.y + DummyBoxHosei.y,
		Pl_Pos.z + DummyBoxHosei.z });
	m_dummyBox->SetRotation(p_rot);
	m_dummyBox->SetScale(DummyBoxScale);

	//�R�}���h
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

	//���S�y��
	m_black = NewGO<SpriteRender>("TitleSprite_Black", 0);
	m_black->Init(L"Assets/sprite/black.dds", FRAME_BUFFER_W, FRAME_BUFFER_H, Black_Priority);
	m_black->SetPosition(CVector3::Zero());

	//���S�T�C�N��
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

	//���ʐݒ�
	for (auto iter = Rogo.TitleRogo_Circle.begin(); iter != Rogo.TitleRogo_Circle.end(); iter++) {
		iter->second->SetPosition({ Rogo.RogoDefPos.x,Rogo.RogoDefPos.y,Rogo.RogoDefPos.z });
		iter->second->SetAlpha(0.0f);
		iter->second->SetScale(0.0f);
	}

	//�������當��
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

	//�~�j����
	Rogo.m_titleRogo_Mozi_Hakobun = NewGO<SpriteRender>("TitleSprite_HakobunMini", 0);
	Rogo.m_titleRogo_Mozi_Hakobun->Init(L"Assets/sprite/Logo_hakobun.dds", Rogo.RogoSpriteSize.x, Rogo.RogoSpriteSize.y, Rogo.RogoCirclePriority);
	Rogo.m_titleRogo_Mozi_Hakobun->SetPosition({ Rogo.RogoDefPos.x,Rogo.RogoDefPos.y,Rogo.RogoDefPos.z });
	Rogo.m_titleRogo_Mozi_Hakobun->SetAlpha(0.0f);

}

/// <summary>
/// �G�t�F�N�g
/// </summary>
void Title::EffectUpdate_RogoEffect() {

	//�����ݒ�
	if (m_rogoEffectTimer == 0.0f) {
		//�T�C�N��
		int Delay = 0;
		for (auto iter = Rogo.TitleRogo_Circle.begin(); iter != Rogo.TitleRogo_Circle.end(); iter++) {
			//�܂Ƃ߂ĉ��o
			iter->second->m_spriteSupporter.SpriteScale(Rogo.RogoCircleMaxScale, 
				Rogo.RogoCircleScaleTime, 
				Delay);
			iter->second->m_spriteSupporter.SpriteScale(1.0f,
				Rogo.RogoCircleScaleTime / 2,
				Delay + Rogo.RogoCircleScaleTime);
			iter->second->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f }, 
				Rogo.RogoCircleScaleTime,
				Delay);
			Delay += Rogo.RogoCircleDelay;		//�f�B���C��������
		}
		//����
		Delay = 0;
		bool UpDounFlag = false;
		for (auto iter = Rogo.TitleRogo_Mozi.begin(); iter != Rogo.TitleRogo_Mozi.end(); iter++) {
			//�܂Ƃ߂ĉ��o
			iter->second->SetScale({ 1.0f,0.0f,1.0f });
			//Y�␳
			float Y_Hosei = Rogo.RogoMoziStartHosei;
			if (UpDounFlag == true) {
				Y_Hosei *= -1.0f;
			}
			iter->second->SetPosition({ 0.0f,Y_Hosei,1.0f });
			//�ړ�����
			float Y_Move = Rogo.RogoMoziMove;
			if (UpDounFlag == true) {
				Y_Move *= -1.0f;
			}
			iter->second->m_spriteSupporter.SpriteMove({ 0.0f,Y_Move },
				Rogo.RogoMoziTime,
				Delay + Rogo.RogoMoziDelay, true);
			//�o�E���h
			Y_Move = (Y_Hosei + Y_Move)* -1.0f;
			iter->second->m_spriteSupporter.SpriteMove({ 0.0f, Y_Move },
				Rogo.RogoMoziTime / 2, 
				Delay + Rogo.RogoMoziTime + Rogo.RogoMoziDelay, true);
			//�g�嗦
			iter->second->m_spriteSupporter.SpriteScale({ 1.0f,0.5f,1.0f }, 
				Rogo.RogoMoziTime,
				Delay + Rogo.RogoMoziDelay);
			iter->second->m_spriteSupporter.SpriteScale({ 1.0f,1.0f,1.0f },
				Rogo.RogoMoziTime / 2,
				Delay + Rogo.RogoMoziTime + Rogo.RogoMoziDelay);
			//�A���t�@
			iter->second->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f },
				Rogo.RogoMoziTime,
				Delay + Rogo.RogoMoziDelay);
			//�I��
			if (UpDounFlag == false) {
				UpDounFlag = true;
			}
			else {
				UpDounFlag = false;
			}
			Delay += Rogo.RogoMoziDelay;		//�f�B���C��������
		}
		//�~�j����
		Rogo.m_titleRogo_Mozi_Hakobun->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,1.0f },
			Rogo.RogoMiniMoziFadeTime,
			Delay + Rogo.RogoMiniMoziFadeDelay);
	}

	//�I��
	m_rogoEffectTimer += CGameTime::GetFrameDeltaTime();

	if (m_rogoEffectTimer >= RogoEffectRimit) {
		//���̃G�t�F�N�g�͏I��
		m_titleEffect = Title_Effect;
	}
}

void Title::EffectUpdate_TitleEffect() {

	//�����ݒ�
	if (m_titleEffectTimer == 0.0f) {
		//���S������ֈړ�
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
		//�����J�o�[���t�F�[�h�A�E�g�����ă^�C�g����ʂ�������
		m_black->m_spriteSupporter.SpriteColor({ 1.0f,1.0f,1.0f,0.0f }, TitleFadeTime, 0);
	}

	//�R�}���h����
	if (m_titleEffectTimer >= TitleCommandEffectRimit && m_commandMoveFlag == false) {

		//�R�}���h�������o
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

	//�I��
	m_titleEffectTimer += CGameTime::GetFrameDeltaTime();

	if (m_titleEffectTimer >= TitleEffectRimit) {
		//���̃G�t�F�N�g�͏I��
		m_titleEffect = Command_Wait;
	}
}

void Title::EffectUpdate_CommandWait() {

	//�I��҂�

	//���S�G�t�F�N�g
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

	//���o
	if (m_commandStartEffectTimer == 0.0f) {

		//�g�����W�V����
		TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox, 
			SceneManager::GetInstance()->GetGameGraphicInstance()->TransitionTime, false);

		switch (m_memberCommand)
		{
		case Title::No_Select:
			std::abort();	//���肦�Ȃ�����
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

	//�I��
	m_commandStartEffectTimer += CGameTime::GetFrameDeltaTime();

	if (m_commandStartEffectTimer >= CommandStartEffectRimit) {
		//�Q�[���}�l�[�W���[�ɏ��������Ă��炤
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

		//�ړ��̎w�����o��
		m_bg1->m_spriteSupporter.SpriteMove({ FRAME_BUFFER_W,0.0f }, BG_MoveTime, 0, true);
		m_bg2->m_spriteSupporter.SpriteMove({ FRAME_BUFFER_W,0.0f }, BG_MoveTime, 0, true);
	}

	//���Ԍo��
	m_bgMoveTimer++;

	//���Z�b�g
	if (m_bgMoveTimer >= BG_MoveTime) {
		m_bgMoveTimer = 0;
	}

}

void Title::CommandSelect() {

	//�ǂ̃R�}���h�ɂ��}�E�X�J�[�\�����d�Ȃ��ĂȂ��ꍇ�p
	bool HitFlag = false;

	//�e�R�}���h��t
	//�X�^�[�g
	if (m_command_Start->MouseOverMouse() == true) {

		HitFlag = true;

		if (m_memberCommand != Game_Start) {
			//���񉉏o
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Cursor.wav");	//SE
			m_command_Start->SetMulColor(CommandMulColor);
			m_command_Start->m_spriteSupporter.SpriteMove({ 0.0f,CommandSelectMove }, CommandSelectMoveTime, 0, true);
			m_command_Start->m_spriteSupporter.SpriteMove({ 0.0f,-CommandSelectMove }, CommandSelectMoveTime, CommandSelectMoveTime, true);
			m_memberCommand = Game_Start;
		}

	}
	else {
		//�߂�
		m_command_Start->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

	}
	//�R���e�B�j���[
	if (m_command_Continue->MouseOverMouse() == true) {
		HitFlag = true;

		if (m_memberCommand != Game_Continue) {
			//���񉉏o
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
	//�G���h
	if (m_command_End->MouseOverMouse() == true) {
		HitFlag = true;

		if (m_memberCommand != Game_End) {
			//���񉉏o
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

	//���ʏ���
	if (HitFlag == false) {
		//�ǂ��ɂ��d�Ȃ��ĂȂ��̂ŏ���������
		m_memberCommand = No_Select;
	}
	else {
		//���N���b�N���ꂽ��m�肳����
		if (MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key) == MouseSupporter::Release_Push) {
			SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/GameStart.wav", 2.0f);
			m_titleEffect = Command_Effect;
		}
	}

}