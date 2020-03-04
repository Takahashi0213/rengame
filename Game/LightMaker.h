#pragma once
#include "system/CGameObjectManager.h"

#include "DirectionLight.h"

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

	/// <summary>
	/// �����ɐݒ肵�����C�g�̕�����ύX����
	/// </summary>
	/// <param name="light">�ύX���郉�C�g�̏ꏊ</param>
	/// <param name="dir">���C�g�̕���</param>
	void LightMaker::D_Light_SetDirection(int lightNo, CVector4 dir) {
		m_light.direction[lightNo] = dir;
	}
	CVector4 LightMaker::D_Light_GetDirection(int lightNo) {
		return m_light.direction[lightNo];
	}

	/// <summary>
	/// �����ɐݒ肵�����C�g�̐F��ύX����
	/// </summary>
	/// <param name="light">�ύX���郉�C�g�̏ꏊ</param>
	/// <param name="col">���C�g�̐F</param>
	void LightMaker::D_Light_SetColer(int lightNo, CVector4 col) {
		m_light.color[lightNo] = col;
	}
	CVector4 LightMaker::D_Light_GetColer(int lightNo) {
		return m_light.color[lightNo];
	}

	/// <summary>
	/// �X�y�L�����̍i���ύX����
	/// </summary>
	/// <param name="lightNo">�ύX���郉�C�g�̏ꏊ</param>
	/// <param name="spec">�X�y�L����</param>
	void LightMaker::D_Light_SetSpec(int lightNo, float spec) {
		m_light.specPower[lightNo] = spec;
	}
	float LightMaker::D_Light_GetSpec(int lightNo) {
		return m_light.specPower[lightNo];
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
	SDirectionLight m_light;
	bool m_lightFlag_D = false;

	CVector3 m_ambientColor = { 0.4f,0.4f,0.4f };	//�����̐F

	CVector3 m_lightCameraPosition;				//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget;				//���C�g�J�����̒����_�B

};

