#pragma once
#include "system/CGameObjectManager.h"
#include "SkinModelRender.h"
#include "PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// スイッチの赤いやつ
/// </summary>
class SwitchObj
{
public:
	SwitchObj();
	~SwitchObj();
	void SwitchObj_Init(CVector3 Pos);

	void GhostCheck();

private:

	//スイッチ状態
	enum SwitchState {
		On,
		Off,
	};

	SkinModelRender m_skinModel;	//赤いモデル
	Player* m_pl = nullptr;			//プレイヤー

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト
	PhysicsGhostObject m_ghostObject;	//ゴーストオブジェクト

	const CVector3 Local = { 0.0f,1.0f,0.0f };	//ベースを基準にした赤い部分のローカル座標
	const CVector3 GhostScale = { 100.0f,100.0f,10.0f };	//判定用ゴーストの範囲

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 5.0f,5.0f,5.0f }; //拡大率

	SwitchState m_switchState = Off;

};

class Switch : public IGameObject
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

private:

	SkinModel m_model;	//スイッチの土台もで～～る
	SwitchObj m_switchObj;	//赤い方を所持

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = { 5.0f,5.0f,5.0f }; //拡大率

};

