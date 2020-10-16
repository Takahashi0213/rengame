#pragma once
#include "system/CGameObjectManager.h"
#include "TransitionSprite.h"

/// <summary>
/// トランジションを実行
/// ・シングルトン
/// </summary>
class TransitionGenerator : public IGameObject
{
	static TransitionGenerator* m_instance;
public:
	//トランジションを呼び出すときのお名前
	enum TransitionName {
		UnderSlide,	//下からフェード
		NanameBox,	//ナナメボックス
	};

	TransitionGenerator();
	~TransitionGenerator();
	void Update()override;
	void Render()override;

	/// <summary>
	/// インスタンスを取得シリーズ
	/// </summary>
	/// <returns>インスタンスです</returns>
	static TransitionGenerator* TransitionGenerator::GetInstance() {
		return m_instance;
	}

	//トランジションの実行
	void TransitionInit(
		const TransitionName& name,
		const int& MoveTime,
		const bool& mode
	);

private:
	TransitionSprite m_transitionSprite;

	struct Transition_Data {		//スプライトパターンデータ構造体
		wchar_t* SpriteName;	//スプライトファイル名
	};

	Transition_Data Transition_DataList[3]{
		{ L"Assets/sprite/under.dds" },
		{ L"Assets/sprite/naname_box.dds" },
		{ L"Assets/sprite/levelUp_8F.dds" },
	};

	//トランジション用
	int m_transitionLimit = 0;			//トランジション実行時間
	float m_borderLine = 0.0f;			//描画されるライン
	bool m_transitionMode = false;		//falseなら表示、trueなら消去
	bool m_nowTransitionFlag = false;	//トランジションちう
	const float MoveSpeed = 10.0f;		//計算用

};

