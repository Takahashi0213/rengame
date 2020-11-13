#pragma once
#include "EventData.h"
#include "GameObject/Player.h"

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
	/// <param name="link_pt">リンクオブジェクトのポインタ配列</param>
	void EvemtStart(const wchar_t* eventName) {
		int EvNo = m_eventData.SearchEventNo(eventName);
		//起動済みのイベントなら強制終了
		if (m_eventData.GetEventSaveFlag(EvNo) == true) {
			return;
		}
		m_nowEventNo = EvNo;
		m_eventEndProgress = m_eventData.SearchEventEndProgress(EvNo);
		m_eventData.SetEventSaveFlag(EvNo);
		m_eventProgress = 0;
		m_nextEventConditions = LeftClick;	//一応初期化
	}
	void EvemtStart(const wchar_t* eventName, ObjectClass* link_pt[MAX_LINK_OBJECT]) {
		int EvNo = m_eventData.SearchEventNo(eventName);
		//起動済みのイベントなら強制終了
		if (m_eventData.GetEventSaveFlag(EvNo) == true) {
			return;
		}
		m_nowEventNo = EvNo;
		m_eventEndProgress = m_eventData.SearchEventEndProgress(EvNo);
		m_eventData.SetEventSaveFlag(EvNo);
		m_eventProgress = 0;
		m_nextEventConditions = LeftClick;	//一応初期化
		for (int i = 0; i < MAX_LINK_OBJECT; i++) {
			m_LinkPt[i] = link_pt[i];
		}
	}

	void GameEventUpdate();

	/// <summary>
	/// イベントセーブを返す
	/// </summary>
	EventSave* GetEventSave() {
		return m_eventData.GetEventSave();
	}

private:
	//イベント一覧
	void Event_Tutorial1();
	void Event_Tutorial2();
	void Event_Tutorial3();
	void Event_Sougen_Key();

	EventData m_eventData;			//イベントデータ

	//頻繁に検索するオブジェクトがあれば保存
	Player* m_player = nullptr;		//プレイヤー

	int m_nowEventNo = -1;			//実行中のイベント番号
	int m_eventProgress = -1;		//実行中のイベント進行度
	int m_eventEndProgress = -1;	//実行中のイベント終了進行度
	bool m_eventEndFlag = false;	//イベント終了フラグ

	//進行関連
	enum NextEventConditions {
		LeftClick,		//左クリックを押されると進行する
		TimeLimit,		//指定した時間になると進行する
	};
	NextEventConditions m_nextEventConditions = LeftClick;	//現在のイベント進行条件
	int m_eventWaitTimer = 0;								//イベント進行タイマー
	int m_eventWaitLimit = 0;								//イベント進行リミット
	bool m_eventWaitFlag = false;							//イベントのクリックorタイムリミット待ちフラグ
	ObjectClass* m_LinkPt[MAX_LINK_OBJECT] = { nullptr };	//関連オブジェクト
	float m_eventMemo = 0.0f;								//イベント用メモ

};

