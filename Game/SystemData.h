#pragma once

/// <summary>
/// システム関連の変数色々
/// </summary>
class SystemData {
public:

	//システム
	bool m_eventNowFlag = false;		//イベント中（会話など）
	bool m_event_PlayerMoveFlag = false;//イベント中でもプレイヤーを動かせるフラグ
	bool m_event_CameraStop = false;	//カメラの移動を停止
	bool m_menuStopFlag = false;		//メニューの操作フラグ	


};