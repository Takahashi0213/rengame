#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"

#include "GameCamera.h"

Sprite g_sprite;		//�X�v���C�g�B
CVector3 g_spritePos = CVector3::Zero();	//�X�v���C�g�̍��W�B

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[
	CGameObjectManager goMgr;

	//MouseSupporter
	MouseSupporter moSup;

	//�X�v���C�g�����_�[
	SpriteRender spRen;

	//���C�g���[�J�[�̐���
	goMgr.NewGO<LightMaker>("LightMaker");
	
	//�J�����T�|�[�^�[�̐���
	goMgr.NewGO<CameraSupporter>("CameraSupporter");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	//2D�J�������������B
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetNear(0.1f);
	g_camera2D.SetFar(1000.0f);

	//CameraSupporter::GetInstance()->CameraMove_Zoom(30.0f, 20.0f, 60.0f, true);

	//�v���C���[
	goMgr.NewGO<Player>("Player");
	goMgr.NewGO<GameCamera>("GameCamera");

	//���C�g�̐����e�X�g
	LightMaker::GetInstance()->D_LightMake({ 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });

	g_sprite.Sprite_Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�J�����̍X�V�B
		//g_camera3D.Update();
		g_camera2D.Camera2D_Update();
		//�}�E�X�T�|�[�^�[�̍X�V
		moSup.MouseUpdate();
		//�A�b�v�f�[�g
		goMgr.Execute();
		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}