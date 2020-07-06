#pragma once
#include <array> 
#include "graphics/Shader.h"

class CPhysicsDebugDraw : public btIDebugDraw {

	struct SConstantBuffer {
		CMatrix mView;
		CMatrix mProj;
	};
	int m_debugMode = btIDebugDraw::DBG_NoDebug;
	//ID3D11DeviceContext* m_deviceContext = nullptr;
	//CPrimitive m_primitive;
	Shader m_vs;	//頂点シェーダー。
	Shader m_ps;	//ピクセルシェーダー。
	ID3D11Buffer* m_cb;
	static const int VERTEX_MAX = 100000;
	std::array<CVector4, VERTEX_MAX> m_vertexBuffer;

	int m_numLine = 0;

public:
	void Init();

	void BeginDraw(ID3D11DeviceContext& rc)
	{
		//m_deviceContext = &rc;
		m_numLine = 0;
	}

	void EndDraw();
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) override
	{
	}
	void reportErrorWarning(const char*) override
	{
	}
	void draw3dText(const btVector3&, const char*) override
	{
	}
	void setDebugMode(int debugMode) override
	{
		m_debugMode = debugMode;
	}
	int	getDebugMode() const override
	{
		return m_debugMode;
	}
};
