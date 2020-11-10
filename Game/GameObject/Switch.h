#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "physics/PhysicsGhostObject.h"
#include "GameObject/Player.h"

/// <summary>
/// スイッチの赤いやつ
/// スイッチ土台にアップデート・レンダーを呼んでもらっている
/// </summary>
class SwitchObj
{
public:
	SwitchObj();
	~SwitchObj();
	void SwitchObj_Init(const CVector3& Pos);

	void SwitchUpdate();
	void SwitchDraw();

	/// <summary>
	/// レンダーモード変更
	/// </summary>
	void SwitchRenderModeChange(const RenderMode renderMode) {
		m_model.SetRenderMode(renderMode);
	}

	/// <summary>
	/// スイッチのオンオフ状態を返す
	/// </summary>
	bool GetSwitchState() {
		return m_switchState;
	}

	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}

private:

	void GhostCheck();

	//スイッチ状態
	enum SwitchState {
		On,
		Off,
	};

	SkinModel m_model;								//スイッチのモデル
	Player* m_pl = nullptr;							//プレイヤー

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト
	PhysicsGhostObject m_ghostObject;				//ゴーストオブジェクト

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 5.0f,5.0f,5.0f };			//拡大率

	SwitchState m_switchState = Off;				//オンオフ状態

	//定数
	const CVector3 Local = { 0.0f,5.0f,0.0f };		//ベースを基準にした赤い部分のローカル座標
	const CVector3 GhostScale = { 140.0f,0.5f,140.0f };	//判定用ゴーストの範囲
	const float GhostY_Up = 15.0f;					//判定用ゴーストを上に持ち上げておく移動量
	const float SwitchMove = 14.0f;					//押されたとき戻った時の移動量
	const int SwitchMoveTime = 12;					//押されたとき戻った時の移動時間

};

/// <summary>
/// スイッチのベース
/// 基準になるのはこっちです
/// </summary>
class Switch : public ObjectClass
{
public:
	Switch();
	~Switch();
	void Update()override;
	void Render()override;

	//設定
	void SetPosition(const CVector3& pos) {
		m_position = pos;
		m_switchObj.SwitchObj_Init(m_position);
	}

	/// <summary>
	/// 座標を返す
	/// </summary>
	CVector3 GetPosition() {
		return m_position;
	}

	/// <summary>
	/// スイッチのオンオフ状態を返す
	/// 外部から見ると仕様が逆なので戻しておく
	/// </summary>
	bool GetSwitchState() {
		if (m_switchObj.GetSwitchState() == false) {
			return true;
		}
		if (m_switchObj.GetSwitchState() == true) {
			return false;
		}
		return false;
	}

private:

	SkinModel m_model;		//スイッチの土台モデル
	SwitchObj m_switchObj;	//赤い方を所持

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

};

