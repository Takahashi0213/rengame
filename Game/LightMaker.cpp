#include "stdafx.h"
#include "LightMaker.h"

LightMaker* LightMaker::m_instance = nullptr;

LightMaker::LightMaker()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

	//�f�B���N�V�������C�g�̏�����
	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
		D_LightDelete(i);
	}

	//���C�g�J�����̍��W
	SetLightCameraPosition({ 0.0f, 1000.0f, 0.0f });
	SetLightCameraTarget({ 0.0f, 0.0f, 0.0f });

}

LightMaker::~LightMaker()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void LightMaker::Update() {
}

void LightMaker::Render() {

}

/// <summary>
/// �f�B���N�V�������C�g��ݒ肷��
/// </summary>
/// <param name="lightNo">���C�g�̔ԍ�</param>
/// <param name="dir">���C�g�̕���</param>
/// <param name="col">���C�g�̐F</param>
/// <param name="spec">�X�y�L����</param>
/// <returns>�쐬�������C�g�̃|�C���^</returns>
void LightMaker::D_LightMake(int lightNo,CVector4 dir,CVector4 col, float spec) {

	m_light.direction[lightNo] = dir;
	m_light.color[lightNo] = col;
	m_light.specPower[lightNo] = spec;

}

/// <summary>
/// �f�B���N�V�������C�g����������
/// </summary>
/// <param name="lightNo">�폜����f�B���N�V�������C�g�̏ꏊ</param>
void LightMaker::D_LightDelete(int lightNo) {

	m_light.direction[lightNo] = { 0.0f, -1.0f, 0.0f, 0.0f };
	m_light.color[lightNo] = { 0.5f,0.5f, 0.5f, 1.0f };
	m_light.specPower[lightNo] = 10.0f;

}
