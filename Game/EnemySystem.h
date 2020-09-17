#pragma once
class EnemySystem
{
public:
	/// <summary>
	/// ”ò‚ñ‚Å‚­‚é” ‚Æ‚Ô‚Â‚©‚Á‚½‚©”»’è
	/// </summary>
	bool BoxAttackSearch(CVector3 position, float range = 120.0f);

private:

	//’è”
	const float Gensui = 0.2f;		//Õ“Ë‚µ‚½” ‚ÌˆÚ“®Œ¸Š
	const float Damage_Y = 2.0f;	//Õ“Ë‚µ‚½” ‚ÌYˆÚ“®
};

