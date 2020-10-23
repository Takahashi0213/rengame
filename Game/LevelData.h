#pragma once
#include <map>
#include"IncludeHeader.h"

class LevelData
{
public:

	//この名前ならこのオブジェクトを作ります的なデータ
	//std::map < std::string, std::string > Level_Map =
	//{ 
	//	{"Switch" , "Switch" }
	//};

	//オブジェクトの種類
	enum Obj_Tag {
		Tag_NULL,					//ダミーデータ
		Tag_Switch,					//スイッチ 対応したドアなどのギミックをLinkObjに設定する
		Tag_Door,					//ドア スイッチから信号を受け取った場合移動する
		Tag_BigDoor1,				//巨大ドア（向かって左側）
		Tag_BigDoor2,				//巨大ドア（向かって右側）
		Tag_Test_Enemy,				//テストエネミー 水でできた鳩
		Tag_Jewel,					//スタージュエル
		Tag_Board,					//看板→Obj_Memoに内容を書く
		Tag_GhostBox_MapMove,		//マップ移動用ゴースト→obj_Memoに接触時呼ばれるマップの名前を書く
		Tag_GhostBox_Event,			//イベント用ゴースト→obj_Memoに接触時呼ばれるイベントの名前を書く
		Tag_StaticBox,				//壁
		Tag_Key1,					//鍵1
	};

	//レベルごとにこいつがオブジェクトの数だけ必要
	struct Obj_Data
	{
		wchar_t Obj_Name[MAX_PATH];			//レベル内のオブジェクト名
		Obj_Tag Tag;						//種類を選択
		wchar_t LinkObj_Name[MAX_PATH];		//関連するオブジェクトの名前
		wchar_t Obj_Memo[MAX_PATH];			//看板とかのテキスト
		CVector3 Position_Memo;				//移動先などの設定用
		bool BoolMemo = false;				//bool型のメモ
		float FloatMemo = 0.0f;				//float型のメモ
		float FloatMemo2 = 0.0f;			//float型のメモ
	};
	//レベルデータ構造体
	struct Level_Data
	{
		wchar_t Level_Name[MAX_PATH];		//レベルのファイル名
		Obj_Data Obj_Array[MAX_LEVEL_OBJ];	//このレベルのオブジェクトたち
	};

	//ここからデータ取得用関数

	/// <summary>
	/// レベルのファイル名取得
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <returns>ファイル名</returns>
	const wchar_t* GetLevelName(const int num) {
		return m_levelData[num].Level_Name;
	}

	/// <summary>
	/// オブジェクトの名前取得
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <param name="obj_num">オブジェクト番号</param>
	/// <returns>オブジェクトの名前</returns>
	const wchar_t* GetObjectName(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Obj_Name;
	}

	/// <summary>
	/// オブジェクトのタグ取得
	/// </summary>
	/// <returns>オブジェクトキー</returns>	
	Obj_Tag GetObjectTag(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Tag;
	}

	/// <summary>
	/// オブジェクトのリンクオブジェクトの名前を取得
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <returns>obj_numから設定されているリンク先オブジェクトの名前</returns>	
	const wchar_t* GetObject_LinkObj(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].LinkObj_Name;
	}

	/// <summary>
	/// オブジェクトメモを取得
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <param name="obj_num">オブジェクト番号</param>
	/// <returns></returns>
	const wchar_t* GetObject_ObjMemo(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Obj_Memo;
	}

	/// <summary>
	/// Vector3メモを取得
	/// マップ移動時のプレイヤー移動先座標など
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <param name="obj_num">オブジェクト番号</param>
	/// <returns>Vector3メモ</returns>
	const CVector3 GetObject_Vector3Memo(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].Position_Memo;
	}

	/// <summary>
	/// boolメモを取得
	/// 汎用的に使う
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <param name="obj_num">オブジェクト番号</param>
	/// <returns>boolメモ</returns>
	const bool GetObject_BoolMemo(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].BoolMemo;
	}

	/// <summary>
	/// floatメモを取得
	/// 汎用的に使う
	/// </summary>
	/// <param name="num">レベル番号</param>
	/// <param name="obj_num">オブジェクト番号</param>
	/// <returns>floatメモ</returns>
	const float GetObject_FloatMemo(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].FloatMemo;
	}
	const float GetObject_FloatMemo2(const int num, const int obj_num) {
		return m_levelData[num].Obj_Array[obj_num].FloatMemo2;
	}

	/// <summary>
	/// LevelDataのサイズを取得
	/// </summary>
	int GetLevelDataSize() {
		return sizeof(m_levelData) / sizeof(Level_Data);
	}

	/// <summary>
	/// 指定した番号レベルのオブジェクト一覧から一致するオブジェクトNoを検索
	/// ヒットしなかった場合は-1を返す
	/// </summary>
	/// <param name="LevelNo">レベルNo</param>
	/// <param name="objName">検索する名前</param>
	/// <returns>ヒットした場所</returns>
	int ObjName_Search(int LevelNo, const wchar_t* objName);

