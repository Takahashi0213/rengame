#pragma once

/// <summary>
/// �O���t�B�b�N�֘A�̕ϐ��F�X
/// </summary>
class GameGraphic {
public:

	//���o�p�ϐ�
	float m_blurIntensity = 0.0f;		//��ʂɃu���[��������|�X�g�G�t�F�N�g�̐��l
	const int m_blurPriority = 6;		//���̐��l�ȉ���t_sprite�̓u���[�̑ΏۂɂȂ�
	bool m_dofFlag = true;				//Dof�����s����H
	const int TransitionTime = 60;		//��ʓ]���g�����W�V�����t���[����

	const CVector3 LoadingAnimePos = { 480.0f,-220.0f,0.0f };	//���[�f�B���O�A�j���[�V�����̍��W

};