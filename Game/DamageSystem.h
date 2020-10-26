#pragma once

/// <summary>
/// ダメージの付与やゲームオーバーの管理s
/// </summary>
class DamageSystem
{
public:
	DamageSystem();
	~DamageSystem();

	void Damage(const int& damage);

	void DamageUpdate();

private:
	float m_damageTimer = 0.0f;
	bool m_damageFlag = false;		//無敵時間フラグ
	const float DamageLimit = 1.0f;	//ダメージの無敵時間
};

