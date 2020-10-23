#pragma once
#include "system/CGameObjectManager.h"
#include "PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// ゴーストボックス
/// マップ移動を作ったり、範囲に入ったら起動するイベントに使える
/// </summary>
class GhostBox : public ObjectClass
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
	void SetPlayerMoveTarget(const CVector3& pos) {
		m_playerMoveTarget = pos;
	}
	void SetYazirushiRot(const float& rotAngle) {
		m_yazirushiRotAngle = rotAngle;
	}
	void SetYazirushiYHosei(const float& hosei) {
		m_yazirushiYHosei = hosei;
	}
	void SetRotFlag(const bool& rotFlag) {
		YazirushiRotFlag = rotFlag;
	}

	/// <summary>
	/// 呼び出すとゴーストを生成する
	/// </summary>
	void CreateGhost();

private:
	PhysicsGhostObject m_ghostObject;				//ゴーストオブジェクト
	SkinModelRender* m_Yazirushi = nullptr;			//マップ移動ゴーストの場合使用する

	Player* m_player = nullptr;						//プレイヤーはここ！

	//レベルセット時に設定するもの
	//マップ移動編
	const wchar_t* m_LoadStageName = nullptr;		//ステージの名前
	CVector3 m_playerMoveTarget;					//プレイヤーの移動先
	float m_yazirushiRotAngle = 0.0f;				//矢印の回転
	float m_yazirushiYHosei = 0.0f;					//矢印のY補正
	bool m_mapMoveFlag = false;						//マップ移動フラグ
	int m_mapMoveTimer = 0;							//マップ移動タイマー
	const float YazirushiMoveHosei = 30.0f;			//矢印の移動量補正
	const int YazirushiMoveTime = 10;				//矢印の移動時間
	bool YazirushiRotFlag = false;					//矢印の回転フラグ（Y_UP）
	//ゲームオーバー編


};

/// <summary>
/// 静的な箱
/// 透明な壁を作れる
/// </summary>
class StaticBox : public ObjectClass
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
