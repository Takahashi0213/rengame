#include "stdafx.h"
#include "LevelSet.h"

//まとめて
#include "IncludeHeader.h"

LevelSet* LevelSet::m_instance = nullptr;

LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

LevelSet::~LevelSet()
{	
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

void LevelSet::Init(const wchar_t* LEVEL_Name) {

	//レベルの要素数を取得（レベル自体がいくつ存在するか）
	int Size = Level_Data.GetLevelDataSize();
	int i = 0;	//配列セット用

	//どのレベルかチェックするためのループ
	for (int i = 0; i < Size; i++) {
		//一致する場合そいつに決定する
		if ( wcscmp(Level_Data.GetLevelName(i), LEVEL_Name) == 0) {
			m_levelNo = i;	//お前しか…いない！
			break;
		}
	}

	//レベルNoを渡す
	GameData::GetInstance()->SetNowMapLevel(m_levelNo);

	//レベル読み込みますますますの
	m_level.Init(LEVEL_Name, [&](LevelObjectData& objData) {
		
		//まずはオブジェクトNoを検索
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, objData.name);
		LevelData::Obj_Tag ObjectTag = Level_Data.GetObjectTag(m_levelNo, ObjNo);

		//生成
		NewObj(objData, ObjectTag);
		//配列に登録
		m_Obj_Data[i] = Obj_Data{ 
			ObjectTag,
			Level_Data.GetObjectName(m_levelNo, ObjNo),
			Level_Data.GetObject_LinkObj(m_levelNo, ObjNo) };

		//代入位置を1つ動かす
		i++;

		return false;
	});

	//リンクします
	LinkObj(m_levelNo,i);

}

void LevelSet::NewObj(LevelObjectData& data, LevelData::Obj_Tag tag) {

	//ポインタの名前はptで統一
	if (tag == LevelData::Obj_Tag::Tag_Switch) {	//スイッチ
		Switch* pt = CGameObjectManager::GetInstance()->NewGO<Switch>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
	}

	if (tag == LevelData::Obj_Tag::Tag_Door) {	//ドア
		Door* pt = CGameObjectManager::GetInstance()->NewGO<Door>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
		pt->GetSkinModelRender()->SetUp(pt->GetPosition(), pt->GetRotation(), pt->GetScale());
	}

	if (tag == LevelData::Obj_Tag::Tag_Test_Enemy) {	//テストエネミー
		TestEnemy* pt = CGameObjectManager::GetInstance()->NewGO<TestEnemy>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
	}

	if (tag == LevelData::Obj_Tag::Tag_Jewel) {	//ジュエル
		StarMoney* pt = CGameObjectManager::GetInstance()->NewGO<StarMoney>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
	}
}

void LevelSet::LinkObj(int levelNo, int i) {

	//オブジェクト配列の要素数分ループする
	for (int ii = 0; ii < i; ii++) {

		//おなまえは
		const wchar_t* nowObjName = m_Obj_Data[ii].ObjName;
		const wchar_t* linkObjName = m_Obj_Data[ii].LinkObjName;
		LevelData::Obj_Tag NowObjTag = m_Obj_Data[ii].ObjTag;

		//リンクオブジェクトがないならスキップ
		if (wcscmp(linkObjName, L"") != 0) {

			//※リンクオブジェクトを探して追加する
			int ObjNo = Level_Data.ObjName_Search(levelNo, linkObjName);
			LevelData::Obj_Tag LinkObjTag = Level_Data.GetObjectTag(levelNo, ObjNo);

			//オブジェクトタグで分岐
			if (LinkObjTag == LevelData::Obj_Tag::Tag_Door) {	//ドア

				//今見てるオブジェクト
				int now_hash = Hash::MakeHash(nowObjName);
				ObjectClass* now_objClass;
				if (NowObjTag == LevelData::Obj_Tag::Tag_Switch) {
					Switch* NowObj = CGameObjectManager::GetInstance()->FindGO<Switch>(now_hash);
					now_objClass = NowObj->GetInstance();
				}
				if (NowObjTag == LevelData::Obj_Tag::Tag_Test_Enemy) {
					TestEnemy* NowObj = CGameObjectManager::GetInstance()->FindGO<TestEnemy>(now_hash);
					now_objClass = NowObj->GetInstance();
				}

				//リンクオブジェクト
				int link_hash = Hash::MakeHash(linkObjName);
				Door* door = CGameObjectManager::GetInstance()->FindGO<Door>(link_hash);
				//ObjectClass* link_objClass = door->GetInstance();
				door->SetLinkObj(now_objClass);
			}

		}

	}

}