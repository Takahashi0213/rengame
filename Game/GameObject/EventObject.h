#pragma once
#include "system/CGameObjectManager.h"

/// <summary>
/// イベントオブジェクト
/// 条件を満たしたら起動するイベント
/// </summary>
class EventObject : public ObjectClass
{
public:
	EventObject();
	~EventObject();
	void Update()override;
	void Render()override;

	//リンクオブジェクトの設定
	//基本的にレベルロード時に呼ぶ
	//一番最後に設定したオブジェクトのタグを参照して動作を決定する
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_setNom++;
	}

	//設定用（レベル生成時に同時に呼ぶのが基本）
	void SetEventName(const wchar_t* eventName) {
		m_eventName = eventName;
	}

private:
	//アクションフラグの変更
	//扉と違って問答無用で実行される、実行後このオブジェクトは削除される
	void UpdateActionFlag() {

		bool CheckFlag = true;		//通過確認

		for (int i = 0; i < 10; i++) {
			if (m_LinkPt[i] != nullptr && m_LinkPt[i]->m_actionFlag == false) {
				CheckFlag = false;
			}
		}
		m_actionFlag = CheckFlag;	//trueのままならｵｹ
	}

	const wchar_t* m_eventName = nullptr;			//イベントの名前

	ObjectClass* m_LinkPt[MAX_LINK_OBJECT] = { nullptr };		//イベントトリガー
	int m_setNom = 0;											//イベントトリガー参照位置

};

