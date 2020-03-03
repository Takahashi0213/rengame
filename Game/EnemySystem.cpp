#include "stdafx.h"
#include "EnemySystem.h"

#include "BoxMaker.h"

bool EnemySystem::BoxAttackSearch(CVector3 position, float range) {

	bool Return_Flag = false;
	//ボックスメイカー
	BoxMaker* BoxMaker_p = BoxMaker::GetInstance();
	std::list<GameBox*> boxList = BoxMaker_p->GetBoxList();
	CVector3 MoveSpeed;
	CVector3 Vec;
	float Range;

	//あらゆる箱を検索
	for (auto go : boxList) {

		//移動中の箱のみなので確認
		if (go->GetBoxTag() == GameBox::BoxTag::Origin) {
			MoveSpeed = go->GetMoveSpeed();
		}else if (go->GetBoxTag() == GameBox::BoxTag::Another) {
			MoveSpeed = go->GetOriginBox()->GetMoveSpeed();
		}
		//移動量チェーーーック
		if (MoveSpeed.x == 0.0f && MoveSpeed.z == 0.0f) {
			//動いてないのでおしまひ
			continue;
		}

		//移動量計算
		Vec = position - (go->GetPosition() + go->GetAnotherHosei());
		Range = Vec.Length();

		//箱との距離判定
		if (Range < range + go->GetAnotherRangeHosei()) {
			//衝突案件
			Return_Flag = true;
			//移動速度変更
			MoveSpeed.x *= Gensui;
			MoveSpeed.z *= Gensui;
			MoveSpeed.x *= -1.0f;	//ひっくり返す
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
