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

	void SetStageName(const wchar_t* stageName) {
		m_LoadStageName = stageName;
	}

	/// <summary>
	/// 呼び出すとゴーストを生成する
	/// </summary>
	void CreateGhost();

private:
	PhysicsGhostObject m_ghostObject;	//ゴーストオブジェクト

	Player* m_player = nullptr;

	const wchar_t* m_LoadStageName;		//ステージの名前

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

private:
	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト

};
