#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender()
{
	//スキンモデルサポーターにアドレスを渡しておく
	m_skinModelSupporter.SkinModelRenderSetting(this);
}


SkinModelRender::~SkinModelRender()
{
}

/// <summary>
/// 初期化する
/// </summary>
/// <param name="filePath">モデルのファイルパス</param>
void SkinModelRender::Model_Init(const wchar_t* filePath) {

	std::vector<VertexBuffer> m_vertexBufferArray;		//頂点バッファの配列。
	std::vector<IndexBuffer> m_indexBufferArray;		//インデックスバッファの配列。

	m_skinModel.Init(filePath);

	//ポリゴンリストの作成
	m_skinModel.FindMesh([&](const auto& mesh) {

		ID3D11DeviceContext* deviceContext = g_graphicsEngine->GetD3DDeviceContext();
		//頂点バッファを作成。
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			//VRAM上の頂点バッファにアクセスできるようにする。
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
				//次の頂点へ。
				pData += mesh->vertexStride;
			}
			//頂点バッファをアンロック
			deviceContext->Unmap(mesh->vertexBuffer.Get(), 0);
			m_vertexBufferArray.push_back(vertexBuffer);
		}
		//インデックスバッファを作成。
		{
			D3D11_MAPPED_SUBRESOURCE subresource;
			//インデックスバッファをロック。
			HRESULT hr = deviceContext->Map(mesh->indexBuffer.Get(), 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &subresource);
			if (FAILED(hr)) {
				return;
			}
			D3D11_BUFFER_DESC bufferDesc;
			mesh->indexBuffer->GetDesc(&bufferDesc);
			//@todo cmoファイルはインデックスバッファのサイズは2byte固定。
			IndexBuffer indexBuffer;
			int stride = 2;
			int indexCount = bufferDesc.ByteWidth / stride;
			unsigned short* pIndex = (unsigned short*)subresource.pData;
			for (int i = 0; i < indexCount; i++) {
				indexBuffer.push_back(pIndex[i]);
			}
			//インデックスバッファをアンロック。
			deviceContext->Unmap(mesh->indexBuffer.Get(), 0);
			m_indexBufferArray.push_back(indexBuffer);
		}

		});

	//Vectorへセット

	//float X = m_vertexBufferArray[0][m_indexBufferArray[0][0]].x;

	for (int i = 0; i < m_indexBufferArray.size(); i++) {
		
		for (int ii = 0; ii < m_indexBufferArray[i].size(); ii += 3) {

			Polygon poly;

			for (int iii = 0; iii < 3; iii++) {
				poly.vertPos[iii].x = m_vertexBufferArray[i][m_indexBufferArray[i][ii + iii]].x;
				poly.vertPos[iii].y = m_vertexBufferArray[i][m_indexBufferArray[i][ii + iii]].y;
				poly.vertPos[iii].z = m_vertexBufferArray[i][m_indexBufferArray[i][ii + iii]].z;
			}

			//ベクトルを計算
			CVector3 v1 = poly.vertPos[1] - poly.vertPos[0];
			CVector3 v2 = poly.vertPos[2] - poly.vertPos[0];
			CVector3 N;
			N.Cross(v2, v1);
			N.Normalize();	//法線
			poly.normal = N;

			m_polygonList.push_back(poly);
		}

	}

	Update(); //ここに書く意味あるのかな…とりあえず書く
}

/// <summary>
/// 初期化する
/// </summary>
/// <param name="filePath">モデルのファイルパス</param>
/// <param name="pos">初期座標</param>
/// <param name="rot">初期回転</param>
/// <param name="scl">初期拡大率</param>
void SkinModelRender::Model_Init(const wchar_t* filePath, CVector3 pos, CQuaternion rot, CVector3 scl) {
	m_skinModel.Init(filePath);
	m_position = pos;
	m_rotation = rot;
	m_scale = scl;
	Update();
}

/// <summary>
/// アップデート
/// </summary>
void SkinModelRender::Update() {
	m_skinModelSupporter.SkinModelSupporterUpdate();
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

/// <summary>
/// 描画
/// </summary>
void SkinModelRender::Render() {
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}