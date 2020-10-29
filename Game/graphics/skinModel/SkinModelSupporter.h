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
	void SkinModelMove(const CVector3& move, const int& moveTime,
		const int& moveDelay, const bool& relative = false);
	void SkinModelRotation(const float& rot, CVector3 axis , const int& moveTime, 
		const int& moveDelay, const bool& loopflag = false);
	//������
	void SkinModelMoveClear() {
		m_skinModelMoveList.clear();
	}

	void SkinModelSupporterUpdate();

	//��Ԏ擾�p
	//���f���̈ړ����X�g�v�f�����擾
	//�ړ����̃��f�����ǂ����𔻕ʂ��� �Ȃ�
	int GetSkinModelMoveListLen() {
		return static_cast<int>(m_skinModelMoveList.size());
	}

private:
	//�����ƕЕt��
	void SkinModelDataUpdate();
	void SkinModelDataReturn();
	//�A�b�v�f�[�g�p
	void SkinModelMoveUpdate();
	void SkinModelRotationUpdate();

	//�����o�ϐ�
	class SkinModelRender* m_skinModelRender;
	CVector3 m_position = CVector3::Zero();						//���W
	CQuaternion m_rotation = CQuaternion().Identity();			//��]
	CVector3 m_scale = CVector3().One();						//�g�嗦
	//Move
	struct SkinModelMoveSet {
		CVector3 m_skinModelMovePos = CVector3().Zero();		//���f���̈ړ���
		CVector3 m_skinModelMoveSpeed = CVector3().Zero();		//���f���̈ړ���
		int m_skinModelMoveLimit = -1;							//���f���̈ړ����ԁi-1�͈ړ����ł͂Ȃ��j
		int m_skinModelMoveDelay = -1;							//���f���̈ړ��f�B���C
		int m_skinModelMoveTimer = -1;							//���f���̈ړ��^�C�}�[
		bool m_skinModelMoveRelative = false;					//���f���̑��Έړ��t���O�itrue�Ȃ瑊�Έړ��j
		bool m_skinModelMoveDeleteFlag = false;					//�폜�t���O�i������Ȃ��łˁj
	};
	std::list<SkinModelMoveSet> m_skinModelMoveList;			//�ړ��̃��X�g
	//Rotation
	CQuaternion m_skinModelRotation = CQuaternion().Identity();	//1�t���[���̉�]��
	int m_skinModelRotationLimit = -1;							//���f���̉�]���ԁi-1�͈ړ����ł͂Ȃ��j
	int m_skinModelRotationDelay = -1;							//���f���̉�]�f�B���C
	int m_skinModelRotationTimer = -1;							//���f���̉�]�^�C�}�[
	bool m_skinModelLoopRotationFlag = false;					//true�Ȃ�i���ɉ��X�Ƀt�H�[�G�o�[�������

};

