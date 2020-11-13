#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// 松明（ポイントライト＆ループエフェクト）
/// アクションフラグに応じて松明のオンオフ変更
/// </summary>
class Torch : public ObjectClass
{
public:
	Torch();
	~Torch();
	void Update()override;
	void Render()override;

	/// <summary>
	/// トーチ状態の変更
	/// falseならオフ、trueならオン
	/// </summary>
	/// <param name="flag"></param>
	void SetTorch(const bool& flag) {
		m_actionFlag = flag;
	}

	/// <summary>
	/// エフェクト補正を設定
	/// </summary>
	void SetHosei(const CVector3& hosei) {
		m_hosei.Set(hosei);
	}

private:
	SkinModel m_model;										//モデル

	bool m_fireFlag = false;								//トーチ変更用

	const float Y_Hosei = 50.0f;							//Y補正
	CVector3 m_hosei = CVector3::Zero();					//補正

	int m_pointLightNo = -1;								//ポイントライト番号
	Effekseer::Handle m_Effect = -1;						//炎エフェクト

	const CVector3 PointLightColor = { 0.8f,0.2f,0.2f };	//ポイントライトの色
	const float PointLightRange = 400.0f;					//ポイントライトの有効範囲
	
};

