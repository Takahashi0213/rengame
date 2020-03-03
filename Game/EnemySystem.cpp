#include "stdafx.h"
#include "EnemySystem.h"

#include "BoxMaker.h"

bool EnemySystem::BoxAttackSearch(CVector3 position, float range) {

	bool Return_Flag = false;
	//�{�b�N�X���C�J�[
	BoxMaker* BoxMaker_p = BoxMaker::GetInstance();
	std::list<GameBox*> boxList = BoxMaker_p->GetBoxList();
	CVector3 MoveSpeed;
	CVector3 Vec;
	float Range;

	//�����锠������
	for (auto go : boxList) {

		//�ړ����̔��݂̂Ȃ̂Ŋm�F
		if (go->GetBoxTag() == GameBox::BoxTag::Origin) {
			MoveSpeed = go->GetMoveSpeed();
		}else if (go->GetBoxTag() == GameBox::BoxTag::Another) {
			MoveSpeed = go->GetOriginBox()->GetMoveSpeed();
		}
		//�ړ��ʃ`�F�[�[�[�b�N
		if (MoveSpeed.x == 0.0f && MoveSpeed.z == 0.0f) {
			//�����ĂȂ��̂ł����܂�
			continue;
		}

		//�ړ��ʌv�Z
		Vec = position - (go->GetPosition() + go->GetAnotherHosei());
		Range = Vec.Length();

		//���Ƃ̋�������
		if (Range < range + go->GetAnotherRangeHosei()) {
			//�ՓˈČ�
			Return_Flag = true;
			//�ړ����x�ύX
			MoveSpeed.x *= Gensui;
			MoveSpeed.z *= Gensui;
			MoveSpeed.x *= -1.0f;	//�Ђ�����Ԃ�
			MoveSpeed.z *= -1.0f;
			MoveSpeed.y = 2.0f;
			if (go->GetBoxTag() == GameBox::BoxTag::Origin) {
				go->SetMoveSpeed(MoveSpeed);
			}
			else if (go->GetBoxTag() == GameBox::BoxTag::Another) {
				go->GetOriginBox()->SetMoveSpeed(MoveSpeed);
			}
		}

	}

	return Return_Flag;
}
