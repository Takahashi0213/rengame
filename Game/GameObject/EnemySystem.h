#pragma once
class EnemySystem : public ObjectClass
{
public:
	/// <summary>
	/// 飛んでくる箱とぶつかったか判定
	/// </summary>
	bool BoxAttackSearch(const CVector3& position, const float& range = 120.0f);

	Player* m_player;				//プレイヤー

	bool m_deathEffectFlag = false;	//死亡エフェクト複数再生防止

private:

	//定数
	const float Gensui = 0.2f;		//衝突した箱の移動減衰
	const float Damage_Y = 2.0f;	//衝突した箱のY移動

};

