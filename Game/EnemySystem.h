#pragma once
class EnemySystem
{
public:
	/// <summary>
	/// ���ł��锠�ƂԂ�����������
	/// </summary>
	bool BoxAttackSearch(CVector3 position, float range = 120.0f);

private:

	//�萔
	const float Gensui = 0.2f;	//�Փ˂������̈ړ�����
};

