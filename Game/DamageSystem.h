#pragma once

/// <summary>
/// ダメージの付与やゲームオーバーの管理s
/// </summary>
class DamageSystem
{
public:
	DamageSystem();
	~DamageSystem();

	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damage">ダメージ</param>
	/// <returns>
	/// 無敵時間中でない（ダメージを与えた）ならtrueを返す
	/// 無敵時間中（ダメージを与えられなかった）ならfalseを返す
	/// </returns>
	bool Damage(const int& damage);

	void DamageUpdate();

private:
	float m_damageTimer = 0.0f;
	bool m_damageFlag = false;		//無敵時間フラグ
	const float DamageLimit = 0.8f;	//ダメージの無敵時間
};

