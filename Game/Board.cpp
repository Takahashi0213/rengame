#include "stdafx.h"
#include "Board.h"


Board::Board()
{
	m_model.Init(L"Assets/modelData/Board.cmo");

	//タグ設定
	m_object = ObjectClass::ObjectClass_Tag::GimmickObj;

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}


Board::~Board()
{
}

void Board::Update() {

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//シャドウキャスター
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);
	ShadowMap::GetInstance()->Update(LightMaker::GetInstance()->GetLightCameraPosition(),
		LightMaker::GetInstance()->GetLightCameraTarget());

}

void Board::Render() {

	m_model.Draw(g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}
