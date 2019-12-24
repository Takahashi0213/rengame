#pragma once
#include "character/CharacterController.h"
#include "Physics/MeshCollider.h"

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

	BoxTag m_boxTag = Another;

	RigidBody m_rb;				//剛体
	MeshCollider m_meshColli;	//コライダー
	CMatrix  m_World;

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率

	std::vector<VertexBuffer>						m_vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBuffer>						m_indexBufferArray;		//インデックスバッファの配列。

	//無茶な計算
	CVector3 m_N;
	CVector3 m_vPos_0;
	CVector3 m_vPos_1;
	CVector3 m_vPos_2;

	bool m_colli_InitFlag = false;

	//子になるボックスども（OrizinBoxだけ変更される）
	std::list<GameBox*> m_boxList;

	//定数
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };
	const float m_gravity = 0.8f;		//重力ﾊﾟｩﾜｧ

};

