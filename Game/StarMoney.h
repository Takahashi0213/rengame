#pragma once
#include "system/CGameObjectManager.h"
#include "Player.h"

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
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}

private:

	void StarMoneyMove();

	SkinModel m_model;			//スキンモデル。
	SkinModel m_model_Kirameki;	//キラメキラリ
	Player* m_pl = nullptr;
	ID3D11ShaderResourceView* m_kiramekiSRV = nullptr;

	//シェイク
	bool m_upDowmFlag = false;			//上下フラグ
	float m_upDowmTimer = 0.0f;			//上下タイマー
	const float UpDownLimit = 0.5f;		//上下リミット
	const float UpDownMove = 0.5f;		//上下移動量

	//定数
	const CVector3 DefScale = { 10.0f,10.0f,10.0f };	//初期サイズ
	const float GetRange = 150.0f;						//取得できる範囲
	const int GetStarMoney = 1;							//取得量

};

