#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender()
{
	//スキンモデルサポーターにアドレスを渡しておく
	m_skinModelSupporter.SkinModelRenderSetting(this);
}


SkinModelRender::~SkinModelRender()
{
}

/// <summary>
/// 初期化する
/// </summary>
/// <param name="filePath">モデルのファイルパス</param>
void SkinModelRender::Model_Init(const wchar_t* filePath) {
	m_skinModel.Init(filePath);
	Update(); //ここに書く意味あるのかな…とりあえず書く
}

/// <summary>
/// 初期化する
/// </summary>
/// <param name="filePath">モデルのファイルパス</param>
/// <param name="pos">初期座標</param>
/// <param name="rot">初期回転</param>
/// <param name="scl">初期拡大率</param>
void SkinModelRender::Model_Init(const wchar_t* filePath, CVector3 pos, CQuaternion rot, CVector3 scl) {
	m_skinModel.Init(filePath);
	m_position = pos;
	m_rotation = rot;
	m_scale = scl;
	Update();
}

/// <summary>
/// アップデート
/// </summary>
void SkinModelRender::Update() {
	m_skinModelSupporter.SkinModelSupporterUpdate();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

/// <summary>
/// 描画
/// </summary>
void SkinModelRender::Render() {
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}