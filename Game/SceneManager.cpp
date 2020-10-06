#include "stdafx.h"
#include "SceneManager.h"

#include "GameCamera.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;


}


SceneManager::~SceneManager()
{	
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void SceneManager::Update() {

}

void SceneManager::Render() {

}
