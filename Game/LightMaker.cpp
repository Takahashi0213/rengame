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
/// ディレクションライトを生成する
/// </summary>
/// <param name="lightNo">ライトの番号</param>
/// <param name="dir">ライトの方向</param>
/// <param name="col">ライトの色</param>
/// <returns>作成したライトのポインタ</returns>
void LightMaker::D_LightMake(int lightNo,CVector4 dir,CVector4 col) {

	m_light.direction[lightNo] = dir;
	m_light.color[lightNo] = col;

}

/// <summary>
/// ディレクションライトを消去する
/// </summary>
/// <param name="lightNo">削除するディレクションライトの場所</param>
void LightMaker::D_LightDelete(int lightNo) {

	m_light.direction[lightNo] = { 0.0f, -1.0f, 0.0f, 0.0f };
	m_light.color[lightNo] = { 0.2f,0.2f, 0.2f, 1.0f };

}
