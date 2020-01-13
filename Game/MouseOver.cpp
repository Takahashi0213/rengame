#include "stdafx.h"
#include "MouseOver.h"

void MouseOver::GetTrianglePositionAndNormal(
	int polyNo,
	IndexBuffer& indexBuffer,
	VertexBuffer& vertexBuffer,
	CMatrix& mWorld,
	CMatrix& mRot,
	CVector3& vPos_0,
	CVector3& vPos_1,
	CVector3& vPos_2,
	CVector3& N)
{
	int vertNo_00 = indexBuffer[polyNo * 3];
	int vertNo_01 = indexBuffer[polyNo * 3 + 1];
	int vertNo_02 = indexBuffer[polyNo * 3 + 2];

	vPos_0 = vertexBuffer[vertNo_00];
	vPos_1 = vertexBuffer[vertNo_01];
	vPos_2 = vertexBuffer[vertNo_02];

	mWorld.Mul(vPos_0);
	mWorld.Mul(vPos_1);
	mWorld.Mul(vPos_2);

	//�x�N�g�����v�Z
	CVector3 v1 = vPos_1 - vPos_0;
	CVector3 v2 = vPos_2 - vPos_0;
	CVector3 v3 = CVector3().Zero();

	N.Cross(v2, v1);
	N.Normalize();	//�@��

}

bool MouseOver::MouseOverCheck(SkinModelRender* smr , CVector3 pos , CQuaternion rot,CVector3 scl) {

	//���b�V��
	if (m_model == nullptr) {
		m_model = smr->GetModel();
		MeshStandBy();
	}

	//�܂��͕ۑ����ăo�b�t�@�̌v�Z������
	bool CheckFlag = false;
	m_model = smr->GetModel();
	m_position = pos;
	m_rotation = rot;
	m_scale = scl;

	CheckFlag = Check();
	return CheckFlag;
}

bool MouseOver::MouseOverCheck(SkinModel* sm, CVector3 pos, CQuaternion rot, CVector3 scl) {

	//���b�V��
	if (m_model == nullptr) {
		m_model = sm;
		MeshStandBy();
	}

	//�܂��͕ۑ����ăo�b�t�@�̌v�Z������
	bool CheckFlag = false;
	m_model = sm;
	m_position = pos;
	m_rotation = rot;
	m_scale = scl;

	CheckFlag = Check();
	return CheckFlag;

}

