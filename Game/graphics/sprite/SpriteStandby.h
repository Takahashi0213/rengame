#pragma once

/// <summary>
/// ���_�o�b�t�@�̏�����
/// </summary>
/// <param name="vertexBuffer">���_�o�b�t�@</param>
/// <param name="w">��</param>
/// <param name="h">����</param>
extern void InitVertexBuffer(ID3D11Buffer*& vertexBuffer, float w, float h);

/// <summary>
/// �C���f�b�N�X�o�b�t�@�̏�����
/// </summary>
/// <param name="indexBuffer">�C���f�b�N�X�o�b�t�@</param>
extern void InitIndexBuffer(ID3D11Buffer*& indexBuffer);

/// <summary>
/// �T���v���X�e�[�g�̏�����
/// </summary>
/// <param name="samplerState">�T���v���X�e�[�g</param>
extern void InitSamplerState(ID3D11SamplerState*& samplerState);

struct SVertex {
	float position[4];		//���_���W
	float uv[2];			//UV���W�B���ꂪ�e�N�X�`�����W
};
