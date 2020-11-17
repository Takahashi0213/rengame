#include "stdafx.h"
#include "SpriteSupporter.h"

SpriteSupporter::SpriteSupporter()
{
}

SpriteSupporter::~SpriteSupporter()
{
}

void SpriteSupporter::SpriteSupporter_Update() {

	//�܂��̓f�[�^�X�V
	SpriteDataUpdate();

	//��������摜�X�V
	SpriteMoveUpdate();
	SpriteRotationUpdate();
	SpriteScaleUpdate();
	SpriteColorUpdate();
	SpriteShakeUpdate();
	SpritePatternUpdate();

	//�I�[�g�f�X�`�F�b�N
	if (m_autoDeathFlag == true) {
		//�S�����삵�Ă��Ȃ��H�H
		if (GetSpriteMoveListLen() == 0 &&
			GetSpriteScaleListLen() == 0) {
			//���ł���
			DeleteGO(m_spriteRender);
		}
	}

	//�Ō�ɍX�V�����f�[�^��Ԃ�
	SpriteDataReturn();
}

void SpriteSupporter::SpriteDataUpdate() {

	m_position = m_spriteRender->GetPosition(m_spriteNo);
	m_rotation = m_spriteRender->GetRotation(m_spriteNo);
	m_scale = m_spriteRender->GetScale(m_spriteNo);
	m_mulColor = m_spriteRender->GetMulColor(m_spriteNo);
	m_maxPattern = m_spriteRender->GetMaxPattern();
	m_nowPattern = m_spriteRender->GetNowPattern();

}

void SpriteSupporter::SpriteDataReturn() {

	m_spriteRender->SetPosition(m_position, m_spriteNo);
	m_spriteRender->SetRotation(m_rotation, m_spriteNo);
	m_spriteRender->SetScale(m_scale, m_spriteNo);
	m_spriteRender->SetMulColor(m_mulColor, m_spriteNo);
	if (m_maxPattern > -1) {
		m_spriteRender->ChangePattern(m_nowPattern);
	}

}

void SpriteSupporter::SpriteDelayReset() {

	//Move
	m_spriteMoveList.clear();
	//Rotation
	m_spriteRotation = CQuaternion().Identity();	//1�t���[���̉�]��
	m_spriteRotationLimit = -1;	//�X�v���C�g�̉�]���ԁi-1�͈ړ����ł͂Ȃ��j
	m_spriteRotationDelay = -1;	//�X�v���C�g�̉�]�f�B���C
	m_spriteRotationTimer = -1; //�X�v���C�g�̉�]�^�C�}�[
	m_spriteLoopRotationFlag = false;		//true�Ȃ�i���ɉ��X�Ƀt�H�[�G�o�[�������
	//Scale
	m_spriteScaleList.clear();
	//MulColor
	m_spriteColor = CVector4().White();		//�ڕW�̐F
	m_spriteColorMove = CVector4().White();	//1�t���[���̕ω���
	m_spriteColorLimit = -1;	//�X�v���C�g�̐F�ύX���ԁi-1�͕ω����ł͂Ȃ��j
	m_spriteColorDelay = -1;	//�X�v���C�g�̕ω��f�B���C
	m_spriteColorTimer = -1;	//�X�v���C�g�̕ω��^�C�}�[
	//Shake
	m_spriteShakeMove.x = 0.0f;
	m_spriteShakeMove.y = 0.0f;
	m_spriteShakeMove_OneFlame.x = 0.0f;
	m_spriteShakeMove_OneFlame.y = 0.0f;
	m_spriteShakeLimit = -1;	//�X�v���C�g�̃V�F�C�N�Ԋu�i-1�͕ω����ł͂Ȃ��j
	m_spriteShakeCount = -1;	//�X�v���C�g�̃V�F�C�N�񐔁i0�̏ꍇ�A�~�߂�܂Ń��[�v����j
	m_spriteShakeCounter = -1;	//�X�v���C�g�̃V�F�C�N�񐔃J�E���^�[
	m_spriteShakeTimer = -1;	//�X�v���C�g�̃V�F�C�N�^�C�}�[

}