bool MouseOver::Check() {

	bool CheckFlag = false;

	//�������v�Z
	CVector3 Ray = MouseSupporter::GetInstance()->GetMousePos_3D() - g_camera3D.GetPosition();
	CVector3 Ray_n = Ray;
	Ray_n.Normalize();

	CMatrix mTrans, mRot, mScale, mWorld;
	mTrans.MakeTranslation(m_position);
	mRot.MakeRotationFromQuaternion(m_rotation);
	mScale.MakeScaling(m_scale);
	mWorld.Mul(mScale, mRot);
	mWorld.Mul(mWorld, mTrans);
	for (int i = 0; i < m_indexBufferArray.size(); i++) {
		auto& indexBuffer = m_indexBufferArray[i];
		auto& vertexBuffer = m_vertexBufferArray[i];
		//�O�p�`�̐��𒲂ׂ�B
		int numPoly = (int)indexBuffer.size() / 3;
		for (int polyNo = 0; polyNo < numPoly; polyNo++) {

			CVector3 vPos_0, vPos_1, vPos_2, N;
			GetTrianglePositionAndNormal(
				polyNo,
				indexBuffer,
				vertexBuffer,
				mWorld,
				mRot,
				vPos_0,
				vPos_1,
				vPos_2,
				N
			);

			CVector3 v1 = vPos_0 - g_camera3D.GetPosition(); //startPos
			CVector3 v2 = vPos_0 - MouseSupporter::GetInstance()->GetMousePos_3D();	//endPos

			//���ς����߂�
			float N1 = (v1.x * N.x) + (v1.y * N.y) + (v1.z * N.z);
			float N2 = (v2.x * N.x) + (v2.y * N.y) + (v2.z * N.z);

			if (N1 < 0 && N2 > 0) {

				//��_�����߂�
				float N_ratio = fabsf(N1) / (fabsf(N1) + fabsf(N2));		//�ˉe�̔䗦

				CVector3 CrossPoint = (g_camera3D.GetPosition() * (1.0f - N_ratio)) + (MouseSupporter::GetInstance()->GetMousePos_3D() * N_ratio);
				v1 = CrossPoint - vPos_0;
				CVector3 v1_ = vPos_1 - vPos_0;
				v1.Cross(v1_);

				v2 = CrossPoint - vPos_1;
				CVector3 v2_ = vPos_2 - vPos_1;
				v2.Cross(v2_);

				CVector3 v3 = CrossPoint - vPos_2;
				CVector3 v3_ = vPos_0 - vPos_2;
				v3.Cross(v3_);

				//���ς��v�Z
				v1.Normalize();
				v2.Normalize();
				v3.Normalize();
				N1 = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
				N2 = (v1.x * v3.x) + (v1.y * v3.y) + (v1.z * v3.z);

				//�ǂ�������̐��H�H�H�H�H
				if (N1 > 0 && N2 > 0 /* && (m_N.x == 0.0f && m_N.y == 0.0f && m_N.z == 0.0f)*/) {
					//�Փ˂��Ă���B
					CheckFlag = true;
				}
			}

		}
	}

	return CheckFlag;

}

/// <summary>
/// �o�b�t�@�̌v�Z������
/// </summary>
void MouseOver::MeshStandBy() {

	m_model->FindMesh([&](const auto& mesh) {

		ID3D11DeviceContext* deviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//���_�o�b�t�@���쐬�B
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			//VRAM��̒��_�o�b�t�@�ɃA�N�Z�X�ł���悤�ɂ���B
			HRESULT hr = deviceContext->Map(mesh->vertexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			if (FAILED(hr)) {
				return;
			}
			D3D11_BUFFER_DESC bufferDesc;
			mesh->vertexBuffer->GetDesc(&bufferDesc);
			int vertexCount = bufferDesc.ByteWidth / mesh->vertexStride;
			char* pData = (char*)subresource.pData;
			VertexBuffer vertexBuffer;
			CVector3 pos;
			for (int i = 0; i < vertexCount; i++) {
				pos = *((CVector3*)pData);

				vertexBuffer.push_back(pos);
				//���̒��_�ցB
				pData += mesh->vertexStride;
			}
			//���_�o�b�t�@���A�����b�N
			deviceContext->Unmap(mesh->vertexBuffer.Get(), 0);
			m_vertexBufferArray.push_back(vertexBuffer);
		}
		//�C���f�b�N�X�o�b�t�@���쐬�B
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			//�C���f�b�N�X�o�b�t�@�����b�N�B
			HRESULT hr = deviceContext->Map(mesh->indexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			if (FAILED(hr)) {
				return;
			}
			D3D11_BUFFER_DESC bufferDesc;
			mesh->indexBuffer->GetDesc(&bufferDesc);
			//@todo cmo�t�@�C���̓C���f�b�N�X�o�b�t�@�̃T�C�Y��2byte�Œ�B
			IndexBuffer indexBuffer;
			int stride = 2;
			int indexCount = bufferDesc.ByteWidth / stride;
			unsigned short* pIndex = (unsigned short*)subresource.pData;
			for (int i = 0; i < indexCount; i++) {
				indexBuffer.push_back(pIndex[i]);
			}
			//�C���f�b�N�X�o�b�t�@���A�����b�N�B
			deviceContext->Unmap(mesh->indexBuffer.Get(), 0);
			m_indexBufferArray.push_back(indexBuffer);
		}

		});
}
