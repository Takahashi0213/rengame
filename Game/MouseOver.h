#pragma once

/// <summary>
/// �}�E�X�I�[�o�[�`�F�b�N����
/// </summary>
class MouseOver
{
public:
	typedef std::vector<CVector3>					VertexBuffer;		//���_�o�b�t�@�B
	typedef std::vector<unsigned int>				IndexBuffer;		//�C���f�b�N�X�o�b�t�@�B

	/// <summary>
	/// �}�E�X���W���`�F�b�N���Ă����ɔ���Ă邩�`�F�[�[�[�b�N�I
	/// </summary>
	/// <param name="smr">�X�L�����f�������_�[</param>
	/// <returns>���ʁitrue�Ȃ�}�E�X�J�[�\���͏Փ˂��Ă���]�C�j</returns>
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

	//�ꎞ�ۑ�
	SkinModel* m_model = nullptr;
	CVector3 m_position;
	CQuaternion m_rotation;
	CVector3 m_scale;

	std::vector<VertexBuffer>						m_vertexBufferArray;		//���_�o�b�t�@�̔z��B
	std::vector<IndexBuffer>						m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��B

};

