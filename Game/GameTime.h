#pragma once

namespace CGameTime {

	/// <summary>
	/// 1フレームの経過時間を取得(単位・秒)
	/// </summary>
	/// <returns>経過時間</returns>
	static const float GetFrameDeltaTime()
	{
		float m_frameDeltaTime = 1.0f / 60.0f; //1フレームの経過時間。
		return m_frameDeltaTime;
	}

}
