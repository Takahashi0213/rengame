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

	//���C�g���[�J�[�̐���
	LightMaker* lm = CGameObjectManager::GetInstance()->NewGO<LightMaker>("LightMaker");
	lm->SetAmbientColor({ 1.0f, 1.0f, 1.0f });

	//�����ݒ�
	SetUp();
}


Title::~Title()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
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
		break;
	case Title::Command_Effect:
		EffectUpdate_CommandEffect();
		break;
	}

	//�J����
	g_camera3D.Update();
}

void Title::Render() {

}

/// <summary>
/// �ŏ��ɌĂ�
/// �����_�[�̐����Ɖ摜�ݒ�
/// </summary>
void Title::SetUp() {

	//�w�i
	m_bg1 = NewGO<SpriteRender>("TitleSprite_BG1", 0);
	m_bg1->SetObjectTag(objectTag::t_BackSprite);
	m_bg1->Init(L"Assets/sprite/White.dds", FRAME_BUFFER_W, FRAME_BUFFER_H, BG1_Priority);
	m_bg1->SetPosition(CVector3::Zero());

	//�{�[��
	m_ball = NewGO<SkinModelRender>("TitleModel_Ball", 0);
	m_ball->Model_Init(L"Assets/modelData/Title_Ball.cmo");
	m_ball->SetPosition(Ball_DefPos);
	CQuaternion rot;
	rot.SetRotationDeg(Ball_RotAxis, Ball_RotAngle);
	m_ball->SetRotation(rot);

	//�R�}���h
	m_command_Start = NewGO<SpriteRender>("TitleSprite_Command1", 0);
	m_command_Start->Init(L"Assets/sprite/Hazimekara.dds", CommandSpriteSize.x, CommandSpriteSize.y, Command_Priority);
	m_command_Start->SetPosition(Command_DefPos);
	m_command_Continue = NewGO<SpriteRender>("TitleSprite_Command2", 0);
	m_command_Continue->Init(L"Assets/sprite/Tudukikara.dds", CommandSpriteSize.x, CommandSpriteSize.y, Command_Priority);
	m_command_Continue->SetPosition({ Command_DefPos.x,Command_DefPos.y - Command_Y_Hosei,Command_DefPos.z });
	m_command_End = NewGO<SpriteRender>("TitleSprite_Command3", 0);
	m_command_End->Init(L"Assets/sprite/End.dds", CommandSpriteSize.x, CommandSpriteSize.y, Command_Priority);
	m_command_End->SetPosition({ Command_DefPos.x,Command_DefPos.y - (Command_Y_Hosei*2.0f),Command_DefPos.z });

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

	//�I��
	m_titleEffectTimer += CGameTime::GetFrameDeltaTime();

	if (m_titleEffectTimer >= TitleEffectRimit) {
		//���̃G�t�F�N�g�͏I��
		m_titleEffect = Command_Wait;
	}
}

void Title::EffectUpdate_CommandWait() {

}

void Title::EffectUpdate_CommandEffect() {

}
