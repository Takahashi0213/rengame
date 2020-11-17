#include "stdafx.h"
#include "EventObject.h"


EventObject::EventObject()
{
}


EventObject::~EventObject()
{
}

void EventObject::Update() {
	
	//�C�x���g���Ȃ狭���I��
	if (SceneManager::GetInstance()->GetSystemInstance()->m_eventNowFlag == true) {
		return;
	}
	//�A�N�V�������[�h�łȂ��Ȃ狭���I��
	if (SceneManager::GetInstance()->GetGameMode() != SceneManager::ActionMode) {
		return;
	}

	//�t���O�̍X�V
	UpdateActionFlag();

	//�����C�x���g���s�\�Ȃ���s���āA�����͏��ł���
	if (m_actionFlag == true) {

		//�C�x���g�̎��s
		SceneManager::GetInstance()->GetGameEvent()->EvemtStart(m_eventName, m_LinkPt);

		//�폜�����
		DeleteGO(this);

	}
}

void EventObject::Render() {

}