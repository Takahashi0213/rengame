/*!
* @brief	�R���W�����Ȃǂ̃f�o�b�O�\�������B
*/

#include "stdafx.h"
#include "PhysicsDebugDraw.h"

void CPhysicsDebugDraw::Init()
{

	//���C���X�g���b�v�̃e�X�g�B
	//m_primitive.Create(
	//	D3D_PRIMITIVE_TOPOLOGY_LINELIST,
	//	static_cast<int>(m_vertexBuffer.size()),
	//	sizeof(CVector4),
	//	&m_vertexBuffer[0],
	//	0,
	//	CIndexBuffer::enIndexType_32,
	//	nullptr
	//);

	m_vs.Load("Assets/shader/linePrimitive.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/linePrimitive.fx", "PSMain", Shader::EnType::PS);
	//m_cb.Create(nullptr, sizeof(SConstantBuffer));

	//ConstantBuffer�p�̃o�b�t�@��`���쐬����B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = (((sizeof(SConstantBuffer) - 1) / 16) + 1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);

	//�@���_�o�b�t�@��ݒ肵�܂��傤
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = static_cast<int>(m_vertexBuffer.size()) * sizeof(CVector4);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &m_vertexBuffer[0];
	HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer_);


}
void CPhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	int baseIndex = m_numLine * 2;
	m_vertexBuffer[baseIndex].Set(CVector3(from.x(), from.y(), from.z()));
	m_vertexBuffer[baseIndex + 1].Set(CVector3(to.x(), to.y(), to.z()));
	m_numLine++;
}
void CPhysicsDebugDraw::EndDraw()
{
	//�萔�o�b�t�@�̍X�V�B
	SConstantBuffer cb;
	cb.mView = g_camera3D.GetViewMatrix();
	cb.mProj = g_camera3D.GetProjectionMatrix();
	//g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_cb, &cb);
	g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);

	g_graphicsEngine->GetD3DDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
	g_graphicsEngine->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m_cb);

	//���̓��C�A�E�g��ݒ�B
	g_graphicsEngine->GetD3DDeviceContext()->IASetInputLayout(m_vs.GetInputLayout());
	//m_primitive.Draw(*g_graphicsEngine->GetD3DDeviceContext(), m_numLine * 2);

	//�A���C���������̒��_�o�b�t�@�̓��e��Graphic�������ɃR�s�[
	g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_vertexBuffer_, 0, NULL, &m_vertexBuffer[0], 0, 0);
	//g_graphicsEngine->GetD3DDeviceContext()->IASetVertexBuffers(m_vertexBuffer_);
	UINT offset = 0;
	UINT stride = sizeof(CVector4);
	g_graphicsEngine->GetD3DDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer_, &stride, &offset);

	//���G����
	g_graphicsEngine->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	g_graphicsEngine->GetD3DDeviceContext()->Draw(	//�`�施�߁B
		m_numLine * 2,				//���_���B
		0
	);
}

