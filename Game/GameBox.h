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

	/// <summary>
	/// 初期状態をセット
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void GameBox_Set(CVector3 pos, CQuaternion rot = CQuaternion::Identity()) {
		m_position = pos;
		m_rotation = rot;
	}

	bool CheckHitRayToPlane(CVector3 startPos, CVector3 endPos,CVector3* boxPos,CVector3& box_N, CVector3& plane_scale);
	
	CVector3 GetPosition() {
		return m_position;
	}

	/// <summary>
	/// 色設定
	/// </summary>
	void SetColor(CVector3 color) {
		m_model.SetEmissionColor(color);
	}
	CVector3 GetColor() {
		return m_model.GetEmissionColor();
	}
	void SetAllColor(CVector3 color);

	//移動量関連
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
	/// 箱のタグを変更する
	/// </summary>
	/// <param name="box_tag">たぐ</param>
	void SetBoxTag(BoxTag box_tag) {
		m_boxTag = box_tag;
	}

	/// <summary>
	/// 箱のタグを取得する
	/// </summary>
	/// <returns>タグです</returns>
	BoxTag GetBoxTag() {
		return m_boxTag;
	}

	/// <summary>
	/// 箱の拡大率を変更する
	/// </summary>
	/// <param name="scl">拡大率！</param>
	void SetScale(CVector3 scl) {
		m_scale = scl;
	}

	/// <summary>
	/// 箱の拡大率を返す
	/// </summary>
	/// <returns>拡大率！！！！！！</returns>
	CVector3 GetScale() {
		return m_scale;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(CQuaternion rot) {
		m_rotation = rot;
	}
	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns>回転</returns>
	CQuaternion GetRotation() {
		return m_rotation;
	}

	void GameBoxUpdate_Colli();

	/// <summary>
	/// 箱のローカル座標！
	/// </summary>
	void SetLocalPos(CVector3 pos) {
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
	SkinModel m_model;	//スキンモデル。

	PhysicsStaticObject m_physicsStaticObject;		//静的物理オブジェクト
	CMatrix  m_World;
	
	LightMaker* m_lightMaker;

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率
	CVector3 m_moveSpeed = CVector3().Zero();

	//親の箱とのローカル座標
	GameBox* m_originBox = nullptr;		//初代箱様！！！！
	CVector3 m_localPosition = CVector3().Zero();	//親との相対座標
	BoxTag m_boxTag = Another;

	//Vector
	std::vector<VertexBuffer>						m_vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBuffer>						m_indexBufferArray;		//インデックスバッファの配列。

	//無茶な計算
	CVector3 m_N;
	CVector3 m_vPos_0;
	CVector3 m_vPos_1;
	CVector3 m_vPos_2;

	bool m_colli_InitFlag = false;

	//子になるボックスども（OrizinBoxだけ変更される）
	std::vector<GameBox*> m_boxList;

	//定数
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };
	const float m_gravity = 0.6f;		//重力ﾊﾟｩﾜｧ
	const float Scale = 50.0f;		//補正計算用
	const float Y_Hosei = 60.0f;	//高さ補正

};

