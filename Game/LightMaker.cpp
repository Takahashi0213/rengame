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
/// �f�B���N�V�������C�g�𐶐�����
/// </summary>
/// <param name="dir">���C�g�̕���</param>
/// <param name="col">���C�g�̐F</param>
/// <returns>�쐬�������C�g�̃|�C���^</returns>
SDirectionLight* LightMaker::D_LightMake(CVector4 dir,CVector4 col) {

	//�f�B���N�V�������C�g�𐶐�����
	SDirectionLight*d = new SDirectionLight;
	
	//���������C���X�^���X���ϒ��z��ɒǉ�����
	m_dLightList.push_back(d);

	return d;
}

/// <summary>
/// �f�B���N�V�������C�g����������
/// </summary>
/// <param name="light">�폜����f�B���N�V�������C�g�̃|�C���^</param>
void LightMaker::D_LightDelete(SDirectionLight* light) {

	//���X�g���������Ĉ�v�������̂�����
	for (auto it = m_dLightList.begin();
		it != m_dLightList.end();
		it++) {
		if (*it == light) {
			delete *it;
			m_dLightList.erase(it); //�ϒ��z�񂩂������
		}
	}

}
