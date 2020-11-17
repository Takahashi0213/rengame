#include "stdafx.h"
#include "EventObject.h"


EventObject::EventObject()
{
}


EventObject::~EventObject()
{
}

void EventObject::Update() {
	
	//イベント中なら強制終了
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//アクションモードでないなら強制終了
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}

	//フラグの更新
	UpdateActionFlag();

	//もしイベント実行可能なら実行して、自分は消滅する
	if (m_actionFlag == true) {

		//イベントの実行
		SceneManager::GetInstance()->GetGameEvent()->EvemtStart(m_eventName, m_LinkPt);

		//削除される
		DeleteGO(this);

	}
}

void EventObject::Render() {

}