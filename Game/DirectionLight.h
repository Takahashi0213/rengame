#pragma once

//�f�B���N�V�������C�g

struct SDirectionLight {
	CVector4 direction[MAX_DIRECTION_LIGHT];		//���C�g�̕���
	CVector4 color[MAX_DIRECTION_LIGHT];			//���C�g�̃J���[
	float specPower[MAX_DIRECTION_LIGHT];			//�X�y�L�����̍i��
};

