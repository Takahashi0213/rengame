#include "stdafx.h"
#include "OP.h"


OP::OP()
{
	//����

}


OP::~OP()
{
}

void OP::OP_Update() {

	if (m_opEffectFlag == false) {

		if (m_opShinkou == 1) {
			//�g�����W�V����
			TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox, 0, true);

			GameEffect::GetInstance()->EasyEffect(L"�I�[�v�j���O��\n�e�X�g���b�Z�[�W",
				GameEffect_Stand::Stand_Normal,
				GameEffect_Stand::New_Stand);
		}
		if (m_opShinkou == 2) {
			GameEffect::GetInstance()->EasyEffect(L"�Q�[���n�܂��I",
				GameEffect_Stand::Stand_Happy,
				GameEffect_Stand::Jump_Stand);
		}
		m_opEffectFlag = true;
	}
	else {
		//�N���b�N�҂�
		if (m_opShinkou == 0) {
			m_opTimer++;
			if (m_opTimer > OP_TimerLimit) {
				//����
				m_opEffectFlag = false;
				m_opShinkou++;
				m_opTimer = 0;
			}
		}
		else {
			//���������ꂽ��c
			int key = MouseSupporter::GetInstance()->GetMouseKey(MouseSupporter::Left_Key);
			if (key == MouseSupporter::Release_Push) {
				//����
				m_opEffectFlag = false;
				m_opShinkou++;
			}
		}
	}

	//�I���`�F�b�N
	if (m_opShinkou >= EndShinkou) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		m_opEndFlag = true;
	}

}