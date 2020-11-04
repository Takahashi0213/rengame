#include "stdafx.h"
#include "EventObject.h"


EventObject::EventObject()
{
}


EventObject::~EventObject()
{
}

void EventObject::Update() {

	UpdateActionFlag();

	//もしイベント実行可能なら実行して、自分は消滅する
	if (m_actionFlag == true) {

		//イベントの実行
		Game::GetInstance()->GetGameEvent()->EvemtStart(m_eventName);

		//削除される
		DeleteGO(this);

	}
}

void EventObject::Render() {

}