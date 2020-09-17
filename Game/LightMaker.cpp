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
	//�|�C���g���C�g�̏�����
	P_LightDeleteAll();

	//�f�o�b�O�p
	//for (int i = 0; i < MAX_POINT_LIGHT; i++) {
	//	CVector3 pos;
	//	pos.x = static_cast<float>(rand() % 1000) - 500.0f;
	//	pos.y = 20.0f; //������20�Œ�B
	//	pos.z = static_cast<float>(rand() % 1000) - 500.0f;
	//	float range = 50.0f;		//�e���͈͂�50�ŌŒ肵�Ă����B
	//	CVector3 color;
	//	color.x = static_cast<float>(rand() % 255) / 255.0f;
	//	color.y = static_cast<float>(rand() % 255) / 255.0f;
	//	color.z = static_cast<float>(rand() % 255) / 255.0f;

	//	P_LightMake(
	//		i,
	//		{0.0f, 30.0f, 0.0f},
	//		{1.0f,0.0f,0.0f},
	//		200.0f);

	//}

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
	m_light.color[lightNo].w = spec;

}

/// <summary>
/// �f�B���N�V�������C�g����������
/// </summary>
/// <param name="lightNo">�폜����f�B���N�V�������C�g�̏ꏊ</param>
void LightMaker::D_LightDelete(int lightNo) {

	m_light.direction[lightNo] = DirectionLight_Direction_Def;
	m_light.color[lightNo] = DirectionLight_Color_Def;

}

/// <summary>
/// �|�C���g���C�g���쐬����
/// </summary>
/// <param name="lightNo">���C�g�ԍ�</param>
/// <param name="pos">���W</param>
/// <param name="col">�J���[</param>
/// <param name="range">�͈�</param>
void LightMaker::P_LightMake(int lightNo, CVector3 pos, CVector3 col, float range) {
	m_pointLight.position[lightNo] = pos;
	m_pointLight.color[lightNo] = col;
	m_pointLight.color[lightNo].w = range;
}

/// <summary>
/// �|�C���g���C�g����������
/// </summary>
/// <param name="lightNo">���C�g�ԍ�</param>
void LightMaker::P_LightDelete(int lightNo) {
	m_pointLight.position[lightNo] = CVector3::Zero();
	m_pointLight.color[lightNo] = CVector3::Zero();
	m_pointLight.color[lightNo].w = 0.0f;
}

//�|�C���g���C�g��S��������
void LightMaker::P_LightDeleteAll() {
	//�݂�� ������
	for (int i = 0; i < MAX_POINT_LIGHT; i++) {
		P_LightDelete(i);
	}
}