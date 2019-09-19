#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender()
{
	//�X�L�����f���T�|�[�^�[�ɃA�h���X��n���Ă���
	m_skinModelSupporter.SkinModelRenderSetting(this);
}


SkinModelRender::~SkinModelRender()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="filePath">���f���̃t�@�C���p�X</param>
void SkinModelRender::Model_Init(const wchar_t* filePath) {
	m_skinModel.Init(filePath);
	Update(); //�����ɏ����Ӗ�����̂��ȁc�Ƃ肠��������
}

/// <summary>
/// ����������
/// </summary>
/// <param name="filePath">���f���̃t�@�C���p�X</param>
/// <param name="pos">�������W</param>
/// <param name="rot">������]</param>
/// <param name="scl">�����g�嗦</param>
void SkinModelRender::Model_Init(const wchar_t* filePath, CVector3 pos, CQuaternion rot, CVector3 scl) {
	m_skinModel.Init(filePath);
	m_position = pos;
	m_rotation = rot;
	m_scale = scl;
	Update();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
void SkinModelRender::Update() {
	m_skinModelSupporter.SkinModelSupporterUpdate();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

/// <summary>
/// �`��
/// </summary>
void SkinModelRender::Render() {
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}