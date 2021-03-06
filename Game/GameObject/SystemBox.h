#pragma once
#include "system/CGameObjectManager.h"
#include "physics/PhysicsGhostObject.h"
#include "Player.h"

/// <summary>
/// ゴーストボックス
/// マップ移動を作ったり、範囲に入ったら起動するイベントに使える
/// </summary>
class GhostBox : public ObjectClass
{
public:
	enum GhostBox_System {
		MapMove,	//マップ移動
		MapEvent,	//マップイベント
		DamageZone,	//落下ダメージ
	};
	//動作の種類を設定
	void SetGhostBox_System(const GhostBox_System boxSystem) {
		m_boxSystem = boxSystem;
	}

	GhostBox();
	~GhostBox();
	void Update()override;
	void Render()override;

	//設定用（レベル生成時に同時に呼ぶのが基本）
	void SetStageName(const wchar_t* stageName) {
		m_LoadName = stageName;
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
	void GhostAction();		//プレイヤー接触時の反応

	PhysicsGhostObject m_ghostObject;				//ゴーストオブジェクト
	SkinModelRender* m_Yazirushi = nullptr;			//マップ移動ゴーストの場合使用する

	Player* m_player = nullptr;						//プレイヤーはここ！
	GhostBox_System m_boxSystem;					//この箱の種類

	//レベルセット時に設定するもの
	const wchar_t* m_LoadName = nullptr;			//ステージ/イベントの名前
	CVector3 m_playerMoveTarget;					//プレイヤーの移動先
	float m_yazirushiRotAngle = 0.0f;				//矢印の回転
	float m_yazirushiYHosei = 0.0f;					//矢印のY補正

	bool m_mapMoveFlag = false;						//マップ移動フラグ
	int m_mapMoveTimer = 0;							//マップ移動タイマー
	const float YazirushiMoveHosei = 30.0f;			//矢印の移動量補正
	const int YazirushiMoveTime = 10;				//矢印の移動時間
	bool YazirushiRotFlag = false;					//矢印の回転フラグ（Y_UP）
	const int FallDamage = 50;						//落下ダメージ
	const float PlayerMiss_Y_Hosei = 100.0f;		//落下した後の復帰地点Y補正


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
