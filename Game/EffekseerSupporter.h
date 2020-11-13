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
		TestData,			//テストデータ（サンプルに入っていた適当なエフェクト）
		EnemyDeath,			//敵が倒れる
		PlayerMove,			//プレイヤーの移動先
		EnemyScope,			//箱を飛ばす先（敵）
		EnemyDiscovery,		//敵に発見された！
		PlayerDeath,		//プレイヤー消滅…
		TorchFire,			//トーチの炎（ループ）
		EffectNum,			//エフェクトの数
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
	/// PostFlagをtrueにすると2D空間に描画される
	/// </summary>
	Effekseer::Handle NewEffect(const wchar_t* EffectFileName, 
		const bool& PostFlag = false,
		const Effekseer::Vector3D& DefPos = { 0.0f,0.0f,0.0f });
	Effekseer::Handle NewEffect(const EffectData EffectFileName,
		const bool& PostFlag = false,
		const Effekseer::Vector3D& DefPos = { 0.0f,0.0f,0.0f });
	Effekseer::Handle NewEffect_Vector(const EffectData EffectFileName,
		const bool& PostFlag = false, const float& X = 0.0f, const float& Y = 0.0f, const float& Z = 0.0f,
		const float& rotX = 0.0f, const float& rotY = 0.0f, const float& rotZ = 0.0f);

	/// <summary>
	/// ここからエフェクト調整
	/// </summary>
	
	/// <summary>
	/// 先に描画されるエフェクトのストップ＆再開
	/// </summary>
	void NoPostStop(const bool& flag);

	/// <summary>
	/// エフェクトの強制削除
	/// </summary>
	/// <remarks>
	/// 
	/// ループするエフェクトの場合、生成時にハンドルを保存しておいて
	/// 任意のタイミングでこの関数を呼び出して削除してください
	/// （削除しないと永遠に残り続けます）
	/// 
	/// </remarks>
	/// <param name="effect">削除するエフェクトのハンドル</param>
	void EffectDelete(const Effekseer::Handle& effect);

	/// <summary>
	/// エフェクトデータの自動削除（毎フレーム呼んでね）
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
	const wchar_t EffectDetaBase[EffectNum][MAX_PATH]{
	{ L"Assets/effect/test.efk" },
	{ L"Assets/effect/EnemyDeath.efk" },
	{ L"Assets/effect/PlayerMove.efk" },
	{ L"Assets/effect/EnemyScope.efk" },
	{ L"Assets/effect/EnemyDiscovery.efk" },
	{ L"Assets/effect/PlayerDeath.efk" },
	{ L"Assets/effect/Torch.efk" },
	};

	std::list<Effect> m_effectList;		//エフェクトリスト

};

