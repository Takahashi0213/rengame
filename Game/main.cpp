#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"

#include "GameCamera.h"

Sprite g_sprite;		//スプライト。
CVector3 g_spritePos = CVector3::Zero();	//スプライトの座標。

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//ゲームオブジェクトマネージャー
	CGameObjectManager goMgr;

	//MouseSupporter
	MouseSupporter moSup;

	//スプライトレンダー
	SpriteRender spRen;

	//ライトメーカーの生成
	goMgr.NewGO<LightMaker>("LightMaker");
	
	//カメラサポーターの生成
	goMgr.NewGO<CameraSupporter>("CameraSupporter");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	//2Dカメラを初期化。
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetNear(0.1f);
	g_camera2D.SetFar(1000.0f);

	//CameraSupporter::GetInstance()->CameraMove_Zoom(30.0f, 20.0f, 60.0f, true);

	//プレイヤー
	goMgr.NewGO<Player>("Player");
	goMgr.NewGO<GameCamera>("GameCamera");

	//ライトの生成テスト
	LightMaker::GetInstance()->D_LightMake({ 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });

	g_sprite.Sprite_Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//カメラの更新。
		//g_camera3D.Update();
		g_camera2D.Camera2D_Update();
		//マウスサポーターの更新
		moSup.MouseUpdate();
		//アップデート
		goMgr.Execute();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}