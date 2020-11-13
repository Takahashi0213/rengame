#include "stdafx.h"
#include "GameEvent.h"


GameEvent::GameEvent()
{
	//プレイヤーの検索
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}

GameEvent::~GameEvent()
{
}

void GameEvent::GameEventUpdate() {

	//イベント実行
	if (m_eventWaitFlag == false) {
		if (m_nowEventNo == 0) {
			Event_Tutorial1();
		}
		if (m_nowEventNo == 1) {
			Event_Tutorial2();
		}
		if (m_nowEventNo == 2) {
			Event_Tutorial3();
		}
		if (m_nowEventNo == 3) {
			Event_Sougen_Key();
		}
	}

	//進行待ち
	if (m_eventWaitFlag == true) {

		//左クリック
		if (m_nextEventConditions == LeftClick) {
			if (GameEffect::GetInstance()->GetInstance_Message()->GetMessageOkuriFlag() == true) {
				//次へ
				m_eventWaitFlag = false;
				m_eventProgress++;
			}
		}
		//タイムリミット
		if (m_nextEventConditions == TimeLimit) {
			m_eventWaitTimer++;
			if (m_eventWaitTimer >= m_eventWaitLimit) {
				//次へ
				m_eventWaitTimer = 0;
				m_eventWaitFlag = false;
				m_eventProgress++;
			}
		}
	}

	//終了チェック
	if (m_nowEventNo > -1 &&
		m_eventProgress >= m_eventEndProgress) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		m_eventEndFlag = true;
	}
	//イベント終了
	if (m_eventEndFlag == true) {
		m_nowEventNo = -1;
		m_eventProgress = -1;
		m_eventEndProgress = -1;
		m_eventEndFlag = false;
	}

}

/// <summary>
/// ここからイベント内容
/// </summary>

void GameEvent::Event_Tutorial1() {

	if (m_eventProgress == 0) {
		GameEffect::GetInstance()->EasyEffect(L"あ！スイッチ発見！",
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 1) {
		GameEffect::GetInstance()->EasyEffect(L"「ＳＰＡＣＥキー」で\nジャンプして\n乗ってみよう！",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
	}
	m_eventWaitFlag = true;
}

void GameEvent::Event_Tutorial2() {

	if (m_eventProgress == 0) {
		GameEffect::GetInstance()->EasyEffect(L"今度は敵…の\nマネキンだね！",
			GameEffect_Stand::Stand_Wow,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 1) {
		GameEffect::GetInstance()->EasyEffect(L"箱をぶつけて\nやっつけよう！",
			GameEffect_Stand::Stand_Ang,
			GameEffect_Stand::Jump_Stand);
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Hint.wav");
	}
	if (m_eventProgress == 2) {
		GameEffect::GetInstance()->EasyEffect(L"箱に近づいて「Ｃキー」\nで箱を持ち上げるよ！",
			GameEffect_Stand::Stand_Ang,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 3) {
		GameEffect::GetInstance()->EasyEffect(L"マネキンにカーソルを\n向けて「Ｃキー」を\n押すと箱を投げるよ！",
			GameEffect_Stand::Stand_Ang,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 4) {
		GameEffect::GetInstance()->EasyEffect(L"近すぎたり遠すぎると\n当たらないから\n気を付けよう！",
			GameEffect_Stand::Stand_Ang,
			GameEffect_Stand::New_Stand);
	}

	m_eventWaitFlag = true;

}

void GameEvent::Event_Tutorial3() {

	if (m_eventProgress == 0) {
		GameEffect::GetInstance()->EasyEffect(L"扉が開いたね！",
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 1) {	//移動する
		GameEffect::GetInstance()->GetInstance_Message()->SetEventFlagAutoOff(true);
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag = true;	//イベントムーヴ
		CVector3 target = m_player->GetPosition();
		target.x += 300.0f;
		m_player->SetMoveTarget(target);
		m_eventWaitLimit = 60;
		m_nextEventConditions = TimeLimit;
	}
	if (m_eventProgress == 2) {	//移動終了
		CameraSupporter::GetInstance()->CameraBackup();
		SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag = false;	//イベントムーヴ
		SceneManager::GetInstance()->GetSystemInstance()->m_event_CameraStop = true;
		m_eventWaitLimit = 1;
	}
	if (m_eventProgress == 3) {	//カメラ移動
		CameraSupporter::GetInstance()->CameraMove({ 0.0f,0.0f,400.0f }, 30, 0);
		CameraSupporter::GetInstance()->CameraTargetMove({ 0.0f,0.0f,400.0f }, 30, 0);
		m_eventWaitLimit = 60;
	}
	if (m_eventProgress == 4) {	//カメラ戻す
		CameraSupporter::GetInstance()->CameraBackup_Restore(30);
		m_eventWaitLimit = 40;
	}
	if (m_eventProgress == 5) {
		GameEffect::GetInstance()->GetInstance_Message()->SetEventFlagAutoOff(false);
		SceneManager::GetInstance()->GetSystemInstance()->m_event_CameraStop = false;
		m_nextEventConditions = LeftClick;
		GameEffect::GetInstance()->EasyEffect(L"あれ？降りたら\n閉まっちゃうんだ！？",
			GameEffect_Stand::Stand_Wow,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 6) {
		GameEffect::GetInstance()->EasyEffect(L"そうだ！私の能力で\n箱を作れば…",
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::Jump_Stand);
	}
	if (m_eventProgress == 7) {
		GameEffect::GetInstance()->EasyEffect(L"扉を開けたままに\nしておけるかも！",
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 8) {
		GameEffect::GetInstance()->EasyEffect(L"「中クリック」で\n箱を作れるよ！",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Hint.wav");
	}
	if (m_eventProgress == 9) {
		GameEffect::GetInstance()->EasyEffect(L"スイッチの上に\n箱を作ってみよう！",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 10) {
		GameEffect::GetInstance()->EasyEffect(L"もし間違えても、\nメニューから「全箱解放」\nすれば大丈夫！",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
		GameData::GetInstance()->SetBoxMakerFlag(true);		//箱が作れるようになる
	}

	m_eventWaitFlag = true;

}

void GameEvent::Event_Sougen_Key() {

	if (m_eventProgress == 0) {
		SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = true;
		CameraSupporter::GetInstance()->CameraBackup();
		m_eventWaitLimit = 10;
		m_nextEventConditions = TimeLimit;
	}
	if (m_eventProgress == 1) {
		SceneManager::GetInstance()->GetSystemInstance()->m_event_CameraStop = true;
		CVector3 pos = m_LinkPt[0]->m_position;
		pos.x -= 50.0f;
		pos.z -= 100.0f;
		pos.y += 600.0f;
		CameraSupporter::GetInstance()->CameraTargetMove(pos - g_camera3D.GetTarget(), 30, 0);
		pos.z -= 300.0f;
		pos.y += 150.0f;
		CameraSupporter::GetInstance()->CameraMove(pos - g_camera3D.GetPosition(), 30, 0);
		CameraSupporter::GetInstance()->CameraMove_Zoom(60.0f, 30, 0);

		m_eventWaitLimit = 40;
	}
	if (m_eventProgress == 2) {	//鍵スポーン
		m_LinkPt[0]->m_actionFlag_2 = true;
		m_eventWaitLimit = 40;
	}
	if (m_eventProgress == 3) {
		SceneManager::GetInstance()->GetSystemInstance()->m_event_CameraStop = false;
		SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag = false;
		m_eventWaitLimit = 1;
	}
	m_eventWaitFlag = true;

}