void SpriteSupporter::SpriteMove(const CVector2& move, const int& moveTime,
	const int& moveDelay, const bool& relative) {

	//���X�g�ɒǉ���
	SpriteMoveSet set = { move,{0.0f,0.0f},moveTime,moveDelay,0,relative,false };
	m_spriteMoveList.push_back(set);

}

void SpriteSupporter::SpriteRotation(const float& rot, const int& moveTime,
	const int& moveDelay, const bool& loopflag) {

	CQuaternion RotationZ;
	RotationZ.SetRotationDeg(CVector3().AxisZ(), rot);

	m_spriteRotation = RotationZ;
	m_spriteRotationLimit = moveTime;
	m_spriteRotationDelay = moveDelay;
	m_spriteLoopRotationFlag = loopflag;
	m_spriteRotationTimer = 0;
}

void SpriteSupporter::SpriteScale(const CVector3& scale, const int& moveTime, const int& moveDelay) {

	//���X�g�ɒǉ���
	SpriteScaleSet set = { scale ,CVector3::Zero(),moveTime,moveDelay , 0 ,false };
	m_spriteScaleList.push_back(set);

}
void SpriteSupporter::SpriteScale(const float& scale, const int& moveTime, const int& moveDelay) {
	CVector3 Scale = { scale ,scale ,1.0f };

	//���X�g�ɒǉ���
	SpriteScaleSet set = { Scale ,CVector3::Zero(),moveTime,moveDelay , 0 ,false };
	m_spriteScaleList.push_back(set);

}

void SpriteSupporter::SpriteColor(const CVector4& color, const int& moveTime, const int& moveDelay) {
	m_spriteColor = color;
	m_spriteColorLimit = moveTime;
	m_spriteColorDelay = moveDelay;
	m_spriteColorTimer = 0;
}

void SpriteSupporter::SpriteShake(const CVector2& move, const int& moveTime, const int& moveCount) {
	m_spriteShakeMove.x = move.x;
	m_spriteShakeMove.y = move.y;
	m_spriteShakeLimit = moveTime;
	m_spriteShakeCount = moveCount;
	m_spriteShakeCounter = 0;
	m_spriteShakeTimer = 0;
	//�ړ������������Ōv�Z
	m_spriteShakeMove_OneFlame.x = (m_spriteShakeMove.x / (m_spriteShakeLimit * 2));
	m_spriteShakeMove_OneFlame.y = (m_spriteShakeMove.y / (m_spriteShakeLimit * 2));

}

void SpriteSupporter::SpritePattern(const int& moveTime, const bool& loopflag, const int& overLimit, const bool& stopflag) {
	m_patternLimit = moveTime;
	m_patternTimer = 0;
	m_patternOverLimit = overLimit;
	m_patternLoopFlag = loopflag;
	m_patternStopFlag = stopflag;
}

//////////////////////////////////////
///////��������A�b�v�f�[�g�֐�///////
//////////////////////////////////////

