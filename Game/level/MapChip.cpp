#include "stdafx.h"
#include "MapChip.h"
#include "Level.h"

MapChip::MapChip(const LevelObjectData& objData)
{
	wchar_t filePath[256];
	wchar_t filePath_Dummy[256];	//切り出すためのもの
	wchar_t nomChar[11] = L"0123456789";	//数字を切り出すため、数字をここにまとめておく

	swprintf_s(filePath_Dummy, L"Assets/modelData/%s.cmo", objData.name);

	//数字だけ切り出す ※追加
	//const wchar_t* text = nullptr;
	//text = filePath_Dummy.c_str();

	int len = (int)wcslen(filePath_Dummy);	//文字数を取得
	int t = 0;		//文字をコピーする際の代入先番号
	for (int i=0; i < len; i++) {

		//数字以外ならコピペ
		bool HitFlag = false;
		for (int s = 0; s < 10; s++) {
			if (filePath_Dummy[i] == nomChar[s]) {
				//一緒ならフラグをいれる
				HitFlag = true;
			}
		}

		//もしヒットしているならばコピーは実行しない
		if (HitFlag == false) {
			filePath[t] = filePath_Dummy[i];
			t++;
		}
		
	}
	filePath[t] = L'\0';

	m_model.Init(filePath);
	m_model.UpdateWorldMatrix(objData.position, objData.rotation, CVector3::One());
	//静的物理オブジェクトをメッシュコライダーから作成する。
	m_physicsStaticObject.CreateMeshObject(m_model, objData.position, objData.rotation);
}

void MapChip::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}