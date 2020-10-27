#pragma once
#include "EventSave.h"

/// <summary>
/// イベントの名前とイベントNoのデータ
/// </summary>
class EventData
{
public:
	//名前と一致するイベント番号を返す（不一致なら-1）
	int SearchEventNo(const wchar_t* eventName);
	/// <summary>
	/// イベントの起動フラグを取得
	/// </summary>
	/// <param name="evNo">イベント番号</param>
	/// <returns>起動済みならtrueを返す</returns>
	bool GetEventSaveFlag(const int& evNo) {
		return m_eventSave.m_eventFlag[evNo];
	}

private:

	EventSave m_eventSave;		//イベントセーブ

	//イベントの名前一覧
	const wchar_t* Event_Data[MAX_EVENT_OBJ]{
		L"Tutorial_1"	//チュートリアル…スイッチと箱
		L"Tutorial_2"	//チュートリアル…箱を投げる
		L"Tutorial_3"	//チュートリアル…ダブルスイッチ
	};

};

