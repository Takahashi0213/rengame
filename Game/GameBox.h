#pragma once
class GameBox
{
public:
	GameBox();
	~GameBox();
	void GameBox_Update();
	void GameBox_Render();

	/// <summary>
	/// ������Ԃ��Z�b�g
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
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
	SkinModel m_model;	//�X�L�����f���B

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦

	typedef std::vector<CVector3>					VertexBuffer;		//���_�o�b�t�@�B
	typedef std::vector<unsigned int>				IndexBuffer;		//�C���f�b�N�X�o�b�t�@�B
	typedef std::unique_ptr<VertexBuffer>			VertexBufferPtr;
	typedef std::unique_ptr<IndexBuffer>			IndexBufferPtr;
	std::vector<VertexBufferPtr>					m_vertexBufferArray;		//���_�o�b�t�@�̔z��B
	std::vector<IndexBufferPtr>						m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��B
	std::unique_ptr<btBvhTriangleMeshShape>			m_meshShape;				//���b�V���`��B
	std::unique_ptr<btTriangleIndexVertexArray>		m_stridingMeshInterface;

	//�萔
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };

};

