#include "stdafx.h"
#include "GameEvent.h"


GameEvent::GameEvent()
{
}


GameEvent::~GameEvent()
{
}

void GameEvent::GameEventUpdate() {

	//�C�x���g���s
	if (m_nowEventNo == 0) {
		Event_Tutorial1();
	}

}

void GameEvent::Event_Tutorial1() {

}