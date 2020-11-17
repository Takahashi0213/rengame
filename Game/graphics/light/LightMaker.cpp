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
	SetLightCameraPosition({ 0.0f, 1000.0f, 100.0f });
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

//ディレクションライト

void LightMaker::D_LightMake(const int& lightNo, const CVector4& dir, const CVector4& col, const float& spec) {

	m_light.direction[lightNo] = dir;
	m_light.color[lightNo] = col;
	m_light.color[lightNo].w = spec;
	m_directionLightSetFlag[lightNo] = true;
}

void LightMaker::D_LightDelete(const int& lightNo) {

	m_light.direction[lightNo] = DirectionLight_Direction_Def;
	m_light.color[lightNo] = DirectionLight_Color_Def;
	m_directionLightSetFlag[lightNo] = false;
}

//ポイントライト

void LightMaker::P_LightMake(const int& lightNo, const CVector3& pos, const CVector3& col, const float& range) {
	m_pointLight.position[lightNo] = pos;
	m_pointLight.color[lightNo] = col;
	m_pointLight.color[lightNo].w = range;
	m_pointLightSetFlag[lightNo] = true;
}

void LightMaker::P_LightDelete(const int& lightNo) {
	m_pointLight.position[lightNo] = CVector3::Zero();
	m_pointLight.color[lightNo] = CVector3::Zero();
	m_pointLight.color[lightNo].w = 0.0f;
	m_pointLightSetFlag[lightNo] = false;
}

void LightMaker::P_LightDeleteAll() {
	//みんな きえる
	for (int i = 0; i < MAX_POINT_LIGHT; i++) {
		P_LightDelete(i);
		m_pointLightSetFlag[i] = false;
	}
}