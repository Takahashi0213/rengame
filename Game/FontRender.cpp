#include "stdafx.h"
#include "FontRender.h"

void FontRender::Update() {
	//�D��x���X�v���C�g�ɕύX
	this->SetObjectTag(t_Sprite);
}

void FontRender::Render() {
	PostRender();
}

void FontRender::PostRender()
{
	m_font.Begin();

	const wchar_t* text = nullptr;
	if (m_text.c_str() != nullptr) {
		text = m_text.c_str();
	}

	m_font.Draw(
		text,
		m_position,
		m_color,
		m_rotation,
		m_scale,
		m_pivot);

	m_font.End();
}
