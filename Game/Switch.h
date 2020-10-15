#pragma once
#include "system/CGameObjectManager.h"
#include "graphics/skinModel/SkinModelRender.h"
#include "PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// スイッチの赤いやつ
/// 下記のスイッチ土台にアップデート・レンダーを呼んでもらっている
/// </summary>
class SwitchObj
{
public:
	SwitchObj();
	~SwitchObj();
	void SwitchObj_Init(CVector3 Pos);

	void SwitchUpdate();
	void SwitchDraw();

	/// <summary>
	/// スイッチのオンオフ状態を返す
	/// </summary>
	bool GetSwitchState() {
		return m_switchState;
	}

	void SetScale(CVector3 scale) {
		m_scale = scale;
	}

private:

	void GhostCheck();

	//スイッチ状態
	enum SwitchState {
		On,
		Off,
	};

	SkinModel m_model;	//スイッチのもで～～る
	Player* m_pl = nullptr;			//プレイヤー

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト
	PhysicsGhostObject m_ghostObject;	//ゴーストオブジェクト

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 5.0f,5.0f,5.0f }; //拡大率

	SwitchState m_switchState = Off;	//オンオフ状態

	//定数
	const CVector3 Local = { 0.0f,5.0f,0.0f };	//ベースを基準にした赤い部分のローカル座標
	const CVector3 GhostScale = { 160.0f,0.5f,160.0f };	//判定用ゴーストの範囲
	const float GhostY_Up = 15.0f;		//判定用ゴーストを上に持ち上げておく移動量
	const float SwitchMove = 14.0f;		//押されたとき戻った時の移動量
	const int SwitchMoveTime = 12;		//押されたとき戻った時の移動時間

};

/// <summary>
/// スイッチのベーース
/// 基準になるのはこっちです
/// </summary>
class Switch : public IGameObject, public ObjectClass
{
public:
	Switch();
	~Switch();
	void Update()override;
	void Render()override;

	//設定
	void SetPosition(CVector3 pos) {
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

	SkinModel m_model;	//スイッチの土台もで～～る
	SwitchObj m_switchObj;	//赤い方を所持

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

};

