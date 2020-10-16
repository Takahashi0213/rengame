#include "stdafx.h"
#include "TransitionGenerator.h"

TransitionGenerator* TransitionGenerator::m_instance = nullptr;

TransitionGenerator::TransitionGenerator()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}
	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


TransitionGenerator::~TransitionGenerator()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void TransitionGenerator::Update() {

	if (m_borderLine < 0.0f) {
		m_nowTransitionFlag = false;
	}
	if (m_borderLine > MoveSpeed) {
		m_nowTransitionFlag = false;
	}

	if (m_nowTransitionFlag == true) {
		if (m_transitionMode == false) {
			m_borderLine += (1.0f / m_transitionLimit)*MoveSpeed;
		}
		else {
			m_borderLine -= (1.0f / m_transitionLimit)*MoveSpeed;
		}
		m_transitionSprite.m_alpha = m_borderLine;
	}

	m_transitionSprite.Sprite_Update();

}
void TransitionGenerator::Render() {

	m_transitionSprite.Sprite_Draw();
}

/// <summary>
/// トランジションの開始
/// falseなら表示、trueなら消去
/// </summary>
/// <remarks>
/// 
/// ※サンプルコード
/// 
/// //斜めボックス、60フレームかけて表示
/// TransitionInit(TransitionName::NanameBox, 60, false);
/// 
/// </remarks>
void TransitionGenerator::TransitionInit(
	const TransitionName& name, 
	const int& MoveTime,
	const bool& mode
) {

	//せってぃんぐ
	m_nowTransitionFlag = true;
	m_transitionLimit = MoveTime;
	m_transitionMode = mode;
	if (mode == false) {
		m_borderLine = 0.0f;
	}
	else {
		m_borderLine = MoveSpeed / 2.0f;
	}
	//ぶちこみます
	m_transitionSprite.Sprite_Init(Transition_DataList[name].SpriteName, FRAME_BUFFER_W, FRAME_BUFFER_H);

}