/// <summary>
/// �X�v���C�g�̈ړ������s
/// </summary>
void SpriteSupporter::SpriteMoveUpdate() {

	//���X�g�����[�v
	for (auto go = m_spriteMoveList.begin();
		go != m_spriteMoveList.end();
		go++) {
		//�^�C�}�[��0�ȏ�Ȃ���s��
		if (go->m_spriteMoveTimer >= 0) {

			if (go->m_spriteMoveTimer >= go->m_spriteMoveDelay) { //�f�B���C���l��

				//�ړ��������v�Z
				if (go->m_spriteMoveTimer == go->m_spriteMoveDelay) {
					if (go->m_spriteMoveRelative == false) { //�w�肳�ꂽ���W�ֈړ�
						go->m_spriteMoveSpeed.x = go->m_spriteMovePos.x - m_position.x;
						go->m_spriteMoveSpeed.y = go->m_spriteMovePos.y - m_position.y;
					}
					else { //���Έړ�
						go->m_spriteMoveSpeed.x = go->m_spriteMovePos.x;
						go->m_spriteMoveSpeed.y = go->m_spriteMovePos.y;
					}
					go->m_spriteMoveSpeed.x /= (float)go->m_spriteMoveLimit;
					go->m_spriteMoveSpeed.y /= (float)go->m_spriteMoveLimit;
				}

				m_position.x += go->m_spriteMoveSpeed.x;
				m_position.y += go->m_spriteMoveSpeed.y;

			}

			go->m_spriteMoveTimer++;

			if (go->m_spriteMoveTimer >= go->m_spriteMoveLimit + go->m_spriteMoveDelay) {
				//�����܂�
				go->m_spriteMoveDeleteFlag = true;
				go->m_spriteMoveTimer = -1;
			}
		}
	}

	//�폜����
	std::list<SpriteMoveSet>::iterator it;
	it = m_spriteMoveList.begin();
	while (it != m_spriteMoveList.end()) {
		if (it->m_spriteMoveDeleteFlag == true) {
			it = m_spriteMoveList.erase(it); //erase�֐��͍폜���ꂽ�C�e���[�^�̎���Ԃ��Ă���̂ŁAerase�̖߂�l���g���B
		}
		else {
			it++; //����ȊO�͎��ցB
		}
	}

}

/// <summary>
/// �X�v���C�g�̉�]�����s
/// </summary>
void SpriteSupporter::SpriteRotationUpdate() {

	//�^�C�}�[��0�ȏ�Ȃ���s��
	if (m_spriteRotationTimer >= 0) {

		if (m_spriteRotationTimer >= m_spriteRotationDelay) { //�f�B���C���l��

			//��]���v�Z
			m_rotation *= m_spriteRotation;

		}

		m_spriteRotationTimer++;

		if (m_spriteRotationTimer >= m_spriteRotationLimit + m_spriteRotationDelay && m_spriteLoopRotationFlag == false) {
			//�����܂�
			m_spriteRotationTimer = -1;
		}
	}

}

/// <summary>
/// �X�v���C�g�̊g��k�������s
/// </summary>
void SpriteSupporter::SpriteScaleUpdate() {

	for (auto go = m_spriteScaleList.begin();
		go != m_spriteScaleList.end();
		go++) {
		//�^�C�}�[��0�ȏ�Ȃ���s��
		if (go->m_spriteScaleTimer >= 0) {

			if (go->m_spriteScaleTimer >= go->m_spriteScaleDelay) { //�f�B���C���l��

				if (go->m_spriteScaleTimer == go->m_spriteScaleDelay) {
					//�v�Z�^�C��
					go->m_spriteScaleMove = go->m_spriteScale - m_scale;
					go->m_spriteScaleMove /= (float)go->m_spriteScaleLimit;
				}

				m_scale += go->m_spriteScaleMove;

			}

			go->m_spriteScaleTimer++;

			if (go->m_spriteScaleTimer >= go->m_spriteScaleLimit + go->m_spriteScaleDelay) {
				//�����܂�
				go->m_spriteScaleDeleteFlag = true;
				go->m_spriteScaleTimer = -1;
			}
		}

	}
	
	//�폜����
	std::list<SpriteScaleSet>::iterator it;
	it = m_spriteScaleList.begin();
	while (it != m_spriteScaleList.end()) {
		if (it->m_spriteScaleDeleteFlag == true) {
			it = m_spriteScaleList.erase(it); //erase�֐��͍폜���ꂽ�C�e���[�^�̎���Ԃ��Ă���̂ŁAerase�̖߂�l���g���B
		}
		else {
			it++; //����ȊO�͎��ցB
		}
	}

}

