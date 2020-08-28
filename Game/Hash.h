#pragma once
#include <string>

//ハッシュ値の作成
class Hash {
public:

	/// <summary>
	/// 文字列からハッシュ値を作成
	/// </summary>
	/// <param name="string">作成したい文字列</param>
	/// <returns>ハッシュ値</returns>
	static int MakeHash(const char* string)
	{
		if (string == nullptr) {
			return 0;
		}
		int hash = 0;
		int l = (int)strlen(string);
		for (int i = 0; i < l; i++) {
			hash = hash * 37 + string[i];
		}
		return hash;
	}

	static int MakeHash(const wchar_t* string)
	{
		if (string == nullptr) {
			return 0;
		}
		//wchar_t hoge = *string;
		//std::hash<wchar_t>()(hoge);
		int hash = 0;
		int l = (int)wcslen(string);
		for (int i = 0; i < l; i++) {
			hash = hash * 37 + string[i];
		}
		return hash;
	}

};