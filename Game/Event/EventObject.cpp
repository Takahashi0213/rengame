#include "stdafx.h"
#include "EventObject.h"


EventObject::EventObject()
{
}


EventObject::~EventObject()
{
}

void EventObject::Update() {

	UpdateActionFlag();

	//�����C�x���g���s�\�Ȃ���s���āA�����͏��ł���
	if (m_actionFlag == true) {

		//�C�x���g�̎��s
		Game::GetInstance()->GetGameEvent()->EvemtStart(m_eventName);

		//�폜�����
		DeleteGO(this);

	}
}

void EventObject::Render() {

}