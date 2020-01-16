#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender()
{
	//�X�L�����f���T�|�[�^�[�ɃA�h���X��n���Ă���
	m_skinModelSupporter.SkinModelRenderSetting(this);
}


SkinModelRender::~SkinModelRender()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="filePath">���f���̃t�@�C���p�X</param>
void SkinModelRender::Model_Init(const wchar_t* filePath) {

	std::vector<VertexBuffer> m_vertexBufferArray;		//���_�o�b�t�@�̔z��B
	std::vector<IndexBuffer> m_indexBufferArray;		//�C���f�b�N�X�o�b�t�@�̔z��B

	m_skinModel.Init(filePath);

	//�|���S�����X�g�̍쐬
	m_skinModel.FindMesh([&](const auto& mesh) {

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

	//Vector�փZ�b�g

	//float X = m_vertexBufferArray[0][m_indexBufferArray[0][0]].x;

	for (int i = 0; i < m_indexBufferArray.size(); i++) {
		
		for (int ii = 0; ii < m_indexBufferArray[i].size(); ii += 3) {

			Polygon poly;

			for (int iii = 0; iii < 3; iii++) {
				poly.vertPos[iii].x = m_vertexBufferArray[i][m_indexBufferArray[i][ii + iii]].x;
				poly.vertPos[iii].y = m_vertexBufferArray[i][m_indexBufferArray[i][ii + iii]].y;
				poly.vertPos[iii].z = m_vertexBufferArray[i][m_indexBufferArray[i][ii + iii]].z;
			}

			//�x�N�g�����v�Z
			CVector3 v1 = poly.vertPos[1] - poly.vertPos[0];
			CVector3 v2 = poly.vertPos[2] - poly.vertPos[0];
			CVector3 N;
			N.Cross(v2, v1);
			N.Normalize();	//�@��
			poly.normal = N;

			m_polygonList.push_back(poly);
		}

	}

	Update(); //�����ɏ����Ӗ�����̂��ȁc�Ƃ肠��������
}

/// <summary>
/// ����������
/// </summary>
/// <param name="filePath">���f���̃t�@�C���p�X</param>
/// <param name="pos">�������W</param>
/// <param name="rot">������]</param>
/// <param name="scl">�����g�嗦</param>
void SkinModelRender::Model_Init(const wchar_t* filePath, CVector3 pos, CQuaternion rot, CVector3 scl) {
	m_skinModel.Init(filePath);
	m_position = pos;
	m_rotation = rot;
	m_scale = scl;
	Update();
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
void SkinModelRender::Update() {
	m_skinModelSupporter.SkinModelSupporterUpdate();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

/// <summary>
/// �`��
/// </summary>
void SkinModelRender::Render() {
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}