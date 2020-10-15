#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "SkinModelEffect.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//�萔�o�b�t�@������B
		m_cb->Release();
	}
	//���C�g�p�̒萔�o�b�t�@�̉���B
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
	//�����p�̒萔�o�b�t�@�̉���B
	if (m_ambientlightCb != nullptr) {
		m_ambientlightCb->Release();
	}
	if (m_samplerState != nullptr) {
		//�T���v���X�e�[�g������B
		m_samplerState->Release();
	}
}

/// <summary>
/// �����̏�����
/// </summary>
void SkinModel::LoadAmbientLight() {
	CVector3 a_color = LightMaker::GetInstance()->GetAmbientColor();
	m_AmbientLight.Ambient_R = a_color.x;
	m_AmbientLight.Ambient_G = a_color.y;
	m_AmbientLight.Ambient_B = a_color.z;
}

/// <summary>
/// �f�B���N�V�������C�g���X�V����
/// </summary>
void SkinModel::D_LightUpdate() {

	for (int i = 0; i < MAX_DIRECTION_LIGHT; i++) {
		m_light.directionLight.direction[i] = LightMaker::GetInstance()->D_Light_GetDirection(i);
		m_light.directionLight.direction[i].Normalize();	//���K���B
		m_light.directionLight.color[i] = LightMaker::GetInstance()->D_Light_GetColer(i);
		m_light.directionLight.color[i].w = LightMaker::GetInstance()->D_Light_GetSpec(i);
	}

}

/// <summary>
/// �|�C���g���C�g���X�V����
/// </summary>
void SkinModel::P_LightUpdate() {

	for (int i = 0; i < MAX_POINT_LIGHT; i++) {
		m_light.pointLight.position[i] = LightMaker::GetInstance()->P_Light_GetPos(i);
		m_light.pointLight.color[i] = LightMaker::GetInstance()->P_Light_GetColor(i);
		m_light.pointLight.color[i].w = LightMaker::GetInstance()->P_Light_GetRange(i);
	}
}

void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	InitSkeleton(filePath);

	//�萔�o�b�t�@�̍쐬�B
	InitConstantBuffer();
	
	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

	//�f�B���N�V�������C�g�̏������B
	D_LightUpdate();
	//�|�C���g���C�g�̏������B
	P_LightUpdate();

	LoadAmbientLight();

	//SkinModelDataManager���g�p����CMO�t�@�C���̃��[�h�B
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}

