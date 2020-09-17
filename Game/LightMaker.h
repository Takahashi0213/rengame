#pragma once
#include "system/CGameObjectManager.h"

#include "DirectionLight.h"
#include "PointLight.h"

//IGameObject���p�����Ă���̂ŊJ�n����NewGO���Ă��������ˁ`

/// <summary>
/// ���C�g��邭��
/// �E�V���O���g��
/// </summary>
class LightMaker : public IGameObject
{
	static LightMaker* m_instance;
public:
	LightMaker();
	~LightMaker();
	void Update()override;
	void Render()override;

	void LightMaker::D_LightMake(int lightNo, CVector4 dir, CVector4 col,float spec);
	void LightMaker::D_LightDelete(int lightNo);

	void LightMaker::P_LightMake(int lightNo, CVector3 pos, CVector3 col, float range);
	void LightMaker::P_LightDeleteAll();
	void LightMaker::P_LightDelete(int lightNo);

	/// <summary>
	/// �����ɐݒ肵�����C�g�̕�����ύX����
	/// </summary>
	void LightMaker::D_Light_SetDirection(int lightNo, CVector4 dir) {
		m_light.direction[lightNo] = dir;
	}
	CVector4 LightMaker::D_Light_GetDirection(int lightNo) {
		return m_light.direction[lightNo];
	}

	/// <summary>
	/// �����ɐݒ肵�����C�g�̐F��ύX����
	/// </summary>
	void LightMaker::D_Light_SetColer(int lightNo, CVector4 col) {
		m_light.color[lightNo] = col;
	}
	CVector4 LightMaker::D_Light_GetColer(int lightNo) {
		return m_light.color[lightNo];
	}

	/// <summary>
	/// �X�y�L�����̍i���ύX����
	/// </summary>
	void LightMaker::D_Light_SetSpec(int lightNo, float spec) {
		m_light.color[lightNo].w = spec;
	}
	float LightMaker::D_Light_GetSpec(int lightNo) {
		return m_light.color[lightNo].w;
	}

	/// <summary>
	/// �|�C���g���C�g�̍��W���擾�E�ύX
	/// </summary>
	void LightMaker::P_Light_SetPos(int lightNo, CVector3 pos) {
		m_pointLight.position[lightNo] = pos;
	}
	CVector3 LightMaker::P_Light_GetPos(int lightNo) {
		CVector3 ret;
		ret.Set(m_pointLight.position[lightNo]);
		return ret;
	}

	/// <summary>
	/// �|�C���g���C�g�̐F���擾�E�ύX
	/// </summary>
	void LightMaker::P_Light_SetColor(int lightNo, CVector3 color) {
		m_pointLight.color[lightNo] = color;
	}
	CVector3 LightMaker::P_Light_GetColor(int lightNo) {
		CVector3 ret;
		ret.Set(m_pointLight.color[lightNo]);
		return ret;
	}

	/// <summary>
	/// �|�C���g���C�g�͈̔͂��擾�E�ύX
	/// </summary>
	void LightMaker::P_Light_SetRange(int lightNo, float range) {
		m_pointLight.color[lightNo].w = range;
	}
	float LightMaker::P_Light_GetRange(int lightNo) {
		return m_pointLight.color[lightNo].w;
	}

	/// <summary>
	/// �f�B���N�V�������C�g�L���t���O��Ԃ�
	/// </summary>
	/// <returns>�t���O</returns>
	bool Get_D_LightFlag() {
		return m_lightFlag_D;
	}
	/// <summary>
	/// �f�B���N�V�������C�g�L���t���O���Z�b�g
	/// </summary>
	/// <param name="flag">�t���O</param>
	void Set_D_LightFlag(bool flag) {
		m_lightFlag_D = flag;
	}

	/// <summary>
	/// �|�C���g���C�g�L���t���O��Ԃ�
	/// </summary>
	/// <returns>�t���O</returns>
	bool Get_P_LightFlag() {
		return m_lightFlag_P;
	}
	/// <summary>
	/// �|�C���g���C�g�L���t���O���Z�b�g
	/// </summary>
	/// <param name="flag">�t���O</param>
	void Set_P_LightFlag(bool flag) {
		m_lightFlag_P = flag;
	}

	/// <summary>
	/// �������Z�b�g����
	/// </summary>
	/// <param name="color">����</param>
	void SetAmbientColor(CVector3 color) {
		m_ambientColor = color;
	}

	/// <summary>
	/// ������Ԃ�
	/// </summary>
	/// <returns>����</returns>
	CVector3 GetAmbientColor() {
		return m_ambientColor;
	}

	/// <summary>
	/// ���C�g�J�����̍��W���w��
	/// </summary>
	/// <param name="pos">���W</param>
	void SetLightCameraPosition(CVector3 pos) {
		m_lightCameraPosition = pos;
	}

	/// <summary>
	/// ���C�g�J�����̍��W��Ԃ�
	/// </summary>
	/// <returns>���W</returns>
	CVector3 GetLightCameraPosition() {
		return m_lightCameraPosition;
	}

	/// <summary>
	/// ���C�g�J�����̒����_���w��
	/// </summary>
	/// <param name="pos">�����_</param>
	void SetLightCameraTarget(CVector3 pos) {
		m_lightCameraTarget = pos;
	}

	/// <summary>
	/// ���C�g�J�����̒����_��Ԃ�
	/// </summary>
	/// <returns>�����_</returns>
	CVector3 GetLightCameraTarget() {
		return m_lightCameraTarget;
	}

	/// <summary>
	/// ���C�g�J�����̎擾
	/// �i�Q��Ver)
	/// </summary>
	/// <param name="m_pos">���W</param>
	/// <param name="m_tgt">�����_</param>
	void GetLightCamera(CVector3& m_pos, CVector3& m_tgt) {
		m_pos = m_lightCameraPosition;
		m_tgt = m_lightCameraTarget;
	}

	/// <summary>
	/// �C���X�^���X���擾�I
	/// </summary>
	/// <returns>�C���X�^���X�ł�</returns>
	static LightMaker* LightMaker::GetInstance() {
		return m_instance;
	}

private:
	//���C�g�����I
	SDirectionLight m_light;
	SPointLight m_pointLight;

	//�L���t���O
	bool m_lightFlag_D = false;	//�f�B���N�V�������C�g�L���t���O
	bool m_lightFlag_P = false;	//�|�C���g���C�g�L���t���O

	CVector3 m_ambientColor = { 0.1f,0.1f,0.2f };	//�����̐F

	CVector3 m_lightCameraPosition;				//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget;				//���C�g�J�����̒����_�B

	//�萔
	const CVector4 DirectionLight_Direction_Def = { 0.0f, -1.0f, 0.0f, 0.0f };	//�f�B���N�V�������C�g�̏������Ŏg��
	const CVector4 DirectionLight_Color_Def = { 0.5f,0.5f, 0.5f, 10.0f };		//�f�B���N�V�������C�g�̏������Ŏg��

};

