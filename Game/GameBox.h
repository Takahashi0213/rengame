#pragma once
#include "character/CharacterController.h"
#include "Physics/MeshCollider.h"
#include "physics/PhysicsStaticObject.h"

class GameBox
{
public:
	enum BoxTag {
		Origin,			//最初に作った箱
		Another,		//その他の箱
	};

	typedef std::vector<CVector3>					VertexBuffer;		//頂点バッファ。
	typedef std::vector<unsigned int>				IndexBuffer;		//インデックスバッファ。
	GameBox();
	~GameBox();
	void GameBox_Update();
	void GameBox_Render();
	bool DeathBox();					//高度が一定以下になったら自死

	/// <summary>
	/// 初期状態をセット
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void GameBox_Set(const CVector3 pos, const CQuaternion rot = CQuaternion::Identity()) {
		m_position = pos;
		m_rotation = rot;
	}

	//レイが当たってるかをチェック
	bool CheckHitRayToPlane(CVector3 startPos, CVector3 endPos,CVector3* boxPos,CVector3& box_N, CVector3& plane_scale);
	
	//座標を返す
	const CVector3& GetPosition() const {
		return m_position;
	}

	/// <summary>
	/// 色取得＆削除
	/// </summary>
	void SetColor(CVector3 color) {
		m_model.SetEmissionColor(color);
	}
	CVector3 GetColor() {
		return m_model.GetEmissionColor();
	}
	//（子供含め）まとめて着色
	void SetAllColor(const CVector3 color);

	//移動量取得＆削除
	CVector3 GetMoveSpeed() {
		return m_moveSpeed;
	}
	void SetMoveSpeed(CVector3 speed) {
		m_moveSpeed = speed;
	}

	/// <summary>
	/// 子のボックスリストを追加する
	/// </summary>
	/// <param name="box">追加する箱のアドレス</param>
	void SetBox(GameBox* box) {
		m_boxList.push_back(box);
	}
	/// <summary>
	/// 子のボックスリストを削除する
	/// </summary>
	void SetBox_Delete() {
		m_boxList.pop_back();
	}
	/// <summary>
	/// 子のボックスリストを返す
	/// </summary>
	/// <returns></returns>
	std::vector<GameBox*> GetBoxList() {
		return m_boxList;
	}

	/// <summary>
	/// 箱のタグを変更＆取得
	/// </summary>
	void SetBoxTag(const BoxTag box_tag) {
		m_boxTag = box_tag;
	}
	BoxTag GetBoxTag() {
		return m_boxTag;
	}

	/// <summary>
	/// 箱の拡大率 設定＆取得
	/// </summary>
	void SetScale(const CVector3 scl) {
		m_scale = scl;
	}
	CVector3 GetScale() {
		return m_scale;
	}

	/// <summary>
	/// 回転を設定＆取得
	/// </summary>
	void SetRotation(const CQuaternion rot) {
		m_rotation = rot;
	}
	CQuaternion GetRotation() {
		return m_rotation;
	}

	/// <summary>
	/// マナパワーの設定と取得（箱の削除に使います）
	/// </summary>
	void SetManaPower(const int mana) {
		m_manaPower = mana;
	}
	int GetManaPower() {
		return m_manaPower;
	}

	/// <summary>
	/// 箱が完成したらコライダーを設定して
	/// それ以降座標に応じてコライダーを移動させる
	/// コライダー専用アップデート
	/// </summary>
	void GameBoxUpdate_Colli();

	/// <summary>
	/// 箱のローカル座標！
	/// </summary>
	void SetLocalPos(const CVector3 pos) {
		m_localPosition = pos;
	}
	CVector3 GetLocalPos() {
		return m_localPosition;
	}

	/// <summary>
	/// 初代箱を設定
	/// </summary>
	void SetOriginBox(GameBox* box) {
		m_originBox = box;
	}
	GameBox* GetOriginBox() {
		return m_originBox;
	}

	/// <summary>
	/// コライダーの設定フラグを返す
	/// </summary>
	bool GetColli_InitFlag() {
		return m_colli_InitFlag;
	}

	/// <summary>
	/// 剛体を返す
	/// </summary>
	RigidBody* GetRigidBody() {
		return m_physicsStaticObject.GetRigidBody();
	}

	/// <summary>
	/// 呼ばれたら子供箱を全て削除
	/// </summary>
	void DeleteBox();

	/// <summary>
	/// 箱を持つときの座標補正量を計算するZO
	/// </summary>
	CVector3 GetAnotherHosei();
	/// <summary>
	/// 箱を持つときの範囲補正量を計算するZE 
	/// </summary>
	float GetAnotherRangeHosei();

private:
	void GetTrianglePositionAndNormal(
		int polyNo,
		IndexBuffer& indexBuffer,
		VertexBuffer& vertexBuffer,
		CMatrix& mWorld,
		CMatrix& mRot,
		CVector3& vPos_0,
		CVector3& vPos_1,
		CVector3& vPos_2,
		CVector3& N);
	/// <summary>
	/// ベクトルの比較用
	/// </summary>
	/// <param name="a">比較したいベクトル１</param>
	/// <param name="b">比較したいベクトル２</param>
	/// <returns>falseなら完全一致、trueならどこか1要素違う</returns>
	bool VectorHikaku(CVector3 a, CVector3 b) {
		bool Flag = false;
		if (fabsf(a.x - b.x) > 0.02f) {
			Flag = true;
		}
		if (fabsf(a.y - b.y) > 0.02f) {
			Flag = true;
		}	
		if (fabsf(a.z - b.z) > 0.02f) {
			Flag = true; 
		}
		return Flag;
	}

	void MeshStandBy();
	const float DeathHeight = -200.0f;	//消滅する最低高度

	SkinModel m_model;	//スキンモデル。

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト
	CMatrix  m_World;
	
	LightMaker* m_lightMaker;		//ライトメーカー（影を落とすなら必要）

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One();				//拡大率
	CVector3 m_moveSpeed = CVector3().Zero();

	//親の箱とのローカル座標
	GameBox* m_originBox = nullptr;					//初代箱様！！！！（基準になる）
	CVector3 m_localPosition = CVector3().Zero();	//親との相対座標
	BoxTag m_boxTag = Another;						//箱のタグ

	//Vector
	std::vector<VertexBuffer>						m_vertexBufferArray;	//頂点バッファの配列。
	std::vector<IndexBuffer>						m_indexBufferArray;		//インデックスバッファの配列。

	//無茶な計算用
	CVector3 m_N;
	CVector3 m_vPos_0;
	CVector3 m_vPos_1;
	CVector3 m_vPos_2;

	bool m_colli_InitFlag = false;		//コライダー設定した？？

	//子になるボックスども（OrizinBoxだけ変更される、Anotherは不要）
	std::vector<GameBox*> m_boxList;
	//マナパワー総数（こちらもOrizin専用）
	int m_manaPower = 0;

	//定数
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };		//箱の初期スケール
	const float m_gravity = 0.6f;		//重力ﾊﾟｩﾜｧ
	const float Scale = 50.0f;			//補正計算用
	const float Y_Hosei = 60.0f;		//高さ補正

};

