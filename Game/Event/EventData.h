#pragma once
#include "EventSave.h"

/// <summary>
/// �C�x���g�̖��O�ƃC�x���gNo�̃f�[�^
/// </summary>
class EventData
{
public:
	//���O�ƈ�v����C�x���g�ԍ���Ԃ��i�s��v�Ȃ�-1�j
	int SearchEventNo(const wchar_t* eventName);
	//�C�x���g�ԍ��ƈ�v����ŏI����ԍ���Ԃ��i�s��v�Ȃ�-1�j
	int SearchEventEndProgress(const int& evNo) {
		return Event_Data[evNo].EventEndProgress;
	}
	/// <summary>
	/// �C�x���g�̋N���t���O���擾
	/// </summary>
	/// <param name="evNo">�C�x���g�ԍ�</param>
	/// <returns>�N���ς݂Ȃ�true��Ԃ�</returns>
	bool GetEventSaveFlag(const int& evNo) {
		return m_eventSave.m_eventFlag[evNo];
	}
	//�C�x���g�����s�ς݂ɂ���
	void SetEventSaveFlag(const int& evNo) {
		m_eventSave.m_eventFlag[evNo] = true;
	}

	/// <summary>
	/// �C�x���g�Z�[�u��Ԃ�
	/// </summary>
	EventSave* GetEventSave() {
		return &m_eventSave;
	}

private:

	EventSave m_eventSave;		//�C�x���g�Z�[�u

	//�C�x���g�f�[�^�\����
	struct EventData_Struct
	{
		const wchar_t* EventName;			//�����p�̖��O
		const int EventEndProgress = -1;	//�C�x���g���I�������b�ԍ�
	};

	//�C�x���g�ꗗ
	const EventData_Struct Event_Data[MAX_EVENT_OBJ]{
		{ L"Tutorial_1"	,	2	},	//�`���[�g���A���c�X�C�b�`
		{ L"Tutorial_2"	,	5	},	//�`���[�g���A���c���𓊂���
		{ L"Tutorial_3"	,	11	},	//�`���[�g���A���c���̐���
		{ L"Sougen_Key"	,	4	},	//�������̏o��
	};

};
