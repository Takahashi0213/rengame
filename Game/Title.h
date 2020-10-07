#pragma once

#include "system/CGameObjectManager.h"

/// <summary>
/// たいとる！
/// ・シングルトン
/// </summary>
class Title : public IGameObject
{
	static Title* m_instance;
public:
	Title();
	~Title();
	void Update()override;
	void Render()override;

	//コマンドの選択状態
	enum TitleCommand {
		No_Select,		//未選択
		Game_Start,		//はじめから
		Game_Continue,	//つづきから
		Game_End,		//終了
	};

	//コマンドの選択状態を返す
	//選んだコマンドの内部処理はSceneManagerが行う
	const TitleCommand& GetCommand()const {
		return m_nowCommand;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static Title* Title::GetInstance() {
		return m_instance;
	}

private:

	//コマンドじゃん
	TitleCommand m_nowCommand = No_Select;	//最初は未選択

};

