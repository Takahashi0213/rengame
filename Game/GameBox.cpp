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

	//ベクトルを計算
	CVector3 v1 = vPos_1 - vPos_0;
	CVector3 v2 = vPos_2 - vPos_0;
	CVector3 v3 = CVector3().Zero();
	
	N.Cross(v2, v1);
	N.Normalize();	//法線

}
GameBox::GameBox()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/box.cmo", enFbxUpAxisY);
	m_scale = BoxDefScale;
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//メッシュ
	MeshStandBy();

}


GameBox::~GameBox()
{


}

/// <summary>
/// 更新
/// </summary>
void GameBox::GameBox_Update() {

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	//シャドウキャスターを登録。
	ShadowMap::GetInstance()->RegistShadowCaster(&m_model);

}

/// <summary>
/// 描画
/// </summary>
void GameBox::GameBox_Render() {
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void GameBox::GameBoxUpdate_Colli() {

	if (m_colli_InitFlag == false) {

		////コライダーを作成。
		//m_meshColli.CreateFromSkinModel(m_model, &m_World);
		////剛体の情報を作成。
		//RigidBodyInfo rbInfo;
		//rbInfo.mass = 5.0f;		//質量。
		//rbInfo.pos = m_position;	//座標。
		//rbInfo.rot = m_rotation;	//回転。
		//rbInfo.collider = &m_meshColli;	//形状。
		////rbInfo.localInteria = { 1.0f, 1.0f, 1.0f };
		////剛体を作成。
		//m_rb.Create(rbInfo);
		////剛体を物理ワールドに追加。
		//PhysicsWorld pw = Game::GetInstance()->GetPhysicsWorld();
		//pw.AddRigidBody(m_rb);

		m_colli_InitFlag = true;
	}

	////物理エンジンで計算された座標を反映する。
	//btTransform& trans = m_rb.GetBody()->getWorldTransform();
	//m_position.Set(trans.getOrigin());
	//CQuaternion qRot;
	//qRot.Set(trans.getRotation());

}

/// <summary>
/// レイと箱の面が衝突しているか調べる処理
/// </summary>
/// <param name="startPos">始点</param>
/// <param name="endPos">終点</param>
bool GameBox::CheckHitRayToPlane(CVector3 startPos, CVector3 endPos, CVector3* boxPos, CVector3& box_N, CVector3& plane_scale) {

	m_N = CVector3::Zero();

	//線分を計算
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
		//三角形の数を調べる。
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

			//内積を求める
			float N1 = (v1.x * N.x) + (v1.y * N.y) + (v1.z * N.z);
			float N2 = (v2.x * N.x) + (v2.y * N.y) + (v2.z * N.z);
			
			if (N1 < 0 && N2 > 0) {

				//交点を求める
				float N_ratio = fabsf(N1) / (fabsf(N1) + fabsf(N2));		//射影の比率
			
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

				//内積を計算
				v1.Normalize();
				v2.Normalize();
				v3.Normalize();
				N1 = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
				N2 = (v1.x * v3.x) + (v1.y * v3.y) + (v1.z * v3.z);

				//どちらも正の数？？？？？
				if (N1 > 0 && N2 > 0 && (m_N.x == 0.0f && m_N.y == 0.0f && m_N.z == 0.0f)) {
					//衝突しているので衝突面の座標と法線を保存
					m_N = N;
					box_N = N;			//これは返す用の法線
					m_vPos_0 = vPos_0;
					m_vPos_1 = vPos_1;
					m_vPos_2 = vPos_2;

					int polyNo_Yobi = polyNo;

					//再検査
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

						//法線が同じならひっかかる場所
						if (m_N.Dot(N) > 0.998f && m_N.Dot(N) < 1.01f && polyNo2 != polyNo_Yobi) {

							//座標を参照渡しで返す
							boxPos[0] = m_vPos_0;
							boxPos[1] = m_vPos_1;
							boxPos[2] = m_vPos_2;

							CVector3 m_vPos_3;
							bool GetFlag = false;

							//vPos_0がさっき渡した座標全てと違うかチェック
							if (VectorHikaku(m_vPos_0, vPos_0) == true && VectorHikaku(m_vPos_1, vPos_0) == true && VectorHikaku(m_vPos_2, vPos_0) == true) {
								m_vPos_3 = vPos_0;	//どことも一致しないのでお前
								GetFlag = true;
							}
							//vPos_1がさっき渡した座標全てと違うかチェック
							if (VectorHikaku(m_vPos_0, vPos_1) == true && VectorHikaku(m_vPos_1, vPos_1) == true && VectorHikaku(m_vPos_2, vPos_1) == true) {
								m_vPos_3 = vPos_1;	//どことも一致しないのでお前
								GetFlag = true;
							}
							//vPos_2がさっき渡した座標全てと違うかチェック
							if (VectorHikaku(m_vPos_0, vPos_2) == true && VectorHikaku(m_vPos_1, vPos_2) == true && VectorHikaku(m_vPos_2, vPos_2) == true) {
								m_vPos_3 = vPos_2;	//どことも一致しないのでお前
								GetFlag = true;
							}

							//フラグチェック
							if (GetFlag == false) {
								std::abort(); //おかしいのでクラッシュ
							}

							boxPos[3] = m_vPos_3;

							//面の大きさを計算す～る
							CVector3 vMax, vMin;
							vMax = boxPos[0];
							vMax.Max(boxPos[1]);
							vMax.Max(boxPos[2]);

							vMin = boxPos[0];
							vMin.Min(boxPos[1]);
							vMin.Min(boxPos[2]);
							
							plane_scale = vMax - vMin;
							
							//衝突した。
							return true;
						}

					}

				}
			}

		}
	}
	//何ともぶつからなかった。
	return false;

}

/// <summary>
/// バッファの計算をする
/// </summary>
void GameBox::MeshStandBy() {

	m_model.FindMesh([&](const auto& mesh) {

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
}
