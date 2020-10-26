#include "stdafx.h"
#include "GameEvent.h"


GameEvent::GameEvent()
{
}


GameEvent::~GameEvent()
{
}

void GameEvent::GameEventUpdate() {

	//イベント実行
	if (m_nowEventNo == 0) {
		Event_Tutorial1();
	}

}

void GameEvent::Event_Tutorial1() {

}