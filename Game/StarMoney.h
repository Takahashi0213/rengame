#pragma once
#include "system/CGameObjectManager.h"

/// <summary>
/// 触れると手に入るお金
/// </summary>
class StarMoney : public IGameObject, public ObjectClass
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
	SkinModel m_model_Kirameki;	//キラメキラリ
	ID3D11ShaderResourceView* m_kiramekiSRV = nullptr;

	//定数
	const CVector3 DefScale = { 10.0f,10.0f,10.0f };	//初期サイズ
};

