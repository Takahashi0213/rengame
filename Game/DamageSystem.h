#pragma once

/// <summary>
/// �_���[�W�̕t�^��Q�[���I�[�o�[�̊Ǘ�s
/// </summary>
class DamageSystem
{
public:
	DamageSystem();
	~DamageSystem();

	/// <summary>
	/// �_���[�W��^����
	/// </summary>
	/// <param name="damage">�_���[�W</param>
	/// <returns>
	/// ���G���Ԓ��łȂ��i�_���[�W��^�����j�Ȃ�true��Ԃ�
	/// ���G���Ԓ��i�_���[�W��^�����Ȃ������j�Ȃ�false��Ԃ�
	/// </returns>
	bool Damage(const int& damage);

	void DamageUpdate();

private:
	float m_damageTimer = 0.0f;
	bool m_damageFlag = false;		//���G���ԃt���O
	const float DamageLimit = 0.8f;	//�_���[�W�̖��G����
};

