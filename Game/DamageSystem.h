#pragma once

/// <summary>
/// �_���[�W�̕t�^��Q�[���I�[�o�[�̊Ǘ�s
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
	bool m_damageFlag = false;		//���G���ԃt���O
	const float DamageLimit = 1.0f;	//�_���[�W�̖��G����
};

