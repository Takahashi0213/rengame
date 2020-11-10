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
	//イベント番号と一致する最終動作番号を返す（不一致なら-1）
	int SearchEventEndProgress(const int& evNo) {
		return Event_Data[evNo].EventEndProgress;
	}
	/// <summary>
	/// イベントの起動フラグを取得
	/// </summary>
	/// <param name="evNo">イベント番号</param>
	/// <returns>起動済みならtrueを返す</returns>
	bool GetEventSaveFlag(const int& evNo) {
		return m_eventSave.m_eventFlag[evNo];
	}
	//イベントを実行済みにする
	void SetEventSaveFlag(const int& evNo) {
		m_eventSave.m_eventFlag[evNo] = true;
	}

	/// <summary>
	/// イベントセーブを返す
	/// </summary>
	EventSave* GetEventSave() {
		return &m_eventSave;
	}

private:

	EventSave m_eventSave;		//イベントセーブ

	//イベントデータ構造体
	struct EventData_Struct
	{
		const wchar_t* EventName;			//検索用の名前
		const int EventEndProgress = -1;	//イベントが終了する会話番号
	};

	//イベント一覧
	const EventData_Struct Event_Data[MAX_EVENT_OBJ]{
		{ L"Tutorial_1", 2 },	//チュートリアル…スイッチ
		{ L"Tutorial_2", 5 },	//チュートリアル…箱を投げる
		{ L"Tutorial_3", 11 },	//チュートリアル…箱の生成
	};

};

