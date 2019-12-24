#include "stdafx.h"
#include "GameBox.h"
#include "Game.h"

void GameBox::GetTrianglePositionAndNormal(
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
GameBox::GameBox()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/box.cmo", enFbxUpAxisY);
	m_scale = BoxDefScale;
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//���b�V��
	MeshStandBy();

}


GameBox::~GameBox()
{


}

/// <summary>
/// �X�V
/// </summary>
void GameBox::GameBox_Update() {

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//�V���h�E�L���X�^�[��o�^�B
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);

}

/// <summary>
/// �`��
/// </summary>
void GameBox::GameBox_Render() {
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void GameBox::GameBoxUpdate_Colli() {

	if (m_colli_InitFlag == false) {

		////�R���C�_�[���쐬�B
		//m_meshColli.CreateFromSkinModel(m_model, &m_World);
		////���̂̏����쐬�B
		//RigidBodyInfo rbInfo;
		//rbInfo.mass = 5.0f;		//���ʁB
		//rbInfo.pos = m_position;	//���W�B
		//rbInfo.rot = m_rotation;	//��]�B
		//rbInfo.collider = &m_meshColli;	//�`��B
		////rbInfo.localInteria = { 1.0f, 1.0f, 1.0f };
		////���̂��쐬�B
		//m_rb.Create(rbInfo);
		////���̂𕨗����[���h�ɒǉ��B
		//PhysicsWorld pw = Game::GetInstance()->GetPhysicsWorld();
		//pw.AddRigidBody(m_rb);

		m_colli_InitFlag = true;
	}

	////�����G���W���Ōv�Z���ꂽ���W�𔽉f����B
	//btTransform& trans = m_rb.GetBody()->getWorldTransform();
	//m_position.Set(trans.getOrigin());
	//CQuaternion qRot;
	//qRot.Set(trans.getRotation());

}

/// <summary>
/// ���C�Ɣ��̖ʂ��Փ˂��Ă��邩���ׂ鏈��
/// </summary>
/// <param name="startPos">�n�_</param>
/// <param name="endPos">�I�_</param>
bool GameBox::CheckHitRayToPlane(CVector3 startPos, CVector3 endPos, CVector3* boxPos, CVector3& box_N, CVector3& plane_scale) {

	m_N = CVector3::Zero();

	//�������v�Z
	CVector3 Ray = endPos - startPos;
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
			
			m_World = mWorld;
			CVector3 v1 = vPos_0 - startPos;
			CVector3 v2 = vPos_0 - endPos;

			//���ς����߂�
			float N1 = (v1.x * N.x) + (v1.y * N.y) + (v1.z * N.z);
			float N2 = (v2.x * N.x) + (v2.y * N.y) + (v2.z * N.z);
			
			if (N1 < 0 && N2 > 0) {

				//��_�����߂�
				float N_ratio = fabsf(N1) / (fabsf(N1) + fabsf(N2));		//�ˉe�̔䗦
			
				CVector3 CrossPoint = (startPos * (1.0f - N_ratio)) + (endPos * N_ratio);
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
				if (N1 > 0 && N2 > 0 && (m_N.x == 0.0f && m_N.y == 0.0f && m_N.z == 0.0f)) {
					//�Փ˂��Ă���̂ŏՓ˖ʂ̍��W�Ɩ@����ۑ�
					m_N = N;
					box_N = N;			//����͕Ԃ��p�̖@��
					m_vPos_0 = vPos_0;
					m_vPos_1 = vPos_1;
					m_vPos_2 = vPos_2;

					int polyNo_Yobi = polyNo;

					//�Č���
					for (int polyNo2 = 0; polyNo2 < numPoly; polyNo2++) {

						CVector3 vPos_0, vPos_1, vPos_2, N;

						GetTrianglePositionAndNormal(
							polyNo2,
							indexBuffer,
							vertexBuffer,
							mWorld,
							mRot,
							vPos_0,
							vPos_1,
							vPos_2,
							N);

						//�@���������Ȃ�Ђ�������ꏊ
						if (m_N.Dot(N) > 0.998f && m_N.Dot(N) < 1.01f && polyNo2 != polyNo_Yobi) {

							//���W���Q�Ɠn���ŕԂ�
							boxPos[0] = m_vPos_0;
							boxPos[1] = m_vPos_1;
							boxPos[2] = m_vPos_2;

							CVector3 m_vPos_3;
							bool GetFlag = false;

							//vPos_0���������n�������W�S�ĂƈႤ���`�F�b�N
							if (VectorHikaku(m_vPos_0, vPos_0) == true && VectorHikaku(m_vPos_1, vPos_0) == true && VectorHikaku(m_vPos_2, vPos_0) == true) {
								m_vPos_3 = vPos_0;	//�ǂ��Ƃ���v���Ȃ��̂ł��O
								GetFlag = true;
							}
							//vPos_1���������n�������W�S�ĂƈႤ���`�F�b�N
							if (VectorHikaku(m_vPos_0, vPos_1) == true && VectorHikaku(m_vPos_1, vPos_1) == true && VectorHikaku(m_vPos_2, vPos_1) == true) {
								m_vPos_3 = vPos_1;	//�ǂ��Ƃ���v���Ȃ��̂ł��O
								GetFlag = true;
							}
							//vPos_2���������n�������W�S�ĂƈႤ���`�F�b�N
							if (VectorHikaku(m_vPos_0, vPos_2) == true && VectorHikaku(m_vPos_1, vPos_2) == true && VectorHikaku(m_vPos_2, vPos_2) == true) {
								m_vPos_3 = vPos_2;	//�ǂ��Ƃ���v���Ȃ��̂ł��O
								GetFlag = true;
							}

							//�t���O�`�F�b�N
							if (GetFlag == false) {
								std::abort(); //���������̂ŃN���b�V��
							}

							boxPos[3] = m_vPos_3;

							//�ʂ̑傫�����v�Z���`��
							CVector3 vMax, vMin;
							vMax = boxPos[0];
							vMax.Max(boxPos[1]);
							vMax.Max(boxPos[2]);

							vMin = boxPos[0];
							vMin.Min(boxPos[1]);
							vMin.Min(boxPos[2]);
							
							plane_scale = vMax - vMin;
							
							//�Փ˂����B
							return true;
						}

					}

				}
			}

		}
	}
	//���Ƃ��Ԃ���Ȃ������B
	return false;

}

/// <summary>
/// �o�b�t�@�̌v�Z������
/// </summary>
void GameBox::MeshStandBy() {

	m_model.FindMesh([&](const auto& mesh) {

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
