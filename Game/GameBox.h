#pragma once
class GameBox
{
public:
	typedef std::vector<CVector3>					VertexBuffer;		//���_�o�b�t�@�B
	typedef std::vector<unsigned int>				IndexBuffer;		//�C���f�b�N�X�o�b�t�@�B
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

	void CheckHitRayToPlane(CVector3 startPos, CVector3 endPos,CVector3* boxPos);
	
	CVector3 GetPosition() {
		return m_position;
	}

	/// <summary>
	/// �q�̃{�b�N�X���X�g��ǉ�����
	/// </summary>
	/// <param name="box"></param>
	void SetBox(GameBox* box) {
		m_boxList.push_back(box);
	}

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
	/// �x�N�g���̔�r�p
	/// </summary>
	/// <param name="a">��r�������x�N�g���P</param>
	/// <param name="b">��r�������x�N�g���Q</param>
	/// <returns>false�Ȃ犮�S��v�Atrue�Ȃ�ǂ���1�v�f�Ⴄ</returns>
	bool VectorHikaku(CVector3 a, CVector3 b) {
		bool Flag = false;
		if (fabsf(a.x - b.x) < 0.02f) {
			Flag = true;
		}
		if (fabsf(a.y - b.y) < 0.02f) {
			Flag = true;
		}	
		if (fabsf(a.z - b.z) < 0.02f) {
			Flag = true;
		}
		return Flag;
	}

	void MeshStandBy();
	SkinModel m_model;	//�X�L�����f���B

	CVector3 m_position = CVector3().Zero();
	CQuaternion m_rotation = CQuaternion().Identity();
	CVector3 m_scale = CVector3().One(); //�g�嗦
	
	std::vector<VertexBuffer>						m_vertexBufferArray;		//���_�o�b�t�@�̔z��B
	std::vector<IndexBuffer>						m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��B

	//�����Ȍv�Z
	CVector3 m_N;
	CVector3 m_vPos_0;
	CVector3 m_vPos_1;
	CVector3 m_vPos_2;

	//�q�ɂȂ�{�b�N�X�ǂ�
	std::list<GameBox*> m_boxList;

	//�萔
	const CVector3 BoxDefScale = { 100.0f,100.0f,100.0f };

};

