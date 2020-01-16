#include "stdafx.h"
#include "SpriteSupporter.h"

SpriteSupporter::SpriteSupporter()
{
}

SpriteSupporter::~SpriteSupporter()
{
}

/// <summary>
/// �X�v���C�g�T�|�[�^�[���܂Ƃ߂ăA�b�v�f�[�g
/// </summary>
void SpriteSupporter::SpriteSupporter_Update() {

	//�܂��̓f�[�^�X�V
	SpriteDataUpdate();

	//��������摜�X�V
	SpriteMoveUpdate();
	SpriteRotationUpdate();
	SpriteScaleUpdate();
	SpriteColorUpdate();
	SpriteShakeUpdate();

	//�Ō�ɍX�V�����f�[�^��Ԃ�
	SpriteDataReturn();
}

/// <summary>
/// �X�v���C�g�̏����ŏ��ɃA�b�v�f�[�g�I
/// </summary>
void SpriteSupporter::SpriteDataUpdate() {

	m_position = m_spriteRender->GetPosition();
	m_rotation = m_spriteRender->GetRotation();
	m_scale = m_spriteRender->GetScale();
	m_mulColor = m_spriteRender->GetMulColor();

}

/// <summary>
/// �X�v���C�g�̏���Ԃ� �Ō�Ɏ��s���悤
/// </summary>
void SpriteSupporter::SpriteDataReturn() {

	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetRotation(m_rotation);
	m_spriteRender->SetScale(m_scale);
	m_spriteRender->SetMulColor(m_mulColor);

}

void SpriteSupporter::SpriteDelayReset() {

	//
	m_spriteMoveList.clear();
	//
	m_spriteRotation = CQuaternion().Identity();	//1�t���[���̉�]��
	m_spriteRotationLimit = -1;	//�X�v���C�g�̉�]���ԁi-1�͈ړ����ł͂Ȃ��j
	m_spriteRotationDelay = -1;	//�X�v���C�g�̉�]�f�B���C
	m_spriteRotationTimer = -1; //�X�v���C�g�̉�]�^�C�}�[
	m_spriteLoopRotationFlag = false;		//true�Ȃ�i���ɉ��X�Ƀt�H�[�G�o�[�������
	//Scale
	m_spriteScale = CVector3().Zero();			//�ڕW�̑傫��
	m_spriteScaleMove = CVector3().Zero();		//1�t���[���̕ω���
	m_spriteScaleLimit = -1;	//�X�v���C�g�̊g�厞�ԁi-1�͈ړ����ł͂Ȃ��j
	m_spriteScaleDelay = -1;	//�X�v���C�g�̊g��f�B���C
	m_spriteScaleTimer = -1;	//�X�v���C�g�̊g��^�C�}�[
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

/// <summary>
/// �摜�ړ����Z�b�g����
/// </summary>
/// <param name="move">�ړ���̍��W</param>
/// <param name="moveTime">�ړ�����</param>
/// <param name="moveDelay">�ړ��f�B���C</param>
/// <param name="relative">���Έړ��t���O true�ɂ����move�ɐݒ肵���l�𑊑΍��W�Ƃ��Ĉ�����</param>
void SpriteSupporter::SpriteMove(CVector2 move, int moveTime, int moveDelay, bool relative) {

	//���X�g�ɒǉ���
	SpriteMoveSet set = { move,{0.0f,0.0f},moveTime,moveDelay,0,relative,false };
	m_spriteMoveList.push_back(set);

}

/// <summary>
/// ��]�ړ����Z�b�g����
/// </summary>
/// <remarks>
/// 
/// �i�v��]���Z�b�g���Ă��Ē�~�������ꍇ�̃T���v���R�[�h
/// SpriteRotation(0.0f, 0,0);
/// 
/// </remarks>
/// <param name="rot">1�t���[���̉�]�ʁifloat�j</param>
/// <param name="moveTime">��]���ԁiloopflag��true�Ȃ疳���j</param>
/// <param name="moveDelay">��]�f�B���C</param>
/// <param name="loopflag">true�ɂ���ƒ�~���߂܂ł����Ɖ�]</param>
void SpriteSupporter::SpriteRotation(float rot, int moveTime, int moveDelay, bool loopflag) {

	CQuaternion RotationZ;
	RotationZ.SetRotationDeg(CVector3().AxisZ(), rot);

	m_spriteRotation = RotationZ;
	m_spriteRotationLimit = moveTime;
	m_spriteRotationDelay = moveDelay;
	m_spriteLoopRotationFlag = loopflag;
	m_spriteRotationTimer = 0;
}

/// <summary>
/// �X���[�Y�Ɋg��k���������Z�b�g����
/// </summary>
/// <param name="scale">�ڕW�̑傫��</param>
/// <param name="moveTime">���쎞��</param>
/// <param name="moveDelay">����f�B���C</param>
void SpriteSupporter::SpriteScale(CVector3 scale, int moveTime, int moveDelay) {

	m_spriteScale = scale;
	m_spriteScaleLimit = moveTime;
	m_spriteScaleDelay = moveDelay;
	m_spriteScaleTimer = 0;
}

/// <summary>
/// �X�v���C�g�̏�Z�J���[�ύX���Z�b�g����
/// </summary>
/// <param name="color">�ڕW�̃J���[</param>
/// <param name="moveTime">���쎞��</param>
/// <param name="moveDelay">����f�B���C</param>
void SpriteSupporter::SpriteColor(CVector4 color, int moveTime, int moveDelay) {
	m_spriteColor = color;
	m_spriteColorLimit = moveTime;
	m_spriteColorDelay = moveDelay;
	m_spriteColorTimer = 0;
}

/// <summary>
/// �X�v���C�g�̃V�F�C�N���Z�b�g����
/// </summary>
/// <param name="move">1��̃V�F�C�N�ɂ�����ړ�����</param>
/// <param name="moveTime">���쎞��</param>
/// <param name="moveCount">����񐔁i0���w�肷��ƃ��[�v�j</param>
void SpriteSupporter::SpriteShake(CVector2 move, int moveTime, int moveCount) {
	m_spriteShakeMove.x = move.x;
	m_spriteShakeMove.y = move.y;
	m_spriteShakeLimit = moveTime;
	m_spriteShakeCount = moveCount;
	m_spriteShakeCounter = 0;
	m_spriteShakeTimer = 0;
	//�ړ����������������Ōv�Z
	m_spriteShakeMove_OneFlame.x = (m_spriteShakeMove.x / (m_spriteShakeLimit * 2));
	m_spriteShakeMove_OneFlame.y = (m_spriteShakeMove.y / (m_spriteShakeLimit * 2));

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
				//go = m_spriteMoveList.erase(go);
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

	//�^�C�}�[��0�ȏ�Ȃ���s��
	if (m_spriteScaleTimer >= 0) {

		if (m_spriteScaleTimer >= m_spriteScaleDelay) { //�f�B���C���l��

			if (m_spriteScaleTimer == m_spriteScaleDelay) {
				//�v�Z�^�C��
				m_spriteScaleMove = m_spriteScale - m_scale;
				m_spriteScaleMove /= (float)m_spriteScaleLimit;
			}

			m_scale += m_spriteScaleMove;

		}

		m_spriteScaleTimer++;

		if (m_spriteScaleTimer >= m_spriteScaleLimit + m_spriteScaleDelay) {
			//�����܂�
			m_spriteScaleTimer = -1;
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