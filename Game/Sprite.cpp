#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	//�폜����Ƃ��Ƀ��������������
	if (m_vertexBuffer != NULL) {
		m_vertexBuffer->Release();
	}
	if (m_indexBuffer != NULL) {
		m_indexBuffer->Release();
	}
	if (m_samplerState != NULL) {
		m_samplerState->Release();
	}
	if (m_mainSprite.Texture != NULL) {
		m_mainSprite.Texture->Release();
	}	
}

/// <summary>
/// �������̋��ʏ����B
/// </summary>
void Sprite::InitCommon(float w, float h ,bool cutFlag)
{
	m_mainSprite.Size.x = w;
	m_mainSprite.Size.y = h;
	//���_�o�b�t�@�̏�����
	InitVertexBuffer(m_vertexBuffer, w, h);

	//�����Œ��f
	if (cutFlag == true) {
		return;
	}

	//�C���f�b�N�X�o�b�t�@�̏�����
	InitIndexBuffer(m_indexBuffer);
	//�T���v���X�e�[�g�̏�����
	InitSamplerState(m_samplerState);
	//�V�F�[�_�[�̃��[�h�B
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_ps_X_Cut.Load("Assets/shader/sprite.fx", "PSMain_X_Cut", Shader::EnType::PS);
	m_ps_Y_Cut.Load("Assets/shader/sprite.fx", "PSMain_Y_Cut", Shader::EnType::PS);
	m_ps_Slice9.Load("Assets/shader/sprite.fx", "PSMain_Slice", Shader::EnType::PS);
	m_ps_Mask.Load("Assets/shader/sprite.fx", "PSMain_Mask", Shader::EnType::PS);
	m_ps_Pattern.Load("Assets/shader/sprite.fx", "PSMain_Pattern", Shader::EnType::PS);

	//�萔�o�b�t�@���������B
	InitConstantBuffer();

}

