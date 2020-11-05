#include "stdafx.h"
#include "EventData.h"

int EventData::SearchEventNo(const wchar_t* eventName) {

	//イベント番号の検索
	for (int i = 0; i < 10; i++) {
		if (wcscmp(eventName, Event_Data[i].EventName) == 0) {
			return i;	//お前です。
		}
	}

	return -1;	//-1でも返しとくか

}