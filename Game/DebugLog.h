#pragma once

class DebugLog
{
public:
	DebugLog();
	~DebugLog();

	/// <summary>
	/// ログを出力します
	/// デバッグモードでないと実行されません
	/// </summary>
	/// <param name="mes">出力するログ</param>
	static void DebugMessage(const char* mes){
#ifdef _DEBUG
		OutputDebugString(mes);
		OutputDebugString("\n");
#endif
	}
private:

};

