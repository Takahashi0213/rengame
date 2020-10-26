#pragma once

/// <summary>
/// イベントの名前とイベントNoのデータ
/// </summary>
class EventData
{
public:
	//名前と一致するイベント番号を返す（不一致なら-1）
	int SearchEventNo(const wchar_t* eventName);

private:

	//イベントの名前一覧
	const wchar_t* Event_Data[10]{
		L"Tutorial_1"	//チュートリアル…スイッチと箱
		L"Tutorial_2"	//チュートリアル…箱を投げる
		L"Tutorial_3"	//チュートリアル…ダブルスイッチ
	};

};

