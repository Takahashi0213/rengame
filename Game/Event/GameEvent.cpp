#include "stdafx.h"
#include "GameEvent.h"


GameEvent::GameEvent()
{
	//�v���C���[�̌���
	m_player = CGameObjectManager::GetInstance()->FindGO<Player>(Hash::MakeHash("Player"), false);
}

GameEvent::~GameEvent()
{
}

void GameEvent::GameEventUpdate() {

	//�C�x���g���s
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

	//�i�s�҂�
	if (m_eventWaitFlag == true) {

		//���N���b�N
		if (m_nextEventConditions == LeftClick) {
			if (GameEffect::GetInstance()->GetInstance_Message()->GetMessageOkuriFlag() == true) {
				//����
				m_eventWaitFlag = false;
				m_eventProgress++;
			}
		}
		//�^�C�����~�b�g
		if (m_nextEventConditions == TimeLimit) {
			m_eventWaitTimer++;
			if (m_eventWaitTimer >= m_eventWaitLimit) {
				//����
				m_eventWaitTimer = 0;
				m_eventWaitFlag = false;
				m_eventProgress++;
			}
		}
	}

	//�I���`�F�b�N
	if (m_nowEventNo > -1 &&
		m_eventProgress >= m_eventEndProgress) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		m_eventEndFlag = true;
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

	if (m_eventProgress == 0) {
		GameEffect::GetInstance()->EasyEffect(L"���I�X�C�b�`�����I",
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 1) {
		GameEffect::GetInstance()->EasyEffect(L"�u�r�o�`�b�d�L�[�v��\n�W�����v����\n����Ă݂悤�I",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
	}
	m_eventWaitFlag = true;
}

void GameEvent::Event_Tutorial2() {

	if (m_eventProgress == 0) {
		GameEffect::GetInstance()->EasyEffect(L"���x�͓G�c��\n�}�l�L�����ˁI",
			GameEffect_Stand::Stand_Wow,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 1) {
		GameEffect::GetInstance()->EasyEffect(L"�����Ԃ���\n������悤�I",
			GameEffect_Stand::Stand_Ang,
			GameEffect_Stand::Jump_Stand);
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Hint.wav");
	}
	if (m_eventProgress == 2) {
		GameEffect::GetInstance()->EasyEffect(L"���ɋ߂Â��āu�b�L�[�v\n�Ŕ��������グ���I",
			GameEffect_Stand::Stand_Ang,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 3) {
		GameEffect::GetInstance()->EasyEffect(L"�}�l�L���ɃJ�[�\����\n�����āu�b�L�[�v��\n�����Ɣ��𓊂����I",
			GameEffect_Stand::Stand_Ang,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 4) {
		GameEffect::GetInstance()->EasyEffect(L"�߂������艓�������\n������Ȃ�����\n�C��t���悤�I",
			GameEffect_Stand::Stand_Ang,
			GameEffect_Stand::New_Stand);
	}

	m_eventWaitFlag = true;

}

void GameEvent::Event_Tutorial3() {

	if (m_eventProgress == 0) {
		GameEffect::GetInstance()->EasyEffect(L"�����J�����ˁI",
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 1) {	//�ړ�����
		GameEffect::GetInstance()->GetInstance_Message()->SetEventFlagAutoOff(true);
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag = true;	//�C�x���g���[��
		CVector3 target = m_player->GetPosition();
		target.x += 300.0f;
		m_player->SetMoveTarget(target);
		m_eventWaitLimit = 60;
		m_nextEventConditions = TimeLimit;
	}
	if (m_eventProgress == 2) {	//�ړ��I��
		CameraSupporter::GetInstance()->CameraBackup();
		SceneManager::GetInstance()->GetSystemInstance()->m_event_PlayerMoveFlag = false;	//�C�x���g���[��
		SceneManager::GetInstance()->GetSystemInstance()->m_event_CameraStop = true;
		m_eventWaitLimit = 1;
	}
	if (m_eventProgress == 3) {	//�J�����ړ�
		CameraSupporter::GetInstance()->CameraMove({ 0.0f,0.0f,400.0f }, 30, 0);
		CameraSupporter::GetInstance()->CameraTargetMove({ 0.0f,0.0f,400.0f }, 30, 0);
		m_eventWaitLimit = 60;
	}
	if (m_eventProgress == 4) {	//�J�����߂�
		CameraSupporter::GetInstance()->CameraBackup_Restore(30);
		m_eventWaitLimit = 40;
	}
	if (m_eventProgress == 5) {
		GameEffect::GetInstance()->GetInstance_Message()->SetEventFlagAutoOff(false);
		SceneManager::GetInstance()->GetSystemInstance()->m_event_CameraStop = false;
		m_nextEventConditions = LeftClick;
		GameEffect::GetInstance()->EasyEffect(L"����H�~�肽��\n�܂����Ⴄ�񂾁I�H",
			GameEffect_Stand::Stand_Wow,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 6) {
		GameEffect::GetInstance()->EasyEffect(L"�������I���̔\�͂�\n�������΁c",
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::Jump_Stand);
	}
	if (m_eventProgress == 7) {
		GameEffect::GetInstance()->EasyEffect(L"�����J�����܂܂�\n���Ă����邩���I",
			GameEffect_Stand::Stand_Happy,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 8) {
		GameEffect::GetInstance()->EasyEffect(L"�u���N���b�N�v��\n���������I",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
		SceneManager::GetInstance()->GetSoundManagerInstance()->InitSE(L"Assets/sound/SE/Hint.wav");
	}
	if (m_eventProgress == 9) {
		GameEffect::GetInstance()->EasyEffect(L"�X�C�b�`�̏��\n��������Ă݂悤�I",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
	}
	if (m_eventProgress == 10) {
		GameEffect::GetInstance()->EasyEffect(L"�����ԈႦ�Ă��A\n���j���[����u�S������v\n����Α��v�I",
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::New_Stand);
		GameData::GetInstance()->SetBoxMakerFlag(true);		//��������悤�ɂȂ�
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
	if (m_eventProgress == 2) {	//���X�|�[��
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