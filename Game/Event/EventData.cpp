#include "stdafx.h"
#include "EventData.h"

int EventData::SearchEventNo(const wchar_t* eventName) {

	//�C�x���g�ԍ��̌���
	for (int i = 0; i < 10; i++) {
		if (wcscmp(eventName, Event_Data[i].EventName) == 0) {
			return i;	//���O�ł��B
		}
	}

	return -1;	//-1�ł��Ԃ��Ƃ���

}