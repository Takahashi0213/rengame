#pragma once
#include <string>

//�n�b�V���l�̍쐬
class Hash {
public:

	/// <summary>
	/// �����񂩂�n�b�V���l���쐬
	/// </summary>
	/// <param name="string">�쐬������������</param>
	/// <returns>�n�b�V���l</returns>
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
};