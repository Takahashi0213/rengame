#include "stdafx.h"
#include "EffekseerSupporter.h"

EffekseerSupporter* EffekseerSupporter::m_instance = nullptr;

EffekseerSupporter::EffekseerSupporter()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


EffekseerSupporter::~EffekseerSupporter()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

Effekseer::Handle EffekseerSupporter::NewEffect(const wchar_t* EffectFileName, bool PostFlag,
	Effekseer::Vector3D DefPos) {

	//�T���v���̃G�t�F�N�g�����[�h����B
	Effekseer::Effect* m_effect = Effekseer::Effect::Create(CGameObjectManager::GetInstance()->GetEffekseerManager(),
		(const EFK_CHAR*)EffectFileName);
	//�G�t�F�N�g���Đ�����B
	Effekseer::Handle m_playEffectHandle = CGameObjectManager::GetInstance()->
		GetEffekseerManager()->Play(m_effect, DefPos.X, DefPos.Y, DefPos.Z);

	//���X�g�ɒǉ���
	Effect set = { m_playEffectHandle,PostFlag };
	m_effectList.push_back(set);

	return m_playEffectHandle;
}

Effekseer::Handle EffekseerSupporter::NewEffect(const EffectData EffectFileName, bool PostFlag,
	Effekseer::Vector3D DefPos) {

	//�T���v���̃G�t�F�N�g�����[�h����B
	Effekseer::Effect* m_effect = Effekseer::Effect::Create(CGameObjectManager::GetInstance()->GetEffekseerManager(),
		(const EFK_CHAR*)EffectDetaBase[EffectFileName]);
	//�G�t�F�N�g���Đ�����B
	Effekseer::Handle m_playEffectHandle = CGameObjectManager::GetInstance()->
		GetEffekseerManager()->Play(m_effect, DefPos.X, DefPos.Y, DefPos.Z);

	//���X�g�ɒǉ���
	Effect set = { m_playEffectHandle,PostFlag };
	m_effectList.push_back(set);

	return m_playEffectHandle;

}

Effekseer::Handle EffekseerSupporter::NewEffect_Vector(const EffectData EffectFileName,
	bool PostFlag, float X, float Y, float Z) {

	//�ϊ�
	Effekseer::Vector3D Pos;
	Pos.X = X;
	Pos.Y = Y;
	Pos.Z = Z;

	//�T���v���̃G�t�F�N�g�����[�h����B
	Effekseer::Effect* m_effect = Effekseer::Effect::Create(CGameObjectManager::GetInstance()->GetEffekseerManager(),
		(const EFK_CHAR*)EffectDetaBase[EffectFileName]);
	//�G�t�F�N�g���Đ�����B
	Effekseer::Handle m_playEffectHandle = CGameObjectManager::GetInstance()->
		GetEffekseerManager()->Play(m_effect, Pos.X, Pos.Y, Pos.Z);

	//���X�g�ɒǉ���
	Effect set = { m_playEffectHandle,PostFlag };
	m_effectList.push_back(set);

	return m_playEffectHandle;

}

void EffekseerSupporter::EffectClear() {

	//�폜����
	std::list<Effect>::iterator it;
	it = m_effectList.begin();
	while (it != m_effectList.end()) {

		if (CGameObjectManager::GetInstance()->GetEffekseerManager()->Exists(it->Handle) == false) {
			it = m_effectList.erase(it); //erase�֐��͍폜���ꂽ�C�e���[�^�̎���Ԃ��Ă���̂ŁAerase�̖߂�l���g���B
		}
		else {
			it++; //����ȊO�͎��ցB
		}
	}

}

void EffekseerSupporter::NoPostStop() {

	for (auto go = m_effectList.begin();
		go != m_effectList.end();
		go++) {

		if (go->PostFlag == false) {
			CGameObjectManager::GetInstance()->GetEffekseerManager()->SetPaused(go->Handle, true);
		}

	}

}
void EffekseerSupporter::NoPostMove() {

	for (auto go = m_effectList.begin();
		go != m_effectList.end();
		go++) {

		if (go->PostFlag == false) {
			CGameObjectManager::GetInstance()->GetEffekseerManager()->SetPaused(go->Handle, false);
		}

	}

}
