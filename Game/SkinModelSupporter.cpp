#include "stdafx.h"
#include "SkinModelSupporter.h"


SkinModelSupporter::SkinModelSupporter()
{
}

SkinModelSupporter::~SkinModelSupporter()
{
}

/// <summary>
/// �܂Ƃ߂ăA�b�v�f�[�g
/// </summary>
void SkinModelSupporter::SkinModelSupporterUpdate() {

	//�܂��̓f�[�^�X�V
	SkinModelDataUpdate();

	//�������烂�f���X�V
	SkinModelMoveUpdate();

	//�Ō�ɍX�V�����f�[�^��Ԃ�
	SkinModelDataReturn();
}

/// <summary>
/// ���f���̏����ŏ��ɃA�b�v�f�[�g�I
/// </summary>
void SkinModelSupporter::SkinModelDataUpdate() {

	m_position = m_skinModelRender->GetPosition();
	m_rotation = m_skinModelRender->GetRotation();
	m_scale = m_skinModelRender->GetScale();

}

/// <summary>
/// ���f���̏���Ԃ� �Ō�Ɏ��s���悤
/// </summary>
void SkinModelSupporter::SkinModelDataReturn() {
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}

/// <summary>
/// �ړ����Z�b�g����
/// </summary>
/// <param name="move">�ړ���̍��W</param>
/// <param name="moveTime">�ړ�����</param>
/// <param name="moveDelay">�ړ��f�B���C</param>
/// <param name="relative">���Έړ��t���O true�ɂ����move�ɐݒ肵���l�𑊑΍��W�Ƃ��Ĉ�����</param>
void SkinModelSupporter::SkinModelMove(CVector3 move, int moveTime, int moveDelay, bool relative) {
	//���X�g�ɒǉ���
	SkinModelMoveSet set = { move,CVector3().Zero(),moveTime,moveDelay,0,relative,false };
	m_skinModelMoveList.push_back(set);
}

/// <summary>
/// ���f���ړ��̃A�b�v�f�[�g
/// </summary>
void SkinModelSupporter::SkinModelMoveUpdate() {

}