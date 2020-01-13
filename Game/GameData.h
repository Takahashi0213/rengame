#pragma once

/// <summary>
/// �Q�[���̃X�e�[�^�X�͂�����
/// ���V���O���g��
/// </summary>
class GameData
{
	static GameData* m_instance;
public:
	enum Place_Data {		//�ꏊ�f�[�^
		Null_Place,		//��
		Warehouse,		//�q��
		Meadow,			//����
	};

	GameData();
	~GameData();

	//�f�[�^�p�֐�

	/// <summary>
	/// �i�s�x���Z
	/// </summary>
	void ProgressPlus() {
		m_progress++;
	}
	/// <summary>
	/// �i�s�x�擾
	/// </summary>
	/// <returns>�i�s�x</returns>
	int GetProgress() {
		return m_progress;
	}

	/// <summary>
	/// ���݈ʒu�ύX
	/// </summary>
	/// <param name="pd">�V�������݈ʒu</param>
	void SetPlace(Place_Data pd) {
		m_nowPlace = pd;
	}
	/// <summary>
	/// ���݈ʒu�擾
	/// </summary>
	/// <returns>�C�}�R�R�I</returns>
	Place_Data GetPlace() {
		return m_nowPlace;
	}

	/// <summary>
	/// ���j���[�t���O�̕ύX
	/// </summary>
	/// <param name="flag">�t���O</param>
	void SetMenuFlag(bool flag) {
		m_menuFlag = flag;
	}
	/// <summary>
	/// ���j���[�t���O�̎擾
	/// </summary>
	/// <returns>�t���O</returns>
	bool GetMenuFlag() {
		return m_menuFlag;
	}

	/// <summary>
	/// �X�^�[�}�l�[�̕ύX
	/// </summary>
	/// <param name="money">���Z�l�i���̐����j</param>
	void StarMoneyPlus(int money) {
		m_starMoney += money;
		if (m_starMoney > MAX_STAR_MONEY) {	//���
			m_starMoney = MAX_STAR_MONEY;
		}

	}
	/// <summary>
	/// �X�^�[�}�l�[���擾
	/// </summary>
	/// <returns>������</returns>
	int GetStarMoney() {
		return m_starMoney;
	}

	/// <summary>
	/// ���ݖ��͂̐ݒ�
	/// </summary>
	/// <param name="power">����</param>
	void SetMagicPower(int power) {
		m_magicPower = power;
	}
	/// <summary>
	/// ���ݖ��͂̉��Z
	/// </summary>
	/// <param name="power">���Z�l�i���̐����j</param>
	void MagicPowerPlus(int power) {
		m_magicPower += power;
		if (m_magicPower > m_magicPower_MAX) {	//���
			m_magicPower = m_magicPower_MAX;
		}
	}
	/// <summary>
	/// ���͂̎擾
	/// </summary>
	/// <returns>���ݒl</returns>
	int GetMagicPower() {
		return m_magicPower;
	}

	/// <summary>
	/// �ő喂�͂̐ݒ�
	/// </summary>
	/// <param name="max">�l</param>
	void SetMaxMagic(int max) {
		m_magicPower_MAX = max;
	}
	/// <summary>
	/// �ő喂�͂̎擾
	/// </summary>
	/// <returns>�ő喂��</returns>
	int GetMaxMagic() {
		return m_magicPower_MAX;
	}

	/// <summary>
	/// ���ݑ̗͂̐ݒ�
	/// </summary>
	/// <param name="hp">����</param>
	void SetHP(int hp) {
		m_hp = hp;
	}
	/// <summary>
	/// ���ݑ̗͂̉��Z
	/// </summary>
	/// <param name="hp">���Z�l�i���̐����j</param>
	void HP_Plus(int hp) {
		m_hp += hp;
		if (m_hp > m_hp_MAX) {	//���
			m_hp = m_hp_MAX;
		}
	}
	/// <summary>
	/// �̗͂̎擾
	/// </summary>
	/// <returns>���ݒl</returns>
	int GetHP() {
		return m_hp;
	}

	/// <summary>
	/// �ő�̗͂̐ݒ�
	/// </summary>
	/// <param name="max">�l</param>
	void SetMaxHP(int max) {
		m_hp_MAX = max;
	}
	/// <summary>
	/// �ő�̗͂̎擾
	/// </summary>
	/// <returns>�ő�̗�</returns>
	int GetMaxHP() {
		return m_hp_MAX;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static GameData* GameData::GetInstance() {
		return m_instance;
	}

private:

	//��{
	int m_progress = 0;		//�i�s�x
	Place_Data m_nowPlace = Null_Place;		//���݈ʒu
	bool m_menuFlag = false;				//�����j���[�J����H

	//����v�f
	struct GameFlag {
		bool m_boxMakerFlag;	//�������\��
		bool m_equipmentFlag;	//�����ύX
		bool m_teleportFlag;	//���j���[����̃e���|�[�g
	};
	GameFlag m_gameFlag;

	//�X�^�[�}�l�[
	int m_starMoney = 0;
	const int MAX_STAR_MONEY = 99999;

	//�v���C���[�X�e�[�^�X
	int m_magicPower = 100;
	int m_magicPower_MAX = 100;
	int m_hp = 100;
	int m_hp_MAX = 100;

};

