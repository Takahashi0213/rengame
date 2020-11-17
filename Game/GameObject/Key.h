#pragma once
#include "system/CGameObjectManager.h"
#include "GameObject/Player.h"
#include "GameObject/ItemSystem.h"

class Key : public ItemSystem
{
public:
	Key();
	~Key();
	void DataSet();
	void Update()override;
	void Render()override;

	//設定用（レベル生成時に同時に呼ぶのが基本）
	void SetItemNo(const int& itemNo) {
		m_itemNo = itemNo;
	}

	//リンクオブジェクトの設定
	//基本的にレベルロード時に呼ぶ
	//一番最後に設定したオブジェクトのタグを参照して動作を決定する
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_setNom++;
	}

private:

	//アクションフラグの変更
	//毎フレーム呼ばれて、どうするべきか判断する
	void UpdateActionFlag() {

		//アクション済みなら終わり
		if (m_actionFlag == true) {
			return;
		}

		bool CheckFlag = true;		//通過確認

		for (int i = 0; i < 10; i++) {
			if (m_LinkPt[i] != nullptr && m_LinkPt[i]->m_actionFlag == false) {
				CheckFlag = false;
			}
		}
		m_actionFlag = CheckFlag;	//trueのままならｵｹ
	}

	void KeySpawn();				//鍵出現演出

	//演出用フラグ
	bool m_setFlag = false;
	bool m_moveFlag = false;
	bool m_drawFlag = false;
	bool m_spawnFlag = false;
	//定数
	const float DefScale = 5.0f;					//拡大率
	const float AutoRotation = 5.0f;				//自動回転量
	const float DownHosei = 450.0f;					//未取得時、地面に埋まる量
	const float UpMove = 560.0f;					//出現時、上に移動する量
	const float UpMove_Bound = 100.0f;				//出現時、下にバウンドする量
	const int UpTime = 20;							//出現演出時間
	const float GetRange = 150.0f;					//取得できる範囲

	//リンクオブジェクト
	ObjectClass* m_LinkPt[MAX_LINK_OBJECT] = { nullptr };		//出現トリガー
	int m_setNom = 0;											//いまどこにいる？

};

