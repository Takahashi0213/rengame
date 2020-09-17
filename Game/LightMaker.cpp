#include "stdafx.h"
#include "LightMaker.h"

LightMaker* LightMaker::m_instance = nullptr;

LightMaker::LightMaker()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

	//ディレクションライトの初期化
	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
		D_LightDelete(i);
	}
	//ポイントライトの初期化
	P_LightDeleteAll();

	//デバッグ用
	//for (int i = 0; i < MAX_POINT_LIGHT; i++) {
	//	CVector3 pos;
	//	pos.x = static_cast<float>(rand() % 1000) - 500.0f;
	//	pos.y = 20.0f; //高さは20固定。
	//	pos.z = static_cast<float>(rand() % 1000) - 500.0f;
	//	float range = 50.0f;		//影響範囲も50で固定しておく。
	//	CVector3 color;
	//	color.x = static_cast<float>(rand() % 255) / 255.0f;
	//	color.y = static_cast<float>(rand() % 255) / 255.0f;
	//	color.z = static_cast<float>(rand() % 255) / 255.0f;

	//	P_LightMake(
	//		i,
	//		{0.0f, 30.0f, 0.0f},
	//		{1.0f,0.0f,0.0f},
	//		200.0f);

	//}

	//ライトカメラの座標
	SetLightCameraPosition({ 0.0f, 1000.0f, 0.0f });
	SetLightCameraTarget({ 0.0f, 0.0f, 0.0f });

}

LightMaker::~LightMaker()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void LightMaker::Update() {
}

void LightMaker::Render() {

}

/// <summary>
/// ディレクションライトを設定する
/// </summary>
/// <param name="lightNo">ライトの番号</param>
/// <param name="dir">ライトの方向</param>
/// <param name="col">ライトの色</param>
/// <param name="spec">スペキュラ</param>
/// <returns>作成したライトのポインタ</returns>
void LightMaker::D_LightMake(int lightNo,CVector4 dir,CVector4 col, float spec) {

	m_light.direction[lightNo] = dir;
	m_light.color[lightNo] = col;
	m_light.color[lightNo].w = spec;

}

/// <summary>
/// ディレクションライトを消去する
/// </summary>
/// <param name="lightNo">削除するディレクションライトの場所</param>
void LightMaker::D_LightDelete(int lightNo) {

	m_light.direction[lightNo] = DirectionLight_Direction_Def;
	m_light.color[lightNo] = DirectionLight_Color_Def;

}

/// <summary>
/// ポイントライトを作成する
/// </summary>
/// <param name="lightNo">ライト番号</param>
/// <param name="pos">座標</param>
/// <param name="col">カラー</param>
/// <param name="range">範囲</param>
void LightMaker::P_LightMake(int lightNo, CVector3 pos, CVector3 col, float range) {
	m_pointLight.position[lightNo] = pos;
	m_pointLight.color[lightNo] = col;
	m_pointLight.color[lightNo].w = range;
}

/// <summary>
/// ポイントライトを消去する
/// </summary>
/// <param name="lightNo">ライト番号</param>
void LightMaker::P_LightDelete(int lightNo) {
	m_pointLight.position[lightNo] = CVector3::Zero();
	m_pointLight.color[lightNo] = CVector3::Zero();
	m_pointLight.color[lightNo].w = 0.0f;
}

//ポイントライトを全部初期化
void LightMaker::P_LightDeleteAll() {
	//みんな きえる
	for (int i = 0; i < MAX_POINT_LIGHT; i++) {
		P_LightDelete(i);
	}
}