#pragma once
#include "system/CGameObjectManager.h"
#include "Game.h"
#include "GameBox.h"
#include "Player.h"
#include "GameCamera.h"

/// <summary>
/// ���𐶐������葀�삵����
/// �E�V���O���g��
/// </summary>
class BoxMaker final : public IGameObject
{
	static BoxMaker* m_instance;
public:
	/// <summary>
	/// ���[�h
	/// NomalMode���ʏ� �ʂ̃N���b�N�҂�
	/// FocusMode���g�咆 ���h���b�O�Ŋg��A�����ƃm�[�}�����[�h�ɖ߂�
	/// </summary>
	enum BoxMakerMode {
		NomalMode,
		FocusMode,
	};
	/// <summary>
	/// ���̌���
	/// </summary>
	enum BoxDirection {
		X_Direction,
		Y_Direction,
		Z_Direction,
	};

	BoxMaker();
	~BoxMaker();
	void Update()override;
	void Render()override;

	/// <summary>
	/// �v���C���[�̃|�C���^��ۑ�
	/// </summary>
	/// <param name="game">�A�h���X</param>
	void SetPlayer(Player* pl) {
		m_player = pl;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static BoxMaker* BoxMaker::GetInstance() {
		return m_instance;
	}

	//���̐F�X���擾����
	std::list<GameBox*> GetBoxList() {
		return m_boxList;
	}

	/// <summary>
	/// ���̏���
	/// </summary>
	/// <param name="deleteBox"></param>
	void BoxDelete(GameBox* deleteBox);
	std::list<GameBox*>::iterator BoxDelete_it(std::list<GameBox*>::iterator deleteBox_it);
	//���̑S����
	void BoxAllDelete();

private:
	void BoxUpdate();
	void ModeChange();
	//�쐬�n�_�ƃv���C���[�̋��������ȉ�����Ȃ��ƍ��Ȃ�
	bool BoxCreateCheck();

	Game* m_game = nullptr;
	Player* m_player = nullptr;

	CVector3 m_boxPos = CVector3().Zero();			//�����W

	BoxMakerMode m_boxMakerMode = NomalMode;		//�{�b�N�X���C�J�[���[�h

	CVector3 m_boxN = CVector3::Zero();				//�@����

	//�����X�g
	std::list<GameBox*> m_boxList;					//�����X�g
	std::list<int>m_manaList;						//���̔����ǂ̂��炢�}�i�������Ă邩�ȁH�̃��X�g
	GameBox* m_nowBox = nullptr;					//���݌��Ă���{�b�N�X
	GameBox* m_nowBox_Stock = nullptr;				//�ȑO���Ă����{�b�N�X���ꎞ�ۑ��I
	std::list<GameBox*> m_nowBoxList;				//���ύX���̃{�b�N�X���X�g
	GameBox* m_originBox = nullptr;					//�ŏ��̔�

	//�ʃ`�F�b�N�p
	bool m_surfaceFlag = false;						//m_boxPoint�̐ݒ�t���O

	//���g��p
	CVector3 m_box_N = CVector3::Zero();			//���Ă���{�b�N�X�̕���
	CVector3 m_box_N_Now = CVector3::Zero();		//���݌��Ă���{�b�N�X�̕���
	CVector2 m_mouseMove = { 0.0f,0.0f };			//�}�E�X�̈ړ��ʂ�ۑ��i�}�C�i�X�ɂȂ����烄�o���j
	CVector3 m_boxScale = CVector3().One();			//�g�嗦�I
	CVector3 m_boxScaleDef = { 0.1f,0.1f,0.1f };	//�f�t�H���g�����̂��
	CVector3 m_surfaceScaleNew = CVector3::Zero();	//���g�債�悤�Ƃ��Ă���ʂ̑傫��
	CVector3 m_boxScaleHosei = CVector3().One();	//���̃f�t�H���g�T�C�Y�ƑI�������ʂ̑傫�����r���ĕ␳���v�Z����I�I�I
	CVector3 m_planeScale = CVector3::Zero();		//�ʂ̑傫����������ꏊ�i�ꎞ�ۑ��j
	CVector3 m_planeScaleNow = CVector3::Zero();	//�ʂ̑傫����������ꏊ�i�ŐV�Łj
	BoxDirection m_boxDirection;					//���݂̔��̌���
	CVector3 m_boxScale_Ratio = CVector3::Zero();	//���̊g�嗦�䗦

	//���W
	//CVector3 m_boxPoint[4];						//����4�̍��W�I
	//CVector3 m_boxPoint_Stock[4];					//��r�p�̊i�[�ꏊ

	//�N���G�C�g����
	int m_box_Nom = 1;								//���݂��锠�̐�
	bool m_undoFlag = false;						//�A���h�D�{�^����������Ă��邩�t���O

	//�}�i����
	int m_downMana = 0;								//�������̃}�i������
	int m_startMana = 0;							//�ڍs���̃}�i
	int m_downMana_Stock = 0;						//�g��k���p�ꎞ�ۑ�
	int m_manaHosei = 0;							//�g��k���p�␳

	//�萔
	const float PosHoseiY = 200.0f;									//���C���q�b�g���Ȃ��������̕␳
	const float m_mouseMoveHosei = 0.5f;							//�}�E�X�̈ړ��ɉ������g�嗦�ύX�̕␳�l
	const CVector3 m_surfaceScaleDef = { 100.0f,100.0f,100.0f };	//�ʂ̃f�t�H���g�T�C�Y
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };			//���̏����X�P�[��
	const float Player_Box_MaxRange = 500.0f;						//���쐬�̌��E����

	//�N���G�C�g���[�h�Ɉڍs���邽�߂ɕK�v�ȍŒ�}�i���A���㔠�𐶐�����Ƃ��ɏ����}�i���ł�����
	const int CreateModeChangeBorder = 10;
	const float DefManaHosei = 5.0f;								//���쐬�̏���}�i�␳ ���ʂɏ��Z���l���傫���قǈ����Ȃ�

};

