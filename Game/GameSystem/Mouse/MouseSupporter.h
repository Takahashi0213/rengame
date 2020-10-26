#pragma once

/// <summary>
/// マウスの色々を楽にする
/// ・シングルトン
/// </summary>
class MouseSupporter final
{
	static MouseSupporter* m_instance;
public:
	MouseSupporter();
	~MouseSupporter();

	//カーソルの状態
	enum mouse_state {
		Not_Push,		//押されていない
		Now_Pushing,	//押されている
		New_Push,		//新規に押された
		Release_Push,	//押していた状態から離された
	};
	//キーの種類
	enum mouse_key {
		Left_Key,
		Right_Key,
		Center_Key,
	};

	void MouseSupporter::MouseUpdate();

	/// <summary>
	/// マウスの状態を返す
	/// </summary>
	/// <param name="key">取得したいキーの種類</param>
	/// <returns>キーの状態</returns>
	mouse_state MouseSupporter::GetMouseKey(const mouse_key& key) {
		mouse_state re;
		switch (key)
		{
		case MouseSupporter::Left_Key:
			re = m_leftMouse;
			break;
		case MouseSupporter::Right_Key:
			re = m_rightMouse;
			break;
		case MouseSupporter::Center_Key:
			re = m_centerMouse;
			break;
		}
		return re;
	}

	/// <summary>
	/// マウスを長押ししていたフレーム数を返す
	/// </summary>
	/// <param name="key">取得したいキーの種類</param>
	/// <returns>フレーム数</returns>
	int MouseSupporter::GetMouseTimer(const mouse_key& key) {
		int re;
		switch (key)
		{
		case MouseSupporter::Left_Key:
			re = m_lestPushTimer;
			break;
		case MouseSupporter::Right_Key:
			re = m_rightPushTimer;
			break;
		}
		return re;
	}

	/// <summary>
	/// 前フレームと比較したマウスの移動量を返す！！
	/// </summary>
	/// <returns>移動量</returns>
	const CVector2& MouseSupporter::GetMouseMove() {
		return m_mouseMove;
	}

	const CVector2 MouseSupporter::GetMousePos();
	CVector3 MouseSupporter::GetMousePos_3D();
	const CVector2 MouseSupporter::GetMousePos_Sprite();
	CVector2 MouseSupporter::GetBeforeMouse(const int p = 0);

	/// <summary>
	/// マウス移動量を設定
	/// </summary>
	/// <remarks>
	/// 
	/// system.cpp以外で呼ばないで！！！
	/// 
	/// </remarks>
	/// <param name="move">移動量</param>
	void MouseSupporter::SetWheelMove(const int& move) {
		m_wheelMove = move;
	}
	/// <summary>
	/// マウス移動量を返す
	/// </summary>
	/// <returns>移動量</returns>
	const int& MouseSupporter::GetWheelMove() {
		return m_wheelMove;
	}

	/// <summary>
	/// インスタンスを取得！
	/// </summary>
	/// <returns>インスタンスです</returns>
	static MouseSupporter* MouseSupporter::GetInstance() {
		return m_instance;
	}

private:

	//カーソルの押された状態を保存する
	mouse_state m_leftMouse = Not_Push;
	mouse_state m_rightMouse = Not_Push;
	mouse_state m_centerMouse = Not_Push;

	//カーソルの押されていた時間を保存する
	int m_lestPushTimer = 0;
	int m_rightPushTimer = 0;
	int m_centerPushTimer = 0;

	//ホイールの移動数を保存する
	int m_wheelMove = 0;

	//前回のマウス座標を保存する
	CVector2 m_beforeMouse[2] = { {0.0f,0.0f},{0.0f,0.0f} };	//2つ目はカメラ操作用
	CVector2 m_mouseMove = { 0.0f,0.0f };
};

