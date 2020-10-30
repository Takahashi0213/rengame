#include "stdafx.h"
#include "GameEvent.h"


GameEvent::GameEvent()
{
}


GameEvent::~GameEvent()
{
}

void GameEvent::GameEventUpdate() {

	//�C�x���g���s
	if (m_nowEventNo == 0) {
		Event_Tutorial1();
	}

	//�C�x���g�I��
	if (m_eventEndFlag == true) {
		m_nowEventNo = -1;
		m_eventProgress = -1;
		m_eventEndProgress = -1;
		m_eventEndFlag = false;
	}

}

/// <summary>
/// ��������C�x���g���e
/// </summary>

void GameEvent::Event_Tutorial1() {

	if (m_eventWaitFlag == false) {

		if (m_eventProgress == 0) {
			GameEffect::GetInstance()->EasyEffect(L"�`���[�g���A��1",
				GameEffect_Stand::Stand_Normal,
				GameEffect_Stand::New_Stand);
		}
		if (m_eventProgress == 1) {
			GameEffect::GetInstance()->EasyEffect(L"�`���[�g���A��1��\n���̂͂Ȃ�",
				GameEffect_Stand::Stand_Normal,
				GameEffect_Stand::New_Stand);
		}
		m_eventWaitFlag = true;
	}
	else {
		//�N���b�N�҂�
		int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
		if (key == MouseSupporter::Release_Push) {
			//����
			m_eventWaitFlag = false;
			m_eventProgress++;
		}
	}

	//�I���`�F�b�N
	if (m_eventProgress >= m_eventEndProgress) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		m_eventEndFlag = true;
	}

}

void GameEvent::Event_Tutorial2() {

}

void GameEvent::Event_Tutorial3() {

}