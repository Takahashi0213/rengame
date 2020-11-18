#pragma once

/// <summary>
/// チュートリアル用操作方法テキスト
/// </summary>
class TutorialSupporter
{
public:
	TutorialSupporter();
	~TutorialSupporter();

	//進行度
	enum Tutorial_Progress {
		Progress_Move,		//移動しよう
		Progress_Switch,	//ジャンプしてスイッチを踏もう
		Progress_Box,		//箱を生成してスイッチに乗せよう
		Progress_Enemy,		//箱を生成して敵にぶつけよう（持ち上げ）
		Progress_Enemy2,	//箱を生成して敵にぶつけよう（投げる）
		Progress_Exit,		//洞窟の出口を目指そう
		ProgressNum,		//要素数
	};

	/// <summary>
	/// チュートリアルの表示を変更する
	/// </summary>
	/// <param name="Progress">表示内容</param>
	void TutorialChange(const Tutorial_Progress Progress);

private:

	Tutorial_Progress m_tutorialProgress = Progress_Move;	//現在の表示

	FontRender* m_tutorialText = nullptr;					//チュートリアルの文字

	//内容
	const wchar_t* Tutorial[ProgressNum]{
		L"左クリックで移動して先へ進む",
		L"ＳＰＡＣＥキーでジャンプして\nスイッチに乗る",
		L"右クリックで箱を作って\nスイッチに乗せる",
		L"箱の近くでＣキーを押して箱を持ち上げる",
		L"もう一度Ｃキーを押すと箱を投げる",
		L"洞窟を脱出する",
	};

	//定数
	const CVector2 TutorialTextPos = { 0.0f,-300.0f };		//チュートリアル文字の座標
	
};

