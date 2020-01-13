#pragma once

/// <summary>
/// マウスオーバーチェックくん
/// </summary>
class MouseOver
{
public:
	typedef std::vector<CVector3>					VertexBuffer;		//頂点バッファ。
	typedef std::vector<unsigned int>				IndexBuffer;		//インデックスバッファ。

	/// <summary>
	/// マウス座標をチェックしてこいつに被ってるかチェーーーック！
	/// </summary>
	/// <param name="smr">スキンモデルレンダー</param>
	/// <returns>結果（trueならマウスカーソルは衝突しているゾイ）</returns>
	bool MouseOverCheck(SkinModelRender* smr, CVector3 pos, CQuaternion rot, CVector3 scl);
	bool MouseOverCheck(SkinModel* sm, CVector3 pos, CQuaternion rot, CVector3 scl);

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
	void MeshStandBy();
	bool Check();

	//一時保存
	SkinModel* m_model = nullptr;
	CVector3 m_position;
	CQuaternion m_rotation;
	CVector3 m_scale;

	std::vector<VertexBuffer>						m_vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBuffer>						m_indexBufferArray;		//インデックスバッファの配列。

};

