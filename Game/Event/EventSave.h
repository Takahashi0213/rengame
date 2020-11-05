#pragma once

/// <summary>
/// イベントの起動フラグを保存するセーブデータ
/// 何度も同じイベントが起動すると困るので…
/// </summary>
class EventSave
{
public:
	//イベントの起動フラグ
	bool m_eventFlag[MAX_EVENT_OBJ] = { false };

};
