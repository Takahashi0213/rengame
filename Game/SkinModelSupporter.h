#pragma once

/// <summary>
/// ���f���̈ړ��≉�o�������R�}���h�ł���Ă����
/// </summary>
class SkinModelSupporter
{
public:
	SkinModelSupporter();
	~SkinModelSupporter();

	/// <summary>
	/// SkinModelRender�̃A�h���X��������
	/// �ŏ��Ɏ��s���ĂˁI
	/// </summary>
	/// <param name="sp">�|�C���^</param>
	void SkinModelRenderSetting(class SkinModelRender* smr) {
		m_skinModelRender = smr;
	}

	//���s����R�}���h
	void SkinModelMove(CVector3 move, int moveTime, int moveDelay, bool relative = false);

	void SkinModelSupporterUpdate();

private:
	//�����ƕЕt��
	void SkinModelDataUpdate();
	void SkinModelDataReturn();
	//�A�b�v�f�[�g�p
	void SkinModelMoveUpdate();

	//�����o�ϐ�
	class SkinModelRender* m_skinModelRender;
	CVector3 m_position = CVector3::Zero();					//���W
	CQuaternion m_rotation = CQuaternion().Identity();		//��]
	CVector3 m_scale = CVector3().One();					//�g�嗦
	//Move
	struct SkinModelMoveSet {
		CVector3 m_skinModelMovePos = CVector3().Zero();	//�X�v���C�g�̈ړ���
		CVector3 m_skinModelMoveSpeed = CVector3().Zero();	//�X�v���C�g�̈ړ���
		int m_skinModelMoveLimit = -1;	//�X�v���C�g�̈ړ����ԁi-1�͈ړ����ł͂Ȃ��j
		int m_skinModelMoveDelay = -1;	//�X�v���C�g�̈ړ��f�B���C
		int m_skinModelMoveTimer = -1; //�X�v���C�g�̈ړ��^�C�}�[
		bool m_skinModelMoveRelative = false;		//�X�v���C�g�̑��Έړ��t���O�itrue�Ȃ瑊�Έړ��j
		bool m_skinModelMoveDeleteFlag = false;	//�X�v���C�g�̍폜�t���O�i������Ȃ��łˁj
	};
	std::list<SkinModelMoveSet> m_skinModelMoveList; //�ړ��̃��X�g
	//Rotation

};

