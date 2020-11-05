#pragma once
#include "character/CharacterController.h"
#include "system/CGameObjectManager.h"
#include "physics/PhysicsStaticObject.h"
#include "GameSystem/Mouse/MouseOver.h"
#include "GameSystem/Box/GameBox.h"

/// <summary>
/// プレイヤー
/// 基本的に消滅しない
/// </summary>
class Player final: public IGameObject
{
public:
	Player();
	~Player();
	void Update()override;
	void Render()override;

	enum EnAnimationClip {
		enAnimationClip_Idle,		//待機
		enAnimationClip_Run,		//走る
		enAnimationClip_Jump,		//ジャンプ
		enAnimationClip_Damage,		//ダメージ
		enAnimationClip_Num,		//アニメーションクリップ
	};

	/// <summary>
	/// プレイヤーが敵からダメージを受けたら呼びましょう！
	/// </summary>
	void PlayerMiss(const CVector3& pos);

	/// <summary>
	/// プレイヤーのポジションを返す
	/// </summary>
	CVector3 GetPosition() {
		return m_position;
	}
	const CVector3& GetPositionBackup() {
		return m_posBackup;
	}
	//プレイヤーの座標を設定
	void SetPosition(const CVector3& pos);
	//移動先を設定
	void SetMoveTarget(const CVector3& pos) {
		m_nextPos = pos;
	}

	/// <summary>
	/// プレイヤーの回転を返す
	/// </summary>
	CQuaternion GetRotation() {
		return m_rotation;
	}

	/// <summary>
	/// スキンモデルレンダーを返す
	/// </summary>
	SkinModelRender* GetSkinModelRender() {
		return m_playerModel;
	}
	SkinModelRender* GetSkinModelRender_SL() {
		return m_playerModel_Sl;
	}

	/// <summary>
	/// キャラコンを取得
	/// </summary>
	CharacterController* GetCharaCon() {
		return &m_charaCon;
	}

private:

	SkinModelRender* m_playerModel;		//プレイヤーのモデル
	SkinModelRender* m_playerModel_Sl;	//プレイヤーのモデル（シルエット）
	CharacterController m_charaCon;		//キャラクターコントローラー。
	LightMaker* m_lightMaker;
	GameUI* m_ui = nullptr;

	//アニメーション
	AnimationClip m_playerAnimationClips[enAnimationClip_Num];	//アニメーションクリップ。

	//モノクロフラグ
	bool m_monochromeFlag = false;

	//アニメーション
	void PlayerAnimation();
	//行動 移動
	void MoveClick();
	void Move();
	void MoveSE();		//足音再生
	void Jump();
	//行動 箱関連
	void BoxUp();
	void BoxCatch();
	void BoxPut();
	void BoxSearch();
	void BoxMove();
	void BoxDelete();
	CVector3 BoxThrowSearch();

	//プレイヤー
	CVector3 m_position = { 0.0f,50.0f,-1900.0f };
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();
	CVector3 m_nextPos = CVector3::Zero();
	CVector3 m_posBackup = CVector3::Zero();

	//移動
	const float m_moveMax = 30.0f;			//最大移動速度
	const float MoveHosei = 20.0f;			//移動力への補正（大きいほど遅くなる）
	Effekseer::Handle m_moveEffect = -1;	//移動エフェクト

	//キャラコン
	const float Radius = 25.0f;				//半径
	const float Height = 30.0f;				//高さ

	//ジャンプ
	bool m_jumpNow = false;					//ジャンプフラグ
	const float m_jumpPower = 26.0f;		//ジャンプﾊﾟｩﾜｧ
	const float m_gravity = 2.0f;			//重力ﾊﾟｩﾜｧ

	//箱持ち上げ
	GameBox* m_upBox = nullptr;				//持ち上げている箱
	GameBox* m_upKouho_Box = nullptr;		//持ち上げ候補の箱
	bool m_boxUpFlag = false;				//箱持ち上げ中？
	bool m_boxMoveFlag = false;				//箱上げ下ろし動作中？（動作中は動けません）
	bool m_upOrDown = false;				//箱を上げているならfalse、下しているならtrue
	bool m_boxButtonFlag = false;			//箱のボタン
	bool m_boxDeleteButtonFlag = false;		//箱のボタン
	const float m_boxPutHosei = 4.0f;		//箱を置くか投げるかの基準補正（大きくすると置きやすくなる）
	const float m_boxUpRange = 200.0f;		//箱を持ち上げられる範囲
	const float m_boxUp_Y_Max = 50.0f;		//箱を持ち上げられる高さの範囲
	const float m_boxUp_Angle = 90.0f;		//箱を持ち上げる視野角範囲
	//上げ下げ移動（catmull）（だったけどベジェ曲線に変更）
	CVector3 m_point_1 = CVector3::Zero();	//終点寄り
	CVector3 m_point_2 = CVector3::Zero();	//始点
	CVector3 m_point_3 = CVector3::Zero();	//終点
	CVector3 m_point_4 = CVector3::Zero();	//始点寄り
	float m_catmull_U = 0.0f;
	const float m_boxMove_Y_Hosei = 150.0f;		//箱を上げる際の最高到達点Y補正
	const float m_boxMove_Y_Hosei_Put = 50.0f;	//箱を下ろす際の最高到達点Y補正
	const float m_boxPos_Y_Hosei = 150.0f;		//箱を持ち上げているときのプレイヤーY補正
	const float m_boxPut_Hosei = 150.0f;		//箱を置くときの移動量
	//箱投げ
	const float BoxThrowMaxLength = 500.0f;		//箱投げのターゲットになる範囲
	const float BoxThrowEffect_Y_Hosei = 50.0f;	//箱投げエフェクトのY補正
	//ダメージ
	const float m_damage_YHosei = 20.0f;		//ダメージを受けた時に飛びあがる量
	const float m_damage_knockback = -200.0f;	//ダメージを受けた時のノックバック距離
	bool m_damage_Flag = false;					//ダメージで飛び上がっている間は方向を固定する
	bool m_damage_JumpFlag = false;				//ダメージで飛び上がっている間は方向を固定する（空中用）
	//足音
	const float StepVolume = 0.5f;				//足音の大きさ
	float m_stepSE_Timer = 0.0f;				//足音用タイマー
	const float StepSE_Limit = 1.0f;			//足音制限時間
	bool m_stepSE_LeftRight = false;			//左足と右足

};

