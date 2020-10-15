#include "stdafx.h"
#include "MouseSupporter.h"

MouseSupporter* MouseSupporter::m_instance = nullptr;

MouseSupporter::MouseSupporter()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


MouseSupporter::~MouseSupporter()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

/// <summary>
/// 更新処理（毎フレーム呼ばれる）
/// </summary>
void MouseSupporter::MouseUpdate() {

	//カーソル状態によって変数を変更
	if (GetAsyncKeyState(VK_LBUTTON)) {
		//左が押された
		m_lestPushTimer++;
		if (m_leftMouse == New_Push) {
			//さっき押された瞬間だったので押されている状態に変更
			m_leftMouse = Now_Pushing;
		}

		if (m_leftMouse == Not_Push || m_leftMouse == Release_Push) {
			//押された瞬間！
			m_leftMouse = New_Push;
			m_lestPushTimer = 0;
		}
	}
	else {
		//左が押されていない
		if (m_leftMouse == Release_Push) {
			//さっき離された瞬間だったので離されている状態に変更
			m_leftMouse = Not_Push;
		}

		if (m_leftMouse == Now_Pushing || m_leftMouse == New_Push) {
			//離された瞬間！
			m_leftMouse = Release_Push;
		}
	}

	if (GetAsyncKeyState(VK_RBUTTON)) {
		//右が押された
		m_rightPushTimer++;
		if (m_rightMouse == New_Push) {
			//さっき押された瞬間だったので押されている状態に変更
			m_rightMouse = Now_Pushing;
		}

		if (m_rightMouse == Not_Push || m_rightMouse == Release_Push) {
			//押された瞬間！
			m_rightMouse = New_Push;
			m_rightPushTimer = 0;
		}
	}
	else {
		//右が押されていない
		if (m_rightMouse == Release_Push) {
			//さっき離された瞬間だったので離されている状態に変更
			m_rightMouse = Not_Push;
		}

		if (m_rightMouse == Now_Pushing || m_rightMouse == New_Push) {
			//離された瞬間！
			m_rightMouse = Release_Push;
		}
	}

	if (GetAsyncKeyState(VK_MBUTTON)) {
		//中央が押された
		m_centerPushTimer++;
		if (m_centerMouse == New_Push) {
			//さっき押された瞬間だったので押されている状態に変更
			m_centerMouse = Now_Pushing;
		}

		if (m_centerMouse == Not_Push || m_centerMouse == Release_Push) {
			//押された瞬間！
			m_centerMouse = New_Push;
			m_centerPushTimer = 0;
		}
	}
	else {
		//中央が押されていない
		if (m_centerMouse == Release_Push) {
			//さっき離された瞬間だったので離されている状態に変更
			m_centerMouse = Not_Push;
		}

		if (m_centerMouse == Now_Pushing || m_centerMouse == New_Push) {
			//離された瞬間！
			m_centerMouse = Release_Push;
		}
	}

	//ホイールの移動数を格納

	CVector2 move = GetBeforeMouse(0);
	m_mouseMove.x = move.x;
	m_mouseMove.y = move.y;

}

/// <summary>
/// 現在のマウス座標を取得
/// </summary>
/// <returns>マウス座標</returns>
const CVector2 MouseSupporter::GetMousePos() {

	POINT po;
	CVector2 m_pointPos = CVector2().Zero();
	bool m_result = GetCursorPos(&po);
	if (m_result == true) { //取得に成功したら実行される
		m_pointPos.x = (float)po.x;
		m_pointPos.y = (float)po.y;
	}
	
	return m_pointPos;
}

/// <summary>
/// 現在のマウス座標を3D座標に変換して取得
/// </summary>
/// <returns>3Dマウス座標</returns>
CVector3 MouseSupporter::GetMousePos_3D() {

	CVector3 m_pointPos = CVector3().Zero();
	CVector2 m_mousePos = GetMousePos();
	float half_w = FRAME_BUFFER_W * 0.5f;
	float half_h = FRAME_BUFFER_H * 0.5f;

	m_mousePos.x -= half_w;
	m_mousePos.y -= half_h;
	m_mousePos.y *= -1.0f;
	g_camera3D.CalcWorldPositionFromScrenPosition(m_pointPos, m_mousePos, 1.0f);

	return m_pointPos;
}

/// <summary>
/// マウス座標を画面座標に変換する
/// </summary>
/// <returns>座標</returns>
const CVector2 MouseSupporter::GetMousePos_Sprite() {

	CVector2 pos = GetMousePos();

	pos.x -= FRAME_BUFFER_W / 2.0f;
	pos.y -= FRAME_BUFFER_H / 2.0f;
	pos.y *= -1.0f;

	return pos;
}

/// <summary>
/// 実行する度に前回の座標と今回の座標の差（ベクトル）を返す
/// </summary>
/// <param name="p">取得する位置（0は常時実行、1はｶｧﾒｨﾗｧ）</param>
/// <returns>差</returns>
CVector2 MouseSupporter::GetBeforeMouse(const int p) {
	CVector2 pos = GetMousePos();
	CVector2 return_pos = { 0.0f,0.0f };

	return_pos.x = pos.x - m_beforeMouse[p].x;
	return_pos.y = pos.y - m_beforeMouse[p].y;

	m_beforeMouse[p].x = pos.x;
	m_beforeMouse[p].y = pos.y;

	return return_pos;
}