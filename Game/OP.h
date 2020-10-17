#pragma once

/// <summary>
/// OPを実行
/// スキップキーを押されると強制終了する
/// </summary>
class OP
{
public:
	OP();
	~OP();

	/// <summary>
	/// OP更新（Gameクラスに呼んでもらう）
	/// </summary>
	void OP_Update();

	/// <summary>
	/// OP終了フラグを返す
	/// </summary>
	bool GetEndFlag() {
		return m_opEndFlag;
	}

private:

	bool m_opEndFlag = false;		//こやつがtrueになった瞬間がOP終焉の時

	//OP進行関連
	int m_opShinkou = 0;			//OP進行度
	bool m_opEffectFlag = false;	//何度もメッセージが表示されないようにするフラグ

	//定数
	const int EndShinkou = 2;

};