/// <summary>
/// ������
/// </summary>
/// <param name="texFilePath">�t�@�C���p�X</param>
/// <param name="w">��</param>
/// <param name="h">����</param>
void Sprite::Sprite_Init(const wchar_t* texFilePath, float w, float h) {

	InitCommon(w, h);

	//�e�N�X�`�������[�h�B
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),				//D3D�f�o�C�X�B
		texFilePath,				//�ǂݍ��މ摜�f�[�^�̃t�@�C���p�X�B
		0,                          //���͋C�ɂ��Ȃ��Ă悢�B
		D3D11_USAGE_DEFAULT,		//���͋C�ɂ��Ȃ��Ă悢�B
		D3D11_BIND_SHADER_RESOURCE,	//���͋C�ɂ��Ȃ��Ă悢�B
		0,							//���͋C�ɂ��Ȃ��Ă悢�B
		0,							//���͋C�ɂ��Ȃ��Ă悢�B
		false,						//���͋C�ɂ��Ȃ��Ă悢�B
		nullptr,					//���͋C�ɂ��Ȃ��Ă悢�B
		&m_mainSprite.Texture		//�ǂݍ��񂾃e�N�X�`����
									//�A�N�Z�X���邽�߂̃C���^�[�t�F�[�X�̊i�[��B
	);

	m_isInited = true;
}
void Sprite::Sprite_Init(ID3D11ShaderResourceView* srv, float w, float h)
{
	//���ʂ̏������������Ăяo���B
	InitCommon(w, h);
	m_mainSprite.Texture = srv;
	m_mainSprite.Texture->AddRef();	//�Q�ƃJ�E���^�𑝂₷�B
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="pos">���s�ړ�</param>
/// <param name="rot">��]</param>
/// <param name="scale">�g��</param>
/// <param name="pivot">��_</param>
void Sprite::Sprite_Update(const CVector3& pos, const CQuaternion& rot, const CVector3& scale, CVector2 pivot) {

	if (m_isInited == false) {
		//����������Ă��Ȃ�
		return;
	}

	//�s�{�b�g�̌v�Z
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//�摜�̃n�[�t�T�C�Y�����߂�
	CVector2 halfSize = m_mainSprite.Size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_mainSprite.World.Mul(mPivotTrans, mScale);
	m_mainSprite.World.Mul(m_mainSprite.World, mRot);
	m_mainSprite.World.Mul(m_mainSprite.World, mTrans);

}
void Sprite::Sprite_Update() {
	if (m_isInited == false) {
		//����������Ă��Ȃ�
		return;
	}

	//�s�{�b�g�̌v�Z
	CVector2 localPivot = m_mainSprite.Pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//�摜�̃n�[�t�T�C�Y�����߂�
	CVector2 halfSize = m_mainSprite.Size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(m_mainSprite.Position);
	mRot.MakeRotationFromQuaternion(m_mainSprite.Rotation);
	mScale.MakeScaling(m_mainSprite.Scale);
	m_mainSprite.World.Mul(mPivotTrans, mScale);
	m_mainSprite.World.Mul(m_mainSprite.World, mRot);
	m_mainSprite.World.Mul(m_mainSprite.World, mTrans);

}

/// <summary>
/// �`��
/// </summary>
void Sprite::Sprite_Draw() {

	if (m_isInited == false) {
		//����������Ă��Ȃ�
		return;
	}

	unsigned int vertexSize = sizeof(SVertex);	//���_�̃T�C�Y�B
	unsigned int offset = 0;
	g_graphicsEngine->GetD3DDeviceContext()->IASetVertexBuffers(	//���_�o�b�t�@��ݒ�B
		0,					//StartSlot�ԍ��B����0�ł����B
		1,					//�o�b�t�@�̐��B����1�ł����B
		&m_vertexBuffer,	//���_�o�b�t�@�B
		&vertexSize,		//���_�̃T�C�Y�B
		&offset				//�C�ɂ��Ȃ��Ă悢�B
	);
	g_graphicsEngine->GetD3DDeviceContext()->IASetIndexBuffer(	//�C���f�b�N�X�o�b�t�@��ݒ�B
		m_indexBuffer,			//�C���f�b�N�X�o�b�t�@�B
		DXGI_FORMAT_R32_UINT,	//�C���f�b�N�X�̃t�H�[�}�b�g�B
								//�����32bit�Ȃ̂ŁADXGI_FORMAT_R32_UINT�ł����B
		0						//�I�t�Z�b�g0�ł����B
	);

	//�e�N�X�`����ݒ�B
	g_graphicsEngine->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &m_mainSprite.Texture);
	//�T���v���X�e�[�g��ݒ�B
	g_graphicsEngine->GetD3DDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

	//���[���h�r���[�v���W�F�N�V�����s����쐬�B
	ConstantBuffer cb;
	cb.WVP = m_mainSprite.World;
	cb.WVP.Mul(cb.WVP, g_camera2D.GetViewMatrix());
	cb.WVP.Mul(cb.WVP, g_camera2D.GetProjectionMatrix());
	cb.mulColor = m_mainSprite.MulColor;
	cb.cut_line = m_cut_UV;
	cb.slice_pattern = m_slicePattern;
	cb.nowPattern = m_nowPattern;

	g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_cb, 0, NULL, &cb, 0, 0);
	g_graphicsEngine->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m_cb);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetConstantBuffers(0, 1, &m_cb);

	g_graphicsEngine->GetD3DDeviceContext()->IASetInputLayout(m_vs.GetInputLayout());
	g_graphicsEngine->GetD3DDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);

	//�X�e�[�g�ɂ����PS��ύX
	switch (m_renderMode)
	{
	case Normal:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
		break;
	case X_Cut:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps_X_Cut.GetBody(), NULL, 0);
		break;
	case Y_Cut:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps_Y_Cut.GetBody(), NULL, 0);
		break;
	case Slice9:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps_Slice9.GetBody(), NULL, 0);
		break;
	case Mask:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps_Mask.GetBody(), NULL, 0);
		break;
	case Pattern:
		g_graphicsEngine->GetD3DDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps_Pattern.GetBody(), NULL, 0);
		break;
	}
	//�v���~�e�B�u�̃g�|���W�[��
	//�g���C�A���O���X�g���b�v��ݒ肷��B
	g_graphicsEngine->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_graphicsEngine->GetD3DDeviceContext()->DrawIndexed(	//�`�施�߁B
		6,				//�C���f�b�N�X���B
		0,				//�J�n�C���f�b�N�X�ԍ��B0�ł����B
		0				//�J�n���_�ԍ��B0�ł����B
	);

}

/// <summary>
/// �萔�o�b�t�@�̏�����
/// </summary>
void Sprite::InitConstantBuffer() {

	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_cb);

}