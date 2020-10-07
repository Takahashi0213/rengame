#include "stdafx.h"
#include "Title.h"

Title* Title::m_instance = nullptr;

Title::Title()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


Title::~Title()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void Title::Update() {

}

void Title::Render() {

}