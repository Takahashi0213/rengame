#pragma once
class GameBox
{
public:
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

	void CheckHitRayToPlane(CVector3 startPos, CVector3 endPos);
	
	CVector3 GetPosition() {
		return m_position;
	}

private:
	void MeshStandBy();
	SkinModel m_model;	//スキンモデル。

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //拡大率

	typedef std::vector<CVector3>					VertexBuffer;		//頂点バッファ。
	typedef std::vector<unsigned int>				IndexBuffer;		//インデックスバッファ。
	typedef std::unique_ptr<VertexBuffer>			VertexBufferPtr;
	typedef std::unique_ptr<IndexBuffer>			IndexBufferPtr;
	std::vector<VertexBufferPtr>					m_vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBufferPtr>						m_indexBufferArray;		//インデックスバッファの配列。
	std::unique_ptr<btBvhTriangleMeshShape>			m_meshShape;				//メッシュ形状。
	std::unique_ptr<btTriangleIndexVertexArray>		m_stridingMeshInterface;

	//定数
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };

};

