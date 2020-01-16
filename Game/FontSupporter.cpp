#include "stdafx.h"
#include "FontSupporter.h"


FontSupporter::FontSupporter()
{
}


FontSupporter::~FontSupporter()
{
}

void FontSupporter::FontSupporter_Update() {

	//î•ñ‚ðŽæ“¾
	FontDataUpdate();

	//XV
	FontMoveUpdate();

	//î•ñ‚ð•Ô‚·
	FontDataReturn();

}

void FontSupporter::FontDataUpdate() {

	m_position.x = m_fontRender->GetPosition().x;
	m_position.y = m_fontRender->GetPosition().y;

}

void FontSupporter::FontDataReturn() {

	m_fontRender->SetPosition(m_position);
}

void FontSupporter::FontMoveSet(CVector2 move, int movespeed, int delay, bool relative) {

	FontDataUpdate();

	m_moveRelative = relative;
	//ˆÚ“®—ÊŒvŽZ
	if (m_moveRelative == false) {
		m_moveSpeed.x = (move.x - m_position.x) / (float)movespeed;
		m_moveSpeed.y = (move.y - m_position.y) / (float)movespeed;
	}
	else {
		m_moveSpeed.x = move.x / (float)movespeed;
		m_moveSpeed.y = move.y / (float)movespeed;
	}
	m_moveLimit = movespeed;
	m_moveDelay = delay;
	m_moveTimer = 0;
	m_moveFlag = true;

}

void FontSupporter::FontMoveUpdate() {

	if (m_moveFlag == true) {

		if (m_moveTimer >= m_moveDelay) {
			//ˆÚ“®ˆ—
			m_position.x += m_moveSpeed.x;
			m_position.y += m_moveSpeed.y;
		}

		m_moveTimer++;

		if (m_moveTimer >= m_moveLimit + m_moveDelay) {
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.y = 0.0f;
			m_moveFlag = false;
		}

	}

}