#pragma once
#include "system/CGameObjectManager.h"

/// <summary>
/// �X�^�[�}�l�[�擾���o
/// EXP�l�����o
/// ���x���A�b�v���o
/// �`���p
/// </summary>
class GameStatusUI
{
public:
	GameStatusUI();
	~GameStatusUI();

	//�\�񏈗��ǉ�
	void AddStarMoney(const int x) {
		StatusData addData = { Status_Anime::StarMoney ,x };
		m_statusList.push_back(addData);
	}
	void AddEXP(const int x) {
		StatusData addData = { Status_Anime::EXP ,x };
		m_statusList.push_back(addData);
	}

	//�O������Ă�ōX�V���Ă�������
	void GameStatusUI_Update();

private:
	enum Status_Anime {
		StatusAnime_NULL,	//��
		StarMoney,
		EXP,
	};
	struct StatusData {
		Status_Anime StatusAnime = Status_Anime::StatusAnime_NULL;	//���̉��o�̎��
		int Add = 0;												//���̉��o�ŉ��Z�����l
	};

	//�֐�
	/// <summary>
	/// �G�t�F�N�g�m�莞�̏������܂Ƃ߂����� ���L�̃G�t�F�N�g���s�������ōs��
	/// </summary>
	/// <param name="it">�m�肵��m_statusList�̃C�e���[�^</param>
	void StatusEffect_StartStandBy(const std::list<StatusData>::iterator it);
	//�G�t�F�N�g�m�莞�A�G�t�F�N�g�����s����
	//�����G�t�F�N�g�̎�ނ��Ⴄ�ꍇ�̓t�F�[�h���s��
	void StatusEffect_Start();
	/// <summary>
	/// �A�j���[�V�������܂Ƃ߂ăt�F�[�h����
	/// </summary>
	/// <param name="anime">�t�F�[�h����͈�</param>
	/// <param name="alpha">�t�F�[�h��̃A���t�@�l</param>
	/// <param name="time">�t�F�[�h����</param>
	void Status_SpriteAlphaSet(const Status_Anime anime, const float alpha, const int time);
	/// <summary>
	/// �G�t�F�N�g�̓����X�V
	/// </summary>
	void Status_EffectUpdate();

	//�X�e�[�^�X���o�\�񃊃X�g
	std::list<StatusData>m_statusList;						//�X�e�[�^�X���o���X�g
	std::list<StatusData>::iterator m_statusList_it;		//�X�e�[�^�X���o���X�g�ŁA���݉��o���̓��e
	
	//�X�e�[�^�X���o
	bool m_statusEffectFlag = false;						//���݉��o���H�itrue�ŉ��o���I�j
	Status_Anime m_nowStatusAnime = StatusAnime_NULL;		//���݉��o���̃A�j���[�V�����̎��

	//�X�^�[�}�l�[�X�v���C�g
	const CVector3 GameStatusUI_StarMoney_DefPos = { -500.0f,100.f,0.0f };	//�X�^�[�}�l�[��{���W
	const CVector3 GameStatusUI_EXP_DefPos = { 0.0f,80.f,0.0f };			//EXP��{���W

	SpriteRender* m_starMoneySprite = nullptr;				//�X�^�[�}�l�[�A�C�R��
	const CVector2 StarMoneySpriteSize = { 60.0f,60.0f };	//�X�^�[�}�l�[�A�C�R���̑傫��

	SpriteRender* m_statusBase_StarMoney = nullptr;			//�X�e�[�^�X�y��
	const CVector2 StarMoneyBaseSize = { 200.0f,60.0f };	//�X�^�[�}�l�[�E�B���h�E�̑傫��

	FontRender* m_text_StarMoney = nullptr;					//�e�L�X�g�I
	const float FontSize = 0.5f;							//�t�H���g�T�C�Y
	const CVector2 StarMoneyTextHosei = { -60.0f, 20.0f };	//�t�H���g�̈ʒu�␳

	//EXP�X�v���C�g
	SpriteRender* m_statusBase_EXP = nullptr;				//EXP�X�e�[�^�X�y��

	SpriteRender* m_statusBar_EXP = nullptr;				//EXP�X�e�[�^�X�o�[
	const CVector2 EXP_Bar_Size = { 38.0f, 14.0f };			//EXP�X�e�[�^�X�o�[�̑傫��

	SpriteRender* m_statusCover_EXP = nullptr;				//EXP�X�e�[�^�X�J�o�[
	const CVector2 EXP_Cover_Size = { 54.0f, 18.0f };		//EXP�X�e�[�^�X�J�o�[�̑傫��

	const CVector2 EXP_SizeHosei = { 3.0f, 2.0f };			//EXP�X�e�[�^�X�̕␳


	const int SpritePriority = 9;							//�D��x

	//�G�t�F�N�g�F�X
	CVector3 m_point_1 = CVector3::Zero();					//�I�_���
	CVector3 m_point_2 = CVector3::Zero();					//�n�_
	CVector3 m_point_3 = CVector3::Zero();					//�I�_
	CVector3 m_point_4 = CVector3::Zero();					//�n�_���
	float m_kyokusen = 0.0f;								//�x�W�F�Ȑ��Ŏg��
	const float Y_Hosei = 50.0f;							//�x�W�F�Ȑ��̍ō����B�_Y�␳
	bool m_effectFlag = false;								//�G�t�F�N�g�\�����H

	//�F�X�萔
	const int StatusAlphaTime = 12;							//�X�e�[�^�X�̃t�F�[�h����


};

/// <summary>
/// �X�^�[�}�l�[���l��������
/// �o���l���l���������ɁA�����̏������ĂԂ�
/// �EGameData�ւ̉��Z
/// �E��ʕ`��
/// �������ōs���Ă����֗��ȏ����Q�ł�
/// ���V���O���g��
/// </summary>
class GameStatus_UISystem final : public IGameObject
{
	static GameStatus_UISystem* m_instance;
public:
	GameStatus_UISystem();
	~GameStatus_UISystem();
	void Update()override;
	void Render()override;

	//����������Z�����p
	void AddStarMoney(const int x) {
		m_gameStatusUI.AddStarMoney(x);
	}
	void AddEXP(const int x) {
		m_gameStatusUI.AddEXP(x);
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static GameStatus_UISystem* GameStatus_UISystem::GetInstance() {
		return m_instance;
	}

private:
	GameStatusUI m_gameStatusUI;
};