/// <summary>
/// �X�v���C�g�̐F�ύX�����s
/// </summary>
void SpriteSupporter::SpriteColorUpdate() {

	//�^�C�}�[��0�ȏ�Ȃ���s��
	if (m_spriteColorTimer >= 0) {

		if (m_spriteColorTimer >= m_spriteColorDelay) { //�f�B���C���l��

			if (m_spriteColorTimer == m_spriteColorDelay) {
				//�v�Z�^�C��
				m_spriteColorMove = m_spriteColor - m_mulColor;
				m_spriteColorMove.x /= (float)m_spriteColorLimit;
				m_spriteColorMove.y /= (float)m_spriteColorLimit;
				m_spriteColorMove.z /= (float)m_spriteColorLimit;
				m_spriteColorMove.w /= (float)m_spriteColorLimit;
			}

			m_mulColor.x += m_spriteColorMove.x;
			m_mulColor.y += m_spriteColorMove.y;
			m_mulColor.z += m_spriteColorMove.z;
			m_mulColor.w += m_spriteColorMove.w;

			//�ŏ��v�Z
			if (m_mulColor.x < 0.0f) {
				m_mulColor.x = 0.0f;
			}			
			if (m_mulColor.y < 0.0f) {
				m_mulColor.y = 0.0f;
			}			
			if (m_mulColor.z < 0.0f) {
				m_mulColor.z = 0.0f;
			}		
			if (m_mulColor.w < 0.0f) {
				m_mulColor.w = 0.0f;
			}

		}

		m_spriteColorTimer++;

		if (m_spriteColorTimer >= m_spriteColorLimit + m_spriteColorDelay) {
			//�����܂�
			m_spriteColorTimer = -1;
		}
	}

}

/// <summary>
/// �X�v���C�g�̃V�F�C�N�����s
/// </summary>
void SpriteSupporter::SpriteShakeUpdate() {

	if (m_spriteShakeLimit == -1) {
		//���s���łȂ�
		return;
	}

	//�ړ�����
	m_position.x += m_spriteShakeMove_OneFlame.x;
	m_position.y += m_spriteShakeMove_OneFlame.y;

	//�^�C�}�[�̏���
	m_spriteShakeTimer++;
	if (m_spriteShakeTimer == (m_spriteShakeLimit / 2)) {
		//�܂�Ԃ�
		m_spriteShakeMove_OneFlame.x *= -1.0f;
		m_spriteShakeMove_OneFlame.y *= -1.0f;

	}
	if (m_spriteShakeTimer >= m_spriteShakeLimit) {

		//1�V�F�C�N����
		m_spriteShakeTimer = 0;
		m_spriteShakeMove_OneFlame.x *= -1.0f;
		m_spriteShakeMove_OneFlame.y *= -1.0f;

		//�����V�F�C�N�łȂ��Ȃ�V�F�C�N�񐔂����Z
		if (m_spriteShakeCount > 0) {
			m_spriteShakeCounter++;
			if (m_spriteShakeCount <= m_spriteShakeCounter) {
				//�V�F�C�N�I��
				m_spriteShakeLimit = -1;
			}
		}
	}

}

/// <summary>
/// �p�^�[���ύX�����s
/// </summary>
void SpriteSupporter::SpritePatternUpdate() {

	if (m_patternLimit > -1) {
		m_patternTimer++;
		if (m_patternTimer >= m_patternLimit) {
			//�p�^�[�����Z
			m_patternTimer = 0;
			m_nowPattern++;
		}
		//�p�^�[�����I�[�o�[�c
		if (m_nowPattern > m_maxPattern - 1) {
			//���[�v����H
			if (m_patternLoopFlag == false) {
				//�A���t�@��0�ɂ��ďI��
				m_patternLimit = -1;
				m_nowPattern = m_maxPattern - 1;
				//��~���Ȃ��Ȃ�t�F�[�h�A�E�g
				if (m_patternStopFlag == false) {
					SpriteColor({ m_mulColor.x,m_mulColor.y,m_mulColor.z, 0.0f }, 6, m_patternOverLimit);
					SpriteColorUpdate();
				}
			}
			else {
				//���[�v����
				m_nowPattern = 0;
			}
		}
	}

}