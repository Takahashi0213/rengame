#pragma once
#include "system/CGameObjectManager.h"
#include "PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// ゴーストボックス
/// マップ移動を作ったり、範囲に入ったら起動するイベントに使える
/// </summary>
class GhostBox : public IGameObject, public ObjectClass
{
public:
	GhostBox();
	~GhostBox();
	void Update()override;
	void Render()override;

	//設定用（レベル生成時に同時に呼ぶのが基本）
	void SetStageName(const wchar_t* stageName) {
		m_LoadStageName = stageName;
	}
	void SetPlayerMoveTarget(const CVector3 pos) {
		m_playerMoveTarget = pos;
	}

	/// <summary>
	/// 呼び出すとゴーストを生成する
	/// </summary>
	void CreateGhost();

private:
	PhysicsGhostObject m_ghostObject;				//ゴーストオブジェクト

	Player* m_player = nullptr;						//プレイヤーはここ！

	//レベルセット時に設定するもの
	//マップ移動編
	const wchar_t* m_LoadStageName = nullptr;		//ステージの名前
	CVector3 m_playerMoveTarget;					//プレイヤーの移動先
	//ゲームオーバー編


};

/// <summary>
/// 静的な箱
/// 透明な壁を作れる
/// </summary>
class StaticBox : public IGameObject, public ObjectClass
{
public:
	StaticBox();
	~StaticBox();
	void Update()override;
	void Render()override;

	/// <summary>
	/// 呼び出すと静的物理オブジェクトを生成する
	/// </summary>
	void CreateStaticBox();

private:
	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

};
