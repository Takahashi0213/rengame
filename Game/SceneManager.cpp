#include "stdafx.h"
#include "SceneManager.h"

#include "GameCamera.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;


}


SceneManager::~SceneManager()
{	
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void SceneManager::Update() {

}

void SceneManager::Render() {

}
