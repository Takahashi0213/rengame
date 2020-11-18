#pragma once

/// <summary>
/// ダメージの付与やゲームオーバーの管理
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

	float m_damageTimer = 0.0f;				//ダメージタイマー
	bool m_damageFlag = false;				//無敵時間フラグ
	const float DamageLimit = 0.8f;			//ダメージの無敵時間
	
	//ダメージフォント
	FontRender* m_damageFont = nullptr;
	const float DamageFontSize = 0.5f;		//ダメージフォントの大きさ
	const float DamageFontMoveY = 30.0f;	//ダメージフォントの移動量
	const int DamageFontMoveTime = 12;		//ダメージフォントの移動時間
	const int DamageFontAlphaTime = 2;		//ダメージフォントの消去時間
	const int DamageFontAlphaDelay = 20;	//ダメージフォントの消去ディレイ

};

