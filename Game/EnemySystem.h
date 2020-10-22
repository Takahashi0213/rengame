#pragma once
class EnemySystem : public ObjectClass
{
public:
	/// <summary>
	/// ”ò‚ñ‚Å‚­‚é” ‚Æ‚Ô‚Â‚©‚Á‚½‚©”»’è
	/// </summary>
	bool BoxAttackSearch(const CVector3& position, const float& range = 120.0f);

	Player* m_player;				//ƒvƒŒƒCƒ„[

private:

	//’è”
	const float Gensui = 0.2f;		//Õ“Ë‚µ‚½” ‚ÌˆÚ“®Œ¸Š
	const float Damage_Y = 2.0f;	//Õ“Ë‚µ‚½” ‚ÌYˆÚ“®

};

