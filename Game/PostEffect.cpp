#include "stdafx.h"
#include "PostEffect.h"
#include "Game.h"

PostEffect::PostEffect()
{
	//�t���X�N���[���`��̂��߂̎l�p�`�v���~�e�B�u���������B
	InitFullScreenQuadPrimitive();

	//�����������̃u�����h�X�e�[�g���쐬����B
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�Z�b�e�B���O�ŏ���������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	auto device = g_graphicsEngine->GetD3DDevice();

	device->CreateBlendState(&blendDesc, &m_blendState);

	//�V�F�[�_�[
	m_vs.Load("Assets/shader/Blur.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/Blur.fx", "PSMain", Shader::EnType::PS);

}

PostEffect::~PostEffect()
{
	if (m_vertexBuffer != nullptr) {
		m_vertexBuffer->Release();
	}
	if (m_blendState != nullptr) {
		m_blendState->Release();
	}
}


void PostEffect::Init() 
{
	m_farShadow.Init();
	m_dof.Init();
}
void PostEffect::Update()
{
}

void PostEffect::Draw()
{
	//Game::GameMode NowGameMode = Game::GetInstance()->GetGameMode();		//���݂̃Q�[�����[�h���Ăяo��
	Game::GameMode NowGameMode = Game::GameMode::ActionMode;

	if (NowGameMode == Game::CreateMode) {
		//�����ꏊ���Â����鏈���i�N���G�C�g����j
		//m_farShadow.Draw(*this);
	}

	//�u���[���B
	m_bloom.Draw(*this);
	//�h�t�B
	m_dof.Draw(*this);

	//��ʂɃu���[��������
	if (Game::GetInstance() != nullptr) {
		if (Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity > 0.0f) {
			BlurDraw();
		}
	}
}

void PostEffect::InitFullScreenQuadPrimitive()
{
	//���_�o�b�t�@���������B
	SVertex vertex[4] = {
		//���_�P
		{
			//���W�@position[4]
			-1.0f,  -1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 1.0f
		},
		//���_�Q
		{
			//���W�@position[4]
			1.0f, -1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 1.0f
		},
		//���_�R
		{
			//���W�@position[4]
			-1.0f,  1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 0.0f
		},
		//���_�S
		{
			//���W�@position[4]
			1.0f,  1.0f, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 0.0f
		},
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//�\���̂�0�ŏ���������B
	bd.Usage = D3D11_USAGE_DEFAULT;				//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@�B
												//��肠������D3D11_USAGE_DEFAULT�ł悢�B
	bd.ByteWidth = sizeof(vertex);				//���_�o�b�t�@�̃T�C�Y�B���_�̃T�C�Y�~���_���ƂȂ�B
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���ꂩ��쐬����o�b�t�@�����_�o�b�t�@�ł��邱�Ƃ��w�肷��B

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	//���_�o�b�t�@�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
}

void PostEffect::DrawFullScreenQuadPrimitive(ID3D11DeviceContext* deviceContext, Shader& vsShader, Shader& psShader)
{
	//�v���~�e�B�u�̃g�|���W�[�Ƃ��āA�g���C�A���O���X�g���b�v��ݒ肷��B
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	unsigned int vertexSize = sizeof(SVertex);
	unsigned int offset = 0;
	//�P�x���o�p�̃V�F�[�_�[��ݒ肷��B
	deviceContext->VSSetShader(
		(ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0
	);
	deviceContext->PSSetShader(
		(ID3D11PixelShader*)psShader.GetBody(), nullptr, 0
	);
	deviceContext->IASetInputLayout(vsShader.GetInputLayout());

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);
	deviceContext->Draw(4, 0);
}

void PostEffect::BlurDraw() {

	//���C�������_�����O�^�[�Q�b�g���擾�B
	auto mainRT = CGameObjectManager::GetInstance()->GetMainRenderTarget();
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//�K�E�V�A���u���[�̏������Ǝ��s
	if (m_blurInitFlag == false) {
		m_gaussianBlur.Init(CGameObjectManager::GetInstance()->GetMainRenderTarget()->GetRenderTargetSRV(),
			Game::GetInstance()->GetGameGraphicInstance()->m_blurIntensity);
		m_blurInitFlag = true;
	}
	m_gaussianBlur.Execute(*this);

	g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());

	//�{�P�摜�̃A�h���X��t0���W�X�^�ɐݒ肷��B
	auto srv = m_gaussianBlur.GetResultTextureSRV();
	deviceContext->PSSetShaderResources(0, 1, &srv);

	ID3D11BlendState* oldBlendState;
	float oldBlendFactor[4];
	UINT oldMask;
	deviceContext->OMGetBlendState(&oldBlendState, oldBlendFactor, &oldMask);
	//�����������p�̃u�����f�B���O�X�e�[�g��ݒ肷��B
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(m_blendState, blendFactor, 0xffffffff);
	//�t���X�N���[���`��B
	DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_ps);

	//�u�����h�X�e�[�g��߂��B
	deviceContext->OMSetBlendState(oldBlendState, oldBlendFactor, oldMask);
	oldBlendState->Release();

}