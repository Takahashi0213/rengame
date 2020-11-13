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

	//レベル読み込みます
	m_level.Init(LEVEL_Name, [&](LevelObjectData& objData) {
		
		//まずはオブジェクトNoを検索
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, objData.name);
		LevelData::Obj_Tag ObjectTag = Level_Data.GetObjectTag(m_levelNo, ObjNo);

		//生成
		NewObj(objData, ObjectTag);
		//以降のオブジェクト検索を高速にするために名前キーを作成しておく。
		const wchar_t* objName = Level_Data.GetObjectName(m_levelNo, ObjNo);
		int nameKey = Hash::MakeHash(objName);
		const wchar_t* linkObjeName = Level_Data.GetObject_LinkObj(m_levelNo, ObjNo);
		int linkObjNameKey = 0;// Hash::MakeHash(linkObjeName);
		//配列に登録
		m_Obj_Data[i] = Obj_Data{ 
			ObjectTag,
			objName,
			nameKey,
			linkObjeName,
			linkObjNameKey
		};

		//代入位置を1つ動かす
		i++;
		
		return true;
	});

	//リンクします
	LinkObj(m_levelNo,i);

}
template<class T> 
T* LevelSet::NewObjCommon(const LevelObjectData& data)
{
	T* pt = CGameObjectManager::GetInstance()->NewGO<T>(data.name, 0);
	pt->SetPosition(data.position*10.0f);
	pt->SetRotation(data.rotation);
	pt->SetScale(data.scale*10.0f);
	return pt;
}
void LevelSet::NewObj(LevelObjectData& data, const LevelData::Obj_Tag tag) {


	//ポインタの名前はptで統一
	if (tag == LevelData::Obj_Tag::Tag_Switch) {		//スイッチ
		NewObjCommon<Switch>(data);
	}

	if (tag == LevelData::Obj_Tag::Tag_Door) {			//ドア
		Door* pt = NewObjCommon<Door>(data);
		pt->GetSkinModelRender()->SetUp(pt->GetPosition(), pt->GetRotation(), pt->GetScale());
	}
	if (tag == LevelData::Obj_Tag::Tag_BigDoor1) {		//巨大ドア1
		BigDoor* pt = NewObjCommon<BigDoor>(data);
		pt->ModelChange(BigDoor::DoorModel::Model_BigDoor);
	}
	if (tag == LevelData::Obj_Tag::Tag_BigDoor2) {		//巨大ドア2
		BigDoor* pt = NewObjCommon<BigDoor>(data);
		pt->ModelChange(BigDoor::DoorModel::Model_BigDoor2);
	}

	if (tag == LevelData::Obj_Tag::Tag_Test_Enemy) {	//テストエネミー
		NewObjCommon<TestEnemy>(data);
	}
	if (tag == LevelData::Obj_Tag::Tag_Mannequin) {		//マネキン
		NewObjCommon<Mannequin>(data);
	}
	if (tag == LevelData::Obj_Tag::Tag_Benite) {		//ベニテー
		NewObjCommon<Benite>(data);
	}

	if (tag == LevelData::Obj_Tag::Tag_Jewel) {			//ジュエル
		NewObjCommon<StarMoney>(data);
	}
	if (tag == LevelData::Obj_Tag::Tag_Key1) {			//鍵
		Key* pt = NewObjCommon<Key>(data);
		pt->SetItemNo(Game::GetInstance()->GetItemSave()->GetItemData()->ItemNoSearch(L"草原の鍵"));
		pt->DataSet();
	}

	if (tag == LevelData::Obj_Tag::Tag_Board) {			//看板
		Board* pt = NewObjCommon<Board>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetBoardMessage(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
	}

	if (tag == LevelData::Obj_Tag::Tag_Torch) {			//松明
		Torch* pt = NewObjCommon<Torch>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetTorch(Level_Data.GetObject_BoolMemo(m_levelNo, ObjNo));
		pt->SetHosei(Level_Data.GetObject_Vector3Memo(m_levelNo, ObjNo));
	}

	if (tag == LevelData::Obj_Tag::Tag_GhostBox_MapMove) {	//ゴーストボックス…移動
		GhostBox* pt = NewObjCommon<GhostBox>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetStageName(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
		pt->SetPlayerMoveTarget(Level_Data.GetObject_Vector3Memo(m_levelNo, ObjNo));
		pt->SetYazirushiRot(Level_Data.GetObject_FloatMemo(m_levelNo, ObjNo));
		pt->SetYazirushiYHosei(Level_Data.GetObject_FloatMemo2(m_levelNo, ObjNo));
		pt->SetRotFlag(Level_Data.GetObject_BoolMemo(m_levelNo, ObjNo));
		pt->SetGhostBox_System(GhostBox::MapMove);
		pt->CreateGhost();
	}
	if (tag == LevelData::Obj_Tag::Tag_GhostBox_Event) {	//ゴーストボックス…イベント
		GhostBox* pt = NewObjCommon<GhostBox>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetStageName(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
		pt->SetGhostBox_System(GhostBox::MapEvent);
		pt->CreateGhost();
	}
	if (tag == LevelData::Obj_Tag::Tag_GhostBox_Damage) {	//ゴーストボックス…ダメージ
		GhostBox* pt = NewObjCommon<GhostBox>(data);
		pt->SetGhostBox_System(GhostBox::DamageZone);
		pt->CreateGhost();
	}
	if (tag == LevelData::Obj_Tag::Tag_StaticBox) {			//スタティックボックス
		StaticBox* pt = NewObjCommon<StaticBox>(data);
		pt->CreateStaticBox();
	}
	if (tag == LevelData::Obj_Tag::Tag_EventObject) {	//イベントオブジェクト
		EventObject* pt = NewObjCommon<EventObject>(data);
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, data.name);
		pt->SetEventName(Level_Data.GetObject_ObjMemo(m_levelNo, ObjNo));
	}

}

void LevelSet::LinkObj(const int levelNo, const int i) {

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

			//今見てるオブジェクト
			int now_hash = m_Obj_Data[ii].nameKey;
			ObjectClass* now_objClass;

			//ここで取得するオブジェクトは他のオブジェクトに「干渉する側」です
			ObjectClass* NowObj = CGameObjectManager::GetInstance()->FindGO<ObjectClass>(now_hash);
			now_objClass = NowObj->GetInstance();

			//ハッシュ値を作成
			int link_hash = Hash::MakeHash(linkObjName);

			//オブジェクトタグで分岐
			if (LinkObjTag == LevelData::Obj_Tag::Tag_Door) {			//ドア
				Door* obj = CGameObjectManager::GetInstance()->FindGO<Door>(link_hash);
				obj->SetLinkObj(now_objClass);
			}
			if (LinkObjTag == LevelData::Obj_Tag::Tag_EventObject) {	//イベントオブジェクト
				EventObject* obj = CGameObjectManager::GetInstance()->FindGO<EventObject>(link_hash);
				obj->SetLinkObj(now_objClass);
			}
			if (LinkObjTag == LevelData::Obj_Tag::Tag_Key1) {			//鍵
				Key* obj = CGameObjectManager::GetInstance()->FindGO<Key>(link_hash);
				obj->SetLinkObj(now_objClass);
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
			ObjectClass* go = CGameObjectManager::GetInstance()->FindGO<ObjectClass>(m_Obj_Data[i].nameKey);
			if (go != nullptr) {
				go->DeleteObject();
			}
		}
	}

}