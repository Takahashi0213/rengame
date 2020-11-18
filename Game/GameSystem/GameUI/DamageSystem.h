#pragma once

/// <summary>
/// �_���[�W�̕t�^��Q�[���I�[�o�[�̊Ǘ�
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

	float m_damageTimer = 0.0f;				//�_���[�W�^�C�}�[
	bool m_damageFlag = false;				//���G���ԃt���O
	const float DamageLimit = 0.8f;			//�_���[�W�̖��G����
	
	//�_���[�W�t�H���g
	FontRender* m_damageFont = nullptr;
	const float DamageFontSize = 0.5f;		//�_���[�W�t�H���g�̑傫��
	const float DamageFontMoveY = 30.0f;	//�_���[�W�t�H���g�̈ړ���
	const int DamageFontMoveTime = 12;		//�_���[�W�t�H���g�̈ړ�����
	const int DamageFontAlphaTime = 2;		//�_���[�W�t�H���g�̏�������
	const int DamageFontAlphaDelay = 20;	//�_���[�W�t�H���g�̏����f�B���C

};

