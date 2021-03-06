#include "stdafx.h"
#include "OP.h"


OP::OP()
{
	//準備

}


OP::~OP()
{
}

void OP::OP_Update() {

	if (m_opEffectFlag == false) {

		if (m_opShinkou == 1) {
			//トランジション
			TransitionGenerator::GetInstance()->TransitionInit(TransitionGenerator::TransitionName::NanameBox, 0, true);

			GameEffect::GetInstance()->EasyEffect(L"オープニングの\nテストメッセージ",
				GameEffect_Stand::Stand_Normal,
				GameEffect_Stand::New_Stand);
		}
		if (m_opShinkou == 2) {
			GameEffect::GetInstance()->EasyEffect(L"ゲーム始まるよ！",
				GameEffect_Stand::Stand_Happy,
				GameEffect_Stand::Jump_Stand);
		}
		m_opEffectFlag = true;
	}
	else {
		//クリック待ち
		if (m_opShinkou == 0) {
			m_opTimer++;
			if (m_opTimer > OP_TimerLimit) {
				//次へ
				m_opEffectFlag = false;
				m_opShinkou++;
				m_opTimer = 0;
			}
		}
		else {
			//左が押されたら…
			if (GameEffect::GetInstance()->GetInstance_Message()->GetMessageOkuriFlag() == true) {
				//次へ
				m_opEffectFlag = false;
				m_opShinkou++;
			}
		}
	}

	//終了チェック
	if (m_opShinkou >= EndShinkou) {
		GameEffect::GetInstance()->GetInstance_Stand()->StandControl(
			GameEffect_Stand::Stand_Normal,
			GameEffect_Stand::Delete_Stand);
		m_opEndFlag = true;
	}

}