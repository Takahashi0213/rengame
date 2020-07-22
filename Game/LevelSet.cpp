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

	//レベル読み込みますますますの
	m_level.Init(LEVEL_Name, [&](LevelObjectData& objData) {
		
		//まずはオブジェクトNoを検索
		int ObjNo = Level_Data.ObjName_Search(m_levelNo, objData.name);
		LevelData::Obj_Tag ObjectTag = Level_Data.GetObjectTag(m_levelNo, ObjNo);

		//生成
		NewObj(objData, ObjectTag);
		//配列に登録（強引にキャストしてるけど大丈夫かは謎です）
		m_Obj_Data[i] = Obj_Data{ 
			ObjectTag,
			(wchar_t)Level_Data.GetObjectName(m_levelNo, ObjNo),
			(wchar_t)Level_Data.GetObject_LinkObj(m_levelNo, ObjNo) };

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
		auto* pt = CGameObjectManager::GetInstance()->NewGO<Switch>((const char*)data.name, 0);
		pt->SetPosition(data.position);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale);
	}

	if (tag == LevelData::Obj_Tag::Tag_Door) {	//ドア
		auto* pt = CGameObjectManager::GetInstance()->NewGO<Door>((const char*)data.name, 0);
		pt->SetPosition(data.position);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale);
	}

	if (tag == LevelData::Obj_Tag::Tag_Test_Enemy) {	//テストエネミー
		auto* pt = CGameObjectManager::GetInstance()->NewGO<TestEnemy>((const char*)data.name, 0);
		pt->SetPosition(data.position);
		pt->SetRotation(data.rotation);
		pt->SetScale(data.scale);
	}

}

void LevelSet::LinkObj(int levelNo, int i) {

	//オブジェクト配列の要素数分ループする
	for (int ii = 0; ii < i; ii++) {

		//おなまえは
		const wchar_t* linkObjName = m_Obj_Data[i].LinkObjName;

		//リンクオブジェクトがないならスキップ
		if (linkObjName == L"") {
			break;
		}

		//※リンクオブジェクトを探して追加する
		int ObjNo = Level_Data.ObjName_Search(levelNo, linkObjName);
		int hoge=0;

	}

}