#pragma once

namespace CGameTime {

	/// <summary>
	/// 1�t���[���̌o�ߎ��Ԃ��擾(�P�ʁE�b)
	/// </summary>
	/// <returns>�o�ߎ���</returns>
	static const float GetFrameDeltaTime()
	{
		float m_frameDeltaTime = 1.0f / 60.0f; //1�t���[���̌o�ߎ��ԁB
		return m_frameDeltaTime;
	}

}
