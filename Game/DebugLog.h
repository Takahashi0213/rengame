#pragma once

class DebugLog
{
public:
	DebugLog();
	~DebugLog();

	/// <summary>
	/// ���O���o�͂��܂�
	/// �f�o�b�O���[�h�łȂ��Ǝ��s����܂���
	/// </summary>
	/// <param name="mes">�o�͂��郍�O</param>
	static void DebugMessage(const char* mes){
#ifdef _DEBUG
		OutputDebugString(mes);
		OutputDebugString("\n");
#endif
	}
private:

};

