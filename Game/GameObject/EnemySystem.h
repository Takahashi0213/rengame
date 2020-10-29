#pragma once
class EnemySystem : public ObjectClass
{
public:
	/// <summary>
	/// ���ł��锠�ƂԂ�����������
	/// </summary>
	bool BoxAttackSearch(const CVector3& position, const float& range = 120.0f);

	Player* m_player;				//�v���C���[

	bool m_deathEffectFlag = false;	//���S�G�t�F�N�g�����Đ��h�~

private:

	//�萔
	const float Gensui = 0.2f;		//�Փ˂������̈ړ�����
	const float Damage_Y = 2.0f;	//�Փ˂�������Y�ړ�

};

