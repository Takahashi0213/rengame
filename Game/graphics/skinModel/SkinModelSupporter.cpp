#include "stdafx.h"
#include "SkinModelSupporter.h"


SkinModelSupporter::SkinModelSupporter()
{
}

SkinModelSupporter::~SkinModelSupporter()
{
}

void SkinModelSupporter::SkinModelSupporterUpdate() {

	//�܂��̓f�[�^�X�V
	SkinModelDataUpdate();

	//�������烂�f���X�V
	SkinModelMoveUpdate();
	SkinModelRotationUpdate();

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

void SkinModelSupporter::SkinModelMove(const CVector3& move, const int& moveTime, 
	const int& moveDelay, const bool& relative) {
	//���X�g�ɒǉ���
	SkinModelMoveSet set = { move,CVector3().Zero(),moveTime,moveDelay,0,relative,false };
	m_skinModelMoveList.push_back(set);
}

void SkinModelSupporter::SkinModelRotation(const float& rot, CVector3 axis, 
	const int& moveTime, const int& moveDelay, const bool& loopflag) {

	//���݂̉�]�ɍ��킹��
	CQuaternion rotation = m_skinModelRender->GetRotation();
	rotation.Multiply(axis);
	rotation.SetRotationDeg(axis, rot);

	m_skinModelRotation = rotation;
	m_skinModelRotationLimit = moveTime;
	m_skinModelRotationDelay = moveDelay;
	m_skinModelLoopRotationFlag = loopflag;
	m_skinModelRotationTimer = 0;
}

/// <summary>
/// ���f���ړ��̃A�b�v�f�[�g
/// </summary>
void SkinModelSupporter::SkinModelMoveUpdate() {

	//���X�g�����[�v
	for (auto go = m_skinModelMoveList.begin();
		go != m_skinModelMoveList.end();
		go++) {
		//�^�C�}�[��0�ȏ�Ȃ���s��
		if (go->m_skinModelMoveTimer >= 0) {

			if (go->m_skinModelMoveTimer >= go->m_skinModelMoveDelay) { //�f�B���C���l��

				//�ړ��������v�Z
				if (go->m_skinModelMoveTimer == go->m_skinModelMoveDelay) {
					if (go->m_skinModelMoveRelative == false) { //�w�肳�ꂽ���W�ֈړ�
						go->m_skinModelMoveSpeed.x = go->m_skinModelMovePos.x - m_position.x;
						go->m_skinModelMoveSpeed.y = go->m_skinModelMovePos.y - m_position.y;
						go->m_skinModelMoveSpeed.z = go->m_skinModelMovePos.z - m_position.z;
					}
					else { //���Έړ�
						go->m_skinModelMoveSpeed.x = go->m_skinModelMovePos.x;
						go->m_skinModelMoveSpeed.y = go->m_skinModelMovePos.y;
						go->m_skinModelMoveSpeed.z = go->m_skinModelMovePos.z;
					}
					go->m_skinModelMoveSpeed.x /= (float)go->m_skinModelMoveLimit;
					go->m_skinModelMoveSpeed.y /= (float)go->m_skinModelMoveLimit;
					go->m_skinModelMoveSpeed.z /= (float)go->m_skinModelMoveLimit;
				}

				m_position.x += go->m_skinModelMoveSpeed.x;
				m_position.y += go->m_skinModelMoveSpeed.y;
				m_position.z += go->m_skinModelMoveSpeed.z;

			}

			go->m_skinModelMoveTimer++;

			if (go->m_skinModelMoveTimer >= go->m_skinModelMoveLimit + go->m_skinModelMoveDelay) {
				//�����܂�
				go->m_skinModelMoveDeleteFlag = true;
				go->m_skinModelMoveTimer = -1;
				//go = m_spriteMoveList.erase(go);
			}
		}
	}

	//�폜����
	std::list<SkinModelMoveSet>::iterator it;
	it = m_skinModelMoveList.begin();
	while (it != m_skinModelMoveList.end()) {
		if (it->m_skinModelMoveDeleteFlag == true) {
			it = m_skinModelMoveList.erase(it); //erase�֐��͍폜���ꂽ�C�e���[�^�̎���Ԃ��Ă���̂ŁAerase�̖߂�l���g���B
		}
		else {
			it++; //����ȊO�͎��ցB
		}
	}

}

/// <summary>
/// ���f���̉�]�����s
/// </summary>
void SkinModelSupporter::SkinModelRotationUpdate() {

	//�^�C�}�[��0�ȏ�Ȃ���s��
	if (m_skinModelRotationTimer >= 0) {

		if (m_skinModelRotationTimer >= m_skinModelRotationDelay) { //�f�B���C���l��

															  //��]���v�Z
			m_rotation *= m_skinModelRotation;

		}

		m_skinModelRotationTimer++;

		if (m_skinModelRotationTimer >= m_skinModelRotationLimit + m_skinModelRotationDelay && m_skinModelLoopRotationFlag == false) {
			//�����܂�
			m_skinModelRotationTimer = -1;
		}
	}

}
