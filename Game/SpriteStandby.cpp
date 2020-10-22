#include "stdafx.h"
#include "SpriteStandby.h"

/// <summary>
/// ���_�o�b�t�@�̏�����
/// </summary>
/// <param name="vertexBuffer">���_�o�b�t�@</param>
/// <param name="w">��</param>
/// <param name="h">����</param>
extern void InitVertexBuffer(ID3D11Buffer*& vertexBuffer, float w, float h) {

	//�����I
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	//���_��ݒ�
	SVertex vertex[4] = {
		//���_1
		{
			-halfW, -halfH, 0.0f, 1.0f, //�|�W�V����
			0.0f, 1.0f, //UV���W
		},
		//���_2
		{
			halfW, -halfH, 0.0f, 1.0f, //�|�W�V����
			1.0f, 1.0f, //UV���W
		},
		//���_3
		{
			-halfW, halfH, 0.0f, 1.0f, //�|�W�V����
			0.0f, 0.0f, //UV���W
		},
		//���_4
		{
			halfW, halfH, 0.0f, 1.0f, //�|�W�V����
			1.0f, 0.0f, //UV���W
		},
	};
	//���_�o�b�t�@���쐬����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd)); //0�ŏ�����
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(vertex); //���_�o�b�t�@�̃T�C�Y��ݒ�
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //���ꂩ��쐬����o�b�t�@�����_�o�b�t�@�ł��邱�Ƃ��w�肷��

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex; //���\�[�X�f�[�^�̃|�C���^���w�肷��

	//���܁`�`�`
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &vertexBuffer);

}

/// <summary>
/// �C���f�b�N�X�o�b�t�@�̏�����
/// </summary>
/// <param name="indexBuffer">�C���f�b�N�X�o�b�t�@</param>
extern void InitIndexBuffer(ID3D11Buffer*& indexBuffer) {

	//���_�ԍ�
	int index[6] = {
		0,1,2, //�O�p�`���
		2,1,3 //�O�p�`���
	};
	//�C���f�b�N�X�o�b�t�@���쐬����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd)); //0�ŏ�����
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index); //�C���f�b�N�X�o�b�t�@�̃T�C�Y��ݒ�
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER; //���ꂩ��쐬����o�b�t�@���C���f�b�N�X�o�b�t�@�ł��邱�Ƃ��w�肷��

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = index; //���\�[�X�f�[�^�̃|�C���^���w�肷��

	//���܂�
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &indexBuffer);

}

/// <summary>
/// �T���v���X�e�[�g�̏�����
/// </summary>
/// <param name="samplerState">�T���v���X�e�[�g</param>
extern void InitSamplerState(ID3D11SamplerState*& samplerState) {

	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//���܁`�`�`
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &samplerState);

}