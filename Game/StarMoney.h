#pragma once
#include "system/CGameObjectManager.h"

class StarMoney : public IGameObject
{
public:
	StarMoney();
	~StarMoney();
	void Update()override;
	void Render()override;

	//設定
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}

private:

	SkinModel m_model;	//スキンモデル。
	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率



};