void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	//cmo�t�@�C���̊g���q��tks�ɕύX����B
	std::wstring skeletonFilePath = filePath;
	//�����񂩂�.cmo�t�@�C���n�܂�ꏊ�������B
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmo�t�@�C����.tks�ɒu��������B
	skeletonFilePath.replace(pos, 4, L".tks");
	//tks�t�@�C�������[�h����B
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//�X�P���g�����ǂݍ��݂Ɏ��s�����B
		//�A�j���[�V�������Ȃ����f���́A�X�P���g�����s�v�Ȃ̂�
		//�ǂݍ��݂Ɏ��s���邱�Ƃ͂���̂ŁA���O�o�͂����ɂ��Ă����B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tks�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//�쐬����o�b�t�@�̃T�C�Y��sizeof���Z�q�ŋ��߂�B
	int bufferSize = sizeof(SVSConstantBuffer);
	//�ǂ�ȃo�b�t�@���쐬����̂�������bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//�o�b�t�@��16�o�C�g�A���C�����g�ɂȂ��Ă���K�v������B
																//�A���C�����g���ā��o�b�t�@�̃T�C�Y��16�̔{���Ƃ������Ƃł��B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�o�b�t�@���ǂ̂悤�ȃp�C�v���C���Ƀo�C���h���邩���w�肷��B
																//�萔�o�b�t�@�Ƀo�C���h����̂ŁAD3D11_BIND_CONSTANT_BUFFER���w�肷��B
	bufferDesc.CPUAccessFlags = 0;								//CPU �A�N�Z�X�̃t���O�ł��B
																//CPU�A�N�Z�X���s�v�ȏꍇ��0�B
	//�쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);

	//�����āA���C�g�p�̒萔�o�b�t�@���쐬�B
	//�쐬����o�b�t�@�̃T�C�Y��ύX���邾���B
	bufferDesc.ByteWidth = Raundup16(sizeof(SLight));
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);

	//�����p�̒萔�o�b�t�@���쐬�B
	bufferDesc.ByteWidth = Raundup16(sizeof(AmbientLight));
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_ambientlightCb);

}
void SkinModel::InitSamplerState()
{
	//�e�N�X�`���̃T���v�����O���@���w�肷�邽�߂̃T���v���X�e�[�g���쐬�B
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMax�Ǝ������킹�邽�߂̃o�C�A�X�B
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//���s�ړ��s����쐬����B
	transMatrix.MakeTranslation( position );
	//��]�s����쐬����B
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//�g��s����쐬����B
	scaleMatrix.MakeScaling(scale);
	//���[���h�s����쐬����B
	//�g��~��]�~���s�ړ��̏��Ԃŏ�Z����悤�ɁI
	//���Ԃ��ԈႦ���猋�ʂ��ς���B
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//�X�P���g���̍X�V�B
	m_skeleton.Update(m_worldMatrix);
	//���C�g�̍X�V�I
	D_LightUpdate();
	P_LightUpdate();
	//�����̍X�V�I
	LoadAmbientLight();
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix ,EnRenderMode renderMode)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());
	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	auto shadowMap = ShadowMap::GetInstance();

	//�萔�o�b�t�@�̓��e���X�V�B
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	//todo ���C�g�J�����̃r���[�A�v���W�F�N�V�����s��𑗂�B
	vsCb.mLightProj = shadowMap->GetLightProjMatrix();
	vsCb.mLightView = shadowMap->GetLighViewMatrix();
	if (m_isShadowReciever == true) {
		vsCb.isShadowReciever = 1;
	}
	else {
		vsCb.isShadowReciever = 0;
	}
	//�@���}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_normalMapSRV != nullptr) {
		vsCb.isHasNormalMap = true;
	}
	else {
		vsCb.isHasNormalMap = false;
	}
	//�X�y�L�����}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_specMapSRV != nullptr) {
		vsCb.isHasSpecMap = true;
	}
	else {
		vsCb.isHasSpecMap = false;
	}
	//AO�}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_aoMapSRV != nullptr) {
		vsCb.isHasAOMap = true;
	}
	else {
		vsCb.isHasAOMap = false;
	}
	//����߂��e�N�X�`�����g�p���邩�ǂ����̃t���O�𑗂�B
	if (m_kiramekiTextureSRV != nullptr) {
		vsCb.isHasKirameki = true;
	}
	else {
		vsCb.isHasKirameki = false;
	}

	//�c��
	vsCb.mHigh = FRAME_BUFFER_H;
	vsCb.mWide = FRAME_BUFFER_W;

	//�F
	vsCb.emissionColor_R = m_emissionColor.x;
	vsCb.emissionColor_G = m_emissionColor.y;
	vsCb.emissionColor_B = m_emissionColor.z;

	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);

	//���C�g�p�̒萔�o�b�t�@���X�V�B
	m_light.eyePos = g_camera3D.GetPosition();
	m_light.specPow = 1.0f;

	d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);
	d3dDeviceContext->UpdateSubresource(m_ambientlightCb, 0, nullptr, &m_AmbientLight, 0, 0);

	//�萔�o�b�t�@��GPU�ɓ]���B
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);

	//�萔�o�b�t�@���V�F�[�_�[�X���b�g�ɐݒ�B
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_ambientlightCb);
	d3dDeviceContext->PSSetConstantBuffers(3, 1, &m_lightCb);

	//�T���v���X�e�[�g��ݒ�B
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//�G�t�F�N�g�ɃN�G�����s���B
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
			modelMaterial->SetRenderMode(m_renderMode, renderMode);
			});

		if (m_normalMapSRV != nullptr) {
			//�@���}�b�v���ݒ肳��Ă����烌�W�X�^t3�ɐݒ肷��B
			d3dDeviceContext->PSSetShaderResources(3, 1, &m_normalMapSRV);
		}
		if (m_specMapSRV != nullptr) {
			//�X�y�L�����}�b�v���ݒ肳��Ă����烌�W�X�^t4�ɐݒ肷��B
			d3dDeviceContext->PSSetShaderResources(4, 1, &m_specMapSRV);
		}
		if (m_aoMapSRV != nullptr) {
			//AO���ݒ肳��Ă����烌�W�X�^t5�ɐݒ肷��B
			d3dDeviceContext->PSSetShaderResources(5, 1, &m_aoMapSRV);
		}
		if (m_kiramekiTextureSRV != nullptr) {
			//����߂��e�N�X�`�����ݒ肳��Ă����烌�W�X�^t6�ɐݒ肷��B
			d3dDeviceContext->PSSetShaderResources(6, 1, &m_kiramekiTextureSRV);
		}

	//�{�[���s���GPU�ɓ]���B
	m_skeleton.SendBoneMatrixArrayToGPU();

	//�A���x�h�e�N�X�`����ݒ肷��B
	ID3D11ShaderResourceView* SRV = ShadowMap::GetInstance()->GetShadowMapSRV();
	d3dDeviceContext->PSSetShaderResources(0, 1, &m_albedoTextureSRV);
	d3dDeviceContext->PSSetShaderResources(2, 1, &SRV);

	//�`��B
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}