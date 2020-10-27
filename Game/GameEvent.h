#pragma once
#include "EventData.h"

/// <summary>
/// EventStart���Ăяo�����ƂŃC�x���g���J�n�ł���
/// Game�N���X���ێ�
/// </summary>
class GameEvent
{
public:
	GameEvent();
	~GameEvent();

	/// <summary>
	/// �C�x���g�̎��s
	/// </summary>
	/// <param name="eventName">�C�x���g�̖��O</param>
	void EvemtStart(const wchar_t* eventName) {
		int EvNo = m_eventData.SearchEventNo(eventName);
		//�N���ς݂̃C�x���g�Ȃ狭���I��
		if (m_eventData.GetEventSaveFlag(EvNo) == true) {
			return;
		}
		m_nowEventNo = EvNo;
		m_eventProgress = -1;
	}

	void GameEventUpdate();

private:
	/// <summary>
	//�C�x���g�ꗗ
	void Event_Tutorial1();

	EventData m_eventData;			//�C�x���g�f�[�^

	int m_nowEventNo = -1;			//���s���̃C�x���g�ԍ�
	int m_eventProgress = -1;		//���s���̃C�x���g�i�s�x
	bool m_eventWaitFlag = false;	//�C�x���g�̃N���b�N�҂��t���O

};

