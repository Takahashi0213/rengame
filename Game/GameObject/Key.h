#pragma once
#include "system/CGameObjectManager.h"
#include "GameObject/Player.h"

class Key : public ObjectClass
{
public:
	Key();
	~Key();
	void Update()override;
	void Render()override;

	//リンクオブジェクトの設定
	//基本的にレベルロード時に呼ぶ
	//一番最後に設定したオブジェクトのタグを参照して動作を決定する
	void SetLinkObj(ObjectClass* linkObj) {
		m_LinkPt[m_setNom] = linkObj;
		m_setNom++;
	}

private:

	SkinModelRender * m_skinModelRender = nullptr;
	
	//アイテムデータ
	const wchar_t* m_ModelName = nullptr;			//モデルの名前
	const int m_itemNo = -1;

	//リンクオブジェクト
	ObjectClass* m_LinkPt[10] = { nullptr };		//出現トリガー
	int m_setNom = 0;								//いまどこにいる？


};

