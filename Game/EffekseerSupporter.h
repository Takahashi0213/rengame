#pragma once
//Effekseerのヘッダーファイル
#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

/// <summary>
/// エフェクト簡単表示
/// ・シングルトン
/// </summary>
class EffekseerSupporter
{
	static EffekseerSupporter* m_instance;
public:
	//エフェクトの種類
	enum EffectData {
		TestData,
		Null,
	};

	//

	struct Effect {	//エフェクトデータ
		int Handle;
		bool PostFlag;
	};
	std::list<Effect>* g_effectList_P = &m_effectList;

	//

	EffekseerSupporter();
	~EffekseerSupporter();
	
	/// <summary>
	/// エフェクトの生成
	/// </summary>
	Effekseer::Handle NewEffect(const wchar_t* EffectFileName, 
		bool PostFlag = false,
		Effekseer::Vector3D DefPos = { 0.0f,0.0f,0.0f });
	Effekseer::Handle NewEffect(const EffectData EffectFileName,
		bool PostFlag = false,
		Effekseer::Vector3D DefPos = { 0.0f,0.0f,0.0f });
	Effekseer::Handle NewEffect_Vector(const EffectData EffectFileName,
		bool PostFlag = false,float X = 0.0f, float Y = 0.0f, float Z = 0.0f);

	/// <summary>
	/// ここからエフェクト調整
	/// </summary>
	
	/// <summary>
	/// 先に描画されるエフェクトのストップ＆再開
	/// </summary>
	void NoPostStop();
	void NoPostMove();

	/// <summary>
	/// エフェクトデータの削除（毎フレーム呼んでね）
	/// </summary>
	void EffectClear();

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static EffekseerSupporter* EffekseerSupporter::GetInstance() {
		return m_instance;
	}

private:

	//エフェクトファイル名
	const wchar_t EffectDetaBase[2][30]{
	{ L"Assets/effect/test.efk" },
	{ L"Assets/effect/test.efk" },
	};

	std::list<Effect> m_effectList;		//エフェクトリスト

};