private:

	//レベルデータ本体（手動入力）
	const Level_Data m_levelData[5]{
		//チュートリアル
		{
			L"Assets/level/stage_00.tkl",	//レベルファイル名
			{
				{ L"Switch1",Tag_Switch,L"Door1" },
				{ L"Switch2",Tag_Switch,L"Door3" },
				{ L"Switch3",Tag_Switch,L"Door3" },
				{ L"Door1",Tag_Door,L"" },
				{ L"Door2",Tag_Door,L"" },
				{ L"Door3",Tag_Door,L"" },
				{ L"Test_Enemy",Tag_Test_Enemy,L"Door2" },
				{ L"GhostBox",Tag_GhostBox_MapMove,L"",L"Sougen1",{ 700.0f,110.0f,-950.0f }, false ,180.0f,-50.0f },	//移動先マップ名＆移動先座標
		}
		},
		//草原1
		{
			L"Assets/level/stage_1_1.tkl",	//レベルファイル名
			{
				{ L"Test_Enemy",Tag_Test_Enemy,L"" },
				{ L"jewel1",Tag_Jewel,L"" },
				{ L"jewel2",Tag_Jewel,L"" },
				{ L"jewel3",Tag_Jewel,L"" },
				{ L"jewel4",Tag_Jewel,L"" },
				{ L"jewel5",Tag_Jewel,L"" },
				{ L"Board1",Tag_Board,L"",L"テスト看板\nメッセージ" },
				{ L"StaticBox1",Tag_StaticBox,L"" },
				{ L"StaticBox2",Tag_StaticBox,L"" },
				{ L"StaticBox3",Tag_StaticBox,L"" },
				{ L"StaticBox4",Tag_StaticBox,L"" },
				{ L"StaticBox5",Tag_StaticBox,L"" },
				{ L"StaticBox6",Tag_StaticBox,L"" },
				{ L"GhostBox1",Tag_GhostBox_MapMove,L"",L"Sougen2",{ 500.0f,100.0f,-950.0f }, false ,180.0f,-750.0f },	//移動先マップ名＆移動先座標
				{ L"GhostBox2",Tag_GhostBox_MapMove,L"",L"Sougen3",{ 1022.0f,100.0f,-88.0f }, false ,180.0f,-750.0f },	//移動先マップ名＆移動先座標
				{ L"GhostBox3",Tag_GhostBox_MapMove,L"",L"Tutorial",{ -393.0f,50.0f,2145.0f }, false ,180.0f,-50.0f },	//移動先マップ名＆移動先座標
			}
		},
		//草原2
		{
			L"Assets/level/stage_1_2.tkl",	//レベルファイル名
			{
				{ L"jewel1",Tag_Jewel,L"" },
				{ L"jewel2",Tag_Jewel,L"" },
				{ L"BigDoor",Tag_BigDoor1,L"" },
				{ L"BigDoor_",Tag_BigDoor2,L"" },
				{ L"StaticBox1",Tag_StaticBox,L"" },
				{ L"StaticBox2",Tag_StaticBox,L"" },
				{ L"StaticBox3",Tag_StaticBox,L"" },
				{ L"StaticBox4",Tag_StaticBox,L"" },
				{ L"StaticBox5",Tag_StaticBox,L"" },
				{ L"GhostBox1",Tag_GhostBox_MapMove,L"",L"Sougen1",{ 1000.0f,100.0f,1000.0f }, true ,-90.0f,-100.0f },	//移動先マップ名＆移動先座標
			}
		},
		//草原3
		{
			L"Assets/level/stage_1_3.tkl",	//レベルファイル名
			{
				{ L"jewel1",Tag_Jewel,L"" },
				{ L"jewel2",Tag_Jewel,L"" },
				{ L"StaticBox1",Tag_StaticBox,L"" },
				{ L"StaticBox2",Tag_StaticBox,L"" },
				{ L"StaticBox3",Tag_StaticBox,L"" },
				{ L"StaticBox4",Tag_StaticBox,L"" },
				{ L"StaticBox5",Tag_StaticBox,L"" },
				{ L"GhostBox1",Tag_GhostBox_MapMove,L"",L"Sougen1",{ 700.0f,110.0f,-950.0f }, false ,180.0f,-250.0f },	//移動先マップ名＆移動先座標
			}
		}

	};

};

