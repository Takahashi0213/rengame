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
	m_levelNo = -1;		//初期化
	//全部初期化
	for (int j = 0; j < MAX_LEVEL_OBJ; j++) {
		m_Obj_Data[j] = {};
	}

	//どのレベルかチェックするためのループ
	for (int j = 0; j < Size; j++) {
		//一致する場合そいつに決定する
		if ( wcscmp(Level_Data.GetLevelName(j), LEVEL_Name) == 0) {
			m_levelNo = j;	//お前しか…いない！
			break;
		}
	}
	//エラーチェック
	if (m_levelNo == -1) {
		//どれにも引っかかっていないためエラー
		std::abort();
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
		
		return true;
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

	if (tag == LevelData::Obj_Tag::Tag_Board) {	//看板
		Board* pt = CGameObjectManager::GetInstance()->NewGO<Board>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetBoardMessage(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
	}

	if (tag == LevelData::Obj_Tag::Tag_GhostBox_MapMove) {	//ゴーストボックス…移動
		//const wchar_t* hoge = Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo);	//テストメッセージ
		GhostBox* pt = CGameObjectManager::GetInstance()->NewGO<GhostBox>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
		pt->CreateGhost();
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetStageName(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
		pt->SetPlayerMoveTarget(Level_Data.GetObject_Vector3Memo(m_levelNo, ObjNo));
	}
	if (tag == LevelData::Obj_Tag::Tag_StaticBox) {	//スタティックボックス
		StaticBox* pt = CGameObjectManager::GetInstance()->NewGO<StaticBox>(data.name, 0);
		pt->SetPosition(data.position*10.0f);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale*10.0f);
		pt->CreateStaticBox();
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

				//ここに追加するオブジェクトは他のオブジェクトに「干渉する側」です
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

void LevelSet::LevelDelete() {

	//全部検索アンド削除である！
	for (int i = 0; i < MAX_LEVEL_OBJ; i++) {
		if (wcscmp(m_Obj_Data[i].ObjName, L"") == 0) {
			//名前がない！強制終了
			break;
		}
		else {
			//検索して消す
			LevelData::Obj_Tag tag = m_Obj_Data[i].ObjTag;
			//削除作業
			if (tag == LevelData::Obj_Tag::Tag_Switch) {
				Switch* pt = CGameObjectManager::GetInstance()->FindGO<Switch>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_Door) {
				Door* pt = CGameObjectManager::GetInstance()->FindGO<Door>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_Test_Enemy) {
				TestEnemy* pt = CGameObjectManager::GetInstance()->FindGO<TestEnemy>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_Jewel) {
				StarMoney* pt = CGameObjectManager::GetInstance()->FindGO<StarMoney>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_Board) {
				Board* pt = CGameObjectManager::GetInstance()->FindGO<Board>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_GhostBox_MapMove) {
				GhostBox* pt = CGameObjectManager::GetInstance()->FindGO<GhostBox>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}
			if (tag == LevelData::Obj_Tag::Tag_StaticBox) {
				StaticBox* pt = CGameObjectManager::GetInstance()->FindGO<StaticBox>(Hash::MakeHash(m_Obj_Data[i].ObjName));
				CGameObjectManager::GetInstance()->DeleteGO(pt);
			}


		}
	}

}