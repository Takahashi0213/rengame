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

	m_vs.Load("shader/linePrimitive.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("shader/linePrimitive.fx", "PSMain", Shader::EnType::PS);
	//m_cb.Create(nullptr, sizeof(SConstantBuffer));
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

	//���G����
	g_graphicsEngine->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_graphicsEngine->GetD3DDeviceContext()->DrawIndexed(	//�`�施�߁B
		m_numLine * 2,				//�C���f�b�N�X���B
		0,							//�J�n�C���f�b�N�X�ԍ��B0�ł����B
		0							//�J�n���_�ԍ��B0�ł����B
	);
}

