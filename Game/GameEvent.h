#pragma once
#include "EventData.h"
#include "GameObject/Player.h"

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
		m_eventEndProgress = m_eventData.SearchEventEndProgress(EvNo);
		m_eventData.SetEventSaveFlag(EvNo);
		m_eventProgress = 0;
		m_nextEventConditions = LeftClick;	//�ꉞ������
	}

	void GameEventUpdate();

private:
	//�C�x���g�ꗗ
	void Event_Tutorial1();
	void Event_Tutorial2();
	void Event_Tutorial3();

	EventData m_eventData;			//�C�x���g�f�[�^

	//�p�ɂɌ�������I�u�W�F�N�g������Εۑ�
	Player* m_player = nullptr;		//�v���C���[

	int m_nowEventNo = -1;			//���s���̃C�x���g�ԍ�
	int m_eventProgress = -1;		//���s���̃C�x���g�i�s�x
	int m_eventEndProgress = -1;	//���s���̃C�x���g�I���i�s�x
	bool m_eventEndFlag = false;	//�C�x���g�I���t���O

	//�i�s�֘A
	enum NextEventConditions {
		LeftClick,		//���N���b�N���������Ɛi�s����
		TimeLimit,		//�w�肵�����ԂɂȂ�Ɛi�s����
	};
	NextEventConditions m_nextEventConditions = LeftClick;	//���݂̃C�x���g�i�s����
	int m_eventWaitTimer = 0;		//�C�x���g�i�s�^�C�}�[
	int m_eventWaitLimit = 0;		//�C�x���g�i�s���~�b�g
	bool m_eventWaitFlag = false;	//�C�x���g�̃N���b�Nor�^�C�����~�b�g�҂��t���O

};

