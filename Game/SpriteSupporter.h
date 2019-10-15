#pragma once

/// <summary>
/// �X�v���C�g�̈ړ��≉�o�������R�}���h�ł���Ă����
/// </summary>
class SpriteSupporter
{
public:
	SpriteSupporter();
	~SpriteSupporter();

	/// <summary>
	/// SpriteRender�̃A�h���X��������
	/// �ŏ��Ɏ��s���ĂˁI
	/// </summary>
	/// <param name="sp">�|�C���^</param>
	void SpriteRenderSetting(class SpriteRender* sp) {
		m_spriteRender = sp;
	}

	void SpriteSupporter_Update();

	//���s����R�}���h
	void SpriteMove(CVector2 move, int moveTime, int moveDelay, bool relative = false);
	void SpriteRotation(float rot, int moveTime, int moveDelay, bool loopflag = false);
	void SpriteScale(CVector3 scale, int moveTime, int moveDelay);
	void SpriteColor(CVector4 color, int moveTime, int moveDelay);
	void SpriteShake(CVector2 move, int moveTime, int moveCount);

private:
	//�����ƕЕt��
	void SpriteDataUpdate();
	void SpriteDataReturn();
	//�A�b�v�f�[�g�p
	void SpriteMoveUpdate();
	void SpriteRotationUpdate();
	void SpriteScaleUpdate();
	void SpriteColorUpdate();
	void SpriteShakeUpdate();

	//�����o�ϐ�
	class SpriteRender* m_spriteRender;
	CVector3 m_position = CVector3::Zero();					//���W
	CQuaternion m_rotation = CQuaternion().Identity();		//��]
	CVector3 m_scale = CVector3().One();					//�g�嗦
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };			//��Z�J���[
	//Move
	struct SpriteMoveSet {
		CVector2 m_spriteMovePos = { 0.0f,0.0f };	//�X�v���C�g�̈ړ���
		CVector2 m_spriteMoveSpeed = { 0.0f,0.0f };	//�X�v���C�g�̈ړ���
		int m_spriteMoveLimit = -1;	//�X�v���C�g�̈ړ����ԁi-1�͈ړ����ł͂Ȃ��j
		int m_spriteMoveDelay = -1;	//�X�v���C�g�̈ړ��f�B���C
		int m_spriteMoveTimer = -1; //�X�v���C�g�̈ړ��^�C�}�[
		bool m_spriteMoveRelative = false;		//�X�v���C�g�̑��Έړ��t���O�itrue�Ȃ瑊�Έړ��j
		bool m_spriteMoveDeleteFlag = false;	//�X�v���C�g�̍폜�t���O�i������Ȃ��łˁj
	};
	std::list<SpriteMoveSet> m_spriteMoveList; //�ړ��̃��X�g
	//Rotation
	CQuaternion m_spriteRotation = CQuaternion().Identity();	//1�t���[���̉�]��
	int m_spriteRotationLimit = -1;	//�X�v���C�g�̉�]���ԁi-1�͈ړ����ł͂Ȃ��j
	int m_spriteRotationDelay = -1;	//�X�v���C�g�̉�]�f�B���C
	int m_spriteRotationTimer = -1; //�X�v���C�g�̉�]�^�C�}�[
	bool m_spriteLoopRotationFlag = false;		//true�Ȃ�i���ɉ��X�Ƀt�H�[�G�o�[�������
	//Scale
	CVector3 m_spriteScale = CVector3().Zero();			//�ڕW�̑傫��
	CVector3 m_spriteScaleMove = CVector3().Zero();		//1�t���[���̕ω���
	int m_spriteScaleLimit = -1;	//�X�v���C�g�̊g�厞�ԁi-1�͈ړ����ł͂Ȃ��j
	int m_spriteScaleDelay = -1;	//�X�v���C�g�̊g��f�B���C
	int m_spriteScaleTimer = -1;	//�X�v���C�g�̊g��^�C�}�[
	//MulColor
	CVector4 m_spriteColor = CVector4().White();		//�ڕW�̐F
	CVector4 m_spriteColorMove = CVector4().White();	//1�t���[���̕ω���
	int m_spriteColorLimit = -1;	//�X�v���C�g�̐F�ύX���ԁi-1�͕ω����ł͂Ȃ��j
	int m_spriteColorDelay = -1;	//�X�v���C�g�̕ω��f�B���C
	int m_spriteColorTimer = -1;	//�X�v���C�g�̕ω��^�C�}�[
	//Shake
	CVector2 m_spriteShakeMove = { 0.0f,0.0f }; //�V�F�C�N�ł̈ړ�����
	int m_spriteShakeLimit = -1;	//�X�v���C�g�̃V�F�C�N�Ԋu�i-1�͕ω����ł͂Ȃ��j
	int m_spriteShakeCount = -1;	//�X�v���C�g�̃V�F�C�N�񐔁i0�̏ꍇ�A�~�߂�܂Ń��[�v����j
	int m_spriteShakeCounter = -1;	//�X�v���C�g�̃V�F�C�N�񐔃J�E���^�[
	int m_spriteShakeTimer = -1;	//�X�v���C�g�̃V�F�C�N�^�C�}�[

};
