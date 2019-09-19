#include "stdafx.h"
#include "LightMaker.h"

LightMaker* LightMaker::m_instance = nullptr;

LightMaker::LightMaker()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

LightMaker::~LightMaker()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void LightMaker::Update() {
}

void LightMaker::Render() {

}

/// <summary>
/// ディレクションライトを生成する
/// </summary>
/// <param name="dir">ライトの方向</param>
/// <param name="col">ライトの色</param>
/// <returns>作成したライトのポインタ</returns>
SDirectionLight* LightMaker::D_LightMake(CVector4 dir,CVector4 col) {

	//ディレクションライトを生成する
	SDirectionLight*d = new SDirectionLight;
	
	//生成したインスタンスを可変長配列に追加する
	m_dLightList.push_back(d);

	return d;
}

/// <summary>
/// ディレクションライトを消去する
/// </summary>
/// <param name="light">削除するディレクションライトのポインタ</param>
void LightMaker::D_LightDelete(SDirectionLight* light) {

	//リストを検索して一致したものを消す
	for (auto it = m_dLightList.begin();
		it != m_dLightList.end();
		it++) {
		if (*it == light) {
			delete *it;
			m_dLightList.erase(it); //可変長配列からも除去
		}
	}

}
