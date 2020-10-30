#pragma once
#include "EventData.h"

/// <summary>
/// EventStartを呼び出すことでイベントを開始できる
/// Gameクラスが保持
/// </summary>
class GameEvent
{
public:
	GameEvent();
	~GameEvent();

	/// <summary>
	/// イベントの実行
	/// </summary>
	/// <param name="eventName">イベントの名前</param>
	void EvemtStart(const wchar_t* eventName) {
		int EvNo = m_eventData.SearchEventNo(eventName);
		//起動済みのイベントなら強制終了
		if (m_eventData.GetEventSaveFlag(EvNo) == true) {
			return;
		}
		m_nowEventNo = EvNo;
		m_eventEndProgress = m_eventData.SearchEventEndProgress(EvNo);
		m_eventProgress = 0;
	}

	void GameEventUpdate();

private:
	//イベント一覧
	void Event_Tutorial1();
	void Event_Tutorial2();
	void Event_Tutorial3();

	EventData m_eventData;			//イベントデータ

	int m_nowEventNo = -1;			//実行中のイベント番号
	int m_eventProgress = -1;		//実行中のイベント進行度
	int m_eventEndProgress = -1;	//実行中のイベント終了進行度
	bool m_eventWaitFlag = false;	//イベントのクリック待ちフラグ
	bool m_eventEndFlag = false;	//イベント終了フラグ

};

